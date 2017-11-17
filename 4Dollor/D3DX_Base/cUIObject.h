#pragma once

// 각 UI는 이 클래스를 상속 받는다.

#include "structUI.h"

class cUIObject
{
protected:
	// map을 안쓰고 배열이나 vector를 써도 상관 없을 것 같음.
	// 배열로 사용 시 파일에서 파싱 후 resize 같은걸로 메모리 크기를 재할당 해줘야 함
	map<string, tagUISprite> m_MUISprite;		// 일반 이미지
	map<string, tagUISprite>::iterator m_MUISpriteIt;		// 일반 이미지 반복자
	map<string, tagUISprite> m_MUISpriteBG;		// 일반 이미지 중 배경. 배경은 제일 먼저 랜더링 해야되므로 따로 분류
	map<string, tagUISprite>::iterator m_MUISpriteBGIt;		// 일반 이미지 중 배경 반복자

	map<string, tagUISpriteButton> m_MUIButton;	// 버튼
	map<string, tagUISpriteButton>::iterator m_MUIButtonIt;	// 버튼 반복자

	float m_CollisionRectReduce;	// Rect를 이미지 크기보다 작게 해야 이쁘게  됨. 그것을 위한 사이즈 조정용 변수
	float m_UIScale;	// UI 전체 크기를 변경. 현재 이미지들이 겜에 비해 너무 큼.
	bool m_DataLoad;

public:
	cUIObject();
	~cUIObject();

	void AddSprite(tagUISpriteLoadData &spriteData);
	

	// 아래 전부다 virtual 붙여야 됨.
	virtual void setup(string className);
	virtual void update();
	virtual void updateButton();
	virtual void updateMatWorld(D3DXMATRIXA16 &matWorld, D3DXVECTOR3 pt);
	virtual void updateCollisionRect(RECT &rc, D3DXIMAGE_INFO imgInfo, D3DXVECTOR3 pt);
	virtual void updateButtonState(D3DXIMAGE_INFO imgInfo, D3DXVECTOR3 pt, int &buttonState, int buttonFunc);
	virtual void updateButtonOverCallback(int num) = 0;
	virtual void updateButtonCallback(int num) = 0;
	virtual void render();
	virtual void renderBG();
	virtual void renderButton();
	virtual void renderNormal();
	virtual void destroy();
	// setupHide는 안해도 될거 같음. 어짜피 scene이 전환되면 update, render를 실행하지 않으므로..
};