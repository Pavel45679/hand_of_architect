#pragma once

#ifdef hoaMath_EXPORTS
#define HOA_MATH_API __declspec(dllexport)
#else
#define HOA_MATH_API __declspec(dllimport)
#endif
