#include "Device.h"
Device::Device(std::string name, UnicastCommunicator *ucomm, MulticastCommunicator *mcomm) {
	deviceName = name;
	deviceModel = "TECHNO-TROUSERS";
	deviceSerial = "W4114C3";
	state = UNDISCOVERED;

	unicomm = ucomm;
	multicomm = mcomm;
}

void Device::iterate(void) {
	std::string reply;
	DiscoveryRequestMessage drq;
	DiscoveryReplyMessage drm(deviceModel, deviceSerial);

	switch(state) {
		case UNDISCOVERED:
			reply = multicomm->getBlocking();
			std::cout << "Message received: " << reply << std::endl;
			if (drq.updateFromString(reply))
			{
				std::cout << "Update received: " << drq.toString() << std::endl;
				multicomm->sendMessage(drm);
				std::cout << "Reply sent: " << drm.toString() << std::endl;
				state = IDLE;
			}
			break;
		case IDLE:
			break;
		case TESTING:
			break;
		case EXITING:
		default:
			break;
	}
}

int Device::powerOn() {
	while (state != EXITING) {
		iterate();
	}
	return 0;
}
