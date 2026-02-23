#include "hoaReader.h"

#include <iostream>

hoaReader::hoaReader(const std::string& text):_stream(text){
}

hoaReader::~hoaReader() = default;

void hoaReader::store(int& value) {
	_stream >> value;
	if (_stream.peek() == ' ')
		_stream.ignore();
}

void hoaReader::store(double& value) {
	_stream >> value;
	if (_stream.peek() == ' ')
		_stream.ignore();
}

void hoaReader::store(hoaPoint& value) {
	store(value.x);
	store(value.y);
	store(value.z);
}

void hoaReader::store(hoaVector & value) {
	store(value.x);
	store(value.y);
	store(value.z);
}

bool hoaReader::isWriter() {
	return false;
}
