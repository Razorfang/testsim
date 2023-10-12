#include "Device.h"
Device::Device(std::string name, UnicastCommunicator *ucomm, MulticastCommunicator *mcomm) {
	deviceName = name;
	deviceModel = "TECHNO-TROUSERS";
	deviceSerial = "W4114C3";
	state = UNDISCOVERED;

	unicomm = ucomm;
	multicomm = mcomm;
}

#include <iostream>


int Device::powerOn() {
	bool stayOn = true;

	DiscoveryReplyMessage discoveryReply(deviceModel, deviceSerial);
	multicomm->sendMessage(discoveryReply);
	std::cout << "Received on loopback: " << multicomm->getMessage()->toString() << std::endl;

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
