#include "hoaTestGraphicObject.h"

void hoaTestGraphicObject::draw(hoaIDrawer* drawer) {
	drawer->drawLine({-100,0,0}, {100,0,0});
	drawer->drawLine({ 0,-100,0 }, { 0,100,0});
}
