#define _AFXDLL
#include <iostream>
#include <stdlib.h>
#include <Afxwin.h>
#include <Windows.h>
#include <fstream>
#include <string>
#include <cstring>
#pragma comment (lib, "User32.lib")

void* GetColor(int x, int y, int* color);
void* GetSize(int* size);
//void* GetPicPos(int r1, int r2, int g1, int g2, int b1, int b2, int* size, int* PicPos, int* color);

int main(void) {

	POINT p;
	double readyKx = 0.8843537, readyKy = 0.8533916, startKx = 0.8503401, startKy = 0.6673960, outKx = 0.8163265, outKy = 0.3282275;//位置参数
	double multiple = 1.25;//显示放大倍数
	int dy = 0;//顶液
	std::string name, line;
	std::ifstream settings("Settings.txt");
	if (!settings) {
		std::cout << "未找到配置文件！请先获取Settings.txt！" << std::endl;
		//char s[2];
		//std::cout << "是否使用默认位置参数？（适用于1440*810分辨率的MuMu模拟器）：（Y/N）" << std::endl;
		//std::cin >> s;
		//if (s[0] == 'Y') {
		//	std::ofstream settings("Settings.txt");
		//	settings << "0.8843537\n" << "0.8533916\n" << "0.8503401\n" << "0.6673960\n" << "0.8163265\n" << "0.3282275\n";

		//}
	}
	else {
		std::getline(settings, line);
		readyKx = atof(line.c_str());
		std::getline(settings, line);
		readyKy = atof(line.c_str());
		std::getline(settings, line);
		startKx = atof(line.c_str());
		std::getline(settings, line);
		startKy = atof(line.c_str());
		std::getline(settings, line);
		outKx = atof(line.c_str());
		std::getline(settings, line);
		outKy = atof(line.c_str());
		std::getline(settings, line);
		multiple = atof(line.c_str());
		std::getline(settings, name);
	}

	int color[3], size[2], PicPos[2];
	for (int i = 0; i < 3; ++i) {
		color[i] = 0;
	}
	for (int i = 0; i < 2; ++i) {
		size[i] = 0;
		PicPos[i] = 0;
	}
	GetSize(size);
	//GetPicPos(10, 20, 110, 130, 140, 180, size, PicPos, color);

	//HWND hwnd = GetForegroundWindow();

	RECT rect;
	HWND hwnd = FindWindowA(NULL, name.c_str());
	GetWindowRect(hwnd, &rect);
	//std::cout << rect.left << " " << rect.right << std::endl;

	double readyX = 0, readyY = 0, startX = 0, startY = 0, outX = 0, outY = 0;
	readyX = rect.left + (rect.right - rect.left) * readyKx;
	readyY = rect.top + (rect.bottom - rect.top) * readyKy;
	startX = rect.left + (rect.right - rect.left) * startKx;
	startY = rect.top + (rect.bottom - rect.top) * startKy;
	outX = rect.left + (rect.right - rect.left) * outKx;
	outY = rect.top + (rect.bottom - rect.top) * outKy;
	while (1) {
		srand(time(0));
		SetCursorPos(readyX + rand() % 20, readyY + rand() % 20);
		mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, GetMessageExtraInfo());
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, GetMessageExtraInfo());
		Sleep(2000 + rand() % 1000);
		GetColor(outX * multiple, outY * multiple, color);
		if (color[0] < 180 && color[0] > 160 && color[1] < 180 && color[1] > 160 && color[2] < 180 && color[2] > 160) {
			if (dy > 0) {

			}
			else {
				std::cout << "理智已耗尽" << std::endl;
				break;
			}
		}
		else if (color[0] > 240 && color[1] > 240 && color[2] > 240) {
			GetColor(startX * multiple, (rect.top + (rect.bottom - rect.top) * 0.8315098) * multiple, color);
			if (color[0] > 100 && color[1] < 200 && color[2] < 200) {

			}
			else {
				std::cout << "理智已耗尽" << std::endl;
				break;
			}
		}
		SetCursorPos(startX + rand() % 20, startY + rand() % 20);
		mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, GetMessageExtraInfo());
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, GetMessageExtraInfo());
		Sleep(80000 + rand() % 2000);
		GetColor((readyX - (rect.right - rect.left) * 0.0173611) * multiple, readyY * multiple, color);
		while (color[0] > 30 || color[1] > 30 || color[2] > 30) {
			Sleep(2000);
		}
		SetCursorPos(rect.left + (rect.right - rect.left) * 0.5 + rand() % 20, rect.top + (rect.bottom - rect.top) * 0.5 + rand() % 20);
		mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, GetMessageExtraInfo());
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, GetMessageExtraInfo());
		Sleep(5000 + rand() % 1000);
	}

	//SetCursorPos(startX, startY);

	system("PAUSE");
	return 0;
}

void* GetColor(int x, int y, int* color) {
	//HWND hWnd = ::GetDesktopWindow();
	//HDC hdc = ::GetDC(hWnd);
	HDC hdc = ::GetDC(NULL);
	COLORREF pixel = ::GetPixel(hdc, x, y);
	int red = -1;
	int green = -1;
	int blue = -1;
	if (pixel != CLR_INVALID) {
		red = GetRValue(pixel);
		green = GetGValue(pixel);
		blue = GetBValue(pixel);
	}
	else {
		printf("错误！");
		system("pause");
	}
	color[0] = red;
	color[1] = green;
	color[2] = blue;
	return 0;
}

void* GetSize(int* size) {
	DEVMODE NewDevMode;
	EnumDisplaySettings(0, ENUM_CURRENT_SETTINGS, &NewDevMode);
	//std::cout << "当前系统刷新率" << NewDevMode.dmDisplayFrequency << "HZ" << std::endl;
	//std::cout << "当前屏幕分辨率" << NewDevMode.dmPelsWidth << "x" << NewDevMode.dmPelsHeight << std::endl;
	size[0] = NewDevMode.dmPelsWidth;
	size[1] = NewDevMode.dmPelsHeight;
	return 0;
}

//void* GetPicPos(int r1, int r2, int g1, int g2, int b1, int b2, int* size, int* PicPos, int* color) {
//	for (int i = 0; i < size[0]; ++i) {
//		for (int j = 0; j < size[1]; ++j) {
//			GetColor(i, j, color);
//			if (color[0] < 20 && color[0] > 10 && color[1] < 130 && color[1] > 110 && color[2] < 180 && color[2] > 140) {
//				PicPos[0] = i;
//				PicPos[1] = j;
//				break;
//			}
//		}
//	}
//	return 0;
//}




/*
1470/914
1200/300
lu:24/143/199  1200/760  1200/460
ru:8/147/212  1400/760
ld:10/87/129  1200/800
rd:7/111/146  1400/800  1300/760
*/