#pragma once

// �� UI�� �� Ŭ������ ��� �޴´�.

#include "structUI.h"

class cUIObject
{
protected:
	// map�� �Ⱦ��� �迭�̳� vector�� �ᵵ ��� ���� �� ����.
	// �迭�� ��� �� ���Ͽ��� �Ľ� �� resize �����ɷ� �޸� ũ�⸦ ���Ҵ� ����� ��
	map<string, tagUISprite> m_MUISprite;		// �Ϲ� �̹���
	map<string, tagUISprite>::iterator m_MUISpriteIt;		// �Ϲ� �̹��� �ݺ���
	map<string, tagUISprite> m_MUISpriteBG;		// �Ϲ� �̹��� �� ���. ����� ���� ���� ������ �ؾߵǹǷ� ���� �з�
	map<string, tagUISprite>::iterator m_MUISpriteBGIt;		// �Ϲ� �̹��� �� ��� �ݺ���

	map<string, tagUISpriteButton> m_MUIButton;	// ��ư
	map<string, tagUISpriteButton>::iterator m_MUIButtonIt;	// ��ư �ݺ���

	float m_CollisionRectReduce;	// Rect�� �̹��� ũ�⺸�� �۰� �ؾ� �̻ڰ�  ��. �װ��� ���� ������ ������ ����
	float m_UIScale;	// UI ��ü ũ�⸦ ����. ���� �̹������� �׿� ���� �ʹ� ŭ.

public:
	cUIObject();
	~cUIObject();

	void AddSprite(tagUISpriteLoadData &spriteData);
	

	// �Ʒ� ���δ� virtual �ٿ��� ��.
	virtual void setup(string WhereIsClass);	// ���θ޴��� mainmenu, �ΰ����̸� ingame���� �Է�
												// �߰� �� ���̺� ���� ������ ��
	virtual void update();
	virtual void updateButton();
	virtual void updateMatWorld(D3DXMATRIXA16 &matWorld, D3DXVECTOR3 pt);
	virtual void updateCollisionRect(RECT &rc, D3DXIMAGE_INFO imgInfo, D3DXVECTOR3 pt);
	virtual void updateButtonState(D3DXIMAGE_INFO imgInfo, D3DXVECTOR3 pt, int &buttonState, UIBUTTONCALLBACK buttonFunc);
	virtual void updateButtonOverCallback(UIBUTTONCALLBACK num) = 0;
	virtual void updateButtonCallback(UIBUTTONCALLBACK num) = 0;
	virtual void render();
	virtual void renderBG();
	virtual void renderButton();
	virtual void renderNormal();
	// setupHide�� ���ص� �ɰ� ����. ��¥�� scene�� ��ȯ�Ǹ� update, render�� �������� �����Ƿ�..
};