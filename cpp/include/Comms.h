#ifndef __COMMS_H_
#define __COMMS_H_

#include <string>
#include <arpa/inet.h>
#include <cstring>
#include <sys/socket.h>
#include <unistd.h>

struct CommData {
	int sockfd;
	struct sockaddr_in receiveAddr;
	struct sockaddr_in sendAddr;
};

class Communicator {

	protected:
		struct CommData data;
	public:
		virtual std::string getMessage(void) = 0;
		virtual void sendMessage(std::string msg) = 0;
};

class UnicastCommunicator : public Communicator {
	public:
		UnicastCommunicator(std::string serverAddr, int port);
		~UnicastCommunicator();

		std::string getMessage(void) override;
		void sendMessage(std::string msg) override;
};

class MulticastCommunicator : public Communicator {
	public:
		MulticastCommunicator(std::string multicastGroup, int port);
		~MulticastCommunicator();

		std::string getMessage(void) override;
		void sendMessage(std::string msg) override;
};

#endif //__COMMS_H_
