#pragma once

#include "DDDB.h"

class DDDB_OP
{
public:
	static void write_mesh_obj(const DreiDDB& dddb,const Mesh& m,FILE* f,const std::string& o_name, const std::string& a_name, const int frame);

	static void write_animation(const DreiDDB& dddb, const Animation& a, const std::string directory, uint mesh_format);

	static void write_object(const DreiDDB& dddb,const Object& o, const std::string directory,uint mesh_format);

	static void write_all(const DreiDDB& dddb, const std::string& directory,uint mesh_format);


	static void write_material_obj(const DreiDDB& dddb,const Material& m,FILE* f, const std::string& texture_dir);

};
