#include "UserArguments.h"

UserArguments::UserArguments(const char **argv) {
	deviceName = argv[1];
	devicePort = std::stoi(argv[2]);
}
