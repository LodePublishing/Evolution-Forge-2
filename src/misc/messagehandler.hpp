#ifndef _MISC_MESSAGEHANDLER_HPP
#define _MISC_MESSAGEHANDLER_HPP

#include <string>
#include <list>

class MessageHandler
{
public:
	MessageHandler();
	~MessageHandler();

	void addMessage(const std::string& msg);
	const std::list<const std::string>& getRemainingMessages() const;
	void clearMessages();

private:
	std::list<const std::string> remainingMessages;
};

inline void MessageHandler::addMessage(const std::string& msg) {
	remainingMessages.push_back(msg);
}

inline const std::list<const std::string>& MessageHandler::getRemainingMessages() const {
	return remainingMessages;
}

inline void MessageHandler::clearMessages() {
	remainingMessages.clear();
}

#endif // _MISC_MESSAGEHANDLER_HPP