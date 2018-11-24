FROM ubuntu:bionic 

# Install tools required for the project
RUN apt-get update \
    && apt-get install gcc -y \
    && apt-get install g++ -y \
    && apt-get install cmake -y \
    && apt-get install wget -y 

# Copy the entire project and build it
COPY . /cpp/src/project/ 
WORKDIR /cpp/src/project/

RUN ./tools/polly/bin/polly --reconfig --toolchain sanitize-address --config Release --fwd CMAKE_EXE_LINKER="-fuse-ld=gold" \
 && ./tools/polly/bin/polly --reconfig --config Release --fwd CMAKE_EXE_LINKER="-fuse-ld=gold" CMAKE_EXPORT_COMPILE_COMMANDS=ON \
 && mkdir /app \
 && cp websocket-chat-server /app

CMD "/app/websocket-chat-server"

EXPOSE 8080
