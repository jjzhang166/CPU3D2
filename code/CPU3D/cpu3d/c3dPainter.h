#pragma once
#include "c3d.h"
class c3dPainter
{
public:
	c3dPainter(void);
	~c3dPainter(void);
	static c3dPainter GetInstance()
	{
		static c3dPainter painter;
		return painter;
	}
	void SetTargetFrameBuffer(c3dFrameBuffer& fBuffer)
	{
		data = &fBuffer;
		bInited = true;
	}
	 void DrawPoint(c3dVertex v);
	
	 void DrawRect(int x, int y, int w, int h);
	 void DrawLine(int px1, int py1, int px2, int py2);
	 void DrawScanLine(c3dVertex v1,c3dVertex v2);
	 void DrawTriangle(c3dVertex& v0, c3dVertex& v1, c3dVertex& v2);
	 void SplitTriangle(const c3dVertex* pIn, c3dVertex** pOut,int& count);
private:
	c3dFrameBuffer* data;
	bool bInited;

};

