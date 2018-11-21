FROM ubuntu:bionic

# Install tools required for the project
RUN apt-get update \
    && apt-get install gcc -y \
    && apt-get install g++ -y \
    && apt-get install cmake -y \
    && apt-get install wget -y 

# Install Boost
RUN cd /home \
    && wget http://downloads.sourceforge.net/project/boost/boost/1.68.0/boost_1_68_0.tar.gz \
    && tar xfz boost_1_68_0.tar.gz \
    && rm boost_1_68_0.tar.gz \
    && cd boost_1_68_0 \
    && ./bootstrap.sh --with-libraries=system > /dev/null 2>&1 \
    && ./b2 install > /dev/null 2>&1

# Copy the entire project and build it
COPY . /cpp/src/project/ 
WORKDIR /cpp/src/project/

RUN mkdir bin \
 && cd bin \
 && cmake .. \
 && make \
 && ls -al \
 && mkdir /app \
 && cp websocket-chat-server /app

CMD "/app/websocket-chat-server"

EXPOSE 8080