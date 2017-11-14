#pragma once
#include "c3d.h"
class c3dDevice
{
public:
	static c3dDevice CreateDevice(int width, int height)
	{
		static c3dDevice inst(width, height);
		return inst;
	}
	c3dRender* GetRender();
	c3dTextureManager* GetTextureMgr();
private:
	c3dDevice(int width, int height);
	~c3dDevice();
	map<int, c3dFrameBuffer*> frameBuffer;
	c3dTextureManager* textureMgr;
	c3dRender* render;
	friend c3dDevice;
};