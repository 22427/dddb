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
			fprintf(f,"v %f %f %f \n",p.x,p.y,p.z);

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

void DDDB_OP::write_animation(const DreiDDB &dddb, const Animation &a, const std::string directory, uint /*mesh_format*/, const std::string &textures)
{
	std::string new_dir = directory+"/"+a.name;

	make_dir(new_dir);


	uint frame = 0;
	for(const auto m_id : a.meshes)
	{
		FILE* f = fopen((directory+"/"+a.name+"/"+std::to_string(frame)+".obj").c_str(),"w");
		write_mesh_obj(dddb,dddb.meshes.at(m_id),f,directory,a.name,frame);
		frame++;
		fclose(f);

		for(const Link& l : dddb.meshes.at(m_id).links)
		{
			Material mat = dddb.materials.at(l.material);

			write_material_obj(dddb,mat,new_dir,textures);


		}


	}
}

void DDDB_OP::write_object(const DreiDDB &dddb, const Object &o, const std::string directory, uint mesh_format, const std::string &textures)
{

	std::string new_dir = directory+"/"+o.name;

	make_dir(new_dir);
	for(const auto a_id : o.animations)
	{
		write_animation(dddb,dddb.animations.at(a_id),new_dir,mesh_format,textures);
	}
}

void DDDB_OP::write_all(const DreiDDB &dddb, const std::string &directory, uint mesh_format, const std::string &textures)
{
	make_dir(directory);
	make_dir(directory+"/"+dddb.name);
	for(uint i  =0 ; i<dddb.object_count;i++)
	{
		write_object(dddb,dddb.objects.at(i),directory+"/"+dddb.name,mesh_format,textures);
	}
}

void DDDB_OP::write_material_obj(const DreiDDB &, const Material &m, const std::string& path, const std::string &textures)
{

	FILE* f = fopen((path+"/"+m.name+".mtl").c_str(),"w");
	fprintf(f,"newmtl %s\n",m.name.c_str());

	fprintf(f,"Ka 1.000 1.000 1.000\n");
	fprintf(f,"Kd 1.000 1.000 1.000\n");
	fprintf(f,"Ks 1.000 1.000 1.000\n");

	std::string ptt = m.path.substr(std::min(m.path.find_last_of('/'),m.path.find_last_of('\\'))+1);
	fprintf(f,"map_Ka  %s \n",ptt.c_str());
	fprintf(f,"map_Kd  %s \n",ptt.c_str());
	fprintf(f,"map_Ks  %s \n",ptt.c_str());

	copy_file(textures+"/"+ptt,path+"/"+ptt);
	fclose(f);
}
