// OpenGL_Core.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "OpenGL_Core.h"
#include "shell/Application.h"

#define MAX_LOADSTRING 100

// ȫ�ֱ���: 
HINSTANCE hInst;                                // ��ǰʵ��
WCHAR szTitle[MAX_LOADSTRING];                  // �������ı�
WCHAR szWindowClass[MAX_LOADSTRING];            // ����������

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

Application theApp;

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	WNDCLASSEX wcex;
	HWND hwnd;
	MSG msg;
	BOOL bQuit = FALSE;

	/* register window class */
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_OWNDC;
	wcex.lpfnWndProc = WindowProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"gl_window";
	wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);;


	if (!RegisterClassEx(&wcex))
		return 0;

	/* create main window */
	hwnd = CreateWindowEx(0,
		L"gl_window",
		L"OpenGL Core Window",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		500,
		500,
		NULL,
		NULL,
		hInstance,
		NULL);

	theApp.Start(hwnd);

	ShowWindow(hwnd, nCmdShow);

	/* program main loop */
	while (!bQuit)
	{
		/* check for messages */
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			/* handle or dispatch messages */
			if (msg.message == WM_QUIT)
			{
				bQuit = TRUE;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			unsigned long tick = GetTickCount();
			theApp.OnRender(tick);
			Sleep(1);
		}
	}

	theApp.End();
	/* destroy the window explicitly */
	DestroyWindow(hwnd);

	return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;

	case WM_DESTROY:
		return 0;

	case WM_KEYDOWN:
	{
		theApp.OnKeyEvent(wParam, Application::eKeyDown);
		break;
	}
	case WM_KEYUP:
	{
		switch (wParam)
		{
		case VK_ESCAPE:
		{
			//PostQuitMessage(0);
			break;
		}
		default:
			theApp.OnKeyEvent(wParam, Application::eKeyUp);
			break;
		}
		break;
	}
	case WM_SIZE:
	{
		WORD nWidth, nHeight;
		nWidth = LOWORD(lParam); // width of client area
		nHeight = HIWORD(lParam); // height of client area
		theApp.OnResize(nWidth, nHeight);
		break;
	}
	/*
	* wParam
	�ò�������������������û�б����£����ܰ����������ֵ
	MK_CONTROL(0x0008)
	CTRL��������
	MK_LBUTTON(0x0001)
	������������
	MK_MBUTTON(0x0010)
	����м�������
	MK_RBUTTON(0x0002)
	����Ҽ�������
	MK_SHIFT(0x0004)
	SHIFT��������
	MK_XBUTTON1(0x0020)
	��һ�� X ��ť������
	MK_XBUTTON2(0x0040)
	�ڶ��� X ��ť������
	lParam
	����һ��32λ�����Ͳ�����
	��16λ��ʾ����ڿͻ������Ͻǵ� X ����
	��16λ��ʾ����ڿͻ������Ͻǵ� Y ����
	* */
	case WM_MOUSEMOVE:
	{
		short x = LOWORD(lParam);
		short y = HIWORD(lParam);
		switch (wParam)
		{
		case MK_LBUTTON:
			theApp.OnMouseEvent(Application::LButtonMouse, Application::MouseMove, x, y);
			break;
		case MK_RBUTTON:
			theApp.OnMouseEvent(Application::RButtonMouse, Application::MouseMove, x, y);
			break;
		case MK_MBUTTON:
			theApp.OnMouseEvent(Application::MButtonMouse, Application::MouseMove, x, y);
			break;
		}
		break;
	}
	case WM_LBUTTONDOWN:
	{
		short x = LOWORD(lParam);
		short y = HIWORD(lParam);
		theApp.OnMouseEvent(Application::LButtonMouse, Application::MouseDown, x, y);
		break;
	}
	case WM_LBUTTONUP:
	{
		short x = LOWORD(lParam);
		short y = HIWORD(lParam);
		theApp.OnMouseEvent(Application::LButtonMouse, Application::MouseUp, x, y);
		break;
	}

	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}