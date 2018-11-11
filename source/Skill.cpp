#include <functional>
#include <iostream>
#include <string>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/config.hpp>
#include <cstdlib>
#include <memory>
#include <thread>
#include <Response.hpp>
#include <Request.hpp>

using tcp = boost::asio::ip::tcp;       
namespace http = boost::beast::http;

template<class Stream>
struct send_lambda
{
	Stream& stream_;
	bool& close_;
	boost::system::error_code& ec_;

	explicit
		send_lambda(
			Stream& stream,
			bool& close,
			boost::system::error_code& ec)
		: stream_(stream)
		, close_(close)
		, ec_(ec)
	{
	}

	template<bool isRequest, class Body, class Fields>
	void
		operator()(http::message<isRequest, Body, Fields>&& msg) const
	{
		close_ = msg.need_eof();
		http::serializer<isRequest, Body, Fields> sr{ msg };
		http::write(stream_, sr, ec_);
	}
};


struct Skill {
	Skill() {
		auto const address = boost::asio::ip::make_address("0.0.0.0");
		auto const port_arg = getOSEnv("PORT", "5000");
		auto const port = static_cast<unsigned short>(std::atoi(port_arg.c_str()));
		doc_root_{ std::make_shared<std::string>(".") };
		ioc_{ 1 };
        acceptor_{ ioc, {address, port} };
	}

	void fail(boost::system::error_code ec, char const* what)
	{
		std::cerr << what << ": " << ec.message() << "\n";
	}

	std::string getOSEnv(boost::string_view name, boost::string_view default_value)
	{
		const char* e = std::getenv(name.data());
		return e ? e : default_value.data();
	}

	template<
		class Body, class Allocator,
		class Send>
		void
		handle_request(
			boost::beast::string_view doc_root,
			http::request<Body, http::basic_fields<Allocator>>&& req,
			Send&& send)
	{
		std::string request{ req.body() };
		std::string response;
		callback_(request, response);
		res.body() = response;
		http::response<http::string_body> res{ http::status::ok, req.version() };
		res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
		res.set(http::field::content_type, "application/json"); //appl json
		res.keep_alive(req.keep_alive());
		res.prepare_payload();
		return send(std::move(res));
	}

	void setCallback(std::function<void(const std::string& request,
		std::string& response)> callback) {
		callback_ = callback;
	}

	std::function<void(const std::string& request, std::string& response)>
		callback_;

	void run() {
		for (;;)
		{
			// This will receive the new connection
			tcp::socket socket_{ ioc };

			// Block until we get a connection
			acceptor_.accept(socket_);

			// Launch the session, transferring ownership of the socket
			std::thread{ std::bind(
				&do_session,
				std::move(socket_),
				doc_root_) }.detach();
		}
	}

private:
	void
		do_session(
			tcp::socket& socket,
			std::shared_ptr<std::string const> const& doc_root)
	{
		bool close = false;
		boost::system::error_code ec;
		boost::beast::flat_buffer buffer;
		send_lambda<tcp::socket> lambda{ socket, close, ec };

		for (;;)
		{
			http::request<http::string_body> req;
			http::read(socket, buffer, req, ec);
			if (ec == http::error::end_of_stream)
				break;
			if (ec)
				return fail(ec, "read");
			handle_request(*doc_root, std::move(req), lambda);
			if (ec)
				return fail(ec, "write");
			if (close)
			{
				break;
			}
		}
		socket.shutdown(tcp::socket::shutdown_send, ec);
	}
	boost::asio::io_context ioc_;
	tcp::acceptor acceptor_;
	boost::asio::signal_set signals_;
	std::shared_ptr<std::string const> const doc_root_;
};
