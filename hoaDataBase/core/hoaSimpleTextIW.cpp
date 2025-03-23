#include "hoaSimpleTextIW.h"

void hoaSimpleTextIW::store(int& i) {
	mStr+=std::to_string(i);
}

void hoaSimpleTextIW::store(double& d) {
	mStr += std::to_string(d);
}

std::vector<char> hoaSimpleTextIW::get() {
	return std::vector<char>(mStr.begin(), mStr.end());
}
