#pragma once
#include "hoaIStorer.h"

#include <string>
#include <iostream>
#include <sstream>

class hoaReader : public hoaIStorer {
public:
	hoaReader(const std::string& text);
	~hoaReader();
	void store(int& value) override;
	void store(double& value) override;
	void store(hoaPoint& value) override;
	void store(hoaVector& value) override;
	bool isWriter() override;

private:
	std::istringstream _stream;
};
