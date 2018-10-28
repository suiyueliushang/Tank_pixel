#include "collision.h"
#include <math.h>

/*
author: rain
*/
position absp(position p1, rotation r)
{
	return position(p1.x()*cos(r.r()) + p1.y()*sin(r.r()), p1.y()*cos(r.r()) - p1.x()*sin(r.r()));
}
