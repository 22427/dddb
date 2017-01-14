#pragma once
#include "util.h"
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <glm/glm.hpp>
#include <vector>
#include <map>


#ifndef EXIT_ERR

#define EXIT_ERR(x) do{fprintf(stderr,x);exit(-1);}while(0)
#define NL do{printf("\n");}while(0)
#define TAB do{printf("\t");}while(0)
#define TABS(l) do{for(int i=0;i<l;i++)printf("\t");}while(0)
#endif

inline void print_chars(uint8_t* b, int cnt)
{
	printf("|");
	for(int i = 0 ; i< cnt;i++)
	{
		printf("%02X|",b[i]);
	}
}


inline void print_ints(uint8_t* bb, int cnt)
{
	printf("|");
	int* b = (int*) bb;
	for(int i = 0 ; i< cnt;i++)
	{
		printf("%d,",b[i]);
	}
	printf("|");
}



inline void print_uint16_ts(uint8_t* bb, int cnt)
{
	printf("|");
	uint16_t* b = (uint16_t*) bb;
	for(int i = 0 ; i< cnt;i++)
	{
		printf("%d,",b[i]);
	}
	printf("|");
}


inline void print_floats(uint8_t* bb, int cnt)
{
	printf("|");
	float* b = (float*) bb;
	for(int i = 0 ; i< cnt;i++)
	{
		printf("%f,",b[i]);
	}
	printf("|");
}


inline float read_float(FILE*f)
{
	float ff;
	fread(&ff,4,1,f);
	return ff;
}

inline uint32_t read_uint32(FILE*f)
{
	uint32_t i;
	fread(&i,4,1,f);
	return  i;
}


inline uint16_t read_uint16(FILE*f)
{
	uint16_t i;
	fread(&i,2,1,f);
	return  i;
}


inline std::string read_string(FILE*f, u_int len)
{
	if(len < 127)
	{
		char fix_b[128];
		fix_b[len] = 0;
		fread(fix_b,len,1,f);
		return std::string(fix_b);
	}

	char *b = (char*) malloc(len+1);
	b[len] = 0;
	fread(b,len,1,f);
	std::string res = b;

	free(b);
	return  res;

}

