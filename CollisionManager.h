#pragma once
#include "ObjectManager.h"

class CollisionManager
{
private: // SingleTone_Methods
	CollisionManager();
	~CollisionManager();

public: // SingleTone_Variables
	static CollisionManager* GetInstance();
	static void DestroyInstance();

public: // method 
	void Detect_Collision(); // ��ü ����Ʈ ���鼭 �浹�˻��ϰ�, ���� �浹�� ���� �Ǿ��ٸ� �ش� ��ü�� �浹 �÷��׸� true�� ����
							 // �浹�˻��Լ�(�浹����, ��üŸ��1, ��üŸ��2) => ��ü Ÿ�� 1�� 2�� �浹���� ���� ���� �浹�� �˻��� 

	void Process_Collision(); // ��ü ���鼭 �浹 �÷��� ture�� ���� ó���ϰ� �ٽ� false�� �ʱ�ȭ


private: //Variables
	static CollisionManager* m_ColMgr;


};


/*
Update / LateUpdate / FixedUpdate ���� CollisionManager�� �浹 ���� �Լ��� ȣ��

�׸��� ȣ��� ������Ʈ �Ŵ����� ���ڷ� �Ѱ���


1. ���� 

2. �浹 ����
	if (�� ���� ���� ������ �Ÿ� <= �� ���� �������� ��)
		�浹 �߻�

3. �浹 ó��

*/