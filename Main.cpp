#include "definitions.h"

Setting speed = { "Software\\51Area", "speed", 0, REG_DWORD, sizeof(DWORD) };

// needed for SCRNSAVE.LIB
BOOL WINAPI RegisterDialogClasses(HANDLE hInst) { return TRUE; }

LRESULT WINAPI ScreenSaverProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static GraphicsEngine* engine = 0;
	static GraphicsView* view = 0;
	static int textTimer = 0;

	switch (uMsg)
	{
	case WM_CREATE:
		{
			RECT rect;
			GetClientRect(hWnd, &rect);

			engine = new GraphicsEngine();
			engine->InitGraphics(hWnd);
			engine->SelectEngine();

			view = new GraphicsView();
			view->InitView(0, 0, rect.right, rect.bottom);
			view->Setup2D();

			::glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 
			::glShadeModel(GL_SMOOTH); 
			::glEnable (GL_BLEND);
			::glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			GetSetting(speed);
			
			switch (speed.dwValue)
			{
			case SPEED_FAST:
				{
					::SetTimer(hWnd, 64, 100, NULL);
					break;
				}
			case SPEED_NORMAL:
				{
					::SetTimer(hWnd, 64, 500, NULL);
					break;
				}
				case SPEED_SLOW:
				{
					::SetTimer(hWnd, 64, 1000, NULL);
					break;
				}
			}
			break;
		}

	case WM_TIMER:
		{
			Area area;

			GenerateArea(view->Width(), view->Height(), area);

			if (textTimer == 20)
			{
				//engine->RenderText("Heey", 100, 100);
			}

			RenderArea(area);
			engine->Swap();
			RenderArea(area);
			engine->Swap();

			textTimer++;
			break;
		}

	case WM_DESTROY:
		{
			engine->CloseGraphics();
			break;
		}
	}
	return DefScreenSaverProc(hWnd, uMsg, wParam, lParam);
}

BOOL WINAPI ScreenSaverConfigureDialog(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		{
			GetSetting(speed);
			
			::SendMessage(GetDlgItem(hDlg, IDC_SPEED), CB_ADDSTRING, 0, (LPARAM)"Fast");
			::SendMessage(GetDlgItem(hDlg, IDC_SPEED), CB_ADDSTRING, 0, (LPARAM)"Normal");
			::SendMessage(GetDlgItem(hDlg, IDC_SPEED), CB_ADDSTRING, 0, (LPARAM)"Slow");

			::SendMessage(GetDlgItem(hDlg, IDC_SPEED), CB_SETCURSEL, speed.dwValue, 0);

			HFONT hFont = (HFONT)GetStockObject(ANSI_FIXED_FONT);
			::SendMessage(GetDlgItem(hDlg, IDC_EMAIL), WM_SETFONT, (WPARAM)hFont, TRUE);
			break;
		}

	case WM_COMMAND:
		{
			switch (wParam)
			{
			case IDOK:
				{
					int newSpeed = ::SendMessage(GetDlgItem(hDlg, IDC_SPEED), CB_GETCURSEL, 0, 0);

					if (newSpeed > -1)
					{
						speed.dwValue = newSpeed;
						SetSetting(speed);
						
						::EndDialog(hDlg, wParam);
					}
					break;
				}
			}
			break;
		}
	case WM_CLOSE :
		{
			EndDialog(hDlg, 0);
			break;
		}
	}
	return 0;  
}
