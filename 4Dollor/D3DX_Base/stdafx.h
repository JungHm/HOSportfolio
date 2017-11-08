// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <assert.h>
#include <vector>
#include <list>
#include <set>
#include <map>


// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "libfbxsdk-md.lib")

extern HWND g_hWnd;

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

// PNT
struct ST_PNT_VERTEXT
{
	D3DXVECTOR3	p;
	D3DXVECTOR3	n;
	D3DXVECTOR2	t;
	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 };
};

#include "cKeyManager.h"
#include "cObject.h"
#include "cObjectManager.h"
#include "cDeviceManager.h"
#include "cTimeManager.h"
#include "cTextureManager.h"
#include "cSpriteManager.h"
#include "cCamera.h"
#include "cSceneManager.h"
#include "cFontManager.h"