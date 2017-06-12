#include "c3dTexture.h"

void c3dTexture::Init(int w,int h)
{
	if ( w <= 0 || h <= 0)
	{
		return;
	}
	texw = w;
	texh = h;
	data = new unsigned char[w * h * 4];
	memset(data,0,w*h*4 * sizeof(unsigned char));
}
//暂时颜色为白色，后面会补充
void c3dTexture::DrawLine(vec2& p1,vec2& p2)
{
	//从bug判断这里是 画线的方式沿着 x坐标来画，当y值变化比较大的时候
	//导致画线不连续，所以这里从根据X递增或者根据y递增是要判断的
	vec2 k = p2 - p1;		
	vec2 kAbs = glm::abs(k);
	bool bLoopedByY = false;
	kAbs.y > kAbs.x ? bLoopedByY = true : bLoopedByY =  false;
	//判断两点坐标是否和法，其实这里 暂时没想到更好的解决办法，
	//因为裁剪 应该是视锥裁剪
	/*if (p1.x >= texw || p2.x >= texw || p1.y >= texh || p2.y >= texh)
	{
	return;
	}*/
	//下面处理的这一块有问题需要修正， 不能改变画线的斜率
	/*if ( p1.x > texw ) p1.x = texw;
	if ( p1.y > texh ) p1.y = texh;
	if ( p2.x > texw ) p2.x = texw;
	if ( p2.y > texh ) p2.y = texh;

	if ( p1.x < 0 ) p1.x = 0;
	if ( p1.y < 0 ) p1.y = 0;
	if ( p2.x < 0 ) p2.x = 0;
	if ( p2.y < 0 ) p2.y = 0;*/



	//这里应该根据 是否沿着Y坐标画线来决定 而且要从做往右
	vec2 srcPoint,dstPoint;
	float stepX = 0;
	float stepY = 0;
	if (bLoopedByY)
	{
		if( p1.y < p2.y )
		{
			srcPoint = p1;
			dstPoint = p2;
		}
		else{
			srcPoint = p2;
			dstPoint = p1;
		}
		float step = k.x / k.y;	//这里要注意，为每走一步Y，x所走的距离 x要转化为整数
		stepX = srcPoint.x;
		for (int y = srcPoint.y; y < dstPoint.y; ++y)
		{
			stepX += step;
			stepY = y;
			int spos = GetPos(stepX, stepY) * 4;
			if (spos > 0 && spos < texw * texh * 4 -3)
			{
				if (spos < texw * texh * 4 -3)
				{
					data[ spos ] = 0xFF;
					data[ spos + 1 ] = 0x00;	//g
					data[ spos + 2 ] = 0x00;	//b
					data[ spos + 3 ] = 0xFF;	//a
				}
			}
		}
	}else{
		//这里是沿着x坐标画线
		if( p1.x < p2.x )
		{
			srcPoint = p1;
			dstPoint = p2;
		}
		else{
			srcPoint = p2;
			dstPoint = p1;
		}
		float step = k.y / k.x;	//这里要注意，为每走一步Y，x所走的距离 x要转化为整数
		stepY = srcPoint.y;
		for (int x = srcPoint.x; x < dstPoint.x; ++x)
		{
			stepY += step;
			stepX = x;
			int spos = GetPos(stepX, stepY) * 4;
			if (spos > 0 && spos < texw * texh * 4 -3)
			{
				data[ spos ] = 0xFF;
				data[ spos + 1 ] = 0xFF;	//g
				data[ spos + 2 ] = 0xFF;	//b
				data[ spos + 3 ] = 0xFF;	//a
			}
		}

	}
}

void c3dTexture::DrawTriangle(vec2& p1,vec2&p2,vec2& p3)
{
	//smoothstep(p1,p2,p3);
	//目前按照点线的方式吧
	DrawLine(p1, p2);
	DrawLine(p2, p3);
	DrawLine(p1, p3);
}

unsigned char* c3dTexture::GetData()
{
	return data;
}

vec2 c3dTexture::GetPos(int p)
{
	int y = p / texw;
	int x = p % texw;
	return vec2(x,y);
}

int c3dTexture::GetPos(vec2 pos)
{
	if (pos.y < 1)
	{
		return pos.x;
	}
	int m = (pos.y - 1) *texw + pos.x;
	return m;
}

int c3dTexture::GetPos(int x,int y)
{
	if (x < 0 || y < 0)
	{
		//获取的位置有越界
		//assert(x < 0);
		return 0;
	}
	if (y < 1)
	{
		return x;
	}
	int m = (y - 1) *texw + x;
	return m;
}

void c3dTexture::DrawDebug(vec2& p1,vec2&p2)
{
#ifdef _DEBUG
	for (int i = 0; i < texw * texh*4; ++i)
	{
		//data[i] = i % 255 ;
	}
#endif // _DEBUG


}

void c3dTexture::Clear()
{
	memset(data,0,4 * texw * texh * sizeof(unsigned char));
}
