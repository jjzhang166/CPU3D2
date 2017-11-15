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
	vec4 ToVec4()
	{
		vec4 vec;
		vec.r = r;
		vec.g = g;
		vec.b = b;
		vec.a = a;
		return vec;
	}
	static c3dColor From(vec4 vec)
	{
		c3dColor clr;
		clr.r = vec.r;
		clr.g = vec.g;
		clr.b = vec.b;
		clr.a = vec.a;
		return clr;
	}
public:
	const static c3dColor White;
	const static c3dColor Green;
	const static c3dColor Red;
	const static c3dColor Blue;
	const static c3dColor Gray;
};
struct c3dTexCoord : public vec4
{
	//float s, t, p, q;	//一般只要前两个；q默认为1
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
	c3dVertex() {};
	~c3dVertex() {};
	vec4 normal;	//法线
	vec4 pos;		//位置
	union {
		c3dColor color;
		c3dTexCoord tex;
	};
	//m 0到1
	static c3dVertex lerp(const c3dVertex& v1,const c3dVertex& v2, float m, bool bColorEnable = true)
	{
		c3dVertex v;
		v.pos = glm::lerp<float>(v1.pos, v2.pos, m);
		v.normal = glm::lerp(v1.normal, v2.normal, m);
		if (bColorEnable)
		{
			vec4 clrv1, clrv2, clrv;
			clrv1 = v1.color.ToVec4();
			clrv2 = v2.color.ToVec4();

			clrv = glm::lerp(clrv1, clrv2, m);
			v.color = c3dColor::From(clrv);
		}
		else
		{
			vec4 tex = glm::lerp(v1.tex, v2.tex, m);
			v.tex.s = tex.s;
			v.tex.t = tex.t;
			v.tex.p = tex.p;
			v.tex.q = tex.q;
		}
	}
};