#pragma once
#include "util.h"
class Link
{
public:
	uint16_t material;
	uint16_t unknown;
	uint16_t triangles;
	uint16_t tex_coords;
	uint16_t points;
	uint16_t brightness;
	void read(FILE* f)
	{
		material = read_uint16(f);
		unknown = read_uint16(f);
		triangles = read_uint16(f);
		tex_coords = read_uint16(f);
		points = read_uint16(f);
		brightness = read_uint16(f);
	}
	void print(int level)
	{
		TABS(level);printf("LNK m:%d | u:%d | t:%d | t:%d | p:%d | b:%d",
						   material,unknown,triangles,tex_coords,points,brightness);
	}
};

class Mesh_unknown
{
public:

	float u1[3];
	float u2[3];
	uint8_t u3[0x80] ;
	uint16_t u4;
	uint8_t u5[0x30];
	uint16_t u6;

	Mesh_unknown(){}

	void read (FILE* f)
	{
		fread(u1,3*sizeof (float),1,f);
		fread(u2,3*sizeof (float),1,f);

		fread(u3,0x80,1,f);
		u4 = read_uint16(f);
		fread(u5,0x30,1,f);
		u6 = read_uint16(f);
	}

	void print(int level)
	{
		TABS(level);printf("MU\n");
		TABS(level); for(int i = 0 ; i<3;i++)
			printf("%f ",u1[i]);
		printf("|| ");
		for(int i = 0 ; i<3;i++)
			printf("%f ",u2[i]);
		NL;
		TABS(level); print_chars(u3,0x80);	NL;
		TABS(level); printf("%d\n",u4);		NL;
		TABS(level); print_chars(u5,0x30);	NL;
		TABS(level); printf("%d\n",u6);
	}
};

class Mesh
{
public:
	uint16_t link_count;
	std::vector<Link> links;
	Mesh_unknown u;
	void read(FILE* f)
	{
		link_count = read_uint16(f);
		for(int i = 0; i< link_count;i++)
		{
			links.push_back(Link());
			links.back().read(f);
		}
		u.read(f);
	}
	void print(int level)
	{
		TABS(level);printf("Mesh\n");
		TABS(level);printf("%d Links:\n",link_count);
		for(auto l : links)
		{
			l.print(level+1);NL;
		}
		NL;
		u.print(level+1);
		NL;


	}

};
