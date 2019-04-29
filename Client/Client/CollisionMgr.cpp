#include "stdafx.h"
#include "CollisionMgr.h"
#include "Obj.h"


CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::CollisionRect(OBJLIST & DestList, OBJLIST & SourList)
{
	RECT rc = {}; 
	for (auto& pDst : DestList)
	{
		for (auto& pSrc : SourList)
		{
			if (IntersectRect(&rc,&pDst->Get_Rect(), &pSrc->Get_Rect()))
			{
				pDst->Collision_Proc(pSrc);
				pSrc->Collision_Proc(pDst);
			}
		}
	}
}

void CCollisionMgr::CollisionRectEX(OBJLIST & DestList, OBJLIST & SourList)
{
	float fMoveX = 0.f, fMoveY = 0.f; 
	for (auto& pDst : DestList)
	{
		for (auto& pSrc : SourList)
		{
			if (CheckRect(pDst, pSrc, &fMoveX, &fMoveY))
			{
				float x = pSrc->Get_Info().fX;
				float y = pSrc->Get_Info().fY; 

				if (fMoveX > fMoveY)
				{
					if (y < pDst->Get_Info().fY)
						fMoveY *= -1.f;

					pSrc->Set_Pos(x, y + fMoveY);
				}
				else
				{
					if (x < pDst->Get_Info().fX)
						fMoveX *= -1.f; 

					pSrc->Set_Pos(x + fMoveX, y);
				}
			}
		}
	}

}

void CCollisionMgr::CollisionSphere(OBJLIST & DestList, OBJLIST & SourList)
{
	for (auto& pDst : DestList)
	{
		for (auto& pSrc : SourList)
		{
			if (CheckSphere(pDst, pSrc))
			{
				pDst->Set_Dead();
				pSrc->Set_Dead();
			}
		}
	}
}

bool CCollisionMgr::CheckSphere(CObj * pDest, CObj * pSour)
{

	// 반지름의 합 구하기. 
	float fRadiusSum = (pDest->Get_Info().fCX * 0.5f) + (pSour->Get_Info().fCX * 0.5f);
	// 밑변과 높이 구하기. 
	float fx = pDest->Get_Info().fX - pSour->Get_Info().fX;
	float fy = pDest->Get_Info().fY - pSour->Get_Info().fY;

	// 피타고라스의 정리를 사용하여 거리를 구하기. 
	float fDist = sqrtf(fx * fx + fy * fy); // a^2 + b^2 = fDist;
	//거리와 반지름의 합으로 충돌판정. 
	return fDist <= fRadiusSum;
}

bool CCollisionMgr::CheckRect(CObj * pDest, CObj * pSour, float* pMoveX, float* pMoveY)
{
	// 반지름의 합. 
	float fRadiusSumX = (pDest->Get_Info().fCX * 0.5f) + (pSour->Get_Info().fCX * 0.5f);
	float fRadiusSumY = (pDest->Get_Info().fCY * 0.5f) + (pSour->Get_Info().fCY * 0.5f);

	float fDistX = fabs(pDest->Get_Info().fX - pSour->Get_Info().fX);
	float fDistY = fabs(pDest->Get_Info().fY - pSour->Get_Info().fY); 

	if (fRadiusSumX >= fDistX && fRadiusSumY >= fDistY)
	{
		*pMoveX = fRadiusSumX - fDistX;
		*pMoveY = fRadiusSumY - fDistY;
		return true; 
	}

	return false;
}
