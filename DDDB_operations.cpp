#include "DDDB_operations.h"

void DDDB_OP::write_mesh_obj(const DreiDDB& dddb,const Mesh& m,FILE* f,const std::string& o_name, const std::string& a_name, const int frame)
{
	uint32_t l_id = 0;
	uint32_t offset = 0;

	for(const Link& l : m.links)
	{

		fprintf(f,"o %s_%s_%d_%d\n",o_name.c_str(),a_name.c_str(),frame,l_id);

		Material mat = dddb.materials.at(l.material);
		fprintf(f,"mtllib %s.mtl\n",mat.name.c_str());
		fprintf(f,"usemtl %s\n",mat.name.c_str());

		const auto& positions = dddb.vertex_data.points[l.points];
		for(const auto& p : positions )
			fprintf(f,"v %f %f %f \n",p.x-0.5f,p.y-0.5f,p.z-0.5f);

		const auto& tex_coords = dddb.vertex_data.texture_coords[l.tex_coords];
		for(const auto& t : tex_coords )
			fprintf(f,"vt %f %f \n",t.x,1.0f-t.y);

		const auto& triangles = dddb.vertex_data.triangles[l.triangles];
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

void DDDB_OP::write_animation(const DreiDDB &dddb, const Animation &a, const std::string directory, uint /*mesh_format*/)
{
	make_dir(directory+"/"+a.name);
	uint frame = 0;
	for(const auto m_id : a.meshes)
	{
		FILE* f = fopen((directory+"/"+a.name+"/"+std::to_string(frame)+".obj").c_str(),"w");
		write_mesh_obj(dddb,dddb.meshes.at(m_id),f,directory,a.name,frame);
		frame++;
		fclose(f);

		make_dir(directory+"/../Materials/");
		make_dir(directory+"/../Textures/");
		for(const Link& l : dddb.meshes.at(m_id).links)
		{
			Material mat = dddb.materials.at(l.material);
			f = fopen((directory+"/"+a.name+"/"+mat.name+".mtl").c_str(),"w");
			//f = fopen((directory+"/../Materials/"+mat.name+".mtl").c_str(),"w");
			write_material_obj(dddb,mat,f,"../");
			fclose(f);

		}


	}
}

void DDDB_OP::write_object(const DreiDDB &dddb, const Object &o, const std::string directory, uint mesh_format)
{

	make_dir(directory+"/"+o.name);
	for(const auto a_id : o.animations)
	{
		write_animation(dddb,dddb.animations.at(a_id),directory+"/"+o.name,mesh_format);
	}
}

void DDDB_OP::write_all(const DreiDDB &dddb, const std::string &directory, uint mesh_format)
{
	make_dir(directory);
	make_dir(directory+"/"+dddb.name);
	for(uint i  =0 ; i<dddb.object_count;i++)
	{
		write_object(dddb,dddb.objects.at(i),directory+"/"+dddb.name,mesh_format);
	}
}

void DDDB_OP::write_material_obj(const DreiDDB &, const Material &m, FILE *f, const std::string &texture_dir)
{

	fprintf(f,"newmtl %s\n",m.name.c_str());

	fprintf(f,"Ka 1.000 1.000 0.000\n");
	fprintf(f,"Kd 1.000 0.000 1.000\n");
	fprintf(f,"Ks 0.000 0.000 1.000\n");
	std::string ptt =texture_dir+m.path.substr(std::min(m.path.find_last_of('/'),m.path.find_last_of('\\'))+1);
	fprintf(f,"map_Ka  %s \n",ptt.c_str());
	fprintf(f,"map_Kd  %s \n",ptt.c_str());
}
