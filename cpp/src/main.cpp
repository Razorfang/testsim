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
	UnicastCommunicator unicomm("192.168.1.64", userArgs.devicePort);
	MulticastCommunicator multicomm("224.3.11.15", 31115);
	Device testDevice(userArgs.deviceName, &unicomm, &multicomm);
	return testDevice.powerOn();
}
