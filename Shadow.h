#pragma once
#include "util.h"
class Shadow
{
public:
	uint8_t data[32][32];


	void read(FILE* f)
	{
		fread(data,32,32,f);
	}


	void print(int level)
	{
		const char* lt = " .:&@***";
		for(int y = 0; y<32;y++)
		{
			for(int x= 0  ; x<32;x++)
			{
				TABS(level); printf("%c",lt[data[x][y]/(255/5)]);
			}
			NL;
		}
	}

};



