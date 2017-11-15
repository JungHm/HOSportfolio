#pragma once

enum UIBUTTONSTATE	// ��ư ����
{
	UIBUTTONSTATE_NORMAL, UIBUTTONSTATE_OVER, UIBUTTONSTATE_SELECT, UIBUTTONSTATE_DISENABLE
};

enum UIBUTTONCALLBACK	// ��ư ���
{
	UIBUTTONCALLBACK_MAIN,
	UIBUTTONCALLBACK_MAIN_HEROINFO_EQUIP, UIBUTTONCALLBACK_MAIN_HEROINFO_ABILITY, UIBUTTONCALLBACK_MAIN_HEROINFO_TALENT,
	UIBUTTONCALLBACK_MAIN_READY,
	UIBUTTONCALLBACK_MAIN_HEROSELECT_HERO, UIBUTTONCALLBACK_MAIN_HEROSELECT_ROLE, UIBUTTONCALLBACK_MAIN_HEROSELECT_GAME,
	UIBUTTONCALLBACK_INGAME = 100,
	UIBUTTONCALLBACK_INGAME_SKILL1, UIBUTTONCALLBACK_INGAME_SKILL2, UIBUTTONCALLBACK_INGAME_SKILL3, UIBUTTONCALLBACK_INGAME_SKILL4,
	UIBUTTONCALLBACK_INGAME_HOME
};

struct tagUISprite
{
	bool BG;
	D3DXVECTOR3 pt;				// ��ǥ
	RECT drawRc;				// �׸� ���� rect
	LPD3DXSPRITE sprite;
	D3DXIMAGE_INFO imgInfo;
	LPDIRECT3DTEXTURE9 texture;
	string parent;				// �θ� �� indexName ����
	D3DXMATRIXA16 matWorld;
};

struct tagUISpriteButton	// ��ư�� �� ���� ���� ����
{
	D3DXVECTOR3 pt;				// ��ǥ
	RECT drawRc;				// �׸� ���� rect
	bool selected;				// ��ư�� ���õ� ������ ��� true. ��ư Ŭ�� �̹����� �׻� ǥ���� �� ���
	int buttonState;			// ��ư ����. normal, over, click
	LPD3DXSPRITE sprite;
	D3DXIMAGE_INFO imgInfo;
	LPDIRECT3DTEXTURE9 texture[4];
	string parent;				// �θ� �� indexName ����
	D3DXMATRIXA16 matWorld;
	UIBUTTONCALLBACK buttonFunc;
};

struct tagUISpriteLoadData
{
	bool BG;
	D3DXVECTOR3 pt;
	string indexName;
	bool button;
	string file[4];
};