#pragma once
#include "c3d.h"
class c3dCameara
{
public:
	c3dCameara(void);
	~c3dCameara(void);
	vec3 pos;		//眼睛位置
	vec3 dir;	//眼睛方向	
	vec3 upDir;	//头部方向

	float ration;	//宽高比
	float fnear;	//近景 远   景
	float ffar;
};

