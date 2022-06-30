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
	// 전체 리스트 돌면서 충돌검사하고, 만약 충돌이 감지 되었다면 해당 객체의 충돌 플래그를 true로 세팅
	// 충돌검사함수(충돌종류, 객체타입1, 객체타입2) => 객체 타입 1과 2의 충돌종류 값을 갖고 충돌을 검사함 

	// 1. 벽 충돌 검사

	// 2. 오브젝트 충돌 검사


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
	// 전체 돌면서 충돌 플래그 ture인 것을 처리하고 다시 false로 초기화
}
