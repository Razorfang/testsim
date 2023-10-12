#include "Device.h"
Device::Device(std::string name, UnicastCommunicator *ucomm, MulticastCommunicator *mcomm) {
	deviceName = name;
	deviceModel = "TECHNO-TROUSERS";
	deviceSerial = 100;
	state = UNDISCOVERED;

	unicomm = ucomm;
	multicomm = mcomm;
}

#include <iostream>

int Device::powerOn() {
	bool stayOn = true;
	std::string msg = "ID;MODEL=" + deviceModel + ";SERIAL=" + std::to_string(deviceSerial);
	
	unicomm->sendMessage(msg);
	std::cout << unicomm->getMessage() << std::endl;

	multicomm->sendMessage(msg);
	std::cout << multicomm->getMessage() << std::endl;

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
