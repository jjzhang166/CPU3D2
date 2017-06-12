#pragma once
#include "c3d.h"
#include "c3dTexture.h"
/*
* c3dApp用作入口类，其中c3dFrame的功能尽量都抽取出来，只保留最原始的功能，即把一张纹理渲染到窗口上面
*/
class c3dWin32Frame
{
public:
	c3dWin32Frame();
	~c3dWin32Frame();
	int setup();
	void update();
	void draw();
	void drawFrameBuffer(unsigned char *,unsigned int);
	void run();
	static LRESULT screen_events(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
protected:
	HDC sHdc;		//临时
	HBITMAP hbitmap;		//
	HBITMAP screen_ob;		//
	unsigned char *screen_fb;	//framebuffer
	HWND hwnd;
	long screen_pitch;
	int screenw ;
	int screenh ;
	c3dTexture tex;
public:
	static c3dWin32Frame * pThis;
};