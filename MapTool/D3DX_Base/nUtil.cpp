#include "stdafx.h"
#include "nUtil.h"

namespace MAPTOOL_UTIL
{
	float getDistance(float startX, float startY, float endX, float endY)
	{
		float x = endX - startX;
		float y = endY - startY;

		return sqrtf(x * x + y * y);
	}
}
