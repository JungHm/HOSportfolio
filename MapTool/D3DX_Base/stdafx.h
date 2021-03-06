// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once
// 콘솔 창 사용
//#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <iostream>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <assert.h>
#include <vector>
#include <list>
#include <set>
#include <map>
#include "nUtil.h"

// 네임 스페이스
using namespace std;
using namespace MAPTOOL_UTIL;

// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#include <d3dx9.h>

// 전역 윈도우 핸들
extern HWND g_hWnd;

// 싱글톤
#define SINGLETONE(class_name)	\
private:	\
	class_name();\
	~class_name();\
public:\
	static class_name* GetInstance()\
	{\
		static class_name instance;\
		return &instance;\
	}

#define SAFE_DELETE(p) { if(p) delete p; p = NULL; }
#define SAFE_RELEASE(p) { if(p) p->Release(); p = NULL; }

#define SYNTHESIZE(varType, varName, funcName)\
	protected: varType varName;\
	public: varType Get##funcName(void) const { return varName; }\
	public: void Set##funcName(varType var) { varName = var; }

#define SYNTHESIZE_PASS_BY_REF(varType, varName, funcName)\
	protected: varType varName;\
	public: varType& Get##funcName(void) { return varName; }\
	public: void Set##funcName(varType& var) { varName = var; }

#define SAFE_ADD_REF(p) { if (p) p->AddRef(); }
#define SYNTHESIZE_ADD_REF(varType, varName, funcName)\
	protected: varType varName;\
	public: virtual varType Get##funcName(void) const { return varName; }\
	public: virtual void Set##funcName(varType var) {\
		if (varName != var) {\
			SAFE_ADD_REF(var);\
			SAFE_RELEASE(varName);\
			varName = var;\
		}\
	}

// 텍스쳐 비율
#define MAX_XPIXEL   1041	
#define MAX_YPIXEL   652
#define ONE_XPIXEL   MAX_XPIXEL / 115
#define ONE_YPIXEL   MAX_YPIXEL / 65
#define ONE_XPER   (float)ONE_XPIXEL / (float)MAX_XPIXEL
#define ONE_YPER   (float)ONE_YPIXEL / (float)MAX_YPIXEL

// 윈도우 시작점, 사이즈
#define WINSTARTX -7
#define WINSTARTY -50
#define WINSIZEX  1500	
#define WINSIZEY  900

// 무한대
#define INF 2345102

struct ST_PC_VERTEXT
{
	D3DXVECTOR3	p;
	D3DCOLOR	c;
	enum { FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE };
};

struct ST_PT_VERTEXT
{
	D3DXVECTOR3	p;
	D3DXVECTOR2	t;
	enum { FVF = D3DFVF_XYZ | D3DFVF_TEX1 };
};

struct ST_PNT_VERTEXT
{
	D3DXVECTOR3	p;
	D3DXVECTOR3	n;
	D3DXVECTOR2	t;
	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 };
};

struct ST_POS_SAMPLE
{
	int			nFrame;
	D3DXVECTOR3	v;

	ST_POS_SAMPLE()
		: nFrame(0)
		, v(0, 0, 0)
	{
	}
};

struct ST_ROT_SAMPLE
{
	int				nFrame;
	D3DXQUATERNION	q;

	ST_ROT_SAMPLE()
		: nFrame(0)
	{
		D3DXQuaternionIdentity(&q);
	}
};

struct NODE
{
	int   nIndex;
	float fCost;
};

struct ST_SPHERE
{
	float		fRadius;
	D3DXVECTOR3	vCenter;
	bool		isPicked;

	ST_SPHERE()
		: fRadius(0.0f), vCenter(0, 0, 0), isPicked(false)
	{
	}
};

struct ST_SPHERE_NODE
{
	LPD3DXMESH		pMesh;
	D3DXMATRIXA16	matWrold;
	D3DXMATRIXA16	matTrans;
	D3DXVECTOR3		vCenter;
	bool			isSelected;

	bool			isVisit;
	vector<NODE>	vecLink;		// 연결된 노드들
};

struct ST_COST
{
	float		fCost;
	int			nViaIndex;
};

struct ST_BOX
{
	LPD3DXMESH		pMesh;
	D3DXMATRIXA16	matWorld;		// 월드
	D3DXMATRIXA16	matScal;		// 스케일링
	D3DXMATRIXA16	matRotY;		// 로테이션 Y
	D3DXMATRIXA16	matTrans;		// 트랜스 레이션
	D3DXVECTOR3		vScaling;		// 스케일링 값
	float			fAngleY;		// 로테이션 Y값
	D3DXVECTOR3		vPosition;		// 위치 값
};

enum eFontType
{
	FT_DEFAULT,
	FT_QUEST,
};

enum CAMMODE
{
	BASE, WORLD
};

enum OBJECTKIND
{
	GATE_01,
	WALL_01, WALL_02, WALL_03, WALL_04, WALL_05,
	FOUNTAIN, 
	ROCK_00, ROCK_04, ROCK_05,
	OBJNUM
};

struct ST_UI_SIZE
{
	int nWidth;
	int nHeight;

	ST_UI_SIZE() : nWidth(0), nHeight(0) { }
	ST_UI_SIZE(int _nWidth, int _nHeight) : nWidth(_nWidth), nHeight(_nHeight) { }
};

#include "cCamera.h"
#include "cObject.h"
#include "cGameObject.h"
#include "cObjectManager.h"
#include "cDeviceManager.h"
#include "cTimeManager.h"
#include "cTextureManager.h"
#include "cFontManager.h"
#include "cKeyManager.h"
#include "cMtlTex.h"
#include "cXFileManager.h"
#include "cFireEffect.h"

typedef struct tagObject
{
	int				nKind;			// 종류
	LPD3DXMESH		pMesh;			// 매쉬
	string			sFileName;		// 파일 이름
	D3DXMATRIXA16	matWorld;		// 월드
	D3DXMATRIXA16	matScal;		// 스케일링
	D3DXMATRIXA16	matRotY;		// 로테이션 Y
	D3DXMATRIXA16	matTrans;		// 트랜스 레이션
	D3DXVECTOR3		vScaling;		// 스케일링 값
	float			fAngleY;		// 로테이션 Y값
	D3DXVECTOR3		vPosition;		// 위치 값
	vector<cMtlTex*>	vecMtlTex;
	ST_SPHERE		sSphere;		// 스페어
} OBJECT;