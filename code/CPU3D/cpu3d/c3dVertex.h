#include "c3d.h"

class c3dVertex
{
public:
	c3dVertex(){};
	~c3dVertex(){};
	vec4 normal;	//法线
	vec4 pos;		//位置
	vec4 color;		//颜色
};