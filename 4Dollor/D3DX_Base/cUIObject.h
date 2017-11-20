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

	// sprite �߰�
	void AddSprite(tagUISpriteLoadData &spriteData);
	
	/*
	UI���� �������� ����ϴ� ��ɵ��� ��� �����Լ��� ����.
	�� �߿��� ���� ó���ؾ� �� ���� ���� �����Լ��� ����.
	����� �Ϸ��� �Լ��� �� �� ����ȭ �� �ʿ䰡 ������,
	�Ϻδ� ���� �����Լ��� ó���ϴ� ���� ����.
	*/

	// ������ �Ľ�
	virtual void setup(string className);
	// ������Ʈ �׷�
	virtual void update();
	// ��ư ��� ������Ʈ �׷�
	virtual void updateButton();
	// Draw�� �ʿ��� World Matrix ���. D3DXMatrixAffineTransformation2D �̰� ���� �Լ� �Ƚᵵ ��.
	virtual void updateMatWorld(D3DXMATRIXA16 &matWorld, D3DXVECTOR3 pt);
	// ��ư �浹�� �ʿ��� Rect ���. ũ�� ����(m_UIScale) �������� Rect ũ�� �������
	virtual void updateCollisionRect(RECT &rc, D3DXIMAGE_INFO imgInfo, D3DXVECTOR3 pt);
	// ��ư ��� ���� ���� üũ (��ư�� ���� üũ). ���� �ڵ�� ���� ������
	virtual void updateButtonState(D3DXIMAGE_INFO imgInfo, D3DXVECTOR3 pt, int &buttonState, int buttonFunc);
	// ���� �����Լ��� �ݹ�. ���콺 ���� �� ����� �����ϱ� ����. �� ������ �ٸ� ����� �����ؾ��ϹǷ� ������ �ʿ�(���������Լ�)
	virtual int updateButtonOverCallback(int num) = 0;
	// ���� �����Լ��� �ݹ�. ���콺 Ŭ�� �� ��� ����
	virtual int updateButtonCallback(int num) = 0;
	// ���� �׷�
	virtual void render();
	// BG ����. ���� ���� ����� �ϹǷ� ���� ������
	virtual void renderBG();
	// ��ư ����
	virtual void renderButton();
	// �� �� �Ϲ� �̹����� ����
	virtual void renderNormal();
	// ��-��
	virtual void destroy();
};