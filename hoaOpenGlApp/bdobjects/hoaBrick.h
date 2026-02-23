#pragma once
#include "hoaObject.h"
#include "hoaPoint.h"
#include "hoaVector.h"
#include "hoaObjEnum.h"
#include "hoaIStorer.h"
#include "hoaGraphicObject.h"

class hoaBrick : public hoaObject{
public:
	void store(hoaIStorer& storer) override;
	int type() override;
	void draw(hoaIDrawer* drawer) override;
private:
	hoaPoint _sPoint;
	hoaVector _dir;
	hoaVector _normal;
	double _width;
	double _height;
	double _length;
};
