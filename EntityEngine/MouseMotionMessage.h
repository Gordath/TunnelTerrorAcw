#ifndef MOUSE_MOTION_MESSAGE_H_
#define MOUSE_MOTION_MESSAGE_H_
#include "Message.h"
#include <GL/GLM/vec2.hpp>

class MouseMotionMessage : public Message {
private:
	glm::vec2 _cursorPosition;

public:
	MouseMotionMessage(const glm::vec2& cursorPosition)
		: Message("mousemotion"),
		  _cursorPosition(cursorPosition)
	{
	}

	virtual ~MouseMotionMessage() = default;

	const glm::vec2& GetCursorPosition() const noexcept { return _cursorPosition; }
};

#endif //MOUSE_MOTION_MESSAGE_H_
