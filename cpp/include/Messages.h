#ifndef __MESSAGES_H_
#define __MESSAGES_H_

#include <string>

class Message {
	public:
		virtual std::string toString(void) = 0;
};

Message *stringToMessage(std::string);

class DiscoveryRequestMessage : public Message {
	public:
		std::string toString(void) override;
};

class DiscoveryReplyMessage : public Message {
	public:
		std::string model;
		std::string serial;
		DiscoveryReplyMessage(std::string msgModel, std::string msgSerial);
		std::string toString(void) override;
};

class TestStartMessage : public Message {
	public:
		int durationSeconds;
		int rateMilliseconds;
		TestStartMessage(int dur, int rate);
		std::string toString(void) override;

};

class TestStopMessage : public Message {
	public:
		std::string toString(void) override;
};

class TestResultMessage : public Message {
	public:
		std::string resultStatus;
		std::string resultReason;
		TestResultMessage(std::string status, std::string reason);
		std::string toString(void) override;
};

class TestStatusMessage : public Message {
	public:
		int timeSinceStart;
		int milliVolts;
		int milliAmps;
		TestStatusMessage(int t, int mv, int ma);
		std::string toString(void) override;

};

class TestStateMessage: public Message {
	public:
		std::string toString(void) override;
};

#endif //__MESSAGES_H_
