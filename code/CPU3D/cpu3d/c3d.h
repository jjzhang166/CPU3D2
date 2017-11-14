#pragma once

#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include <iostream>
#include <windows.h>
#include <wchar.h>
#include <tchar.h>
#include <string>
#include <map>

using namespace glm;
using namespace std;
//
const double pi = 3.1415926f;

typedef std::string c3dString;
//string必须放到log之前
#include "c3dLog.h"

#include "c3dVertex.h"
class c3dRender;
class c3dDevice;
class c3dFrameBuffer;
class c3dTextureManager;