#include "DDDB.h"



int main(int argc, char** argv)
{
	const char* file_path = "nahrung.3db";
	const char* res_path = "res/";

	if(argc >= 2)
		file_path = argv[1];
	if(argc >= 3)
		res_path = argv[2];

	bool list = false;

	for(int i = 1 ; i < argc ;i++)
	{
		if(std::string(argv[i]) == "-l")
			list = true;
	}

	printf("opening file %s\n",file_path);
	FILE* f = fopen(file_path,"r");
	if(!f)
		EXIT_ERR("Failed opening file\n");


	DreiDDB dddb;
	dddb.read(f);
	if(list)
	{
		dddb.print(0);
	}
	else
	{
		dddb.export_all(res_path);
	}
	NL;
	return 0;
}


