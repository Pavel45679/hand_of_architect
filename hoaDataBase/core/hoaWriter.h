#pragma once
#include "hoaIStorer.h"

#include <string>
#include <iostream>
#include <sstream>

class hoaWriter : public hoaIStorer {
public:
	hoaWriter();
	~hoaWriter();
	void store(int& value) override;
	void store(double& value) override;
	void store(hoaPoint& value) override;
	void store(hoaVector& value) override;
	bool isWriter() override;

	std::string getText();
private:
	std::ostringstream _stream;
};
