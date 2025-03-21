#include "hoaObject.h"
#include <iostream>

hoaObject::hoaObject() {
	std::cout << "hoaObject created!" << std::endl;
}

void hoaObject::printMessage() {
	std::cout << "Hello from hoaObject!" << std::endl;
}