#pragma once

#ifdef STDS_EXPORTS
#  define STDS_API __declspec(dllexport)
#else
#  define STDS_API __declspec(dllimport)
#endif

#define _STRINGIFY(x) #x
#define STRINGIFY(x) _STRINGIFY(x)
#define _stringof STRINGIFY
