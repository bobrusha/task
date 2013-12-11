#ifndef _SCREEN_H_
#define _SCREEN_H_
#include <list>
//#include "bomb.h"
#include "texture.h"

using namespace std;

const int step = 40;
const int arr_w = 15, arr_h = 13;

int calculateIndex (int x)
{
	x += (step - 10);
	x /= step;
	return x;
}

class screen
{
	int arr [arr_h][arr_w];
	bool run;

public:
	void clearScreen()
	{
		
		for (int i = 0; i < arr_h - 1; i++)
		{
			for ( int j=0; j < arr_w - 1; j++)
				arr[i][j] = 0;
		}
		
		for (int i = 0; i < arr_h; i++)
			arr[i][0] = 4;
		
		for (int i = 0; i < arr_h; i++)
			arr[i][14] = 4;
		
		for (int i = 0; i < arr_w; i++)
			arr[0][i] = 4;

		for (int i = 0; i < arr_w; i++)
			arr[12][i] = 4;

		run = true;
	}

	screen ()
	{
		clearScreen();
	}
	void print()
	{
		for (int i = 0; i < arr_h; i++)
		{
			for ( int j=0; j < arr_w; j++)
				std::cout<<arr[i][j]<<" ";
			std::cout<<" "<<std::endl;
		}
	}

	void setRun ( const bool& r )
	{
		run = r;
	}

	bool getRun ()
	{
		return run;
	}

	void setArrayElement (const int& k, const int& i, const int& j)
	{
		arr[i][j] = k;
	}

	int getArrayElement (const int& i, const int& j)
	{
		return arr[i][j];
	}

};


int youLose(screen& scrn)
{

	std::cout<<"QQ"<<std::endl;
	scrn.setRun(false);
	return 0;
}

#endif