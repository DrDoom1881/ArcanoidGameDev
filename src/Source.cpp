#include "Object.h"
#include "mFramework.h"
#include <iostream>
#include <string.h>
static int width = 800;
static int height = 600;
static bool ScrType = false;
static char* numbers[] = { "0","1","2","3","4","5","6","7","8","9",};

int numPars(int size, const char* argv, int numOfFirst = 0)
{
	int number = 0;
	
	for (int i = numOfFirst; i < size + numOfFirst; ++i)
	{
		bool flag = true;
		int c = 0;
		while (flag)
		{
			if (argv[i] == *numbers[c])
				flag = false;
			++c;
		}
		number += pow(10,((size) - (i - numOfFirst + 1))) * (c - 1) ;
	}
	return number;
}


void arguments(const int i, const char* argv)
{
	if (i == 0)
	{
		return;
	}
	else
	{
		if (strcmp( argv, "-window") == 0)
		{
			ScrType = false;
			return;
		}
		else
		{
			if (strcmp( argv, "-fullscreen" ) == 0)
			{
				ScrType = true;
				return;
			}
		}
		int Wsize = 0;
		while ((argv[Wsize] == 'x') == 0)
		{
			++Wsize;
		}
		int Hsize = strlen(argv) - (Wsize + 1);//"1366x720" 4 3
		width = numPars(Wsize , argv);
		height = numPars(Hsize, argv, Wsize + 1);
	}
}

int main(int argc, char* argv[])
{
	
	for (int i = 1; i < argc; ++i)
	{
		arguments(i, argv[i]);	
	}
	srand((unsigned int)time(0));
	mFramework* Arcanoid = new mFramework(width, height, ScrType);
	Object::Framework = Arcanoid;
	return run(Arcanoid);
} 