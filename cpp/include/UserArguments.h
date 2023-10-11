#ifndef __USER_ARGUMENTS_H_
#define __USER_ARGUMENTS_H_

#include <string>

class UserArguments {
	public:
		std::string deviceName;
		int devicePort;

		UserArguments(const char **argv);
};

#endif // __USER_ARGUMENTS_H_
