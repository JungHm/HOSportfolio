// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once
// 콘솔 창 사용
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
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

// 네임 스페이스
using namespace std;

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
#define MAX_XPIXEL   1187
#define MAX_YPIXEL   601
#define ONE_XPIXEL   MAX_XPIXEL / 160
#define ONE_YPIXEL   MAX_YPIXEL / 80
#define ONE_XPER   (float)ONE_XPIXEL / (float)MAX_XPIXEL
#define ONE_YPER   (float)ONE_YPIXEL / (float)MAX_YPIXEL

// 윈도우 시작점, 사이즈
#define WINSTARTX 300
#define WINSTARTY 100
#define WINSIZEX  1500	
#define WINSIZEY  900

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

enum eFontType
{
	FT_DEFAULT,
	FT_QUEST,
};

enum CAMMODE
{
	BASE, IN_GAME, WORLD
};

#include "cObject.h"
#include "cGameObject.h"
#include "cObjectManager.h"
#include "cDeviceManager.h"
#include "cTimeManager.h"
#include "cTextureManager.h"
#include "cFontManager.h"
#include "cKeyManager.h"
#include "cCamera.h"