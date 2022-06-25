#pragma once
#include "Circle_.h"
#include "ObjectManager.h"
#include <vector>
using namespace std;

ObjectManager* ObjectManager::m_ObjMgr = nullptr;
// 스태틱 멤버 변수는 반드시 초기화를 해주어야 함! (프로그램 생성과 동시에 초기화를 해주는데 값이 없다면 오류)

ObjectManager* ObjectManager::GetInstance() 
{
	if (!m_ObjMgr)
		m_ObjMgr = new ObjectManager;
	return m_ObjMgr;
}

void ObjectManager::DestroyInstance()
{
	delete m_ObjMgr;
}

void ObjectManager::Update() // 일반적인 업데이트
{
	for (list<Geometry*>::iterator iter = m_CircleList.begin(); iter != m_CircleList.end(); ++iter)
	{
		(*iter)->Move(); // Position Update
	}
}

void ObjectManager::LateUpdate() // 충돌 검사 
{

}

void ObjectManager::FixedUpdate() // 충돌 처리 (Ex. 떼어주기)
{

}

void ObjectManager::Render(HDC hdc)
{
	for (list<Geometry*>::iterator iter = m_CircleList.begin(); iter != m_CircleList.end(); ++iter)
	{
		(*iter)->Render(hdc);
	}
}

void ObjectManager::Create_Circle(POINT pos)
{
	Circle* t = new Circle(pos, 10, 30);

	cout << "Create New Circle_Object!\n\n";

	m_CircleList.push_back(t);

}