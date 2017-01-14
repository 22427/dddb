#pragma once
#include "util.h"

class VertexData
{
public:
	uint16_t triangle_list_count;
	uint16_t texture_coord_list_count;
	uint16_t point_list_count;
	uint16_t brightness_list_count;

	uint32_t unknown_list_count;


	std::vector<uint16_t> triangle_list_lens;
	std::vector<uint16_t> texture_coord_list_lens;
	std::vector<uint16_t> point_list_lens;
	std::vector<uint16_t> brightness_list_lens;

	std::vector<std::vector<uint16_t>> triangles;
	std::vector<std::vector<glm::vec2>> texture_coords;
	std::vector<std::vector<glm::vec3>> points;
	std::vector<std::vector<uint8_t>> brightnesses;
	std::vector<std::array<uint8_t,20>> unknowns;

	void read(FILE* f)
	{
		triangle_list_count = read_uint16(f);
		texture_coord_list_count = read_uint16(f);
		point_list_count = read_uint16(f);
		brightness_list_count = read_uint16(f);
		unknown_list_count = read_uint32(f);

		triangle_list_lens.resize(triangle_list_count);
		triangles.resize(triangle_list_count);
		uint j = 0;
		for(auto& i : triangle_list_lens)
		{
			i = read_uint16(f);
			triangles[j].resize(i);
			j++;
		}

		texture_coord_list_lens.resize(texture_coord_list_count);
		texture_coords.resize(texture_coord_list_count);
		j = 0;
		for(auto& i : texture_coord_list_lens)
		{
			i = read_uint16(f);
			texture_coords[j].resize(i);
			j++;
		}

		point_list_lens.resize(point_list_count);
		points.resize(point_list_count);
		j = 0;
		for(auto& i : point_list_lens)
		{
			i = read_uint16(f);
			points[j].resize(i);
			j++;
		}

		brightness_list_lens.resize(brightness_list_count);
		brightnesses.resize(brightness_list_count);
		j = 0;
		for(auto& i : brightness_list_lens)
		{
			i = read_uint16(f);
			brightnesses[j].resize(i);
			j++;
		}

		unknowns.resize(unknown_list_count);
		for(auto& u : unknowns)
		{
			fread(u.data(),20,1,f);
		}


		for(auto& ts : triangles)
		{
			for(auto& t : ts)
			{
				t = read_uint16(f);
			}
		}


		for(auto& ts : texture_coords)
		{
			for(auto& t : ts)
			{
				t[0] = read_float(f);
				t[1] = read_float(f);
			}
		}


		const float scale = 1.0f/(float)(0xffff);
		for(auto& ts : points)
		{
			for(auto& t : ts)
			{
				t[0] = scale*read_uint16(f);
				t[1] = scale*read_uint16(f);
				t[2] = scale*read_uint16(f);
			}
		}

		for(auto& ts : brightnesses)
		{
			fread(ts.data(),ts.size(),1,f);
		}

	}

	void print(int level)
	{

		TABS(level);printf("Vertex Data\n");
		TABS(level);printf("%d triangle lists:\n",triangle_list_count); NL;
		TABS(level+1);
		for( auto t : triangle_list_lens)
			printf("%d, ",t);
		NL;
		TABS(level);printf("%d tex_coord lists:\n",texture_coord_list_count); NL;
		TABS(level+1);
		for( auto t : texture_coord_list_lens)
			printf("%d, ",t);
		NL;
		TABS(level);printf("%d point lists:\n",point_list_count); NL;
		TABS(level+1);
		for( auto t : point_list_lens)
			printf("%d, ",t);
		NL;
		TABS(level);printf("%d brightness lists:\n",brightness_list_count); NL;
		TABS(level+1);
		for( auto t : brightness_list_lens)
			printf("%d, ",t);
		NL;
		TABS(level);printf("%d unknown lists:\n",unknown_list_count); NL;
		TABS(level+1);
		for( auto t : unknowns)
			print_chars(t.data(),20);
	}


};
