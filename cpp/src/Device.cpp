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
	std::string loopbackReply = multicomm->getBlocking();
	if (discoveryReply.updateFromString(loopbackReply)) {
		std::cout << "Reply received: " << loopbackReply << std::endl;
	}
	else {
		std::cout << "Invalid reply: " << loopbackReply << std::endl;
	}

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
