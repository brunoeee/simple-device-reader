#ifndef DEVICEREADER_H_
#define DEVICEREADER_H_

#include <ctime>
#include <string>
#include <iostream>
#include <vector>
#include <cpp_redis/cpp_redis>

class DeviceReader {

private:
	int interval;
	std::string name;
	std::string host;
	std::size_t port;
	std::string keyList;
	inline void count_event(const clock_t &begin, int &intervalIndex, int &last_intervalIndex, double &last_elapsed_secs, int &count);

public:
	DeviceReader(std::string name);
	DeviceReader(std::string name, std::string host, std::size_t port);
	DeviceReader(std::string name, std::string host, std::size_t port, std::string keyList, int interval);
	void operator()(int seconds);
};

#endif /* DEVICEREADER_H_ */
