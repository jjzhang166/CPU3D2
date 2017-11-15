#include "c3dPainter.h"
#include "c3dFrameBuffer.h"

c3dPainter::c3dPainter(void) :bInited(false)
{
}


c3dPainter::~c3dPainter(void)
{
}

void c3dPainter::DrawPoint(c3dVertex v)
{
	if (data == nullptr)
	{
		c3dLog::WriteErrorLog(Nullptr);
	}
	//这里只有位置和颜色 深度信息
	int nIndex = v.pos.x * v.pos.y;
	if (nIndex < 0 || nIndex > data->GetSize()) c3dLog::WriteErrorLog(InvalidSize);
	unsigned char *pFrameBuffer = data->GetFrameBuffer();
	unsigned char *pZBuffer = data->GetZBuffer();
	if (v.pos.z >= pZBuffer[nIndex])
	{
		unsigned char * vp = pFrameBuffer + nIndex * 3;
		vp[0] = v.color.r;
		vp[1] = v.color.g;
		vp[2] = v.color.b;
	}
}

void c3dPainter::DrawRect(int x, int y, int w, int h)
{

}

void c3dPainter::DrawLine(int px1, int py1, int px2, int py2)
{

}
void c3dPainter::DrawScanLine(c3dVertex v1, c3dVertex v2)
{

}
//v1 v2是在一条水平线上 这样能省很多计算
void c3dPainter::DrawTriangle(c3dVertex& v0, c3dVertex& v1, c3dVertex& v2)
{
	//这里对triangle有一个要求 v1 v2 v3 中有一条边是水平的


}

void c3dPainter::SplitTriangle(const c3dVertex* pIn, c3dVertex** pOut, int& count)
{
	if (pIn == nullptr)
	{
		c3dLog::WriteErrorLog(Nullptr);
		return;
	}
	const c3dVertex& vi0 = pIn[0];
	const c3dVertex& vi1 = pIn[1];
	const c3dVertex& vi2 = pIn[2];

	c3dVertex vt0, vt1, vt2;
	//特殊情况 0 1 2 中有2个点纵坐标相等
	if (vi0.pos.y == vi1.pos.y || vi1.pos.y == vi2.pos.y || vi2.pos.y == vt0.pos.y)
	{
		count = 1;
		*pOut[0] = vi0;
		*pOut[1] = vi1;
		*pOut[2] = vi2;
	}

	//这里是按水平扫描

	c3dVertex splitVer = vi0;

	int top, bottom;
	int nTopIndex, nMiddleIndex, nBottomIndex;
	c3dVertex vMiddleInter;
	top = max(max(vi0.pos.y, vi1.pos.y), vi2.pos.y);
	bottom = min(min(vi0.pos.y, vi1.pos.y), vi2.pos.y);
	for (int i = 0; i < 2; i++)
	{
		if (pIn[i].pos.y == top)
		{
			nTopIndex = i;
		}
		if (pIn[i].pos.y == bottom)
		{
			nBottomIndex = i;
		}
	}
	nMiddleIndex = 0 + 1 + 2 - nTopIndex - nBottomIndex;	//这个他们的id总和是一定的，不多解释 反正他们几个肯定是0 1 2不重样

	//glm::intersectLineTriangle()
	//middle top bottom的交点
	float v = (pIn[nMiddleIndex].pos.y - bottom) / (float)(bottom - top);
	vMiddleInter = c3dVertex::lerp(pIn[nTopIndex], pIn[nBottomIndex],v);
	pOut[0][0] = pIn[nTopIndex];
	pOut[1][0] = pIn[nBottomIndex];
	pOut[0][1] = pOut[1][1] = pIn[nMiddleIndex];
	pOut[0][2] = pOut[1][2] = vMiddleInter;
	count = 2;
}
