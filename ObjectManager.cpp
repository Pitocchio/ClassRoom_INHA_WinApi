#include "ObjectManager.h"

ObjectManager* ObjectManager::m_ObjMgr = nullptr;
// ����ƽ ��� ������ �ݵ�� �ʱ�ȭ�� ���־�� ��! (���α׷� ������ ���ÿ� �ʱ�ȭ�� ���ִµ� ���� ���ٸ� ����)

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
	// CollisionManager ȣ���ؼ� �浹 ���� ����
	// 1. CollisionManager Ŭ������ �浹 ���� �޼ҵ� �ۼ�
	// 2. ȣ��� Objmng.GetInstance
}

void ObjectManager::FixedUpdate() // Process Collision
{
	// CollisionManager ȣ���ؼ� �浹 ó�� ���� 
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
