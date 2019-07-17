// #include "deviceReader.hpp"
#include <string>
#include <iostream>
#include <thread>

#include "DeviceReader.h"


int main(int argc, char **argv) {

	// create producer
	DeviceReader deviceReader1("device1", argv[1], 6379);
	DeviceReader deviceReader2("device2", argv[2], 6379);
	DeviceReader deviceReader3("device3", argv[3], 6379);

	// create threads
	std::thread device1(deviceReader1, 10);
	std::thread device2(deviceReader2, 10);
	std::thread device3(deviceReader3, 10);

	// synchronize threads:
	device1.join();
	device2.join();
	device3.join();


	return 0;
}
