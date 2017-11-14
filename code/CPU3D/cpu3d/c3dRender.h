#pragma once
#include "c3d.h"
//绘画的三种状态 线模式，颜色模式，纹理模式
enum RenderMode
{
	Color,
	Texture
};
enum FillMode
{
	LINE,
	Fill
};
enum ProjectionMode	//暂时不用
{
	ModelProjection,	//正交投影
	OrthoProjection		//模型投影
};
class c3dRender
{
public:
	RenderMode renderMode;
	FillMode fillMode;
	//这个是最基本的类型，三角形为填充面。
	void RenderVertex(c3dVertex& p);
	void RenderLine(c3dVertex& p1, c3dVertex& p2);
	void RenderTriagle(c3dVertex& p1, c3dVertex& p2, c3dVertex& p3);
private:
	c3dRender(const c3dDevice* pDev);
	const c3dDevice* pDevice;
	friend c3dDevice;
};
