#include "hoaSimpleTextIR.h"

void hoaSimpleTextIR::store(int& i) {
	i = std::strtol(mBuff, &mBuff, 10);
}

void hoaSimpleTextIR::store(double& d) {
	d = std::strtod(mBuff, &mBuff);
}
