#include <iostream>

#include "Device.h"
#include "UserArguments.h"
#include "Comms.h"

int main(int argc, const char **argv) {

	// Validate inputs
	if (argc != 3) {
		std::cerr << "You specified " << argc << " arguments. You must specify exactly two arguments: a device name and a device port!" << std::endl;
		return 1;
	}

	UserArguments userArgs(argv);
	Device testDevice(&userArgs);

	std::cout << "Device name is " << testDevice.deviceName << " and port is " << testDevice.devicePort << std::endl;
	std::cout << "Device model is " << testDevice.deviceModel << " and serial number is " << testDevice.deviceSerial << std::endl;

	return testDevice.powerOn();
}
