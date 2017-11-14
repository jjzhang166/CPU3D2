#include "c3dApp.h"

static LRESULT screen_events(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
	case WM_KEYUP: 
		
		break;
	case  WM_KEYDOWN:
	
		break;
	case WM_LBUTTONDOWN:
	
		break;
	case WM_LBUTTONUP:
	
		break;
	case  WM_MOUSEMOVE:

		break;
	case WM_PAINT:

		break;
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
			MessageBox(NULL, _T("我要关闭了"),_T("关闭提示:"),MB_OK);
		break;

	default: 
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}
c3dApp::c3dApp()
{

}

c3dApp::~c3dApp()
{

}

int c3dApp::setup()
{
	screenw = 1200;
	screenh = 800;
	tex.Allocate(screenw, screenh);
	TCHAR title[] = _T("c3d app");

	WNDCLASS wc = { CS_BYTEALIGNCLIENT, (WNDPROC)screen_events, 0, 0, 0, 
		NULL, NULL, NULL, NULL, _T("SCREEN3.1415926") };
	BITMAPINFO bi = { { sizeof(BITMAPINFOHEADER), screenw, -screenh, 1, 32, BI_RGB, 
		screenw * screenh * 4, 0, 0, 0, 0 }  };

	RECT rect = {0,0,screenw,screenh};
	int wx, wy, sx, sy;
	LPVOID ptr;
	HDC hDC;
	//close();

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
	return 0;
}

void c3dApp::update()
{
	HDC hDC = GetDC(hwnd);
	BitBlt(hDC, 0, 0, screenw, screenh, sHdc, 0, 0, SRCCOPY);
	ReleaseDC(hwnd, hDC);
}

void c3dApp::draw()
{
	unsigned char * data = tex.GetData();
	int size = tex.GetSize();
	memcpy(screen_fb,data, size * 4 * sizeof(unsigned char));
}

void c3dApp::mousePressed(int button,int x,int y)
{

}

void c3dApp::mouseReleased(int button,int x,int y)
{

}

void c3dApp::keyPressed(int key)
{

}

void c3dApp::keyReleased(int key)
{

}

void c3dApp::dispatch()
{
	MSG msg;

	while (GetMessage (&msg, NULL, 0, 0))       
	{       
		TranslateMessage (&msg) ;       
		DispatchMessage (&msg) ;    
		
	}      
}
