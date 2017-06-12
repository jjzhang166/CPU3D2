#pragma once
#include "c3d.h"


class c3dCube
{
public:
	c3dCube(){
		data[0] = vec4( 1, 1, 1, 1);
		data[1] = vec4( 1,-1, 1, 1);
		data[2] = vec4(-1, 1, 1, 1);
		data[3] = vec4(-1,-1, 1, 1);
		data[4] = vec4( 1, 1,-1,-1);
		data[5] = vec4( 1,-1,-1,-1);
		data[6] = vec4(-1, 1,-1,-1);
		data[7] = vec4(-1,-1,-1,-1);
	}
	bool SetScale(float f)
	{
		if (f==0)
		{
			return false;
		}
		for (int i= 0; i < 8; ++i)
		{
			data[i].w = f;
		}
		return true;
	};

	vec4 data[8];
};