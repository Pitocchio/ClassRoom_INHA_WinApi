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
	for (list<Geometry*>::iterator it = m_CircleList.begin(); it != m_CircleList.end(); ++it)
	{
		(*it)->Move(); // Position Update
	}
}

void ObjectManager::LateUpdate(RECT rc) // Detect Collision
{
	// CollisionManager 호출해서 충돌 감지 진행
	// 1. CollisionManager 클래스에 충돌 감지 메소드 작성, 오브젝트 매니저 정보 가져올 수 있는 GET함수 작성
	// 2. 호출시 Objmng.GetInstance
	
	// 벽충돌 체크해서 포지션값까지 바꿔줌
	for (list<Geometry*>::iterator it = m_CircleList.begin(); it != m_CircleList.end(); ++it)
	{
		(*it)->CheckCollisionWall(rc); 
	}

	// 오브젝트끼리의 충돌을 검사해서 충돌인 경우 충돌 bool 값 변경 or 충돌체 저장
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

				// 겹친 거리만큼 빼줌
				(*it1)->Set_Pos((*it1)->Get_Pos().x - (s / 2.0), (*it1)->Get_Pos().y - (s / 2.0));
				(*it2)->Set_Pos((*it2)->Get_Pos().x + (s / 2.0), (*it2)->Get_Pos().y + (s / 2.0));

				// 서로의 앵글을 바꿔줌
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
	// CollisionManager 호출해서 충돌 처리 진행 

	for (list<Geometry*>::iterator it = m_CircleList.begin(); it != m_CircleList.end(); ++it)
	{
		// Circle* ptr = dynamic_cast<Circle*>(*it);

		int x, y = 0;
		if ((*it)->Peak_IsCollision()) // 충돌체의 정보가 NULL이 아니라면
		{
			// 충돌처리

			// 1. 두 점 사이의 거리
			double m = sqrt(pow((dynamic_cast<Circle*>(*it)->Get_CollisionObj()->Get_Pos().x - dynamic_cast<Circle*>(*it)->Get_Pos().x), 2) +
							pow((dynamic_cast<Circle*>(*it)->Get_CollisionObj()->Get_Pos().y - dynamic_cast<Circle*>(*it)->Get_Pos().y), 2));

			// 2. 겹치는 만큼의 길이 (반지름 * 2 - 두 점 사이의 거리)
			double s = (dynamic_cast<Circle*>(*it)->Get_Radius() * 2) - m;

			x = dynamic_cast<Circle*>(*it)->Get_Pos().x + (((dynamic_cast<Circle*>(*it)->Get_CollisionObj()->Get_Pos().x - dynamic_cast<Circle*>(*it)->Get_Pos().x) / m) * s);
		    y = dynamic_cast<Circle*>(*it)->Get_Pos().y + (((dynamic_cast<Circle*>(*it)->Get_CollisionObj()->Get_Pos().y - dynamic_cast<Circle*>(*it)->Get_Pos().y) / m) * s);

			dynamic_cast<Circle*>(*it)->Set_Pos(x, y);

			cout << "충돌 처리!\n\n";

			(*it)->Reset_CollisionObj(); // 충돌체 정보 초기화
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



// 정석 방법, 그러나 돌아가지 않음
	//for (int i = 0; i < TYPEEND; ++i)
	//{
	//	for (list<Geometry*>::iterator it = m_ObjMap.find((OBJECT_TYPE)i)->second.begin(); it != m_ObjMap.find((OBJECT_TYPE)i)->second.end(); ++it)
	//	{
	//		(*it)->Move(); // Position Update
	//		cout << "ObjectManager Update!\n\n";
	//	}
	//}