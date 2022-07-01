#include "ObjectManager.h"

ObjectManager* ObjectManager::m_ObjMgr = nullptr;
// ����ƽ ��� ������ �ݵ�� �ʱ�ȭ�� ���־�� ��! (���α׷� ������ ���ÿ� �ʱ�ȭ�� ���ִµ� ���� ���ٸ� ����)

ObjectManager::ObjectManager() {}

ObjectManager::~ObjectManager() {}

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

void ObjectManager::Initialize()
{
	/*for (int i = 0; (OBJECT_TYPE)i < OBJECT_TYPEEND; ++i)
	{
		LIST_GEO temp;
		m_ObjMap.insert({ (OBJECT_TYPE)i , temp });
	}*/

	/*
	���� ����� �ƿ� �ʿ� ����Ʈ�� ENUM��ŭ �Ҵ��صΰ� ����, �� ���� ����Ʈ�� ��Ұ� ���� �ʾҴ��� ������Ʈ������ ���ʿ��ϰ� ������ for������ ��ȯ��
	�׷��� �Ʒ� ����� ����Ʈ�� ��Ұ� ���� �ʾҴٸ� �� �� �ʿ� ����Ʈ�� �Ҵ�, �� ����Ʈ�� 0�̴ϱ� ����Ʈ�� ��Ұ� ���ٸ� ����Ʈ�� ���� ���� (�ξ� ȿ����, but �������� ���� ��)
	*/
}
 
void ObjectManager::Update() // General Update
{
	//map�� key�� ����(first �Ƚᵵ OK)
	for (OBJ_MAP::iterator mapiter = m_ObjMap.begin(); mapiter != m_ObjMap.end(); ++mapiter) // OBJLIST
	{
		//map�� value(����Ʈ)�� ����
		for (LIST_GEO::iterator iter = mapiter->second.begin(); iter != mapiter->second.end(); ++iter) // GEOLIST
		{
			(*iter)->Move();
		}
	}
}

void ObjectManager::LateUpdate(RECT rc) // Detect Collision
{	
	/*
	CollisionManager ȣ���ؼ� �浹 ���� ����
	1. CollisionManager Ŭ������ �浹 ���� �޼ҵ� �ۼ�, ������Ʈ �Ŵ��� ���� ������ �� �ִ� GET�Լ� �ۼ�
	2. ȣ��� Objmng.GetInstance
	*/

	// ���浹 üũ�ؼ� �����ǰ����� �ٲ���
	/*for (int i = 0; (OBJECT_TYPE)i < OBJECT_TYPEEND; ++i)
	{
		OBJ_MAP::iterator iter_map = m_ObjMap.find((OBJECT_TYPE)i);

		if (iter_map == m_ObjMap.end())
			continue;

		for (LIST_GEO::iterator iter_lst = iter_map->second.begin(); iter_lst != iter_map->second.end(); ++iter_lst)
		{
			(*iter_lst)->CheckCollisionWall(rc);
		}
	}*/ // ������ �ڵ� (�ٸ� ������ ������ ���)
	for (OBJ_MAP::iterator mapiter = m_ObjMap.begin(); mapiter != m_ObjMap.end(); ++mapiter) // OBJLIST
	{
		for (LIST_GEO::iterator iter = mapiter->second.begin(); iter != mapiter->second.end(); ++iter) // GEOLIST
		{
			(*iter)->CheckCollisionWall(rc);
		}
	}

	//// ������Ʈ������ �浹�� �˻��ؼ� �浹�� ��� �浹 bool �� ���� or �浹ü ����
	//for (list<Geometry*>::iterator it1 = m_CircleList.begin(); it1 != m_CircleList.end(); ++it1)
	//{
	//	for (list<Geometry*>::iterator it2 = m_CircleList.begin(); it2 != m_CircleList.end(); ++it2)
	//	{
	//		if (*it1 == *it2)
	//			continue;

	//		double m = sqrt(pow(((*it2)->Get_Pos().x - (*it1)->Get_Pos().x), 2) + pow(((*it2)->Get_Pos().y - (*it1)->Get_Pos().y), 2));

	//		if (dynamic_cast<Circle*>(*it1)->Get_Radius() * 2 > m)
	//		{
	//			cout << "�浹ó�� ����!\n";
	//			double s = (dynamic_cast<Circle*>(*it1)->Get_Radius() * 2) - m;

	//			// ��ģ �Ÿ���ŭ ����
	//			(*it1)->Set_Pos((*it1)->Get_Pos().x - (s / 2.0), (*it1)->Get_Pos().y - (s / 2.0));
	//			(*it2)->Set_Pos((*it2)->Get_Pos().x + (s / 2.0), (*it2)->Get_Pos().y + (s / 2.0));

	//			// ���⺤�� ��ȯ
	//			Vector2 temp = (*it1)->Get_LookVec();
	//			(*it1)->Set_Lookvec((*it2)->Get_LookVec());
	//			(*it2)->Set_Lookvec(temp);
	//			cout << "�浹ó�� ����!\n\n\n";
	//			
	//		}
	//	}
	//}
}

//void ObjectManager::FixedUpdate() // Process Collision
//{
//	// CollisionManager ȣ���ؼ� �浹 ó�� ���� 
//
//	for (list<Geometry*>::iterator it = m_CircleList.begin(); it != m_CircleList.end(); ++it)
//	{
//		// Circle* ptr = dynamic_cast<Circle*>(*it);
//
//		int x, y = 0;
//		if ((*it)->Peak_IsCollision()) // �浹ü�� ������ NULL�� �ƴ϶��
//		{
//			// �浹ó��
//
//			// 1. �� �� ������ �Ÿ�
//			double m = sqrt(pow((dynamic_cast<Circle*>(*it)->Get_CollisionObj()->Get_Pos().x - dynamic_cast<Circle*>(*it)->Get_Pos().x), 2) +
//							pow((dynamic_cast<Circle*>(*it)->Get_CollisionObj()->Get_Pos().y - dynamic_cast<Circle*>(*it)->Get_Pos().y), 2));
//
//			// 2. ��ġ�� ��ŭ�� ���� (������ * 2 - �� �� ������ �Ÿ�)
//			double s = (dynamic_cast<Circle*>(*it)->Get_Radius() * 2) - m;
//
//			x = dynamic_cast<Circle*>(*it)->Get_Pos().x + (((dynamic_cast<Circle*>(*it)->Get_CollisionObj()->Get_Pos().x - dynamic_cast<Circle*>(*it)->Get_Pos().x) / m) * s);
//		    y = dynamic_cast<Circle*>(*it)->Get_Pos().y + (((dynamic_cast<Circle*>(*it)->Get_CollisionObj()->Get_Pos().y - dynamic_cast<Circle*>(*it)->Get_Pos().y) / m) * s);
//
//			dynamic_cast<Circle*>(*it)->Set_Pos(x, y);
//
//			cout << "�浹 ó��!\n\n";
//
//			(*it)->Reset_CollisionObj(); // �浹ü ���� �ʱ�ȭ
//		}
//	}
//}

void ObjectManager::Render(HDC hdc)
{
	for (OBJ_MAP::iterator mapiter = m_ObjMap.begin(); mapiter != m_ObjMap.end(); ++mapiter) // OBJLIST
	{
		for (LIST_GEO::iterator iter = mapiter->second.begin(); iter != mapiter->second.end(); ++iter) // GEOLIST
		{
			(*iter)->Render(hdc);
		}
	}
}

void ObjectManager::Add_Object(int objtype, Geometry* temp)
{
	if (temp == nullptr)
		return;	// temp�� �������� ����

	OBJ_MAP::iterator iter = m_ObjMap.find((OBJECT_TYPE)objtype);

	//if (iter == m_ObjMap.end())
	//	return; // �ش� Ű���� value�� �������� ����
	 
	
	// �ֻ�� Initialize() �Լ��� ���� ���� but �� ȿ������ ����� �Ʒ� �ּ��ڵ��. ������ �ֻ�� ����
	// �ֻ�� Initialize() ���� �Ϸ��� �� if�� Ȱ��ȭ
	if (iter == m_ObjMap.end())
	{
		LIST_GEO lstTemp;
		lstTemp.push_back(temp);
		m_ObjMap.insert({ (OBJECT_TYPE)objtype , lstTemp });
		return;
	}

	iter->second.push_back(temp);

}

