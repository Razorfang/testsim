#include "Messages.h"

std::vector<std::string> split(std::string s, std::string delim) {
	std::istringstream stream(s);
	std::string token;
	std::vector<std::string> tokens;
	while (std::getline(stream, token, delim[0])) {
		tokens.push_back(token);
	}
	return tokens;
}

#include <iostream>
void printTokens(std::vector<std::string> &tokens) {
	for (const std::string &token : tokens) {
		std::cout << "Token: " << token << std::endl;
	}
}

std::string DiscoveryRequestMessage::toString(void) {
	return "ID;";
}

bool DiscoveryRequestMessage::updateFromString(std::string s) {
	(void)s;
	return true;
}

DiscoveryReplyMessage::DiscoveryReplyMessage(std::string msgModel, std::string msgSerial) {
	model = msgModel;
	serial = msgSerial;
}

std::string DiscoveryReplyMessage::toString(void) {
	return "ID;MODEL=" + model + ";SERIAL=" + serial + ";";
}


bool DiscoveryReplyMessage::updateFromString(std::string s) {
	// Matches the pattern 'ID;MODEL=<anything-but-;>;SERIAL=<anything-but-;>;
	std::vector<std::string> tokens = split(s, ";");
	printTokens(tokens);
	if (4 != tokens.size()) {
		return false;
	}

	if ("ID" != tokens[0]) {
		return false;
	}

	std::vector<std::string> subTokens = split(tokens[1], "=");
	printTokens(subTokens);
	if (2 == subTokens.size()) {
		model = subTokens[1];		
	}
	else {
		return false;
	}

	subTokens = split(tokens[2], "=");
	printTokens(subTokens);
	if (2 == subTokens.size()) {
		serial = subTokens[1];
	}
	else {
		return false;
	}

	return true;
}

TestStartMessage::TestStartMessage(int dur, int rate) {
	durationSeconds = dur;
	rateMilliseconds = rate;
}

std::string TestStartMessage::toString(void) {
	return "TEST;CMD=START;DURATION=" + std::to_string(durationSeconds) + ";RATE=" + std::to_string(rateMilliseconds) + ";";
}

bool TestStartMessage::updateFromString(std::string s) {
	// Matches the pattern 'TEST;CMD=START;DURATION=<seconds>;RATE=<ms>;'
	std::vector<std::string> tokens = split(s, ";");
	if (5 != tokens.size()) {
		return false;
	}

	if ("TEST" != tokens[0]) {
		return false;
	}

	if ("CMD=START" != tokens[1]) {
		return false;
	}

	std::vector<std::string> subTokens = split(tokens[2], "=");
	if (2 == tokens.size()) {
		durationSeconds = stoi(subTokens[1]);
	}
	else {
		return false;
	}


	subTokens = split(tokens[3], "=");
	if (2 == tokens.size()) {
		rateMilliseconds = stoi(subTokens[1]);
	}
	else {
		return false;
	}

	return true;
}

std::string TestStopMessage::toString(void) {
	return "TEST;CMD=STOP;";
}

bool TestStopMessage::updateFromString(std::string s) {
	(void)s;
	return true;
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

#include <cassert>
bool TestResultMessage::updateFromString(std::string s) {
	(void)s;
	assert(1 == 0);
	return false;
}

TestStatusMessage::TestStatusMessage(int t, int mv, int ma) {
	timeSinceStart = t;
	milliVolts = mv;
	milliAmps = ma;
}

std::string TestStatusMessage::toString(void) {
	return "STATUS;TIME=" + std::to_string(timeSinceStart) + ";milliVolts=" + std::to_string(milliVolts) + ";MA=" + std::to_string(milliAmps) + ";";
}

bool TestStatusMessage::updateFromString(std::string s) {
	(void)s;
	assert(2 == 0);
	return false;
}

std::string TestStateMessage::toString(void) {
	return "STATUS;STATE=IDLE";
}

bool TestStateMessage::updateFromString(std::string s) {
	(void)s;
	return true;
}
