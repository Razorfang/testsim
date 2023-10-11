#include "Device.h"

Device::Device(UserArguments *args) {
	deviceName = args->deviceName;
	devicePort = args->devicePort;

	// Model is constant for now
	deviceModel = "DEV100";

	// Serial number is constant for now
	deviceSerial = 100;

	state = UNDISCOVERED;
}

#include <iostream>

int Device::powerOn() {
	UnicastCommunicator unicomm("127.0.0.1", devicePort);
	MulticastCommunicator multicomm("224.3.11.15", 31115);

	bool stayOn = true;
	std::string msg = "ID;MODEL=" + deviceModel + ";SERIAL=" + std::to_string(deviceSerial);
	
	unicomm.sendMessage(msg);
	std::cout << unicomm.getMessage() << std::endl;

	//multicomm.sendMessage(msg);
	std::cout << multicomm.getMessage() << std::endl;

	return 0;

	while (stayOn) {
		switch (state) {
			case UNDISCOVERED:
				break;
			case IDLE:
				break;
			case TESTING:
				break;
			default:
				stayOn = false;
		}
	}

	return 0;
}
