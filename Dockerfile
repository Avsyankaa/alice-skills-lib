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

RUN mkdir bin \
 && cd bin \
 && cmake .. \
 && make \
 && ls -al \
 && mkdir /app \
 && cp websocket-chat-server /app

CMD "/app/websocket-chat-server"

EXPOSE 8080
