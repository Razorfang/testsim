#ifndef __DEVICE_H_
#define __DEVICE_H_

#include <string>
#include <iostream>
#include <chrono>
#include <thread>

#include "UserArguments.h"
#include "Comms.h"
#include "Messages.h"

enum deviceState {
	UNDISCOVERED,
	IDLE,
	TESTING,
	EXITING,
};

class Device {
	private:
		std::string deviceName;
		std::string deviceModel;
		std::string deviceSerial;
		enum deviceState state;
		UnicastCommunicator *unicomm;
		MulticastCommunicator *multicomm;

		void iterate(void);
	public:
		Device(std::string name, UnicastCommunicator *ucomm, MulticastCommunicator *mcomm);
		int powerOn(void);
};

#endif //__DEVICE_H_
