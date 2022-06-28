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
	for (list<Geometry*>::iterator it = m_CircleList.begin(); it != m_CircleList.end(); ++it)
	{
		(*it)->Move(); // Position Update
	}
}

void ObjectManager::LateUpdate(RECT rc) // Detect Collision
{
	// CollisionManager ȣ���ؼ� �浹 ���� ����
	// 1. CollisionManager Ŭ������ �浹 ���� �޼ҵ� �ۼ�, ������Ʈ �Ŵ��� ���� ������ �� �ִ� GET�Լ� �ۼ�
	// 2. ȣ��� Objmng.GetInstance
	
	// ���浹 üũ�ؼ� �����ǰ����� �ٲ���
	for (list<Geometry*>::iterator it = m_CircleList.begin(); it != m_CircleList.end(); ++it)
	{
		(*it)->CheckCollisionWall(rc); 
	}

	// ������Ʈ������ �浹�� �˻��ؼ� �浹�� ��� �浹 bool �� ���� or �浹ü ����
	for (list<Geometry*>::iterator it1 = m_CircleList.begin(); it1 != m_CircleList.end(); ++it1)
	{
		for (list<Geometry*>::iterator it2 = m_CircleList.begin(); it2 != m_CircleList.end(); ++it2)
		{
			if (*it1 == *it2)
				continue;

			double m = sqrt(pow(((*it2)->Get_Pos().x - (*it1)->Get_Pos().x), 2) + pow(((*it2)->Get_Pos().y - (*it1)->Get_Pos().y), 2));

			if (dynamic_cast<Circle*>(*it1)->Get_Radius() * 2 > m)
			{
				double s = (dynamic_cast<Circle*>(*it1)->Get_Radius() * 2) - m;

				// ��ģ �Ÿ���ŭ ����
				(*it1)->Set_Pos((*it1)->Get_Pos().x - (s / 2.0), (*it1)->Get_Pos().y - (s / 2.0));
				(*it2)->Set_Pos((*it2)->Get_Pos().x + (s / 2.0), (*it2)->Get_Pos().y + (s / 2.0));

				// ������ �ޱ��� �ٲ���
				double temp_theta = (*it1)->Get_Theta();
				(*it1)->Set_Theta((*it2)->Get_Theta());
				(*it2)->Set_Theta(temp_theta);

				/*POINT temp = (*it1)->Get_Pos();
				(*it1)->Set_Pos((*it2)->Get_Pos());
				(*it2)->Set_Pos(temp);*/
			}
		}
	}
}

void ObjectManager::FixedUpdate() // Process Collision
{
	// CollisionManager ȣ���ؼ� �浹 ó�� ���� 

	for (list<Geometry*>::iterator it = m_CircleList.begin(); it != m_CircleList.end(); ++it)
	{
		// Circle* ptr = dynamic_cast<Circle*>(*it);

		int x, y = 0;
		if ((*it)->Peak_IsCollision()) // �浹ü�� ������ NULL�� �ƴ϶��
		{
			// �浹ó��

			// 1. �� �� ������ �Ÿ�
			double m = sqrt(pow((dynamic_cast<Circle*>(*it)->Get_CollisionObj()->Get_Pos().x - dynamic_cast<Circle*>(*it)->Get_Pos().x), 2) +
							pow((dynamic_cast<Circle*>(*it)->Get_CollisionObj()->Get_Pos().y - dynamic_cast<Circle*>(*it)->Get_Pos().y), 2));

			// 2. ��ġ�� ��ŭ�� ���� (������ * 2 - �� �� ������ �Ÿ�)
			double s = (dynamic_cast<Circle*>(*it)->Get_Radius() * 2) - m;

			x = dynamic_cast<Circle*>(*it)->Get_Pos().x + (((dynamic_cast<Circle*>(*it)->Get_CollisionObj()->Get_Pos().x - dynamic_cast<Circle*>(*it)->Get_Pos().x) / m) * s);
		    y = dynamic_cast<Circle*>(*it)->Get_Pos().y + (((dynamic_cast<Circle*>(*it)->Get_CollisionObj()->Get_Pos().y - dynamic_cast<Circle*>(*it)->Get_Pos().y) / m) * s);

			dynamic_cast<Circle*>(*it)->Set_Pos(x, y);

			cout << "�浹 ó��!\n\n";

			(*it)->Reset_CollisionObj(); // �浹ü ���� �ʱ�ȭ
		}
	}
}

void ObjectManager::Render(HDC hdc)
{
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



// ���� ���, �׷��� ���ư��� ����
	//for (int i = 0; i < TYPEEND; ++i)
	//{
	//	for (list<Geometry*>::iterator it = m_ObjMap.find((OBJECT_TYPE)i)->second.begin(); it != m_ObjMap.find((OBJECT_TYPE)i)->second.end(); ++it)
	//	{
	//		(*it)->Move(); // Position Update
	//		cout << "ObjectManager Update!\n\n";
	//	}
	//}