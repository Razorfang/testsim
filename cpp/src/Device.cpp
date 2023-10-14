#include "Device.h"
Device::Device(std::string name, UnicastCommunicator *ucomm, MulticastCommunicator *mcomm) {
	deviceName = name;
	deviceModel = "TECHNO-TROUSERS";
	state = UNDISCOVERED;

	unicomm = ucomm;
	multicomm = mcomm;
}

void Device::iterate(void) {
	std::string reply;
	DiscoveryRequestMessage drq;
	DiscoveryReplyMessage drm(deviceModel, deviceName);
	TestStartMessage tst(0, 0);
	TestStopMessage tsp;

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
			std::cout << "Waiting to start or stop a test..." << std::endl;
			reply = unicomm->getBlocking();
			std::cout << "Message received: " << reply << std::endl;
			if (tst.updateFromString(reply)) {
				std::cout << "Start received: " << tst.toString() << std::endl;
			}
			else if (tsp.updateFromString(reply)) {
				std::cout << "Stop received: " << tsp.toString() << std::endl;
			}
			else {
				std::cout << "Unknown message!" << std::endl;
			}
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
