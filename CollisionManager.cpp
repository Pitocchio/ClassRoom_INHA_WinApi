#include "CollisionManager.h"

CollisionManager* CollisionManager::m_ColMgr = nullptr;

CollisionManager::CollisionManager()
{

}

CollisionManager::~CollisionManager()
{

}

CollisionManager* CollisionManager::GetInstance()
{
	if (!m_ColMgr)
		m_ColMgr = new CollisionManager;
	return m_ColMgr;
}

void CollisionManager::DestroyInstance()
{
	delete m_ColMgr;
}

void CollisionManager::Detect_Collision() 
{
	// ��ü ����Ʈ ���鼭 �浹�˻��ϰ�, ���� �浹�� ���� �Ǿ��ٸ� �ش� ��ü�� �浹 �÷��׸� true�� ����
	// �浹�˻��Լ�(�浹����, ��üŸ��1, ��üŸ��2) => ��ü Ÿ�� 1�� 2�� �浹���� ���� ���� �浹�� �˻��� 

	// 1. �� �浹 �˻�

	// 2. ������Ʈ �浹 �˻�


	//for (OBJ_MAP::iterator mapiter = m_ObjMap.begin(); mapiter != m_ObjMap.end(); ++mapiter) // OBJLIST
	//{
	//	for (LIST_GEO::iterator iter = mapiter->second.begin(); iter != mapiter->second.end(); ++iter) // GEOLIST
	//	{
	//		(*iter)->CheckCollisionWall(rc);
	//	}
	//}
	ObjectManager::GetInstance()->Get_Map();

	for ()

	
}

void CollisionManager::Process_Collision() 
{
	// ��ü ���鼭 �浹 �÷��� ture�� ���� ó���ϰ� �ٽ� false�� �ʱ�ȭ
}
