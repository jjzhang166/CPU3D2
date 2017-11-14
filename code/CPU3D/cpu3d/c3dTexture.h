#pragma once
#include "c3d.h"


/*
纹理的绘制功能实质上是2d的绘图。
在render里面会有一份实现，这里只做
简单实现先保留部分功能。
*/
class c3dTexture
{
public:
	c3dTexture() {}
	~c3dTexture() {}
	bool Allocate(int width, int height,const c3dColor& color=c3dColor::White);
	bool LoadFromImage(c3dString fileName);
	void Release();
	//2d
	void DrawLine(vec2& p1, vec2& p2);	//直接画到像素缓冲区
	void DrawTriangle(vec2& p1, vec2&p2, vec2& p3); //画三角形
	void DrawDebug(vec2& p1, vec2&p2); //画三角形
	//aabb 方式实现
	void DrawTriangleFill(vec2& p1, vec2&p2, vec2& p3);
	//绘制扫描线
	void DrawScanLine(vec2& p1, int w);

	unsigned char* GetData();
	vec2 GetPos(int p);
	int GetPos(vec2 pos);
	int GetPos(int x, int y);
	int GetSize() { return texw* texh; };
	void Clear();
private:
	unsigned char *data;
	int texw, texh;
	bool bInit;
};
class c3dTextureManager
{
public:
	void Switch(int nTexIndex);
	bool Add(int nTexIndex, c3dTexture& tex);
	bool Remove(int nTexIndex);
	c3dTexture* GetCurrentTexture();
	int GetCurrentIndex() const { return nCurrentIndex; }
private:
	std::map<int, c3dTexture*> data;
	int nCurrentIndex;

	c3dTextureManager(const c3dDevice* pDev);
	const c3dDevice* pDevice;
	friend c3dDevice;
};