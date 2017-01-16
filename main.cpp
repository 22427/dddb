#include "DDDB.h"
#include "DDDB_operations.h"





class Settings
{
public:

	std::string file_name;
	std::string output_direcotry;
	std::string operation;
	std::string texture_dir;

	Settings()
	{
		file_name = "baby.3db";
		output_direcotry = "./";
		operation = "ls";
		texture_dir = "textures";
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
		else if(arg == "-tex")
		{
			i++;
			s.texture_dir= argv[i];
		}


	}
	return s;
}
#include <glad/glad.h>
#include <GLFW/glfw3.h>


class Viewer
{
	GLFWwindow* window;
	DreiDDB* db;

public:
	Viewer(DreiDDB* dddb):window(nullptr),db(dddb)
	{
		if(!glfwInit())
			EXIT_ERR("Failed to init GLFW3");

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
		GLFWwindow* window = glfwCreateWindow(800, 600, "DDDB Viewer", NULL, NULL);
		if (!window)
		{
			EXIT_ERR("Failed to create Window");
		}
		glfwMakeContextCurrent(window);

		if(!gladLoadGL())
		{
			EXIT_ERR("glad failed to load extensions");
		}

	}
	~Viewer()
	{
		if(window)
			glfwDestroyWindow(window);
		glfwTerminate();

	}

};

int main(int argc, char** argv)
{
	Settings s = parse_cmd(argc,argv);



	FILE* f = fopen(s.file_name.c_str(),"r");
	if(!f)
		EXIT_ERR("Failed opening file: %s",s.file_name.c_str());

	DreiDDB dddb;
	dddb.read(f);

	if(s.operation == "ls")
	{
		dddb.print(0);
	}
	else if(s.operation == "ea")
	{
		DDDB_OP::write_all(dddb,s.output_direcotry,0,s.texture_dir);
	}
	else if(s.operation == "view")
	{
		Viewer v(&dddb);
	}
	NL;
	return 0;
}


