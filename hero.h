#ifndef _HERO_H
#define _HERO_H
#include "block.h"

class hero
{
public:
	int l, r, b, t, lives;
	bool inportal;
	sf::Sprite sprite;

	hero (screen &scrn): l (10), r(50), b(370), t(410), lives (2), inportal(false) 
	{	
		scrn.setArrayElement(1,calculateIndex(b),calculateIndex (l));
	}

	void Damaged()
	{
		lives --;
	}
	void MoveL (screen &scrn, portal& quit)
	{
		
		if ( scrn.getArrayElement(calculateIndex(b),calculateIndex (l - step)) == 3 )
		{
			youLose(scrn);
			Damaged();
		}
		else
			if ( scrn.getArrayElement (calculateIndex(b), calculateIndex (l - step)) == 0 )
			{
				scrn.setArrayElement (0, calculateIndex(b),calculateIndex (l));
				l -= step;
				r -= step;
				scrn.setArrayElement(1, calculateIndex(b), calculateIndex (l)); 
			}
			else 
				if (scrn.getArrayElement(calculateIndex(b), calculateIndex (l - step)) == 6 && quit.up == true)
				{
					inportal = true;
				}
	}
	void MoveR (screen &scrn, portal& quit)
	{
		if ( scrn.getArrayElement(calculateIndex(b), calculateIndex (l + step)) == 3 )
		{
			youLose(scrn);
			Damaged();
		}
		else
		{
			if (scrn.getArrayElement(calculateIndex(b), calculateIndex (l + step)) == 0)
			{
				scrn.setArrayElement(0, calculateIndex(b), calculateIndex (l));
				l += step;
				r += step;
				scrn.setArrayElement(1, calculateIndex(b), calculateIndex (l)); 
			}
			else 
				if (scrn.getArrayElement(calculateIndex(b), calculateIndex (l + step)) == 6 && quit.up==true)
				{
					inportal = true;
				}
		}
	}
	void MoveU (screen &scrn, portal& quit)
	{
		if ( scrn.getArrayElement(calculateIndex(b - step), calculateIndex (l)) == 3 )
		{
			youLose(scrn);
			Damaged();
		}
		else
		{
			if (scrn.getArrayElement(calculateIndex(b - step), calculateIndex (l)) == 0 )
			{
				scrn.setArrayElement(0, calculateIndex(b), calculateIndex (l));
				b -= step;
				t -= step;
				scrn.setArrayElement(1, calculateIndex(b), calculateIndex (l)); 
			}
			else 
				if (scrn.getArrayElement(calculateIndex(b -step), calculateIndex (l)) == 6 && quit.up==true)
				{
					inportal = true; //проверить а нужно ли это?
				}
		}
	}
	void MoveD (screen &scrn, portal& quit)
	{
		if ( scrn.getArrayElement(calculateIndex(b + step), calculateIndex (l)) == 3 )
		{
			youLose(scrn);
			Damaged();
		}
		else
		{
			if (scrn.getArrayElement(calculateIndex(b + step), calculateIndex (l)) == 0)
			{
				scrn.setArrayElement(0, calculateIndex(b), calculateIndex (l));
				b += step;
				t += step;
				scrn.setArrayElement(1, calculateIndex(b), calculateIndex (l)); 
			}
			else 
				if (scrn.getArrayElement(calculateIndex(b + step), calculateIndex (l)) == 6 && quit.up==true)
				{
					inportal = true;
				}
		}
	}
};

#endif