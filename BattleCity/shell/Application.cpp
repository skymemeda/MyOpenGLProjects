#include "Application.h"
#include <assert.h>
#include <PhBase/Archive.h>
#include <windows.h>
#include <gl/gl3w.h>
#include <gl/GL.h>
#include <graphics/RenderPass.h>
#include <res/TexPool.h>
#include <render/GUIRender.h>
#include <render/UIWidget.h>
#include <render/Glypher.h>
#include "GameManager.h"
typedef ph::GUIRender Render;
Render* render;
GameManager *gameManager = nullptr;

Application::Application()
{    
} 
 
Application::~Application()
{    
}

void Application::Start(void* _hwnd)
{
	view = ph::ViewOGL::CreateView(_hwnd);
	char fullpath[256];
	GetModuleFileNameA(NULL, fullpath, 256);
	char * ptr = &fullpath[strlen(fullpath) - 1];

	while (*(--ptr) != '\\') {}

	std::string rootdir;
	rootdir.assign(&fullpath[0], ptr + 1);
	rootdir.append("/asset/");
	ph::Archive * arch = ph::GetDefArchive();
	arch->Init(rootdir.c_str());
	ph::TexPool::InitTexPool(arch);

	render = ph::GUIRender::GetInstance(arch);
	GameManager::initGameManager(render);
	gameManager = new GameManager();
}

void Application::OnResize( int _w, int _h )
{
    if( _w < 2)
    {
        _w = 2;
    }
    if( _h < 2)
    {
        _h = 2;
    }

	_w = (_w >> 1) << 1;
	_h = (_h >> 1) << 1;

	view->Resize(_w, _h);
	ph::GUIRender::GUIViewport(_w, _h);
	gameManager->update();
}

void Application::End()
{
    view->Release();
}   

#ifndef M_PI
#define M_PI		3.14159265358979323846
#endif

void Application::OnRender(unsigned long _tick)
{
	view->Begin(); __gl_check_error__
	render->Begin();
	gameManager->draw();
    view->End();
}

void Application::OnKeyEvent( unsigned char _key, eKeyEvent _event )
{
	if( _event == eKeyDown )
	{
		gameManager->keyPressed(_key);
	}
}

void Application::OnMouseEvent( eMouseButton _bt , eMouseEvent _event, int _x, int _y  )
{
	static int lx = 0;
	static int ly = 0;
	
	static int dx;
	static int dy;
	
	dx = _x - lx;
	dy = _y - ly;
	ly = _y;
	lx = _x;
	
	switch( _event )
	{
		case MouseDown:
		{
			//ui->on_touch_event( _x, view->GetViewport()->top-_y, uiv2::Touch::touch_event_down, 0);
			break;
		}
		case MouseUp:
		{
			//ui->on_touch_event(_x, view->GetViewport()->top - _y, uiv2::Touch::touch_event_up, 0);
			break;
		}
		case MouseMove:
		{
			//ui->on_touch_event(_x, view->GetViewport()->top - _y, uiv2::Touch::touch_event_move, 0);
			break;
		}
	}
}

namespace uiv2
{
	void on_textinput_begin(int _x, int _y, const char * _text)
	{

	}
}

