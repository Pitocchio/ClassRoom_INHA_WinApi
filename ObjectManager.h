#pragma once
#include "Geometry_.h"
#include "Circle_.h"
#include "CollisionManager.h"
#include <algorithm>
#include <map>
#include <list>
#include <cmath>
using namespace std;

class ObjectManager
{
public: // Enum
	enum OBJECT_TYPE { CIRCLE, SQUARE, STAR, OBJECT_TYPEEND };

private: // SingleTone_Methods
	ObjectManager();
	~ObjectManager();

public: // SingleTone_Variables
	static ObjectManager* GetInstance();
	static void DestroyInstance();
	
public: // Update
	void Initialize();
	void Update(); 
	void LateUpdate(RECT rc); 
	void FixedUpdate(); 
	void Render(HDC hdc);

public: // Method
	void Add_Object(int objtype, Geometry*); // ������ ��ü�� �˸��� ����Ʈ�� �־���

private: // Variables
	static ObjectManager* m_ObjMgr; // �̱��� ������Ʈ �Ŵ��� ����ƽ ����
	
	typedef list<Geometry*> LIST_GEO; // list<Geometry*> �ڷ����� LIST_GEO��� �̸����� ������ (�� �ڷ����� �̸��� ������, �ڷ��� �̸��� ��ϱ� ª�� ���ϰ� ����)
	typedef map <OBJECT_TYPE, LIST_GEO> OBJ_MAP; // ���� ��������
	OBJ_MAP m_ObjMap;


	/*
	LIST_GEO = GEO_LIST
	OBJ_MAP = OBJ_LIST
	*/
};
