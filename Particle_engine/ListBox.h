#ifndef LISTBOX_H
#define LISTBOX_H

#include "Control.h"
#include <vector>


class ListBox: public Control
{
public: 
	ListBox(int posx, int posy, int width, int height);
	void addItem(string label);
	void removeItem(int index);
	void setCurrent(int index);

	int getIndex(void);
	int getlistsize(void);

	virtual bool updateControl( MouseState &state);
	virtual void drawControl();
	virtual string getType();

protected:
	int index;
	std::vector<string> items;
};

# endif