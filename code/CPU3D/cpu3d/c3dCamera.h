#pragma once
#include "c3d.h"
class c3dCamera
{
public:
	c3dCamera(void);
	~c3dCamera(void);
	vec3 pos;		//眼睛位置
	vec3 dir;	//眼睛方向	
	vec3 upDir;	//头部方向

	float ration;	//宽高比
	float fnear;	//近景 远   景
	float ffar;
};

