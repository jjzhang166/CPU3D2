#include"c3dDevice.h"
#include "c3dRender.h"
#include "c3dTexture.h"
#include "c3dFrameBuffer.h"
c3dRender* c3dDevice::GetRender()
{
	return render;
}

c3dTextureManager* c3dDevice::GetTextureMgr()
{
	return textureMgr;
}

c3dDevice::c3dDevice(int width, int height)
{
	if (width < 0 || height < 0 || width > 4096 || height > 4096)
	{
		c3dLog::WriteErrorLog(InvalidSize);
		c3dLog::WriteLog(c3dLog::Warn, "已经调整到合理的大小");
		width = 640;
		height = 480;
	}
	render = new c3dRender(this);
	textureMgr =  new c3dTextureManager(this);
	frameBuffer[0] = new c3dFrameBuffer();
	frameBuffer[0]->Allocate(width, height);
	
}

c3dDevice::~c3dDevice()
{
	if (render != nullptr)
	{
		delete render;
		render = nullptr;
	}
	if (textureMgr != nullptr)
	{
		delete textureMgr;
		textureMgr = nullptr;
	}
}
