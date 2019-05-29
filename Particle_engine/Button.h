#ifndef BUTTON_H
#define BUTTON_H

#include "Control.h"

class Button: public Control
{
public: 
	Button(string label, int x, int y, int width, int height);
	virtual bool updateControl( MouseState &state);
	virtual void drawControl();
	virtual string getType();

private:
	string  label;
	bool down;

};

#endif