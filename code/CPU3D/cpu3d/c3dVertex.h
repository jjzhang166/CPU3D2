#pragma once
#include "c3d.h"
struct c3dColor
{
	unsigned char r, g, b, a;
	c3dColor()
	{
		memset(this, 255, sizeof(this));
	}
	c3dColor(unsigned char rcolor, unsigned char gcolor, unsigned char bcolor)
	{
		r = rcolor; g = gcolor; b = bcolor;
	}
public :
	const static c3dColor White;
	const static c3dColor Green;
	const static c3dColor Red;
	const static c3dColor Blue;
	const static c3dColor Gray;
};
struct c3dTexCoord
{
	float s, t, p, q;	//一般只要前两个；q默认为1
	c3dTexCoord()
	{
		s = t = p = 0;
		q = 1;
	}
};
/* 使用color还是tex 根据状态管理来确定。 */
class c3dVertex
{
public:
	c3dVertex(){};
	~c3dVertex(){};
	vec4 normal;	//法线
	vec4 pos;		//位置
	union {
		c3dColor color;
		c3dTexCoord tex;
	} ;
};