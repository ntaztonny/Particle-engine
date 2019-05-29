#include "Slider.h"

const int tickthinkness = 5;

Slider::Slider (string lbl, float mn, float mx, int positionx, int positiony, int width, int height): 
	Control(positionx, positiony, width, height)
{
	defaultvalue = 0.0f;
	currentValue = NULL;
	min = mn;
	max = mx;
	label  = lbl;
	dragging = false;
}

void Slider::setValue (float *value)
{
	currentValue = value;

	if(currentValue != NULL)
		defaultvalue = *currentValue;
		
}

bool Slider::updateControl( MouseState &state)
{
	Control::updateControl(state);

	int x = state.mousex;
	int y = state.mousey;

	if (inside == true)
	{	if (state.leftMouseButton)
			{ dragging = true; }
		if (state.rightMouseButton)
			{
				*currentValue = defaultvalue;
			}
	}

	if (!state.leftMouseButton)
	{
		dragging = false;
	}

	if (dragging == true)
	{
		 (*currentValue) =  float(x-posx) / width *  (max-min) + min;

		 if((*currentValue) > max)
				 *currentValue = max;

		 else if((*currentValue) < min)
					*currentValue = min;
		 
	}

	return dragging;
}
void Slider::drawControl()
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

	int  xvalue = (int)((*currentValue- min)/ (max - min) * (width - 20) + posx );
	MouseState state;
	
	
	glColor4f(0.3f, 0.3f, 1.0f, 0.5f);

	glBegin(GL_QUADS);
		glVertex2d(xvalue + tickthinkness,	posy);
		glVertex2d(xvalue,					posy);
		glVertex2d(xvalue,					posy + height);
		glVertex2d(xvalue + tickthinkness,	posy + height);
	glEnd();

		glColor4f(0.7f, 0.7f, 0.7f, 1.0f);
		iEngine ->drawText(posx + 3, posy + 15, label.data());

}

string Slider::getType()
{
	return "Slider";
}