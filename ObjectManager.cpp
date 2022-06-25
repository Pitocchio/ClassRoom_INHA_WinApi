#pragma once
#include "Circle_.h"
#include "ObjectManager.h"
#include <vector>
using namespace std;

ObjectManager* ObjectManager::m_ObjMgr = nullptr;
// ����ƽ ��� ������ �ݵ�� �ʱ�ȭ�� ���־�� ��! (���α׷� ������ ���ÿ� �ʱ�ȭ�� ���ִµ� ���� ���ٸ� ����)

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

void ObjectManager::Update() // �Ϲ����� ������Ʈ
{
	for (list<Geometry*>::iterator iter = m_CircleList.begin(); iter != m_CircleList.end(); ++iter)
	{
		(*iter)->Move(); // Position Update
	}
}

void ObjectManager::LateUpdate() // �浹 �˻� 
{

}

void ObjectManager::FixedUpdate() // �浹 ó�� (Ex. �����ֱ�)
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