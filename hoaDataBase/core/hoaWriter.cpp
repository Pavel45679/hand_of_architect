#include "hoaWriter.h"

hoaWriter::hoaWriter(){
}

hoaWriter::~hoaWriter() = default;

void hoaWriter::store(int& value) {
	_stream << value << " ";
}

void hoaWriter::store(double& value) {
	_stream << value << " ";
}

void hoaWriter::store(hoaPoint& value) {
	store(value.x);
	store(value.y);
	store(value.z);
}

void hoaWriter::store(hoaVector & value) {
	store(value.x);
	store(value.y);
	store(value.z);
}

bool hoaWriter::isWriter() {
	return true;
}

std::string hoaWriter::getText() {
	return _stream.str();
}
