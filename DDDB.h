#pragma once
#include "Animation.h"
#include "Cmap.h"
#include "Material.h"
#include "Mesh.h"
#include "Object.h"
#include "Shadow.h"
#include "VertexData.h"

class DreiDDB
{
public:
	int len_name;
	std::string name;
	uint16_t material_count;
	std::vector<Material> materials;

	int mesh_count;
	std::vector<Mesh> meshes;


	uint16_t object_count;
	std::vector<Object> objects;

	uint16_t animation_count;
	std::vector<Animation> animations;

	uint16_t shadow_count;
	std::vector<Shadow> shadows;


	uint16_t cmaps_count;
	std::vector<CMap> cmaps;

	VertexData vertex_data;

	DreiDDB()
	{}
	void read(FILE* f);

	void print(int level);

};
