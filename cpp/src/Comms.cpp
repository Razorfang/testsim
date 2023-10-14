#include "Comms.h"

static struct sockaddr_in genSockData(std::string dst, int port) {
	struct sockaddr_in data;
	memset(&data, 0, sizeof(data));
	data.sin_family = AF_INET;
	data.sin_port = htons(port);
	data.sin_addr.s_addr = inet_addr(dst.c_str());
	return data;
}

UnicastCommunicator::UnicastCommunicator(std::string serverAddr, int port) {
	data.sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	data.receiveAddr = genSockData(serverAddr, port);

	memset(data.pfd, 0, sizeof(data.pfd));
	data.pfd[0].fd = data.sockfd;
	data.pfd[0].events = POLLIN;

	bind(data.sockfd, (const struct sockaddr *)&data.receiveAddr, sizeof(data.receiveAddr));

	data.sendAddr = genSockData(serverAddr, port);
}

UnicastCommunicator::~UnicastCommunicator() {
	close(data.sockfd);
}

void UnicastCommunicator::sendMessage(Message &msg) {
	std::string message = msg.toString();
	sendto(data.sockfd, message.c_str(), message.length(), 0, (struct sockaddr *)&data.sendAddr, sizeof(data.sendAddr));
}

std::string UnicastCommunicator::getBlocking(void) {
	char buffer[4096];
	memset(buffer, '\0', sizeof(buffer));
	socklen_t arg = sizeof(data.receiveAddr);
	recvfrom(data.sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&data.receiveAddr, &arg);
	return std::string(buffer);
}

std::string UnicastCommunicator::pollReceive(void) {
	if (poll(data.pfd, 1, 0) < 0) {
		return std::string();
	}

	if (data.pfd[0].revents & POLLIN) {
		return getBlocking();
	}

	return std::string();
}

MulticastCommunicator::MulticastCommunicator(std::string multicastGroup, int port) {
	data.sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	data.receiveAddr = genSockData(multicastGroup, port);

	memset(data.pfd, 0, sizeof(data.pfd));
	data.pfd[0].fd = data.sockfd;
	data.pfd[0].events = POLLIN;

	int enable = 1;
	setsockopt(data.sockfd, IPPROTO_IP, IP_MULTICAST_LOOP, &enable, sizeof(enable));
	setsockopt(data.sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable));

	bind(data.sockfd, (const struct sockaddr *)&data.receiveAddr, sizeof(data.receiveAddr));

	struct ip_mreq mreq;
	mreq.imr_multiaddr.s_addr = inet_addr(multicastGroup.c_str());
	mreq.imr_interface.s_addr = htonl(INADDR_ANY);
	setsockopt(data.sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *)&mreq, sizeof(mreq));

	data.sendAddr = genSockData(multicastGroup, port);
}

MulticastCommunicator::~MulticastCommunicator() {
	close(data.sockfd);
}


void MulticastCommunicator::sendMessage(Message &msg) {
	std::string message = msg.toString();
	sendto(data.sockfd, message.c_str(), message.length(), 0, (struct sockaddr *)&data.sendAddr, sizeof(data.sendAddr));
}

std::string MulticastCommunicator::getBlocking(void) {
	char buffer[4096];
	memset(buffer, '\0', sizeof(buffer));
	socklen_t arg = sizeof(data.receiveAddr);
	recvfrom(data.sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&data.receiveAddr, &arg);
	return std::string(buffer);
}

std::string MulticastCommunicator::pollReceive(void) {
	if (poll(data.pfd, 1, 0) < 0) {
		return std::string();
	}

	if (data.pfd[0].revents & POLLIN) {
		return getBlocking();
	}

	return std::string();
}
