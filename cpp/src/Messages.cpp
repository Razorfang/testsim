#include "Messages.h"

Message *stringToMessage(std::string) {
	return new TestStateMessage();
}

std::string DiscoveryRequestMessage::toString(void) {
	return "ID;";
}

DiscoveryReplyMessage::DiscoveryReplyMessage(std::string msgModel, std::string msgSerial) {
	model = msgModel;
	serial = msgSerial;
}

std::string DiscoveryReplyMessage::toString(void) {
	return "ID;MODEL=" + model + ";SERIAL=" + serial + ";";
}

TestStartMessage::TestStartMessage(int dur, int rate) {
	durationSeconds = dur;
	rateMilliseconds = rate;
}

std::string TestStartMessage::toString(void) {
	return "TEST;CMD=START;DURATION=" + std::to_string(durationSeconds) + ";RATE=" + std::to_string(rateMilliseconds) + ";";
}

std::string TestStopMessage::toString(void) {
	return "TEST;CMD=STOP;";
}

TestResultMessage::TestResultMessage(std::string status, std::string reason) {
	resultStatus = status;
	resultReason = reason;
}

std::string TestResultMessage::toString(void) {
	std::string msg = "TEST;RESULT=" + resultStatus + ";";
	if ("error" == resultStatus) {
		msg += "MSG=" + resultReason;
	}
	return msg;
}

TestStatusMessage::TestStatusMessage(int t, int mv, int ma) {
	timeSinceStart = t;
	milliVolts = mv;
	milliAmps = ma;
}

std::string TestStatusMessage::toString(void) {
	return "STATUS;TIME=" + std::to_string(timeSinceStart) + ";milliVolts=" + std::to_string(milliVolts) + ";MA=" + std::to_string(milliAmps) + ";";
}

std::string TestStateMessage::toString(void) {
	return "STATUS;STATE=IDLE";
}

