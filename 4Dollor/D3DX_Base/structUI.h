#pragma once

enum UIBUTTONSTATE	// 버튼 상태
{
	UIBUTTONSTATE_NORMAL, UIBUTTONSTATE_OVER, UIBUTTONSTATE_SELECT, UIBUTTONSTATE_DISENABLE
};

enum UIBUTTONCALLBACK	// 버튼 기능
{
	UIBUTTONCALLBACK_MAIN,
	UIBUTTONCALLBACK_MAIN_HEROINFO_EQUIP, UIBUTTONCALLBACK_MAIN_HEROINFO_ABILITY, UIBUTTONCALLBACK_MAIN_HEROINFO_TALENT,
	UIBUTTONCALLBACK_MAIN_HEROSELECT_HERO, UIBUTTONCALLBACK_MAIN_HEROSELECT_ROLE, UIBUTTONCALLBACK_MAIN_HEROSELECT_GAME,
	UIBUTTONCALLBACK_MAIN_READY = 50,
	UIBUTTONCALLBACK_INGAME = 100,
	UIBUTTONCALLBACK_INGAME_SKILL1, UIBUTTONCALLBACK_INGAME_SKILL2, UIBUTTONCALLBACK_INGAME_SKILL3, UIBUTTONCALLBACK_INGAME_SKILL4,
	UIBUTTONCALLBACK_INGAME_HOME = 150,
	UIBUTTONCALLBACK_LOADING1 = 1000,
	UIBUTTONCALLBACK_LOADING2
};

struct tagUISprite
{
	bool BG;
	D3DXVECTOR3 pt;				// 좌표
	RECT drawRc;				// 그릴 영역 rect
	LPD3DXSPRITE sprite;
	D3DXIMAGE_INFO imgInfo;
	LPDIRECT3DTEXTURE9 texture;
	string parent;				// 부모가 될 indexName 넣음
	D3DXMATRIXA16 matWorld;
};

struct tagUISpriteButton	// 버튼을 걍 따로 나눠 놓음
{
	D3DXVECTOR3 pt;				// 좌표
	RECT drawRc;				// 그릴 영역 rect
	bool selected;				// 버튼이 선택된 상태일 경우 true. 버튼 클릭 이미지를 항상 표현할 때 사용
	int buttonState;			// 버튼 상태. normal, over, click
	LPD3DXSPRITE sprite;
	D3DXIMAGE_INFO imgInfo;
	LPDIRECT3DTEXTURE9 texture[4];
	string parent;				// 부모가 될 indexName 넣음
	D3DXMATRIXA16 matWorld;
	int buttonFunc;
};

struct tagUISpriteLoadData
{
	bool BG;
	D3DXVECTOR3 pt;
	string indexName;
	bool button;
	int buttonFunc;
	string file[4];
};