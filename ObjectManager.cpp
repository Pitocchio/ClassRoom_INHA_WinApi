#include "ObjectManager.h"

ObjectManager* ObjectManager::m_ObjMgr = nullptr;
// 스태틱 멤버 변수는 반드시 초기화를 해주어야 함! (프로그램 생성과 동시에 초기화를 해주는데 값이 없다면 오류)

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
	위의 방식은 아예 맵에 리스트를 ENUM만큼 할당해두고 시작, 즉 아직 리스트에 요소가 들어가지 않았더라도 업데이트에서는 불필요하게 리스를 for문으로 순환함
	그러나 아래 방식은 리스트에 요소가 들어가지 않았다면 그 때 맵에 리스트를 할당, 즉 리스트가 0이니까 리스트에 요소가 없다면 리스트를 돌지 않음 (훨씬 효율적, but 가독성은 위가 승)
	*/
}
 
void ObjectManager::Update() // General Update
{
	//map의 key를 돈다(first 안써도 OK)
	for (OBJ_MAP::iterator mapiter = m_ObjMap.begin(); mapiter != m_ObjMap.end(); ++mapiter) // OBJLIST
	{
		//map의 value(리스트)를 돈다
		for (LIST_GEO::iterator iter = mapiter->second.begin(); iter != mapiter->second.end(); ++iter) // GEOLIST
		{
			(*iter)->Move();
		}
	}
}

void ObjectManager::LateUpdate(RECT rc) // Detect Collision
{	
	/*
	CollisionManager 호출해서 충돌 감지 진행
	1. CollisionManager 클래스에 충돌 감지 메소드 작성, 오브젝트 매니저 정보 가져올 수 있는 GET함수 작성
	2. 호출시 Objmng.GetInstance
	*/

	// 벽충돌 체크해서 포지션값까지 바꿔줌
	/*for (int i = 0; (OBJECT_TYPE)i < OBJECT_TYPEEND; ++i)
	{
		OBJ_MAP::iterator iter_map = m_ObjMap.find((OBJECT_TYPE)i);

		if (iter_map == m_ObjMap.end())
			continue;

		for (LIST_GEO::iterator iter_lst = iter_map->second.begin(); iter_lst != iter_map->second.end(); ++iter_lst)
		{
			(*iter_lst)->CheckCollisionWall(rc);
		}
	}*/ // 용하형 코드 (다른 식으로 돌리는 방법)
	for (OBJ_MAP::iterator mapiter = m_ObjMap.begin(); mapiter != m_ObjMap.end(); ++mapiter) // OBJLIST
	{
		for (LIST_GEO::iterator iter = mapiter->second.begin(); iter != mapiter->second.end(); ++iter) // GEOLIST
		{
			(*iter)->CheckCollisionWall(rc);
		}
	}

	//// 오브젝트끼리의 충돌을 검사해서 충돌인 경우 충돌 bool 값 변경 or 충돌체 저장
	//for (list<Geometry*>::iterator it1 = m_CircleList.begin(); it1 != m_CircleList.end(); ++it1)
	//{
	//	for (list<Geometry*>::iterator it2 = m_CircleList.begin(); it2 != m_CircleList.end(); ++it2)
	//	{
	//		if (*it1 == *it2)
	//			continue;

	//		double m = sqrt(pow(((*it2)->Get_Pos().x - (*it1)->Get_Pos().x), 2) + pow(((*it2)->Get_Pos().y - (*it1)->Get_Pos().y), 2));

	//		if (dynamic_cast<Circle*>(*it1)->Get_Radius() * 2 > m)
	//		{
	//			cout << "충돌처리 시작!\n";
	//			double s = (dynamic_cast<Circle*>(*it1)->Get_Radius() * 2) - m;

	//			// 겹친 거리만큼 빼줌
	//			(*it1)->Set_Pos((*it1)->Get_Pos().x - (s / 2.0), (*it1)->Get_Pos().y - (s / 2.0));
	//			(*it2)->Set_Pos((*it2)->Get_Pos().x + (s / 2.0), (*it2)->Get_Pos().y + (s / 2.0));

	//			// 방향벡터 교환
	//			Vector2 temp = (*it1)->Get_LookVec();
	//			(*it1)->Set_Lookvec((*it2)->Get_LookVec());
	//			(*it2)->Set_Lookvec(temp);
	//			cout << "충돌처리 종료!\n\n\n";
	//			
	//		}
	//	}
	//}
}

//void ObjectManager::FixedUpdate() // Process Collision
//{
//	// CollisionManager 호출해서 충돌 처리 진행 
//
//	for (list<Geometry*>::iterator it = m_CircleList.begin(); it != m_CircleList.end(); ++it)
//	{
//		// Circle* ptr = dynamic_cast<Circle*>(*it);
//
//		int x, y = 0;
//		if ((*it)->Peak_IsCollision()) // 충돌체의 정보가 NULL이 아니라면
//		{
//			// 충돌처리
//
//			// 1. 두 점 사이의 거리
//			double m = sqrt(pow((dynamic_cast<Circle*>(*it)->Get_CollisionObj()->Get_Pos().x - dynamic_cast<Circle*>(*it)->Get_Pos().x), 2) +
//							pow((dynamic_cast<Circle*>(*it)->Get_CollisionObj()->Get_Pos().y - dynamic_cast<Circle*>(*it)->Get_Pos().y), 2));
//
//			// 2. 겹치는 만큼의 길이 (반지름 * 2 - 두 점 사이의 거리)
//			double s = (dynamic_cast<Circle*>(*it)->Get_Radius() * 2) - m;
//
//			x = dynamic_cast<Circle*>(*it)->Get_Pos().x + (((dynamic_cast<Circle*>(*it)->Get_CollisionObj()->Get_Pos().x - dynamic_cast<Circle*>(*it)->Get_Pos().x) / m) * s);
//		    y = dynamic_cast<Circle*>(*it)->Get_Pos().y + (((dynamic_cast<Circle*>(*it)->Get_CollisionObj()->Get_Pos().y - dynamic_cast<Circle*>(*it)->Get_Pos().y) / m) * s);
//
//			dynamic_cast<Circle*>(*it)->Set_Pos(x, y);
//
//			cout << "충돌 처리!\n\n";
//
//			(*it)->Reset_CollisionObj(); // 충돌체 정보 초기화
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
		return;	// temp가 존재하지 않음

	OBJ_MAP::iterator iter = m_ObjMap.find((OBJECT_TYPE)objtype);

	//if (iter == m_ObjMap.end())
	//	return; // 해당 키값의 value가 존재하지 않음
	 
	
	// 최상단 Initialize() 함수와 같은 역할 but 더 효율적인 방법이 아래 주석코드다. 설명은 최상단 참고
	// 최상단 Initialize() 적용 하려면 위 if문 활성화
	if (iter == m_ObjMap.end())
	{
		LIST_GEO lstTemp;
		lstTemp.push_back(temp);
		m_ObjMap.insert({ (OBJECT_TYPE)objtype , lstTemp });
		return;
	}

	iter->second.push_back(temp);

}

