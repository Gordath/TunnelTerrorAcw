#pragma once
#include <string>

class Message {
protected:
	std::string _type;

public:
	Message(std::string type);
	virtual ~Message();

	std::string GetMessageType() const noexcept { return _type; }
};
