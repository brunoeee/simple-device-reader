PROJECT_ROOT = /app/devices_project/

OBJS =  DeviceReader.o main.o

CFLAGS += -O2
CXXFLAGS += -std=c++17

all:	devices_reader

devices_reader:	$(OBJS)
	g++ -o $@ $^ -lcpp_redis -ltacopie -pthread

%.o:	$(PROJECT_ROOT)%.cpp
	g++ -c $(CFLAGS) $(CXXFLAGS) $(CPPFLAGS) -o $@ $<

clean:
	rm -fr devices_reader $(OBJS)