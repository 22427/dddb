#pragma once
#include "util.h"
class CMap
{
public:
	uint16_t width;
	uint16_t height;
	uint16_t u1;
	uint16_t u2;
	unsigned char* data;
	CMap():data(nullptr)
	{}

	CMap(const CMap& cm): data(nullptr)
	{
		width = cm.width;
		height = cm.height;
		u1 = cm.u1;
		u2 = cm.u2;

		if(cm.data)
		{
			data = (unsigned char*) malloc(cm.width*cm.height);
			memcpy(data,cm.data,cm.width*cm.height);
		}
	}

	~CMap()
	{
		if(data)
			free(data);
	}

	void read(FILE* f)
	{
		width = read_uint16(f);
		height = read_uint16(f);
		u1 = read_uint16(f);
		u2 = read_uint16(f);
		data = (unsigned char*) malloc(width*height);
		fread(data,width,height,f);
	}
	void print(int level)
	{
		TABS(level);printf("CMap:\n");
		TABS(level);printf("w: %d | h: %d | u1: %d | u2: %d",width,height,u1,u2);
	}
};


