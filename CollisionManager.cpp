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

	
}

void CollisionManager::Process_Collision() 
{
	// ��ü ���鼭 �浹 �÷��� ture�� ���� ó���ϰ� �ٽ� false�� �ʱ�ȭ
}
