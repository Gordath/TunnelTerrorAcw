#ifndef MOUSE_CLICK_MESSAGE_H_
#define MOUSE_CLICK_MESSAGE_H_
#include "Message.h"
#include <GL/GLM/detail/type_vec2.hpp>

enum class MouseButtonType {
	L_BUTTON,
	R_BUTTON,
	M_BUTTON
};

class MouseClickMessage : public Message {
private:
	MouseButtonType _button;
	glm::vec2 _cursorPosition;
	bool _pressed;

public:
	MouseClickMessage(MouseButtonType button, const glm::vec2& cursorPosition, bool pressed)
		: Message("mouseclick"), _button(button), _cursorPosition(cursorPosition), _pressed(pressed)
	{
	}

	virtual ~MouseClickMessage() = default;

	MouseButtonType GetMouseButton() const noexcept { return _button; }

	const glm::vec2& GetCursorPosition() const noexcept { return _cursorPosition; }

	bool GetState() const noexcept { return _pressed; }
};

#endif //MOUSE_CLICK_MESSAGE_H_
