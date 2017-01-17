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

	float u1[3]; // bounding box minimum
	float u2[3]; // bounding box maximum

	//	uint8_t u3[0x80] ;
	int32_t u3[32] ; // refer to the unknown attributes. The values are in the correct range.
	// usually most of them are 0.

	int16_t u4; // shadow map id
	uint8_t u5[0x30]; // shadow geometry 4*3 floats form a rectangle
	int16_t u6; // color map id

	Mesh_unknown(){}

	void read (FILE* f)
	{
		fread(u1,3*sizeof (float),1,f);
		fread(u2,3*sizeof (float),1,f);


		fread(u3,32*4,1,f);
		/*fread(u3_2,2*4,1,f);
		fread(&u3_3,1*4,1,f);
		fread(u3_4,21*4,1,f);
*/
		u4 = read_int16(f);
		fread(u5,0x30,1,f);
		u6 = read_int16(f);
	}

	void print(int level)
	{
		TABS(level);printf("MU\n");
		TABS(level);printf("MU12");for(int i = 0 ; i<3;i++)
			printf("%f ",u1[i]);
		printf("|| ");
		for(int i = 0 ; i<3;i++)
			printf("%f ",u2[i]);
		NL;
		TABS(level);printf("MU3 ui "); print_uints(u3,32);	NL;
		/*TABS(level);printf("MU3_2  i "); print_uints(u3_2,2);	NL;
		TABS(level);printf("MU3_3  i "); print_uints(&u3_3,1);	NL;
		TABS(level);printf("MU3_4  i "); print_ints(u3_4,21);	NL;
*/
		TABS(level);printf("MU4  s %d",u4); print_int16_ts((uint8_t*)&u4,1);		NL;
		TABS(level);printf("MU5  b "); print_bytes(u5,0x30);	NL;
		TABS(level);printf("MU5  f "); print_floats(u5,0x30/4);	NL;

		TABS(level);printf("MU6  s "); print_int16_ts((uint8_t*)&u6,1);		NL;

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
