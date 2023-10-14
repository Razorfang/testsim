#ifndef __COMMS_H_
#define __COMMS_H_

#include <string>
#include <arpa/inet.h>
#include <cstring>
#include <sys/socket.h>
#include <unistd.h>
#include <poll.h>

#include "Messages.h"

struct CommData {
	int sockfd;
	struct sockaddr_in receiveAddr;
	struct pollfd pfd[1];
};

class Communicator {

	protected:
		struct CommData data;
	public:
		virtual std::string getBlocking(void) = 0;
		virtual std::string pollReceive(void) = 0;
		virtual void sendMessage(Message &msg) = 0;
};

class UnicastCommunicator : public Communicator {
	public:
		UnicastCommunicator(std::string serverAddr, int port);
		~UnicastCommunicator();

		std::string getBlocking(void) override;
		std::string pollReceive(void) override;
		void sendMessage(Message &msg) override;
};

class MulticastCommunicator : public Communicator {
	public:
		MulticastCommunicator(std::string multicastGroup, int port);
		~MulticastCommunicator();

		std::string getBlocking(void) override;
		std::string pollReceive(void) override;
		void sendMessage(Message &msg) override;
};

#endif //__COMMS_H_
