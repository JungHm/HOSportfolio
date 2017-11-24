#include "stdafx.h"
#include "nUtil.h"

namespace MAPTOOL_UTIL
{
	float getAngle(float startX, float startY, float endX, float endY)
	{
		float x = endX - startX;
		float y = endY - startY;
		float distance = sqrtf(x * x + y * y);
		float angle = acosf(x / distance);

		if (endY > startY)
		{
			angle = D3DX_PI * 2 - angle;
			if (angle >= D3DX_PI * 2) angle -= D3DX_PI * 2;
		}
		return angle;
	}

	float getDistance(float startX, float startY, float endX, float endY)
	{
		float x = endX - startX;
		float y = endY - startY;

		return sqrtf(x * x + y * y);
	}
}
