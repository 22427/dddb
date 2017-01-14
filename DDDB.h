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



	void export_mesh_obj(FILE* f,const std::string& name , const int a_id, const int m_id, const int frame_no)
	{
		const Mesh& m = meshes[m_id];
		uint32_t l_id = 0;
		uint32_t offset = 0;

		for(const auto& l : m.links)
		{
			fprintf(f,"o %s_%d_%d_%d_%d\n",name.c_str(),a_id,m_id,l_id,frame_no);
			const auto& positions = vertex_data.points[l.points];
			for(const auto& p : positions )
				fprintf(f,"v %f %f %f \n",p.x-0.5f,p.y-0.5f,p.z-0.5f);

			const auto& tex_coords = vertex_data.texture_coords[l.tex_coords];
			for(const auto& t : tex_coords )
				fprintf(f,"vt %f %f \n",t.x,t.y);

			const auto& triangles = vertex_data.triangles[l.triangles];
			for(uint32_t i = 0 ; i< triangles.size();i+=3)
			{
				fprintf(f,"f %d/%d %d/%d %d/%d\n",
						offset+triangles[i]+1, offset+triangles[i]+1,
						offset+triangles[i+1]+1, offset+triangles[i+1]+1,
						offset+triangles[i+2]+1, offset+triangles[i+2]+1);
			}

			offset+=positions.size();
			l_id++;

		}
	}

	void export_animation(const std::string base_path,const std::string& name, const int a_id)
	{
		const Animation& a = animations[a_id];
		uint frame = 0;
		for(const auto m_id : a.meshes)
		{
			FILE* f = fopen((base_path+"/"+name+std::to_string(a_id)+"_"+std::to_string(frame)+".obj").c_str(),"w");
			export_mesh_obj(f,name,a_id,m_id,frame);
			frame++;
		}
	}


	void export_object(const std::string base_path, const int object_id)
	{
		const Object& o = objects[object_id];
		for(const auto a_id : o.animations)
		{
			export_animation(base_path,o.name,a_id);
		}
	}

	void export_all(const std::string base_path)
	{
		for(uint i  =0 ; i<object_count;i++)
		{
			export_object(base_path,i);
		}
	}
};
