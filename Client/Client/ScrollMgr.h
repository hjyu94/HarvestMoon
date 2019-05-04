#pragma once
class CScrollMgr
{
public:
	CScrollMgr();
	~CScrollMgr();
public:
	static float Get_ScrollX() { return m_iScrollX; }
	static void Sum_ScrollX(float x) { m_iScrollX += x; }
		
	static float Get_ScrollY() { return m_iScrollY; }
	static void Sum_ScrollY(float y) { m_iScrollY += y; }
	
	static void Reset_Scroll() { m_iScrollX = 0; m_iScrollY = 0; }

	static void ScrollLock();

private:
	static int m_iScrollX;
	static int m_iScrollY;
};

