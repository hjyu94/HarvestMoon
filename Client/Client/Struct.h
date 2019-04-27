#pragma once
typedef struct tagInfo
{
	// ��ü�� ��ǥ. 
	float fX; 
	float fY; 
	// ��ü�� ũ�� 
	float fCX;
	float fCY;
}INFO;

typedef struct tagLinePos
{
	tagLinePos()
	{
		ZeroMemory(this, sizeof(tagLinePos));
	}
	tagLinePos(float x, float y)
		:fx(x)
		, fy(y)
	{}
	float fx; 
	float fy; 
}LINEPOS;

typedef struct tagLine
{
	tagLine()
	{
		ZeroMemory(this, sizeof(tagLine));
	}
	tagLine(LINEPOS& rLP, LINEPOS& rRP)
		:tLeftPoint(rLP)
		, tRightPoint(rRP)
	{}
	LINEPOS tLeftPoint;
	LINEPOS tRightPoint;
}LINEINFO;

typedef struct tagFrame
{
	int iFrameStart_X;// ���� ����. 
	int iFrameEnd_X; // ����
	int iFrameStart_Y; // // y ��, ���°�. 
	DWORD dwFrameSpeed; //��� �ӵ�. 
	DWORD dwFrameTime; // �ð���. 

}FRAME;