#ifndef SLIDER_H
#define SLIDER_H

#include "Control.h"

class Slider: public Control
{
public: 
	Slider (string label, float min, float max, int positionx, int positiony, int width, int height);
	void setValue (float *value);

	virtual bool updateControl( MouseState &state);
	virtual void drawControl();
	virtual string getType();

protected:
	bool  dragging;
	float defaultvalue;
	float *currentValue;
	string label;
	float min, max;

};

#endif