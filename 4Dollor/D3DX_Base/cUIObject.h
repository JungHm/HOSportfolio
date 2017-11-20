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

public:
	cUIObject();
	~cUIObject();

	// sprite 추가
	void AddSprite(tagUISpriteLoadData &spriteData);
	
	/*
	UI에서 공통으로 사용하는 기능들을 묶어서 가상함수로 선언.
	그 중에서 따로 처리해야 될 것은 순수 가상함수로 선언.
	제대로 하려면 함수를 좀 더 세분화 할 필요가 있으며,
	일부는 순수 가상함수로 처리하는 것이 좋음.
	*/

	// 데이터 파싱
	virtual void setup(string className);
	// 업데이트 그룹
	virtual void update();
	// 버튼 기능 업데이트 그룹
	virtual void updateButton();
	// Draw에 필요한 World Matrix 계산. D3DXMatrixAffineTransformation2D 이거 쓰면 함수 안써도 됨.
	virtual void updateMatWorld(D3DXMATRIXA16 &matWorld, D3DXVECTOR3 pt);
	// 버튼 충돌에 필요한 Rect 계산. 크기 비율(m_UIScale) 기준으로 Rect 크기 계산해줌
	virtual void updateCollisionRect(RECT &rc, D3DXIMAGE_INFO imgInfo, D3DXVECTOR3 pt);
	// 버튼 기능 실행 여부 체크 (버튼의 상태 체크). 수업 코드와 거의 동일함
	virtual void updateButtonState(D3DXIMAGE_INFO imgInfo, D3DXVECTOR3 pt, int &buttonState, int buttonFunc);
	// 순수 가상함수로 콜백. 마우스 오버 시 기능을 실행하기 위함. 각 씬별로 다른 기능을 실행해야하므로 재정의 필요(순수가상함수)
	virtual int updateButtonOverCallback(int num) = 0;
	// 순수 가상함수로 콜백. 마우스 클릭 시 기능 실행
	virtual int updateButtonCallback(int num) = 0;
	// 랜더 그룹
	virtual void render();
	// BG 랜더. 제일 먼저 해줘야 하므로 따로 빼놓음
	virtual void renderBG();
	// 버튼 랜더
	virtual void renderButton();
	// 그 외 일반 이미지들 랜더
	virtual void renderNormal();
	// 해-제
	virtual void destroy();
};