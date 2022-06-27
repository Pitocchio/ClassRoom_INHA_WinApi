#include "ObjectManager.h"

ObjectManager* ObjectManager::m_ObjMgr = nullptr;
// 스태틱 멤버 변수는 반드시 초기화를 해주어야 함! (프로그램 생성과 동시에 초기화를 해주는데 값이 없다면 오류)

ObjectManager::ObjectManager()
{
	m_ObjMap.insert({ CIRCLE, m_CircleList });
	m_ObjMap.insert({ SQUARE, m_SquareList });
	m_ObjMap.insert({ STAR, m_StarList });	
}

ObjectManager::~ObjectManager()
{

}

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

void ObjectManager::Update() // General Update
{
	for (int i = 0; i < TYPEEND; ++i)
	{
		for (list<Geometry*>::iterator it = m_ObjMap.find((OBJECT_TYPE)i)->second.begin(); it != m_ObjMap.find((OBJECT_TYPE)i)->second.end(); ++it)
		{
			(*it)->Move(); // Position Update
		}
	}
}

void ObjectManager::LateUpdate() // Detect Collision
{
	// CollisionManager 호출해서 충돌 감지 진행
	// 1. CollisionManager 클래스에 충돌 감지 메소드 작성
	// 2. 호출시 Objmng.GetInstance
}

void ObjectManager::FixedUpdate() // Process Collision
{
	// CollisionManager 호출해서 충돌 처리 지행 
}

void ObjectManager::Render(HDC hdc)
{
	for (list<Geometry*>::iterator it = m_CircleList.begin(); it != m_CircleList.end(); ++it)
	{
		(*it)->Render(hdc);
	}
}

void ObjectManager::Create_Circle(POINT pos)
{
	Circle* t = new Circle(pos, 10, 30);

	cout << "Create New Circle_Object!\n\n";

	m_CircleList.push_back(t);

}
