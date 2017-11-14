#pragma once
#include "IPainter.h"
class c3dPainter : public IPainter
{
public:
	c3dPainter(void);
	~c3dPainter(void);
	virtual void DrawPoint(int x,int y);
	virtual void DrawRect(int x,int y,int w,int h);
	virtual void DrawLine(int px1,int py1,int px2,int py2);
	virtual void DrawScanLine();

};

