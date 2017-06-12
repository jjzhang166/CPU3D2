#include "c3dExFrame.h"

static LRESULT screen_events(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
	case WM_KEYUP: 
		c3dExFrame::GetInstance().c3dKeyUp(wParam);
		break;
	case  WM_KEYDOWN:
		c3dExFrame::GetInstance().c3dKeyPressed(wParam);
		break;
	case WM_LBUTTONDOWN:
		c3dExFrame::GetInstance().c3dMouseDown(0,0,0);
		break;
	case WM_LBUTTONUP:
		c3dExFrame::GetInstance().c3dMouseUp(0,0,0);
		break;
	case  WM_MOUSEMOVE:
		c3dExFrame::GetInstance().c3dMouseMove(0, 0, 0);
		break;
	case WM_PAINT:
		c3dExFrame::GetInstance().c3dDraw();
		c3dExFrame::GetInstance().c3dUpdate();
		break;
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		//	MessageBox(NULL, _T("我要关闭了"),_T("关闭提示:"),MB_OK);
		break;
	//case  WM_SIZE:
	//	AfxMessageBox("")
	//	break;
	default: 
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}

int c3dExFrame::c3dInit()
{
	screenw = 1200;
	screenh = 800;
	tex.Init(screenw, screenh);
	TCHAR title[] = _T("c3d frame");
	cam.ration = screenw / screenh;

	WNDCLASS wc = { CS_BYTEALIGNCLIENT, (WNDPROC)screen_events, 0, 0, 0, 
		NULL, NULL, NULL, NULL, _T("SCREEN3.1415926") };
	BITMAPINFO bi = { { sizeof(BITMAPINFOHEADER), screenw, -screenh, 1, 32, BI_RGB, 
		screenw * screenh * 4, 0, 0, 0, 0 }  };

	RECT rect = {0,0,screenw,screenh};
	int wx, wy, sx, sy;
	LPVOID ptr;
	HDC hDC;
	close();

	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.hInstance = GetModuleHandle(NULL);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	if (!RegisterClass(&wc)) return -1;

	hwnd = CreateWindow(_T("SCREEN3.1415926"), title,
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		0, 0, 0, 0, NULL, NULL, wc.hInstance, NULL);
	if (hwnd == NULL) return -2;
	hDC = GetDC(hwnd);
	sHdc = CreateCompatibleDC(hDC);
	ReleaseDC(hwnd, hDC);

	hbitmap = CreateDIBSection(sHdc, &bi, DIB_RGB_COLORS, &ptr, 0, 0);
	if (hbitmap == NULL) return -3;

	screen_ob = (HBITMAP)SelectObject(sHdc, hbitmap);
	screen_fb = (unsigned char*)ptr;
	screen_pitch = screenw * 4;

	AdjustWindowRect(&rect, GetWindowLong(hwnd, GWL_STYLE), 0);
	wx = rect.right - rect.left;
	wy = rect.bottom - rect.top;
	sx = (GetSystemMetrics(SM_CXSCREEN) - wx) / 2;
	sy = (GetSystemMetrics(SM_CYSCREEN) - wy) / 2;
	if (sy < 0) sy = 0;
	SetWindowPos(hwnd , NULL, sx, sy, wx, wy, (SWP_NOCOPYBITS | SWP_NOZORDER | SWP_SHOWWINDOW));
	SetForegroundWindow(hwnd);

	ShowWindow(hwnd, SW_NORMAL);
	UpdateWindow(hwnd);

	memset(screen_fb, 0,screenw * screenh * 4);
	vec4 eye = vec4( 0, 0, 2, 1 );
	vec4 at = vec4 (0, 0, 0, 1 );
	vec4 up = vec4 ( 0, 1, 0, 1 );
	c3dLookAt(mview,eye,at,up);
	transform = mworld * mview * project;
	perspective(transform,0,screenw/screenh,0,20);
	//c3dDraw();
	mview = glm::scale(mview,vec3(10, 10, 10));
	return 0;
}

void c3dExFrame::c3dUpdate()
{
	//transform = mworld * mview * project;
	/*CPaintDC cdc();*/
	HDC hDC = GetDC(hwnd);
	BitBlt(hDC, 0, 0, screenw, screenh, sHdc, 0, 0, SRCCOPY);
	ReleaseDC(hwnd, hDC);
}
float f = 0.005f;
void c3dExFrame::c3dDraw()
{
	tex.Clear();
	mview = glm::rotate(mview, f, glm::vec3(0, 0.001, 0.001)); 
	transform = mworld * mview * project;
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			if ( i != j )
			{
				vec4 v1,v2;
				vec4 ina,inb;
				vec2 out1,out2;
				//ina =  vec4(glm::rotateY(glm::vec3(cube.data[i]),1.0f), f);
				//inb =  vec4(glm::rotateY(glm::vec3(cube.data[j]),1.0f), f);
				ina = cube.data[i];
				inb = cube.data[j];
				apply( v1, ina, transform);
				apply( v2, inb, transform);
				c3dToScreenCoord(out1, v1);
				c3dToScreenCoord(out2, v2);
				tex.DrawLine(out1, out2);
			}
		}

	}

	vec2 lastPos;
	POINT p;
	GetCursorPos(&p);

	unsigned char * data = tex.GetData();
	int size = tex.GetSize();
	memcpy(screen_fb,data, size * 4 * sizeof(unsigned char));
}

void c3dExFrame::c3dKeyPressed(int key)
{

	skey[ key & 511] = true;

	char ch = key;
	switch (ch)
	{
	case 'A':
		MessageBox(hwnd, _T("hello"),_T("a:"),MB_OK);
		break;
	case 'D':
		MessageBox(hwnd, _T("hello"),_T("d:"),MB_OK);
		break;
	default:
		break;
	}

}

void c3dExFrame::c3dSetIdentity(mat4x4& m)
{
	m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1.0f; 
	m[0][1] = m[0][2] = m[0][3] = 0.0f;
	m[1][0] = m[1][2] = m[1][3] = 0.0f;
	m[2][0] = m[2][1] = m[2][3] = 0.0f;
	m[3][0] = m[3][1] = m[3][2] = 0.0f;
}

void c3dExFrame::c3dLookAt(mat4x4& m,vec4& eye,vec4& at,vec4& up)
{
	vec3 xaxis, yaxis;
	vec3 zaxis;
	vec4 z = at - eye;
	zaxis = vec3(z);
	normalize(zaxis);
	xaxis = cross(vec3(up),zaxis);
	normalize(xaxis);
	yaxis = cross(zaxis,xaxis);

	m[0][0] = xaxis.x;
	m[1][0] = xaxis.y;
	m[2][0] = xaxis.z;
	m[3][0] = -1 * dot(xaxis,vec3(eye));
	// m[3][0] = -vector_dotproduct(&xaxis, eye);
	m[0][1] = yaxis.x;
	m[1][1] = yaxis.y;
	m[2][1] = yaxis.z;
	m[3][1] = -1 * dot(yaxis,vec3(eye));
	//	 m[3][1] = -vector_dotproduct(&yaxis, eye);
	m[0][2] = zaxis.x;
	m[1][2] = zaxis.y;
	m[2][2] = zaxis.z;
	m[3][2] = dot(zaxis,vec3(eye));
	//	 m[3][2] = -vector_dotproduct(&zaxis, eye);
	m[0][3] =  m[1][3] =  m[2][3] = 0.0f;
	m[3][3] = 1.0f;
}

void c3dExFrame::perspective(mat4x4& m, float fovy, float aspect, float zn, float zf)
{
	float fax = 1.0f / (float)tan(fovy * 0.5f);

	c3dSetZero(m);
	m[0][0] = (float)(fax / aspect);
	m[1][1] = (float)(fax);
	m[2][2] = zf / (zf - zn);
	m[3][2] = - zn * zf / (zf - zn);
	m[2][3] = 1;
}

void c3dExFrame::c3dSetZero(mat4x4& m)
{
	m[0][0] =  m[0][1] =  m[0][2] =  m[0][3] = 0.0f;
	m[1][0] =  m[1][1] =  m[1][2] =  m[1][3] = 0.0f;
	m[2][0] =  m[2][1] =  m[2][2] =  m[2][3] = 0.0f;
	m[3][0] =  m[3][1] =  m[3][2] =  m[3][3] = 0.0f;
	transform = mworld * mview * project;
}


void c3dExFrame::close()
{
	if (sHdc) {
		if (sHdc) { 
			SelectObject(sHdc, hbitmap); 
			hbitmap = NULL; 
		}
		DeleteDC(sHdc);
		hbitmap = NULL;
	}
	if (hbitmap) { 
		DeleteObject(hbitmap); 
		hbitmap = NULL; 
	}
	if (hbitmap) { 
		CloseWindow(hwnd); 
		hwnd = NULL; 
	}
}

void c3dExFrame::dispatch()
{
	MSG msg;

	while (GetMessage (&msg, NULL, 0, 0))       
	{       
		TranslateMessage (&msg) ;       
		DispatchMessage (&msg) ;    
		
	}      
	/*while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		c3dDraw();
		c3dUpdate();
	}*/

}

c3dExFrame::c3dExFrame()
{
	this->c3dInit();
}

c3dExFrame::~c3dExFrame()
{

}

void c3dExFrame::c3dDeviceSetTexture( void *bits, long pitch, int w, int h)
{
	// 设置当前纹理
	char *ptr = (char*)bits;
	int j;
	assert(w <= 1024 && h <= 1024);
	for (j = 0; j < h; ptr += pitch, j++) 	// 重新计算每行纹理的指针
		texture[j] = (unsigned int *)ptr;
	tex_width = w;
	tex_height = h;
	max_u = (float)(w - 1);
	max_v = (float)(h - 1);
}

void c3dExFrame::apply(vec4& y,vec4& x,mat4x4& m)
{
	float X = x.x, Y = x.y, Z = x.z, W = x.w;
	y.x = X * m[0][0] + Y * m[1][0] + Z * m[2][0] + W * m[3][0];
	y.y = X * m[0][1] + Y * m[1][1] + Z * m[2][1] + W * m[3][1];
	y.z = X * m[0][2] + Y * m[1][2] + Z * m[2][2] + W * m[3][2];
	y.w = X * m[0][3] + Y * m[1][3] + Z * m[2][3] + W * m[3][3];
}

void c3dExFrame::c3dKeyUp(int key)
{
	skey[ key & 511] = false;
}

void c3dExFrame::c3dMouseDown(int button,int x,int y)
{
	POINT p;
	GetCursorPos(&p);
	ScreenToClient(hwnd,&p);
	lastPoint.x = p.x;
	lastPoint.y = p.y;
	bMouseDown = true;
}

void c3dExFrame::c3dMouseUp(int button,int x,int y)
{
	bMouseDown = false;
	POINT p;
	GetCursorPos(&p);
	ScreenToClient(hwnd,&p);
	vec2 final = vec2(p.x,p.y);
#if _DEBUG
	cout<<lastPoint.x<<","<<lastPoint.y<<")("<<final.x<<","<<final.y<<endl;
#endif // _DEBUG


	tex.DrawLine(lastPoint,final);
}

void c3dExFrame::c3dToScreenCoord(vec2& out,vec4& in)
{
	out.x = in.x + 0.5 * screenw;
	out.y = in.y + 0.5 * screenh;
}

void c3dExFrame::c3dMouseMove(int button,int x,int y)
{
	if (bMouseDown)
	{
	//	f += 0.000f;
	}
}
