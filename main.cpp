#include "DDDB.h"
#include "DDDB_operations.h"

class Settings
{
public:

	std::string file_name;
	std::string output_direcotry;
	std::string operation;
	std::string texture_subdir;

	Settings()
	{
		file_name = "baby.3db";
		output_direcotry = "out";
		operation = "list";
		texture_subdir = "textures";
	}

};

Settings parse_cmd(int argc, char** argv)
{
	Settings s;
	for(int i = 1 ; i<argc ; i++)
	{
		std::string arg = argv[i];
		if(arg == "-if")
		{
			i++;
			s.file_name = argv[i];
		}
		else if(arg == "-od")
		{
			i++;
			s.output_direcotry= argv[i];
		}
		else if(arg == "-op")
		{
			i++;
			s.operation= argv[i];
		}
		else if(arg == "-texdir")
		{
			i++;
			s.texture_subdir= argv[i];
		}


	}
	return s;
}


int main(int argc, char** argv)
{
	Settings s = parse_cmd(argc,argv);


	FILE* f = fopen(s.file_name.c_str(),"r");
	if(!f)
		EXIT_ERR("Failed opening file: %s",s.file_name.c_str());

	DreiDDB dddb;
	dddb.read(f);

	if(s.operation == "list")
	{
		dddb.print(0);
	}
	else if(s.operation == "ea")
	{
		DDDB_OP::write_all(dddb,s.output_direcotry,0);
	}
	NL;
	return 0;
}


