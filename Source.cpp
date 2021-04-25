#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <ctime>


HDC hDC = GetDC(GetConsoleWindow());
COORD scrn;
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
HPEN PenC = CreatePen(PS_SOLID, 1, RGB(100, 100, 100));
HPEN PenB = CreatePen(PS_SOLID, 1, RGB(255, 151, 0));
HPEN PenHB = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
HPEN PenHG = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
HPEN PenHR = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
HPEN PenHW = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
HPEN PenBl = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
HPEN PenL = CreatePen(PS_SOLID, 1, RGB(82, 206, 237));
HPEN PenY = CreatePen(PS_SOLID, 1, RGB(255, 255, 0));

const int maze_wall_n = 773;
int maze_wall_x[maze_wall_n];
int maze_wall_y[maze_wall_n];

const int maze_lock_n = 17;
int maze_lock_x[maze_lock_n];
int maze_lock_y[maze_lock_n];
int maze_lock_m[maze_lock_n];

const int maze_door_n = 37;
int maze_door_x[maze_door_n];
int maze_door_y[maze_door_n];
int maze_door_l[maze_door_n];

int lockn;
bool lockon = 0;

int speed = 0;

using namespace std;

void fil(int x, int y, int h, int a) {
	for (int i = 0; i < a; i += 1) {
		MoveToEx(hDC, x + i, y, NULL);
		LineTo(hDC, x + i, y + h);
	}
}

void wall(int x, int y) {
	SelectObject(hDC, PenB);
	fil(x - 15, y - 15, 32, 32);
	SelectObject(hDC, PenC);
	MoveToEx(hDC, x + 16, y + 16, NULL);
	LineTo(hDC, x - 16, y + 16);
	MoveToEx(hDC, x + 16, y + 15, NULL);
	LineTo(hDC, x - 16, y + 15);
	MoveToEx(hDC, x + 16, y - 15, NULL);
	LineTo(hDC, x - 16, y - 15);
	MoveToEx(hDC, x + 16, y, NULL);
	LineTo(hDC, x - 16, y);
	MoveToEx(hDC, x + 16, y - 1, NULL);
	LineTo(hDC, x - 16, y - 1);
	MoveToEx(hDC, x + 16, y + 1, NULL);
	LineTo(hDC, x - 16, y + 1);

	MoveToEx(hDC, x + 16, y + 16, NULL);
	LineTo(hDC, x + 16, y - 2);
	MoveToEx(hDC, x + 15, y + 16, NULL);
	LineTo(hDC, x + 15, y - 2);
	MoveToEx(hDC, x - 15, y + 16, NULL);
	LineTo(hDC, x - 15, y - 2);
	MoveToEx(hDC, x, y, NULL);
	LineTo(hDC, x, y - 16);
	MoveToEx(hDC, x - 1, y, NULL);
	LineTo(hDC, x - 1, y - 16);
	MoveToEx(hDC, x - 2, y, NULL);
	LineTo(hDC, x - 2, y - 16);
}

void lock(int x, int y, int m) {
	SelectObject(hDC, PenL);
	fil(x - 15, y - 15, 32, 32);
	SelectObject(hDC, PenBl);
	MoveToEx(hDC, x - 8, y + 16, NULL);
	LineTo(hDC, x - 8, y - 16);
	MoveToEx(hDC, x + 8, y + 16, NULL);
	LineTo(hDC, x + 8, y - 16);
	MoveToEx(hDC, x - 15, y + 8, NULL);
	LineTo(hDC, x + 17, y + 8);
	MoveToEx(hDC, x - 15, y - 8, NULL);
	LineTo(hDC, x + 17, y - 8);
	MoveToEx(hDC, x, y + 16, NULL);
	LineTo(hDC, x, y + 8);
	MoveToEx(hDC, x, y - 16, NULL);
	LineTo(hDC, x, y - 8);
	MoveToEx(hDC, x + 16, y, NULL);
	LineTo(hDC, x + 8, y);
	MoveToEx(hDC, x - 16, y, NULL);
	LineTo(hDC, x - 8, y);
	switch (m) {
	case 0:
		SelectObject(hDC, PenHR);
		fil(x - 5, y - 1, 8, 11);
		SetPixel(hDC, x - 5, y - 2, RGB(255, 0, 0));
		SetPixel(hDC, x - 5, y - 3, RGB(255, 0, 0));
		SetPixel(hDC, x - 4, y - 4, RGB(255, 0, 0));
		SetPixel(hDC, x - 3, y - 5, RGB(255, 0, 0));
		MoveToEx(hDC, x - 2, y - 6, NULL);
		LineTo(hDC, x + 2, y - 6);
		SetPixel(hDC, x + 5, y - 2, RGB(255, 0, 0));
		SetPixel(hDC, x + 5, y - 3, RGB(255, 0, 0));
		SetPixel(hDC, x + 4, y - 4, RGB(255, 0, 0));
		SetPixel(hDC, x + 3, y - 5, RGB(255, 0, 0));
		break;
	case 1:
		SelectObject(hDC, PenY);
		fil(x - 5, y - 1, 8, 11);
		SetPixel(hDC, x - 5, y - 2, RGB(255, 255, 0));
		SetPixel(hDC, x - 5, y - 3, RGB(255, 255, 0));
		SetPixel(hDC, x - 4, y - 4, RGB(255, 255, 0));
		SetPixel(hDC, x - 3, y - 5, RGB(255, 255, 0));
		MoveToEx(hDC, x - 2, y - 6, NULL);
		LineTo(hDC, x + 2, y - 6);
		SetPixel(hDC, x + 5, y - 2, RGB(255, 255, 0));
		SetPixel(hDC, x + 5, y - 3, RGB(255, 255, 0));
		SetPixel(hDC, x + 4, y - 4, RGB(255, 255, 0));
		SetPixel(hDC, x + 3, y - 5, RGB(255, 255, 0));
		break;
	case 2:
		SelectObject(hDC, PenHG);
		fil(x - 5, y - 1, 8, 11);
		SetPixel(hDC, x - 5, y - 2, RGB(0, 255, 0));
		SetPixel(hDC, x - 5, y - 3, RGB(0, 255, 0));
		SetPixel(hDC, x - 5, y - 4, RGB(0, 255, 0));
		SetPixel(hDC, x - 5, y - 5, RGB(0, 255, 0));
		SetPixel(hDC, x - 4, y - 6, RGB(0, 255, 0));
		SetPixel(hDC, x - 3, y - 7, RGB(0, 255, 0));
		MoveToEx(hDC, x - 2, y - 8, NULL);
		LineTo(hDC, x + 2, y - 8);
		SetPixel(hDC, x + 5, y - 4, RGB(0, 255, 0));
		SetPixel(hDC, x + 5, y - 5, RGB(0, 255, 0));
		SetPixel(hDC, x + 4, y - 6, RGB(0, 255, 0));
		SetPixel(hDC, x + 3, y - 7, RGB(0, 255, 0));
		break;
	}
}

void door(int x, int y, int m) {
	if (m == 2) {
		SelectObject(hDC, PenBl);
		fil(x - 15, y - 15, 32, 32);
	}
	else {
		SelectObject(hDC, PenHB);
		fil(x - 15, y - 2, 5, 32);
		fil(x - 2, y - 15, 32, 5);
		switch (m) {
		case 0:
			SelectObject(hDC, PenHR);
			break;
		case 1:
			SelectObject(hDC, PenHG);
			break;
		}
		fil(x - 2, y - 2, 5, 5);
		fil(x - 15, y - 15, 14, 14);
		fil(x + 3, y - 15, 14, 14);
		fil(x - 15, y + 3, 14, 14);
		fil(x + 3, y + 3, 14, 14);
	}
}

void hero(int x, int y, int poz, int mode) {

	{
		SelectObject(hDC, PenHB);
		fil(x - 12, y - 12, 25, 25);
		{
			SetPixel(hDC, x - 12, y - 12, RGB(0, 0, 0));
			SetPixel(hDC, x - 12, y + 12, RGB(0, 0, 0));
			SetPixel(hDC, x - 13, y + 9, RGB(0, 0, 255));
			SetPixel(hDC, x + 12, y - 12, RGB(0, 0, 0));
			SetPixel(hDC, x + 9, y - 13, RGB(0, 0, 255));
			SetPixel(hDC, x + 12, y + 12, RGB(0, 0, 0));
		}
		{
			MoveToEx(hDC, x - 9, y + 13, NULL);
			LineTo(hDC, x + 9, y + 13);
			MoveToEx(hDC, x + 8, y + 14, NULL);
			LineTo(hDC, x - 8, y + 14);
			MoveToEx(hDC, x + 6, y + 15, NULL);
			LineTo(hDC, x - 6, y + 15);
			MoveToEx(hDC, x + 3, y + 16, NULL);
			LineTo(hDC, x - 3, y + 16);
		}
		{
			MoveToEx(hDC, x - 9, y - 13, NULL);
			LineTo(hDC, x + 9, y - 13);
			MoveToEx(hDC, x + 8, y - 14, NULL);
			LineTo(hDC, x - 8, y - 14);
			MoveToEx(hDC, x + 6, y - 15, NULL);
			LineTo(hDC, x - 6, y - 15);
			MoveToEx(hDC, x + 3, y - 16, NULL);
			LineTo(hDC, x - 3, y - 16);
		}
		{
			MoveToEx(hDC, x + 13, y - 9, NULL);
			LineTo(hDC, x + 13, y + 9);
			MoveToEx(hDC, x + 14, y + 8, NULL);
			LineTo(hDC, x + 14, y - 8);
			MoveToEx(hDC, x + 15, y + 6, NULL);
			LineTo(hDC, x + 15, y - 6);
			MoveToEx(hDC, x + 16, y + 3, NULL);
			LineTo(hDC, x + 16, y - 3);
		}
		{
			MoveToEx(hDC, x - 13, y - 9, NULL);
			LineTo(hDC, x - 13, y + 9);
			MoveToEx(hDC, x - 14, y + 8, NULL);
			LineTo(hDC, x - 14, y - 8);
			MoveToEx(hDC, x - 15, y + 6, NULL);
			LineTo(hDC, x - 15, y - 6);
			MoveToEx(hDC, x - 16, y + 3, NULL);
			LineTo(hDC, x - 16, y - 3);
		}
	}
	{
		switch (mode) {
		case 0:
			SelectObject(hDC, PenHG);
			break;
		case 1:
			SelectObject(hDC, PenHW);
			break;
		case 2:
			SelectObject(hDC, PenHR);
			break;
		}
		fil(x - 8, y - 8, 17, 17);
		{
			MoveToEx(hDC, x - 6, y - 9, NULL);
			LineTo(hDC, x + 7, y - 9);
			MoveToEx(hDC, x - 5, y - 10, NULL);
			LineTo(hDC, x + 6, y - 10);
			MoveToEx(hDC, x - 3, y - 11, NULL);
			LineTo(hDC, x + 4, y - 11);
		}
		{
			MoveToEx(hDC, x - 6, y + 9, NULL);
			LineTo(hDC, x + 7, y + 9);
			MoveToEx(hDC, x - 5, y + 10, NULL);
			LineTo(hDC, x + 6, y + 10);
			MoveToEx(hDC, x - 3, y + 11, NULL);
			LineTo(hDC, x + 4, y + 11);
		}
		{
			MoveToEx(hDC, x + 9, y - 6, NULL);
			LineTo(hDC, x + 9, y + 7);
			MoveToEx(hDC, x + 10, y - 5, NULL);
			LineTo(hDC, x + 10, y + 6);
			MoveToEx(hDC, x + 11, y - 3, NULL);
			LineTo(hDC, x + 11, y + 4);
		}
		{
			MoveToEx(hDC, x - 9, y - 6, NULL);
			LineTo(hDC, x - 9, y + 7);
			MoveToEx(hDC, x - 10, y - 5, NULL);
			LineTo(hDC, x - 10, y + 6);
			MoveToEx(hDC, x - 11, y - 3, NULL);
			LineTo(hDC, x - 11, y + 4);
		}
	}
	switch (mode) {
	case 1:
		SelectObject(hDC, PenHG);
		break;
	default:
		SelectObject(hDC, PenHR);
		break;
	}
	switch (poz) {
	case 0:
		fil(x - 3, y - 16, 6, 7);
		break;
	case 1:
		fil(x + 11, y - 3, 7, 6);
		break;
	case 2:
		fil(x - 3, y + 11, 6, 7);
		break;
	case 3:
		fil(x - 16, y - 3, 7, 6);
		break;
	}
}

void build_maze() {
	maze_wall_x[0] = 1;
	maze_wall_y[0] = 1;
	maze_wall_x[1] = 57;
	maze_wall_y[1] = 11;
	maze_wall_x[2] = 5;
	maze_wall_y[2] = 32;
	for (int i = 3; i < 33; i++) {
		maze_wall_x[i] = 1;
		maze_wall_y[i] = i + 1;
	}
	for (int i = 33; i < 40; i++) {
		maze_wall_x[i] = i - 31;
		maze_wall_y[i] = 1;
	}
	for (int i = 40; i < 87; i++) {
		maze_wall_x[i] = i - 29;
		maze_wall_y[i] = 1;
	}
	for (int i = 89; i < 122; i++) {
		maze_wall_x[i] = 58;
		maze_wall_y[i] = i - 88;
	}
	for (int i = 122; i < 178; i++) {
		maze_wall_x[i] = i - 120;
		maze_wall_y[i] = 33;
	}
	for (int i = 178; i < 222; i++) {
		maze_wall_x[i] = i - 167;
		maze_wall_y[i] = 2;
	}
	maze_wall_x[222] = 57;
	maze_wall_y[222] = 2;
	maze_wall_x[223] = 4;
	maze_wall_y[223] = 2;
	maze_wall_x[224] = 5;
	maze_wall_y[224] = 2;
	maze_wall_x[225] = 7;
	maze_wall_y[225] = 2;
	maze_wall_x[226] = 8;
	maze_wall_y[226] = 2;
	maze_wall_x[227] = 57;
	maze_wall_y[227] = 4;
	maze_wall_x[228] = 57;
	maze_wall_y[228] = 5;
	for (int i = 229; i < 270; i++) {
		maze_wall_x[i] = i - 215;
		maze_wall_y[i] = 5;
	}
	for (int i = 271; i < 280; i++) {
		maze_wall_x[i] = 11;
		maze_wall_y[i] = i - 268;
	}
	maze_wall_x[280] = 8;
	maze_wall_y[280] = 3;
	maze_wall_x[281] = 8;
	maze_wall_y[281] = 4;
	maze_wall_x[282] = 8;
	maze_wall_y[282] = 7;
	maze_wall_x[283] = 8;
	maze_wall_y[283] = 8;
	maze_wall_x[284] = 8;
	maze_wall_y[284] = 9;
	maze_wall_x[285] = 8;
	maze_wall_y[285] = 10;
	maze_wall_x[286] = 8;
	maze_wall_y[286] = 11;
	maze_wall_x[287] = 9;
	maze_wall_y[287] = 11;
	maze_wall_x[288] = 10;
	maze_wall_y[288] = 11;
	for (int i = 289; i < 298; i++) {
		maze_wall_x[i] = 4;
		maze_wall_y[i] = i - 286;
	}
	for (int i = 299; i < 339; i++) {
		maze_wall_x[i] = i - 284;
		maze_wall_y[i] = 11;
	}
	for (int i = 340; i < 346; i++) {
		maze_wall_x[i] = 14;
		maze_wall_y[i] = i - 334;
	}
	for (int i = 347; i < 352; i++) {
		maze_wall_x[i] = i - 294;
		maze_wall_y[i] = 10;
	}
	for (int i = 353; i < 357; i++) {
		maze_wall_x[i] = i - 305;
		maze_wall_y[i] = 10;
	}
	for (int i = 358; i < 362; i++) {
		maze_wall_x[i] = i - 315;
		maze_wall_y[i] = 10;
	}
	for (int i = 363; i < 366; i++) {
		maze_wall_x[i] = i - 324;
		maze_wall_y[i] = 10;
	}
	for (int i = 367; i < 371; i++) {
		maze_wall_x[i] = i - 333;
		maze_wall_y[i] = 10;
	}
	maze_wall_x[371] = 32;
	maze_wall_y[371] = 10;
	maze_wall_x[372] = 31;
	maze_wall_y[372] = 10;
	maze_wall_x[373] = 31;
	maze_wall_y[373] = 9;
	maze_wall_x[374] = 31;
	maze_wall_y[374] = 8;
	maze_wall_x[375] = 28;
	maze_wall_y[375] = 8;
	maze_wall_x[376] = 28;
	maze_wall_y[376] = 7;
	maze_wall_x[377] = 28;
	maze_wall_y[377] = 6;
	maze_wall_x[378] = 27;
	maze_wall_y[378] = 6;
	maze_wall_x[379] = 44;
	maze_wall_y[379] = 8;
	maze_wall_x[380] = 45;
	maze_wall_y[380] = 8;
	maze_wall_x[381] = 45;
	maze_wall_y[381] = 9;
	maze_wall_x[382] = 44;
	maze_wall_y[382] = 9;
	maze_wall_x[383] = 15;
	maze_wall_y[383] = 6;
	for (int i = 384; i < 393; i++) {
		maze_wall_x[i] = i - 367;
		maze_wall_y[i] = 6;
	}
	for (int i = 393; i < 400; i++) {
		maze_wall_x[i] = i - 359;
		maze_wall_y[i] = 6;
	}

	for (int i = 400; i < 407; i++) {
		maze_wall_x[i] = i - 366;
		maze_wall_y[i] = 7;
	}
	for (int i = 407; i < 458; i++) {
		maze_wall_x[i] = i - 403;
		maze_wall_y[i] = 14;
	}
	for (int i = 458; i < 466; i++) {
		maze_wall_x[i] = 4;
		maze_wall_y[i] = i - 443;
	}
	for (int i = 466; i < 475; i++) {
		maze_wall_x[i] = 4;
		maze_wall_y[i] = i - 442;
	}
	for (int i = 475; i < 491; i++) {
		maze_wall_x[i] = 5;
		maze_wall_y[i] = i - 460;
	}
	maze_wall_x[491] = 57;
	maze_wall_y[491] = 13;
	maze_wall_x[492] = 57;
	maze_wall_y[492] = 14;
	for (int i = 493; i < 508; i++) {
		maze_wall_x[i] = 54;
		maze_wall_y[i] = i - 478;
	}
	for (int i = 508; i < 520; i++) {
		maze_wall_x[i] = 55;
		maze_wall_y[i] = i - 491;
	}
	for (int i = 520; i < 568; i++) {
		maze_wall_x[i] = i - 512;
		maze_wall_y[i] = 30;
	}
	for (int i = 568; i < 581; i++) {
		maze_wall_x[i] = 8;
		maze_wall_y[i] = i - 551;
	}
	for (int i = 581; i < 624; i++) {
		maze_wall_x[i] = i - 572;
		maze_wall_y[i] = 17;
	}
	for (int i = 624; i < 634; i++) {
		maze_wall_x[i] = 51;
		maze_wall_y[i] = i - 606;
	}
	for (int i = 634; i < 674; i++) {
		maze_wall_x[i] = i - 623;
		maze_wall_y[i] = 27;
	}
	for (int i = 674; i < 681; i++) {
		maze_wall_x[i] = 11;
		maze_wall_y[i] = i - 654;
	}
	for (int i = 681; i < 686; i++) {
		maze_wall_x[i] = i - 668;
		maze_wall_y[i] = 20;
	}
	for (int i = 686; i < 690; i++) {
		maze_wall_x[i] = i - 674;
		maze_wall_y[i] = 21;
	}
	maze_wall_x[690] = 17;
	maze_wall_y[690] = 21;
	for (int i = 691; i < 725; i++) {
		maze_wall_x[i] = i - 677;
		maze_wall_y[i] = 24;
	}
	maze_wall_x[725] = 25;
	maze_wall_y[725] = 18;
	for (int i = 726; i < 732; i++) {
		maze_wall_x[i] = 20;
		maze_wall_y[i] = i - 708;
	}
	for (int i = 732; i < 759; i++) {
		maze_wall_x[i] = i - 709;
		maze_wall_y[i] = 21;
	}
	for (int i = 759; i < 763; i++) {
		maze_wall_x[i] = 50;
		maze_wall_y[i] = i - 739;
	}
	maze_wall_x[763] = 28;
	maze_wall_y[763] = 20;
	maze_wall_x[764] = 31;
	maze_wall_y[764] = 18;
	maze_wall_x[765] = 34;
	maze_wall_y[765] = 20;
	maze_wall_x[766] = 37;
	maze_wall_y[766] = 18;
	maze_wall_x[767] = 40;
	maze_wall_y[767] = 20;
	maze_wall_x[768] = 43;
	maze_wall_y[768] = 18;
	maze_wall_x[769] = 46;
	maze_wall_y[769] = 20;
	maze_wall_x[770] = 50;
	maze_wall_y[770] = 18;
	maze_wall_x[771] = 50;
	maze_wall_y[771] = 25;
	maze_wall_x[772] = 50;
	maze_wall_y[772] = 26;
	for (int i = 0; i < maze_wall_n; i++) {
		maze_wall_x[i] *= 32;
		maze_wall_y[i] *= 32;
		wall(maze_wall_x[i], maze_wall_y[i]);
	}

	maze_lock_x[0] = 4;
	maze_lock_y[0] = 23;
	maze_lock_x[1] = 57;
	maze_lock_y[1] = 12;
	maze_lock_x[2] = 57;
	maze_lock_y[2] = 3;
	maze_lock_x[3] = 55;
	maze_lock_y[3] = 29;
	maze_lock_x[4] = 52;
	maze_lock_y[4] = 10;
	maze_lock_x[5] = 5;
	maze_lock_y[5] = 31;
	maze_lock_x[6] = 47;
	maze_lock_y[6] = 10;
	maze_lock_x[7] = 42;
	maze_lock_y[7] = 10;
	maze_lock_x[8] = 12;
	maze_lock_y[8] = 20;
	maze_lock_x[9] = 38;
	maze_lock_y[9] = 10;
	maze_lock_x[10] = 16;
	maze_lock_y[10] = 21;
	maze_lock_x[11] = 33;
	maze_lock_y[11] = 10;
	maze_lock_x[12] = 50;
	maze_lock_y[12] = 24;
	maze_lock_x[13] = 26;
	maze_lock_y[13] = 6;
	maze_lock_x[14] = 16;
	maze_lock_y[14] = 6;
	maze_lock_x[15] = 50;
	maze_lock_y[15] = 19;
	maze_lock_x[16] = 6;
	maze_lock_y[16] = 2;
	for (int i = 0; i < maze_lock_n; i++) {
		maze_lock_x[i] *= 32;
		maze_lock_y[i] *= 32;
		lock(maze_lock_x[i], maze_lock_y[i], maze_lock_m[i]);
	}

	maze_door_x[0] = 4;
	maze_door_y[0] = 12;
	maze_door_l[0] = 0;
	maze_door_x[1] = 4;
	maze_door_y[1] = 13;
	maze_door_l[1] = 0;

	maze_door_x[2] = 12;
	maze_door_y[2] = 11;
	maze_door_l[2] = 1;
	maze_door_x[3] = 13;
	maze_door_y[3] = 11;
	maze_door_l[3] = 1;

	maze_door_x[4] = 55;
	maze_door_y[4] = 14;
	maze_door_l[4] = 2;
	maze_door_x[5] = 56;
	maze_door_y[5] = 14;
	maze_door_l[5] = 2;

	maze_door_x[6] = 55;
	maze_door_y[6] = 5;
	maze_door_l[6] = 3;
	maze_door_x[7] = 56;
	maze_door_y[7] = 5;
	maze_door_l[7] = 3;

	maze_door_x[8] = 55;
	maze_door_y[8] = 31;
	maze_door_l[8] = 4;
	maze_door_x[9] = 55;
	maze_door_y[9] = 32;
	maze_door_l[9] = 4;

	maze_door_x[10] = 50;
	maze_door_y[10] = 6;
	maze_door_l[10] = 5;
	maze_door_x[11] = 50;
	maze_door_y[11] = 7;
	maze_door_l[11] = 5;
	maze_door_x[12] = 50;
	maze_door_y[12] = 8;
	maze_door_l[12] = 5;
	maze_door_x[13] = 50;
	maze_door_y[13] = 9;
	maze_door_l[13] = 5;

	maze_door_x[14] = 6;
	maze_door_y[14] = 29;
	maze_door_l[14] = 6;
	maze_door_x[15] = 7;
	maze_door_y[15] = 29;
	maze_door_l[15] = 6;

	maze_door_x[16] = 52;
	maze_door_y[16] = 18;
	maze_door_l[16] = 7;
	maze_door_x[17] = 53;
	maze_door_y[17] = 18;
	maze_door_l[17] = 7;

	maze_door_x[18] = 40;
	maze_door_y[18] = 8;
	maze_door_l[18] = 8;
	maze_door_x[19] = 40;
	maze_door_y[19] = 9;
	maze_door_l[19] = 8;

	maze_door_x[20] = 17;
	maze_door_y[20] = 18;
	maze_door_l[20] = 9;
	maze_door_x[21] = 17;
	maze_door_y[21] = 19;
	maze_door_l[21] = 9;

	maze_door_x[22] = 36;
	maze_door_y[22] = 8;
	maze_door_l[22] = 10;
	maze_door_x[23] = 36;
	maze_door_y[23] = 9;
	maze_door_l[23] = 10;

	maze_door_x[24] = 12;
	maze_door_y[24] = 24;
	maze_door_l[24] = 11;
	maze_door_x[25] = 13;
	maze_door_y[25] = 24;
	maze_door_l[25] = 11;

	maze_door_x[26] = 29;
	maze_door_y[26] = 8;
	maze_door_l[26] = 12;
	maze_door_x[27] = 30;
	maze_door_y[27] = 8;
	maze_door_l[27] = 12;

	maze_door_x[28] = 21;
	maze_door_y[28] = 21;
	maze_door_l[28] = 13;
	maze_door_x[29] = 22;
	maze_door_y[29] = 21;
	maze_door_l[29] = 13;

	maze_door_x[30] = 5;
	maze_door_y[30] = 11;
	maze_door_l[30] = 14;
	maze_door_x[31] = 6;
	maze_door_y[31] = 11;
	maze_door_l[31] = 14;
	maze_door_x[32] = 7;
	maze_door_y[32] = 11;
	maze_door_l[32] = 14;

	maze_door_x[33] = 9;
	maze_door_y[33] = 1;
	maze_door_l[33] = 15;
	maze_door_x[34] = 10;
	maze_door_y[34] = 1;
	maze_door_l[34] = 15;

	maze_door_x[35] = 8;
	maze_door_y[35] = 5;
	maze_door_l[35] = 16;
	maze_door_x[36] = 8;
	maze_door_y[36] = 6;
	maze_door_l[36] = 16;

	for (int i = 0; i < maze_door_n; i++) {
		maze_door_x[i] *= 32;
		maze_door_y[i] *= 32;
		door(maze_door_x[i], maze_door_y[i], 0);
	}
}

int main() {
	setlocale(LC_ALL, "rus");
	srand(time(0));
	cout << "Нажмите Alt + Enter";
	system("timeout /nobreak /t 5");
	system("cls");
	cout << " Управление:\n  Движение:\n     w\n   a s d\n\n  Поворот:\n    q e\n\n Активировать: x\n\n Изменить скорость: r f\n\n Чтобы открыть дверь, активируйте соответствующий интерфейс\n ";
	system("pause");
	SelectObject(hDC, PenBl);
	fil(0, 0, 10000, 10000);
	build_maze();
	int hero_x = 16, hero_y = 76, hero_p = 1, hero_m = 0;
	hero(hero_x, hero_y, hero_p, hero_m);
	scrn.X = 0; scrn.Y = 0;
	SetConsoleCursorPosition(h, scrn);
	cout << "Скорость: 0";
	while (true) {
		if (_kbhit())
		{
			SelectObject(hDC, PenBl);
			fil(hero_x - 16, hero_y - 16, 33, 33);
			switch (_getch())
			{
			case 'w':
			{
				if (hero_y <= 16) {
					hero_y = 1054;
				}
				else {
					hero_y -= speed;
				}
				for (int i = 0; i < maze_wall_n; i++) {
					if (((abs(maze_wall_x[i] - hero_x)) <= 32) && ((abs(maze_wall_y[i] - hero_y)) <= 32)) {
						if (hero_y >= 1054) {
							hero_y = 16;
						}
						else {
							hero_y += speed;
						}
						break;
					}
				}
				for (int i = 0; i < maze_door_n; i++) {
					if (((abs(maze_door_x[i] - hero_x)) <= 32) && ((abs(maze_door_y[i] - hero_y)) <= 32)) {
						if (hero_y >= 1054) {
							hero_y = 16;
						}
						else {
							hero_y += speed;
						}
						break;
					}
				}
				break;
			}
			case 'a':
			{
				if (hero_x <= 16) {
					hero_x = 1854;
				}
				else {
					hero_x -= speed;
				}
				for (int i = 0; i < maze_wall_n; i++) {
					if (((abs(maze_wall_x[i] - hero_x)) <= 32) && ((abs(maze_wall_y[i] - hero_y)) < 32)) {
						if (hero_x >= 1854) {
							hero_x = 16;
						}
						else {
							hero_x += speed;
						}
						break;
					}
				}for (int i = 0; i < maze_door_n; i++) {
					if (((abs(maze_door_x[i] - hero_x)) <= 32) && ((abs(maze_door_y[i] - hero_y)) < 32)) {
						if (hero_x >= 1854) {
							hero_x = 16;
						}
						else {
							hero_x += speed;
						}
						break;
					}
				}
				break;
			}
			case 's':
			{
				if (hero_y >= 1054) {
					hero_y = 16;
				}
				else {
					hero_y += speed;
				}
				for (int i = 0; i < maze_wall_n; i++) {
					if (((abs(maze_wall_x[i] - hero_x)) <= 32) && ((abs(maze_wall_y[i] - hero_y)) <= 32)) {
						if (hero_y <= 16) {
							hero_y = 1054;
						}
						else {
							hero_y -= speed;
						}
						break;
					}
				}
				for (int i = 0; i < maze_door_n; i++) {
					if (((abs(maze_door_x[i] - hero_x)) <= 32) && ((abs(maze_door_y[i] - hero_y)) <= 32)) {
						if (hero_y <= 16) {
							hero_y = 1054;
						}
						else {
							hero_y -= speed;
						}
						break;
					}
				}
				break;
			}
			case 'd':
			{
				if (hero_x >= 1854) {
					hero_x = 16;
				}
				else {
					hero_x += speed;
				}
				for (int i = 0; i < maze_wall_n; i++) {
					if (((abs(maze_wall_x[i] - hero_x)) <= 32) && ((abs(maze_wall_y[i] - hero_y)) <= 32)) {
						if (hero_x <= 16) {
							hero_x = 1854;
						}
						else {
							hero_x -= speed;
						}
						break;
					}
				}
				for (int i = 0; i < maze_door_n; i++) {
					if (((abs(maze_door_x[i] - hero_x)) <= 32) && ((abs(maze_door_y[i] - hero_y)) <= 32)) {
						if (hero_x <= 16) {
							hero_x = 1854;
						}
						else {
							hero_x -= speed;
						}
						break;
					}
				}
				break;
			}
			case 'q':
			{
				if (hero_p == 0) {
					hero_p = 3;
				}
				else {
					hero_p--;
				}
				break;
			}
			case 'e':
			{
				if (hero_p == 3) {
					hero_p = 0;
				}
				else {
					hero_p++;
				}
				break;
			}
			case 'x':
			{
				if (lockon && maze_lock_m[lockn] != 2) {
					maze_lock_m[lockn] = 2;
					lock(maze_lock_x[lockn], maze_lock_y[lockn], maze_lock_m[lockn]);
					hero(hero_x, hero_y, hero_p, hero_m);
					Sleep(2500 + rand() % 5000);
					for (int i = 0; i < maze_door_n; i++) {
						if (maze_door_l[i] == lockn) {
							door(maze_door_x[i], maze_door_y[i], 2);
							maze_door_x[i] = 0;
							maze_door_y[i] = 0;
						}
					}
				}
				else {
					hero_m = 2;
					hero(hero_x, hero_y, hero_p, hero_m);
					Sleep(1000);
				}
				break;
			}
			case 'r':
			{
				speed++;
				if (speed > 32)speed = 32;
				break;
			}
			case 'f':
			{
				speed--;
				if (speed < 0)speed = 0;
				break;
			}
			}
			hero_m = 0;
			for (int i = 0; i < maze_lock_n; i++) {
				if (maze_lock_m[i] == 0 || maze_lock_m[i] == 1) {
					if ((abs(hero_x - maze_lock_x[i]) <= 5 && abs(hero_y - maze_lock_y[i] - 32) <= 5 && hero_p == 0) ||
						(abs(hero_x - maze_lock_x[i] + 32) <= 5 && abs(hero_y - maze_lock_y[i]) <= 5 && hero_p == 1) ||
						(abs(hero_x - maze_lock_x[i]) <= 5 && abs(hero_y - maze_lock_y[i] + 32) <= 5 && hero_p == 2) ||
						(abs(hero_x - maze_lock_x[i] - 32) <= 5 && abs(hero_y - maze_lock_y[i]) <= 5 && hero_p == 3)) {
						hero_m = 1;
						maze_lock_m[i] = 1;
						lockn = i;
						lockon = 1;
						lock(maze_lock_x[i], maze_lock_y[i], 1);
						for (int j = 0; j < maze_door_n; j++) {
							if (maze_door_l[j] == i) {
								door(maze_door_x[j], maze_door_y[j], 1);
							}
						}
						break;
					}
					else {
						maze_lock_m[i] = 0;
					}
				}
			}
			if (lockon == 1 && maze_lock_m[lockn] == 0) {
				lockon = 0;
				lock(maze_lock_x[lockn], maze_lock_y[lockn], maze_lock_m[lockn]);
				for (int j = 0; j < maze_door_n; j++) {
					if (maze_door_l[j] == lockn) {
						door(maze_door_x[j], maze_door_y[j], 0);
					}
				}

			}
			scrn.X = 10; scrn.Y = 0;
			SetConsoleCursorPosition(h, scrn);
			cout << "  ";
			scrn.X = 10; scrn.Y = 0;
			SetConsoleCursorPosition(h, scrn);
			cout << speed;
			hero(hero_x, hero_y, hero_p, hero_m);
			if (hero_x >= 290 && hero_x <= 318 && hero_y == 16) {
				system("cls");
				cout << "Вы победили";
				system("timeout /nobreak /t 2");
				system("pause");
				return 0;
			}
		}
	}
}