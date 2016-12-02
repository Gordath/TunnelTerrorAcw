#pragma once
#include "GameObject.h"

class LetterDisplay : public GameObject {
private:
	char _letter;

public:
	LetterDisplay();
	~LetterDisplay();

	int GetCurrentLetter() const { return _letter; }

	bool SetCurrentLetter(char c) 
	{
		if (c >= 'A' && c <= 'Z') {
			_letter = c;
			return true;
		}
		return false;
	}


	void Update(double deltaTime) override;
};
