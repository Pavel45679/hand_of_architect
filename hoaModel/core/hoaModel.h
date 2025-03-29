#ifdef HOAMODEL_EXPORTS
#define HOAMODEL_API __declspec(dllexport)
#else
#define HOAMODEL_API __declspec(dllimport)
#endif

HOAMODEL_API void printMessage();

