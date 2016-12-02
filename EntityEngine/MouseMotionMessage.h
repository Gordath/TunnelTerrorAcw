#ifndef MOUSE_MOTION_MESSAGE_H_
#define MOUSE_MOTION_MESSAGE_H_
#include "Message.h"
#include <GL/GLM/vec2.hpp>

class MouseMotionMessage : public Message {
private:
	glm::ivec2 _cursorPosition;

public:
	MouseMotionMessage(const glm::ivec2& cursorPosition)
		: Message("mousemotion"),
		  _cursorPosition(cursorPosition)
	{
	}

	virtual ~MouseMotionMessage() = default;

	const glm::ivec2& GetCursorPosition() const noexcept { return _cursorPosition; }
};

#endif //MOUSE_MOTION_MESSAGE_H_
