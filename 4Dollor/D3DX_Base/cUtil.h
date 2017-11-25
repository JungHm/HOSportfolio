#pragma once

namespace Util 
{
	//struct Ray
	//{
	//	D3DXVECTOR3 origin;
	//	D3DXVECTOR3 direction;
	//};


	Ray CalcPickingRay(int x, int y);
	

	Ray D3DXVec2TransformArray(int nScreenX, int nScreenY);


	bool IntersectTri(IN Ray r, IN D3DXVECTOR3 & v0, IN D3DXVECTOR3 & v1, IN D3DXVECTOR3 & v2, OUT D3DXVECTOR3& vPickedPosition);
}