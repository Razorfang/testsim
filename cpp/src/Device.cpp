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

	DiscoveryRequestMessage discoveryRequest;

	std::string reply = multicomm->getBlocking();
	if (discoveryRequest.updateFromString(reply)) {
		std::cout << "Discovery received: " << reply << std::endl;
	}


	multicomm->sendMessage(discoveryReply);
	reply = multicomm->getBlocking();
	if (discoveryReply.updateFromString(reply)) {
		std::cout << "Loopback reply received: " << reply << std::endl;
	}
	else {
		std::cout << "Invalid loopback reply: " << reply << std::endl;
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
