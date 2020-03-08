#pragma once

/* Predefine some common types. */
typedef unsigned char								uchar;
typedef unsigned short								ushort;
typedef unsigned int								uint;
typedef unsigned long								ulong;

typedef unsigned char								byte;
typedef unsigned short								word;
typedef unsigned int								dword;
typedef unsigned long long							qword;

/* For storage based declarations. */
typedef signed char									int8;
typedef signed short								int16;
typedef signed int									int32;
typedef signed long long							int64;

typedef unsigned char								uint8;
typedef unsigned short								uint16;
typedef unsigned int								uint32;
typedef unsigned long long							uint64;

typedef unsigned short								real16;
typedef float										real32;
typedef double										real64;
typedef long double									real80;


/* String type. */
typedef const char* CStr;
typedef const wchar_t* WCStr;
#ifdef __NO_CRT__
typedef const unsigned short* UCStr;
#else
typedef const char16_t* UCStr;
#endif
