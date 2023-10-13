#ifndef __MESSAGES_H_
#define __MESSAGES_H_

#include <string>
#include <vector>
#include <sstream>

class Message {
	public:
		virtual std::string toString(void) = 0;
		// Returns true if we can generate this type of message from a string and false otherwise.
		virtual bool updateFromString(std::string s) = 0;
};

class DiscoveryRequestMessage : public Message {
	public:
		std::string toString(void) override;
		bool updateFromString(std::string s) override;
};

class DiscoveryReplyMessage : public Message {
	public:
		std::string model;
		std::string serial;
		DiscoveryReplyMessage(std::string msgModel, std::string msgSerial);
		std::string toString(void) override;
		bool updateFromString(std::string s) override;
};

class TestStartMessage : public Message {
	public:
		int durationSeconds;
		int rateMilliseconds;
		TestStartMessage(int dur, int rate);
		std::string toString(void) override;
		bool updateFromString(std::string s) override;
};

class TestStopMessage : public Message {
	public:
		std::string toString(void) override;
		bool updateFromString(std::string s) override;
};

class TestResultMessage : public Message {
	public:
		std::string resultStatus;
		std::string resultReason;
		TestResultMessage(std::string status, std::string reason);
		std::string toString(void) override;
		bool updateFromString(std::string s) override;
};

class TestStatusMessage : public Message {
	public:
		int timeSinceStart;
		int milliVolts;
		int milliAmps;
		TestStatusMessage(int t, int mv, int ma);
		std::string toString(void) override;
		bool updateFromString(std::string s) override;
};

class TestStateMessage: public Message {
	public:
		std::string toString(void) override;
		bool updateFromString(std::string s) override;
};


#endif //__MESSAGES_H_
