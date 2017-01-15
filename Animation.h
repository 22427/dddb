#pragma once
#include "util.h"
class Animation
{
public:
	u_int32_t len_name;
	std::string name;

	uint16_t mesh_count;
	std::vector<uint32_t> meshes;

	uint16_t u1;
	float u2;
	uint32_t len_animation_file;
	std::string animation_file;
	float u4[3];
	float u5[3];

	void read(FILE* f)
	{
		len_name = read_uint32(f);
		name = read_string(f,len_name);
		mesh_count =read_uint16(f);
		for(int i = 0 ; i < mesh_count ; i++)
		{
			meshes.push_back(read_uint32(f));
		}

		u1 = read_uint16(f);
		u2 = read_float(f);
		len_animation_file = read_uint32(f);
		animation_file = read_string(f,len_animation_file);

		for(int i  = 0 ; i <3;i++)
			u4[i] = read_float(f);
		for(int i  = 0 ; i <3;i++)
			u5[i] = read_float(f);
	}


	void print(int level)
	{
		TABS(level);printf("Animation: 'U know nothing John Snow!' \n");
		TABS(level);printf("%s\n",name.c_str());
		TABS(level);printf("%d meshes:",mesh_count);
		bool first = true;
		for(auto m : meshes)
		{
			if(!first)
			{
				printf(",");
			}
			else
			{
				first = false;
			}
			printf("%d",m);
		}
		NL;
		TABS(level); printf("%d | %f | '%s'",u1,u2,animation_file.c_str());
		NL;

		TABS(level); for(int i = 0 ; i<3;i++)
			printf("%f ",u4[i]);
		printf("|| ");
		for(int i = 0 ; i<3;i++)
			printf("%f ",u5[i]);
	}

};
