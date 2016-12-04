#pragma once
#include "GameObject.h"


class DigitDisplay : public GameObject {
private:
	int _number;

public:
	DigitDisplay();
	~DigitDisplay();

	int GetCurrentDigit() const { return _number; }

	bool SetCurrentDigit(int i)
	{
		if (i >= 0 && i < 10) {
			_number = i;
			return true;
		}
		return false;
	}

	void Update(double deltaTime) override;
};
