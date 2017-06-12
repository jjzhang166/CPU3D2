#include <iostream>
#include "cpu3d/c3dExFrame.h"
#include "cpu3d/c3dApp.h"
#include "cpu3d/c3dWin32Frame.h"
using namespace std;
using namespace glm;
int main()
{
	/*c3dFrame& f = c3dFrame::GetInstance();
	f.dispatch();*/
	c3dWin32Frame app;
	app.setup();
	app.run();
	
	return 0;
}