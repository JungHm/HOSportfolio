#pragma once

#define g_FXLoad	cFxLoad::GetInstance()
#define g_sEffect	cFxLoad::GetInstance()->GetEffect()
#define g_sDecl		cFxLoad::GetInstance()->GetDecl()

class cFxLoad
{
private:
	LPD3DXEFFECT g_pEffect; //����Ʈ �������̽�
	LPDIRECT3DVERTEXDECLARATION9 g_pDecl;// ������������
public:
	SINGLETONE(cFxLoad);

	void InitFx(DWORD fvf);
	//�ؽ���/ �������
	void SetupFx(LPDIRECT3DTEXTURE9 texture, D3DXMATRIXA16* matW);

	LPD3DXEFFECT GetEffect() { return g_pEffect; }
	LPDIRECT3DVERTEXDECLARATION9 GetDecl() { return g_pDecl; }
};

