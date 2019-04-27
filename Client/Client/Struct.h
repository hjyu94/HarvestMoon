#pragma once
typedef struct tagInfo
{
	// 객체의 좌표. 
	float fX; 
	float fY; 
	// 객체의 크기 
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
	int iFrameStart_X;// 시작 지점. 
	int iFrameEnd_X; // 끝점
	int iFrameStart_Y; // // y 즉, 상태값. 
	DWORD dwFrameSpeed; //재생 속도. 
	DWORD dwFrameTime; // 시간값. 

}FRAME;