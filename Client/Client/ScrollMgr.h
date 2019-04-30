#pragma once
class CScrollMgr
{
public:
	CScrollMgr();
	~CScrollMgr();
public:
	static float Get_ScrollX() { return m_fScrollX; }
	static void Sum_ScrollX(float x) { m_fScrollX += x; }
		
	static float Get_ScrollY() { return m_fScrollY; }
	static void Sum_ScrollY(float y) { m_fScrollY += y; }

	static void ScrollLock();

private:
	static float m_fScrollX;
	static float m_fScrollY;
};

