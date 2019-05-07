#pragma once
class CLine
{
public:
	CLine();
	CLine(LINEINFO& rLineInfo);
	~CLine();
public:
	LINEINFO& Get_LineInfo() { return m_tInfo; }
public:
	void Render(HDC hDC);
	void Set_LineInfo(LINEPOS& rRightPoint) { m_tInfo.tRightPoint = rRightPoint; }
	void Set_LineInfo(LINEPOS& rLeftPoint, LINEPOS& rRightPoint) 
	{
		m_tInfo.tLeftPoint = rLeftPoint;
		m_tInfo.tRightPoint = rRightPoint;
	}

private:
	LINEINFO m_tInfo; 
};

