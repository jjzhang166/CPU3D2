#pragma once
#include "IRender.h"
class c3dRender : public IRender
{
public:
	c3dRender(void);
	~c3dRender(void);
	virtual void DrawPoint(int x,int y);
	virtual void DrawRect(int x,int y,int w,int h);
	virtual void DrawLine(int px1,int py1,int px2,int py2);
	virtual void DrawScanLine();

};

