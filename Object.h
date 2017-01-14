#pragma once
#include "util.h"
class Object
{
public:
	uint32_t len_name;
	std::string name;
	std::vector<uint32_t> animations;

	void read(FILE* f)
	{
		len_name = read_uint32(f);
		name = read_string(f,len_name);

		uint16_t cnt = read_uint16(f);
		animations.resize(cnt);
		for(int i = 0  ; i< cnt; i++)
		{
			animations[i] = read_uint32(f);
		}


	}
	void print(int level)
	{
		TABS(level);printf("Object\n");
		TABS(level);printf("%s\n",name.c_str());
		TABS(level);printf("%d animations(former attributes!):",static_cast<int>(animations.size()));
		bool first = true;
		for(auto l : animations)
		{
			if(!first)
			{
				printf(",");

			}
			else
			{
				first = false;
			}
			printf("%d",l);
		}

	}

};
