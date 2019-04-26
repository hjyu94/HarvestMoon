#pragma once
class CObj
{
public:
	CObj();
	virtual ~CObj();
public:
	const INFO& Get_Info()const { return m_tInfo; }
	const RECT& Get_Rect()const { return m_tRect; }

public:
	virtual void Initialize() =0;
	virtual int  Update() =0;
	virtual void LateUpdate()= 0;
	virtual void Render(HDC hDC) = 0;
	virtual void Release() = 0;

public:
	void Set_Pos(float fx, float fy) 
	{
		m_tInfo.fX = fx; 
		m_tInfo.fY = fy; 
	}
	void Set_Angle(float fAngle) { m_fAngle = fAngle; }
	void Set_Dead() { m_bIsDead = true; }
	void Set_Target(CObj* pTarget) { m_pTarget = pTarget; }

public:
	void UpdateRect(); 
	void FrameMove();
	virtual void LateInit(); 

protected:
	INFO m_tInfo; 
	RECT m_tRect; 
	FRAME m_tFrame; 
	float m_fSpeed; 
	float m_fAngle; 
	bool m_bIsDead;
	CObj* m_pTarget; 
	bool m_bIsInit; 
};

