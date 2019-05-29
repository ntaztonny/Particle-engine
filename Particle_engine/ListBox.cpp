
#include "ListBox.h"

const int itemHeight = 18;

ListBox::ListBox(int posx, int posy, int width, int height):
	Control(posx, posy, width, height)
{
	index = 0;

}
void ListBox::addItem(string label)
{
	items.push_back(label);
}
void ListBox::removeItem(int index)
{	
	int i = 0;
		for(vector<string>::iterator it = items.begin(); it != items.end(); it++)
		{
			if(i == index)
			{
				items.erase(it);
				break;
			}

			i++;
		}

		if(index >= (int)items.size())
			index = (int) items.size() - 1;

}
void ListBox::setCurrent(int i)
{
	index = i;	
	
}

int ListBox::getIndex(void)
{
	return index;
}
int ListBox::getlistsize(void)
{
	return (int)items.size();
}

bool ListBox::updateControl( MouseState &state)
{
	Control::updateControl(state);

	int x  = state.mousex;
	int y  = state.mousey;

	if (inside == true && state.leftMouseButton)
	{
		int tempy = (y - posy)/itemHeight;

		if (tempy >= 0 && tempy < (int) items.size())
		{
			index = tempy;
			return true;
	
		}
	}

	return false;
}
void ListBox::drawControl()
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

	if (index >= 0)
	{	
		int currentY = posy + index *itemHeight;

		glColor4f(0.3f, 0.3f, 0.8f, 0.5f);

		glBegin(GL_QUADS);
			glVertex2d(posx + width,	currentY);
			glVertex2d(posx,			currentY);
			glVertex2d(posx,			currentY + itemHeight);
			glVertex2d(posx + width,	currentY + itemHeight);
		glEnd();
	}

	glColor4f(0.7f, 0.7f, 0.7f, 1.0f);
	for (int i =0; i < (int)items.size(); i++)
		iEngine ->drawText(posx +4, posy + 2 + i*itemHeight, items[i].data());
}
string ListBox::getType()
{
	return "ListBox";
}