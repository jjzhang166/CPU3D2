#pragma once
#include "c3dVertex.h"
/*
FrameBuffer专门用来实现RTT功能的。所以这里需要zBuffer.
*/
class c3dFrameBuffer 
{
public:
	c3dFrameBuffer() :bInited(false),bUseZbuffer(true) {}
	~c3dFrameBuffer() { Release(); }
	bool Allocate(int width, int height, const c3dColor& color = c3dColor::Gray)
	{
		if (width <= 0 || height <= 0 || width > 4096 || height > 4096)
		{
			c3dLog::WriteErrorLog(InvalidSize);
			return false;
		}
		if (bInited)
		{
			c3dLog::WriteErrorLog(InvalidInit);
			return false;
		}
		size = width * height;
		frameBuffer = new unsigned char[4 * size];
		zBuffer = new unsigned char[size];
		for (int nIndex = 0; nIndex < size; nIndex++)
		{
			frameBuffer[nIndex] = color.r;
			frameBuffer[nIndex+1] = color.g;
			frameBuffer[nIndex+2] = color.b;
			frameBuffer[nIndex+3] = color.a;
			zBuffer[nIndex] = 1;	//默认深度值
		}
		return true;
	}

	void Release()
	{
		if (bInited)
		{
			if (frameBuffer != nullptr)
			{
				delete frameBuffer;
				frameBuffer = nullptr;
			}
			if (zBuffer != nullptr)
			{
				delete zBuffer;
				zBuffer = nullptr;
			}

		}
	}

	long GetSize() const { return size; }
private:
	unsigned char* frameBuffer;	//rgba
	unsigned char* zBuffer;
	bool bUseZbuffer;
	long size;
	bool bInited;

};