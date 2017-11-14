#include "c3dRender.h"

c3dRender::c3dRender(const c3dDevice* pDev)
{
	if (pDev == nullptr)
	{
		c3dLog::WriteErrorLog(Nullptr);
	}
	pDevice = pDev;
	renderMode = RenderMode::Color;
	fillMode = FillMode::LINE;
}

void c3dRender::RenderVertex(c3dVertex& p)
{

}

void c3dRender::RenderLine(c3dVertex& p1, c3dVertex& p2)
{

}

void c3dRender::RenderTriagle(c3dVertex& p1, c3dVertex& p2, c3dVertex& p3)
{

}


