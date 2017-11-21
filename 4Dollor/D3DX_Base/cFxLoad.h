#pragma once

#define g_FXLoad	cFxLoad::GetInstance()
#define g_sEffect	cFxLoad::GetInstance()->GetEffect()
#define g_sDecl		cFxLoad::GetInstance()->GetDecl()

class cFxLoad
{
private:
	LPD3DXEFFECT g_pEffect; //이펙트 인터페이스
	LPDIRECT3DVERTEXDECLARATION9 g_pDecl;// 정점선언정보
public:
	SINGLETONE(cFxLoad);

	void InitFx(DWORD fvf);
	//텍스쳐/ 월드행렬
	void SetupFx(LPDIRECT3DTEXTURE9 texture, D3DXMATRIXA16* matW);

	LPD3DXEFFECT GetEffect() { return g_pEffect; }
	LPDIRECT3DVERTEXDECLARATION9 GetDecl() { return g_pDecl; }
};

