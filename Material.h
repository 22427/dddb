#pragma once
#include "util.h"
class Material
{
public:
	int len_name;
	std::string name;

	int len_path;
	std::string path;

	int i; // ??
	//Material():name(nullptr),path(nullptr){}
	~Material()
	{
		/*if(name)
			free(name);
		if(path)
			free(path);*/
	}

	void read(FILE*f)
	{
		fread(&(len_name),4,1,f);
		//name = (char*)(malloc(len_name));

		name = read_string(f,len_name);

		fread(&(len_path),4,1,f);
		//path = (char*)(malloc(len_path));

		path = read_string(f,len_path);

		fread(&i,4,1,f);
	}

	void print(int level)
	{
		TABS(level);printf("Material");NL;
		TABS(level);printf("%d: %s",len_name,name.c_str());
		TAB;printf("%d: %s",len_path,path.c_str());
		TAB;
		printf("%d <- ???",i);
	}
};
