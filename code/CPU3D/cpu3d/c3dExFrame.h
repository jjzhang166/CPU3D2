#pragma once
//这里是否使用一个绘图机制
#include "c3d.h"
#include "c3dCamera.h"
#include "c3dTexture.h"
#include "c3dShapes.h"
class c3dExFrame
{
public:
	static c3dExFrame& GetInstance()
	{
		static c3dExFrame frame;
		return frame;
	}
	c3dExFrame();
	~c3dExFrame();
	int c3dInit();
	void c3dUpdate();
	void c3dDraw();
	void c3dLookAt(mat4x4& m,vec4& eyePos,vec4& at,vec4& up);
	//鼠标键盘机制
	void c3dKeyPressed(int key);
	void c3dKeyUp(int key);
	void c3dMouseDown(int button,int x,int y);
	void c3dMouseUp(int button,int x,int y);
	void c3dMouseMove(int button,int x,int y);
	void perspective(mat4x4& m, float fovy, float aspect, float zn, float zf);
	void dispatch();
private:
	void c3dDeviceSetTexture( void *bits, long pitch, int w, int h );
	void c3dSetIdentity(mat4x4& m);
	void c3dSetZero(mat4x4& m);
	void c3dToScreenCoord(vec2&,vec4&);
	void close();
	
	void apply(vec4& y,vec4& x,mat4x4& m);
private:
	c3dCamera cam;	//相机
	vec2 screen;
	mat4x4	mview;	//模型矩阵
	mat4x4  mworld;	//世界矩阵
	mat4x4 project;	//投影矩阵
	mat4x4 transform;
	HDC sHdc;		//临时
	HBITMAP hbitmap;		//
	HBITMAP screen_ob;		//
	unsigned char *screen_fb;	//framebuffer
	HWND hwnd;
	long screen_pitch;

	unsigned int **texture;          // 纹理：同样是每行索引
	int tex_width;              // 纹理宽度
	int tex_height;             // 纹理高度
	float max_u;
	float max_v;
	int renderState;
	int screenw ;
	int screenh ;
	//---------------------
	c3dTexture tex;

	bool skey[512];

	vec2 lastPoint;

	//关于正方体 的一个些几何体
	c3dCube cube;
	bool bMouseDown;
};
static LRESULT screen_events(HWND hWnd, UINT msg, 
							 WPARAM wParam, LPARAM lParam) ;