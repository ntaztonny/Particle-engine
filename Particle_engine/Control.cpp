
#include "Control.h"

std::list<Control *> Control::controls;

Control:: Control(int x, int y, int w, int h)
{
	controls.push_back(this);
	posx = x;
	posy = y;
	width = w;
	height = h;

}

Control:: ~Control()
{
	controls.remove(this);

}

bool Control::updateControl( MouseState &state)
{
	int x = state.mousex;
	int y = state.mousey;

	inside = false;
	if ((x >= posx && x <= posx+width) && (y >= posy && y <= posy +height))
	{
		inside = true;
	
	}
	return false;

}

int Control::getHeight()
{
	return height;
}

int Control::getWidth()
{
	return width;
}
	
void Control::setSize(int w, int h)
{
	width = w;
	height = h;
}

void Control::setPosition(int x, int y)
{
	posx = x;
	posy = y;
}

Control * addControl(Control * control)
{
	static int lastx = 5;
	static int lasty = 5;

	control ->setPosition(lastx, lasty);
	lasty += control ->getHeight() + 5;

	return control;

}