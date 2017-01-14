#include "DDDB.h"

void DreiDDB::read(FILE *f)
{
	uint8_t buff[12];

	fread(buff,12,1,f);

//	print_chars(buff,12);
//	printf("\n" );

	len_name = read_uint32(f);
	name = read_string(f,len_name);


	material_count = read_uint16(f);
	materials.resize(material_count);
	for(int i = 0 ; i< material_count;i++)
	{
		materials[i].read(f);
	}

	mesh_count = read_uint32(f);
	meshes.resize(mesh_count);
	for(int i = 0 ; i< mesh_count;i++)
	{
		meshes[i].read(f);
	}

	object_count = read_uint16(f);
	objects.resize(object_count);
	for(int i = 0 ; i< object_count;i++)
	{
		objects[i].read(f);
	}

	animation_count = read_uint16(f);
	animations.resize(animation_count);
	for(int i = 0 ; i< animation_count;i++)
	{
		animations[i].read(f);
	}


	shadow_count = read_uint16(f);
	shadows.resize(shadow_count);
	for(int i = 0 ; i< shadow_count;i++)
	{
		shadows[i].read(f);
	}

	cmaps_count = read_uint16(f);
	cmaps.resize(cmaps_count);
	for(int i = 0 ; i< cmaps_count;i++)
	{
		cmaps[i].read(f);
	}

	vertex_data.read(f);
	fclose(f);
}

void DreiDDB::print(int level)
{
	TABS(level);printf("DreiDDB\n");
	TABS(level);printf("name: %s",name.c_str());
	NL;
	printf("----------------------------------------------------------------------------------");NL;
	TABS(level); printf("%d materials:\n",material_count);
	for(auto m : materials)
	{
		m.print(level+1);NL;
	}
	printf("----------------------------------------------------------------------------------");NL;
	TABS(level);printf("%d meshes:\n",mesh_count);
	for(auto m : meshes)
	{
		m.print(level+1);NL;
	}
	printf("----------------------------------------------------------------------------------");NL;
	TABS(level);printf("%d objects:\n",object_count);
	for(auto o : objects)
	{
		o.print(level+1);NL;
	}
	printf("----------------------------------------------------------------------------------");NL;
	TABS(level);printf("%d animtions:\n",animation_count);
	for(auto a : animations)
	{
		a.print(level+1);NL;
	}
	printf("----------------------------------------------------------------------------------");NL;
	TABS(level);printf("%d shadows:\n",shadow_count);
	for(auto s : shadows)
	{
		s.print(level+1);NL;
	}
	printf("----------------------------------------------------------------------------------");NL;
	TABS(level);printf("%d cmaps:\n",cmaps_count);
	for(auto c : cmaps)
	{
		c.print(level+1);NL;
	}
	printf("----------------------------------------------------------------------------------");NL;
	vertex_data.print(level+1);
}
