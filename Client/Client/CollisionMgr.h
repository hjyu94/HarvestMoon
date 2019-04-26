#pragma once
class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();

public:
	static void CollisionRect(OBJLIST& DestList, OBJLIST& SourList);
	static void CollisionRectEX(OBJLIST& DestList, OBJLIST& SourList);
	static void CollisionSphere(OBJLIST& DestList, OBJLIST& SourList);

private:
	static bool CheckSphere(CObj* pDest, CObj* pSour);
	static bool CheckRect(CObj* pDest, CObj* pSour, float* pMoveX, float* pMoveY);
};

