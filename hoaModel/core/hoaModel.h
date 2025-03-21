#ifndef MYLIBRARY_H
#define MYLIBRARY_H

#ifdef _WIN32
#ifdef MYLIBRARY_EXPORTS
#define MYLIBRARY_API __declspec(dllexport)
#else
#define MYLIBRARY_API __declspec(dllimport)
#endif
#else
#define MYLIBRARY_API
#endif

MYLIBRARY_API void printMessage();

#endif // MYLIBRARY_H
