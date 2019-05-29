
#include "Button.h"

Button::Button(string lbl, int x, int y, int width, int height):
	Control(x,y,width,height)
{
	label = lbl;
	down = false;
}
bool Button::updateControl( MouseState &state)
{
	Control::updateControl(state);

	if(inside == true)
	{
		if(state.leftMouseButton)
		{
			down = true;
		}
		else if(down)
		{
			down = false;
			return true;
		}
	}

	return false;
}

void Button::drawControl()
{
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDisable(GL_TEXTURE_2D);
	glColor4f(0.7f, 0.7f, 0.7f, 0.8f);

	glBegin(GL_QUADS);
		glVertex2d(posx + width,	posy);
		glVertex2d(posx,			posy);
		glVertex2d(posx,			posy + height);
		glVertex2d(posx + width,	posy + height);
	glEnd();

	if (inside == true)
	{
		glColor4f(0.3f, 0.3f, 0.8f, 1.0f);
		glLineWidth(2.0f);
	
	}
	else
	{
		glColor4f(0.3f, 0.3f, 0.8f, 0.6f);
		glLineWidth(1.0f);
	}

	glBegin(GL_LINE_STRIP);
		glVertex2d(posx + width,	posy);
		glVertex2d(posx,			posy);
		glVertex2d(posx,			posy + height);
		glVertex2d(posx + width,	posy + height);
		glVertex2d(posx + width,	posy);
	glEnd();

	int textx = posx + (width - iEngine -> getTextWidth(label.data()))/2;
	int texty = posy + (height - iEngine -> getTextHeight(label.data()))/2;

	glColor4f(0.7f, 0.7f, 0.7f, 1.0f);
	iEngine ->drawText(textx, texty, label.data());
}


string Button::getType()
{
	return "Button";
}

