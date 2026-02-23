#include "hoaBrick.h"

void hoaBrick::store(hoaIStorer& storer) {
	storer.store(_sPoint);
	storer.store(_dir);
	storer.store(_width);
	storer.store(_height);
	storer.store(_length);
};

int hoaBrick::type() {
	return std::to_underlying(hoaObjEnum::brick);
}

void hoaBrick::draw(hoaIDrawer* drawer) {
	const hoaVector vec = _dir.cross(_normal);
	const hoaVector vecLength = _dir * _length;
	const hoaVector vecWidth = vec * _width;
	const hoaVector vecHeight = _normal * _height;

	const hoaPoint p1 = _sPoint + vecWidth / 2;
	const hoaPoint p2 = p1 + vecLength;
	const hoaPoint p3 = p2 - vecWidth;
	const hoaPoint p4 = p3 - vecLength;
	const hoaPoint p5 = p1 + vecHeight;
	const hoaPoint p6 = p2 + vecHeight;
	const hoaPoint p7 = p3 + vecHeight;
	const hoaPoint p8 = p4 + vecHeight;

	drawer->drawLine(p1,p2);
	drawer->drawLine(p2,p3);
	drawer->drawLine(p3,p4);
	drawer->drawLine(p4,p1);

	drawer->drawLine(p5,p6);
	drawer->drawLine(p6,p7);
	drawer->drawLine(p7,p8);
	drawer->drawLine(p8,p5);

	drawer->drawLine(p1,p5);
	drawer->drawLine(p2,p6);
	drawer->drawLine(p3,p7);
	drawer->drawLine(p4,p8);
}
