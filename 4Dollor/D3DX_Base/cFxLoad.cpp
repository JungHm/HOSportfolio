#include "stdafx.h"
#include "cFxLoad.h"


cFxLoad::cFxLoad()
{
}


cFxLoad::~cFxLoad()
{
}

void cFxLoad::InitFx(DWORD fvf)
{
	D3DVERTEXELEMENT9 decl[MAX_FVF_DECL_SIZE];
	D3DXDeclaratorFromFVF(fvf, decl);//FVF�� ����ؼ� ���������� �ڵ����� ä���ִ´�
	g_pD3DDevice->CreateVertexDeclaration(decl, &g_pDecl);//������������ g_pDecl�� ����

	//shader.fx������ �о�ͼ� ID3DXEffect �������̽��� �����Ѵ�.
	D3DXCreateEffectFromFile(g_pD3DDevice, L"FX/shader.fx", NULL, NULL, 0, NULL, &g_pEffect, NULL);

}

void cFxLoad::SetupFx(LPDIRECT3DTEXTURE9 texture, D3DXMATRIXA16* matW)
{
	g_pEffect->SetTexture("m_TextureDiffuse", texture);
	g_pEffect->SetMatrix("matW", matW);
	g_pEffect->SetMatrix("matV", &g_Cam->GetView());
	g_pEffect->SetMatrix("matP", &g_Cam->GetProj());
}
