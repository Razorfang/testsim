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
	bind(data.sockfd, (const struct sockaddr *)&data.receiveAddr, sizeof(data.receiveAddr));

	data.sendAddr = genSockData(serverAddr, port);
}

UnicastCommunicator::~UnicastCommunicator() {
	close(data.sockfd);
}

void UnicastCommunicator::sendMessage(std::string msg) {
	sendto(data.sockfd, msg.c_str(), msg.length(), 0, (struct sockaddr *)&data.sendAddr, sizeof(data.sendAddr));
}

std::string UnicastCommunicator::getMessage(void) {
	char buffer[4096];
	socklen_t arg = sizeof(data.receiveAddr);
	recvfrom(data.sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&data.receiveAddr, &arg);
	return buffer;
}

MulticastCommunicator::MulticastCommunicator(std::string multicastGroup, int port) {
	data.sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	data.receiveAddr = genSockData(multicastGroup, port);

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

void MulticastCommunicator::sendMessage(std::string msg) {
	sendto(data.sockfd, msg.c_str(), msg.length(), 0, (struct sockaddr *)&data.sendAddr, sizeof(data.sendAddr));
}

std::string MulticastCommunicator::getMessage(void) {
	char buffer[4096];
	socklen_t arg = sizeof(data.receiveAddr);
	recvfrom(data.sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&data.receiveAddr, &arg);
	return buffer;
}


