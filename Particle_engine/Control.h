#ifndef CONTROL_H
#define CONTROL_H

#include "GLEngine.h"
#include <list>
#include <string>
using std::string;

struct MouseState
{
	int leftMouseButton, rightMouseButton, middleMouseButton;
	int mousex, mousey;

	MouseState()
	{
		leftMouseButton = 0;
		rightMouseButton = 0;
		middleMouseButton = 0;

	
	}
	
};
class Control
{
protected:
	int width, height;
	int posx, posy;
	bool inside;

	
public:
	static std::list<Control *> controls;

public:

	Control(int x, int y, int width, int height);
	virtual ~Control();

	virtual bool updateControl( MouseState &state);
	virtual void drawControl() = 0;
	virtual string getType() = 0;

	int getHeight();
	int getWidth();
	void setSize(int width, int height);
	void setPosition(int x, int y);



};



Control * addControl(Control * control);

#endif