#pragma once
#include "util.h"
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <glm/glm.hpp>
#include <vector>
#include <map>
#include <fstream>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#ifndef EXIT_ERR
#define EXIT_ERR(...) do{\
	fprintf(stderr,"[ERR][F:%s:%d] ",__FILE__,__LINE__);\
	fprintf(stderr,__VA_ARGS__);fprintf(stderr,"\n");\
	}while(0)

#define NL do{printf("\n");}while(0)
#define TAB do{printf("\t");}while(0)
#define TABS(l) do{for(int i=0;i<l;i++)printf("\t");}while(0)
#endif

inline void print_bytes(uint8_t* b, int cnt)
{

	printf("|");
	for(int i = 0 ; i< cnt;i++)
	{
		printf("%02X|",(uint32_t)b[i]);
	}
}

inline void print_uints(void* bb, int cnt)
{
	printf("|");
	uint32_t* b = (uint32_t*) bb;
	for(int i = 0 ; i< cnt;i++)
	{
		printf("%u|",b[i]);
	}
}

inline void print_ints(void* bb, int cnt)
{
	printf("|");
	int* b = (int*) bb;
	for(int i = 0 ; i< cnt;i++)
	{
		printf("%d|",b[i]);
	}
}



inline void print_uint16_ts(void* bb, int cnt)
{
	printf("|");
	uint16_t* b = (uint16_t*) bb;
	for(int i = 0 ; i< cnt;i++)
	{
		printf("%u|",b[i]);
	}

}

inline void print_int16_ts(void* bb, int cnt)
{
	printf("|");
	int16_t* b = (int16_t*) bb;
	for(int i = 0 ; i< cnt;i++)
	{
		printf("%d|",b[i]);
	}

}


inline void print_floats(void* bb, int cnt)
{
	printf("|");
	float* b = (float*) bb;
	for(int i = 0 ; i< cnt;i++)
	{
		printf("%f|",b[i]);
	}
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


inline int16_t read_int16(FILE*f)
{
	int16_t i;
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

inline bool make_dir(const std::string& dir)
{
	struct stat st;
	memset(&st,0,sizeof(struct stat));
	if (stat(dir.c_str(), &st) == -1)
	{
		mkdir(dir.c_str(), 0700);
		return true;
	}
	return false;
}

inline bool copy_file(const std::string& from, const std::string& to)
{
	std::ifstream  src(from, std::ios::binary);
	if(!src.is_open())
		return false;
	std::ofstream  dst(to,   std::ios::binary);
	if(!dst.is_open())
		return  false;

	dst << src.rdbuf();
	src.close();
	dst.close();
	return true;
}

template<typename T>
inline typename std::enable_if<std::is_unsigned<T>::value, T>::type
float_to_int(const float f)
{
	return static_cast<T>(f*std::numeric_limits<T>::max()/*((1<<((sizeof(T)*8)))-1)*/);
}


template<typename T>
inline typename std::enable_if<std::is_signed<T>::value, T>::type
float_to_int(const float f)
{
	return static_cast<T>(f*((1<<((sizeof(T)*8)-1))-1));
}


template<typename T>
inline typename std::enable_if<std::is_unsigned<T>::value>::type
float_to_int(const float f, T& t)
{
	t = static_cast<T>(f*((1<<((sizeof(T)*8)))-1));
}


template<typename T>
inline typename std::enable_if<std::is_signed<T>::value>::type
float_to_int(const float f, T& t)
{
	t = static_cast<T>(f*((1<<((sizeof(T)*8)-1))-1));
}



template<typename T>
inline typename std::enable_if<std::is_signed<T>::value, float>::type
int_to_float(const T x)
{
	const T t = ((1<<((sizeof(T)*8)-1))-1);
	return std::max(static_cast<float>(x)/t,-1.0f);
}


template<typename T>
inline typename std::enable_if<std::is_unsigned<T>::value, float>::type
int_to_float(const T x)
{
	const T t = std::numeric_limits<T>::max();//((1<<((sizeof(T)*8)))-1);
	return static_cast<float>(x)/t;
}



