#include "DeviceReader.h"

DeviceReader::DeviceReader(std::string name):name(std::move(name)), host{"localhost"}, port{6379}, keyList{"mylist"}, interval{10} {
}

DeviceReader::DeviceReader(std::string name, std::string host, std::size_t port):name(std::move(name)), host(std::move(host)), port{port}, keyList{"mylist"}, interval{10} {
}

DeviceReader::DeviceReader(std::string name, std::string host, std::size_t port, std::string keyList, int interval):name(std::move(name)), host{"localhost"}, port{6379}, keyList{"mylist"}, interval{10} {
}


void DeviceReader::operator()(int seconds=-1) {

	if(seconds > 0){
		this->interval = seconds;
	}

	cpp_redis::client client;

	std::cout << this->name << " connecting " << this->host << ":" << this->port << std::endl;
	client.connect(host, port,
			[&](const std::string &host, std::size_t port, cpp_redis::connect_state status) {
		if (status == cpp_redis::connect_state::dropped) {
			std::cout << this->name << " disconnected from " << host << ":" << port << std::endl;
		}
	});

	std::vector<std::string> keys;
	keys.push_back(this->keyList);

	clock_t begin = clock();

	double last_elapsed_secs = 0;
	int last_intervalIndex = 0;

	int intervalIndex = 0;

	int count = 0;
	while(true){

		client.lpop(this->keyList, [&](cpp_redis::reply& reply) {
			if (reply.is_string()){
				DeviceReader::count_event(begin, intervalIndex, last_intervalIndex, last_elapsed_secs, count);
			}
		});
		client.sync_commit();

		client.blpop(keys, 10000, [&](cpp_redis::reply& reply) {
			if (reply.is_string()){
				DeviceReader::count_event(begin, intervalIndex, last_intervalIndex, last_elapsed_secs, count);
			}
		});

		client.sync_commit();
	}


}

inline void DeviceReader::count_event(const clock_t &begin, int &intervalIndex, int &last_intervalIndex, double &last_elapsed_secs, int &count){

	clock_t now = clock();
	double elapsed_secs = double(now - begin) / CLOCKS_PER_SEC;
	intervalIndex = elapsed_secs/this->interval;
	if(last_intervalIndex != intervalIndex){
		// simple consumer
		std::cout << this->name << ": occurrence: " <<  count << " between: ";
		std::cout << elapsed_secs - last_elapsed_secs << " seconds" << std::endl;
		count = 0;
		last_elapsed_secs = elapsed_secs;
	}else{
		count = count + 1;
	}
	last_intervalIndex = intervalIndex;
}
