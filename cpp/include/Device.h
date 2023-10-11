#ifndef __DEVICE_H_
#define __DEVICE_H_

#include <string>
#include "UserArguments.h"
#include "Comms.h"

enum deviceState {
	UNDISCOVERED,
	IDLE,
	TESTING,
};

class Device {
	public:
		std::string deviceName;
		std::string deviceModel;
		int devicePort;
		int deviceSerial;
		enum deviceState state;

		Device(UserArguments *args);
		int powerOn(void);
};

#endif //__DEVICE_H_
