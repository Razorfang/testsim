#include "Device.h"
Device::Device(std::string name, UnicastCommunicator *ucomm, MulticastCommunicator *mcomm) {
	deviceName = name;
	deviceModel = "TECHNO-TROUSERS";
	state = UNDISCOVERED;

	unicomm = ucomm;
	multicomm = mcomm;
}

int Device::powerOn(void) {
	std::string reply;
	DiscoveryRequestMessage drq;
	TestStopMessage tsp;
	TestStartMessage tst(0, 0);

	while (state != EXITING)
	{
		switch(state) {
			case UNDISCOVERED:
				reply = multicomm->getBlocking();
				std::cout << "Message received: " << reply << std::endl;
				if (drq.updateFromString(reply))
				{
					DiscoveryReplyMessage drm(deviceModel, deviceName);
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
					TestResultMessage trm("STARTED", "");
					std::cout << "Start received: " << reply << std::endl;
					unicomm->sendMessage(trm);
					std::cout << "Response sent: " << trm.toString() << std::endl;
					state = TESTING;
				}
				else if (tsp.updateFromString(reply)) {
					TestResultMessage trm("error", "ALREADY-STOPPED");
					std::cout << "Stop received: " << reply << std::endl;
					unicomm->sendMessage(trm);
					std::cout << "Response sent: " << trm.toString() << std::endl;
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

	return 0;
}

