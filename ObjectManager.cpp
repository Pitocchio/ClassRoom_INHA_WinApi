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
	// ���� ���, �׷��� ���ư��� ����
	//for (int i = 0; i < TYPEEND; ++i)
	//{
	//	for (list<Geometry*>::iterator it = m_ObjMap.find((OBJECT_TYPE)i)->second.begin(); it != m_ObjMap.find((OBJECT_TYPE)i)->second.end(); ++it)
	//	{
	//		(*it)->Move(); // Position Update
	//		cout << "ObjectManager Update!\n\n";
	//	}
	//}

	for (list<Geometry*>::iterator it = m_CircleList.begin(); it != m_CircleList.end(); ++it)
	{
		(*it)->Move(); // Position Update
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
	// ���� ���, �׷��� ���ư��� ����
	/*for (int i = 0; i < TYPEEND; ++i)
	{
		for (list<Geometry*>::iterator it = m_ObjMap.find((OBJECT_TYPE)i)->second.begin(); it != m_ObjMap.find((OBJECT_TYPE)i)->second.end(); ++it)
		{
			(*it)->Render(hdc);
			cout << "ObjectManager Render!\n\n";
		}
	}*/


	for (list<Geometry*>::iterator it = m_CircleList.begin(); it != m_CircleList.end(); ++it)
	{
		(*it)->Render(hdc);
	}

	
}

void ObjectManager::Add_Object(int ObjType, Geometry* temp)
{
	switch (ObjType)
	{
		case 0:
			m_CircleList.push_back(temp);
			break;

		case 1: 
			m_SquareList.push_back(temp);
			break;

		case 2:
			m_StarList.push_back(temp);
			break;

		default :
			NULL;
	}
}

