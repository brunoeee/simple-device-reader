FROM alpine:3.10.1

RUN apk update && apk add musl-dev git make cmake g++

# intall cpp_redis
RUN cd /opt && git clone https://github.com/cpp-redis/cpp_redis.git
WORKDIR /opt/cpp_redis
RUN git submodule init && git submodule update
RUN mkdir build && cd build
RUN cmake . -DCMAKE_BUILD_TYPE=Release
RUN make
RUN make install

# wait for connections
COPY . /app
WORKDIR /app
RUN ["chmod", "+x", "wait-for"]

# compile app
RUN make -f ./devices_project/Makefile
RUN chmod +x devices_reader
