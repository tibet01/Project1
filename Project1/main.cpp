﻿#include<stdio.h>
#include<Windows.h>
#include<conio.h>
#include<time.h>
int point = 0, check_star[75][5] = {};
void draw_ship(int, int);
void gotoxy(int, int);
void erase_ship(int, int);
void setcursor(bool);
void setcolor(int, int);
void draw_shot(int, int);
void erase_shot(int, int);
void draw_star(int, int);
void erase_star(int, int);
void score(int, int);
char cursor(int, int);

int main() {
	int x = 38, y = 20,new_star_x,new_star_y, position_x[5], position_y[5], shot[5] = {}, num = 0, star, star_x[20], star_y[20], star_1 = 0;
	char ch = ' ';
	setcursor(0);
	srand(time(NULL)); 
	cursor(1, 3);

	for (star = 0; star < 20; star++) 
	{
		while (check_star[star_x[star]][star_y[star]]==1)
		{
			star_x[star] = (rand() % 61) + 10;	 
			star_y[star] = (rand() % 4) + 1;
		} 
		draw_star(star_x[star], star_y[star]);
	}

	draw_ship(x, y);
	
	do {
		score(x, y); 
		if (_kbhit()) {
			ch = _getch();
			if (ch == 'a') {
				num = 1;
			}

			if (ch == 'd') {
				num = 2;
			}


			if (ch == 's') {   
				num = 3;
			}


			if (ch == ' ') {   

				for (int i = 0; i < 5; i++) { 
					if (shot[i] == 0) {

						shot[i] = 1;		
						position_x[i] = x + 2;  // ใช้ค่าตน.ของยานมาให้เท่ากับ ตัวแปร position    // *** และให้กรสุนมันขยับไปตรงกลางยานโดยการ +2
						position_y[i] = y - 1;

						draw_shot(position_x[i], position_y[i]); // ใช้ค่า x เป็นค่าของยาน เลยเป็นยานออกมา
						break;

					}
				}
			}

			fflush(stdin);
		} 

		if (num == 1 && x > 0)   
		{
			erase_ship(x, y); 
			draw_ship(--x, y);
		}
		if (num == 2 && x < 73)	 
		{
			erase_ship(x, y); 
			draw_ship(++x, y);
		}  


		for (int i = 0; i < 5; i++) {
			if (shot[i] == 1)    //ค่าที่รับจากลูปด้านบน เปิดค่าให้มันยิงมา
			{

				erase_shot(position_x[i], position_y[i]); 


				if (position_y[i] > 0) {     

					position_y[i] = position_y[i] - 1; 


					if (cursor(position_x[i], position_y[i]) == '*') {  

						shot[i] = 0;								
						erase_star(position_x[i], position_y[i]);
						erase_shot(position_x[i], position_y[i]);
						Beep(900, 300);  //ให้เกิดเสียง
						draw_star(rand() % 65, rand() % 5);   // ให้ดาวเกิดสุ่มเรื่อยๆ หลังโดนยิงไป 1 อัน 
						point+=1;  // เมื่อยิงโดน ให้เพิ่มค่าscore ทีละ 1 

					}

					else 
					{
						draw_shot(position_x[i], position_y[i]); //จาก  position_y[i] - 1 ถ้ามันยังไม่น้อยกว่า 0 (ต่อข้อความข่างล่าง)
																// มันก็จะวาดอันใหม่ที่ตำแหน่งโดนลบไป 1 แล้วจากด้านบนที่ลบไป
					}

				}
				else // ถ้าเกินให้เซ้ตค่า ตัวรับว่ายิง เป็น 0 เพื่อให้ยินใหม่ได้
				{
					erase_shot(position_x[i], position_y[i]);
					shot[i] = 0;
				}


			}
		}
		Sleep(100);
	} while (ch != 'x');  setcolor(7, 0);


	return 0;
}


char cursor(int x, int y) {
	HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
	char buf[2]; COORD c = { x,y }; DWORD num_read;
	if (!ReadConsoleOutputCharacter(hStd, (LPTSTR)buf, 1, c, (LPDWORD)&num_read))
		return '\0';
	else
		return buf[0];
}

void score(int x, int y) {  
	setcolor(5, 0);
	gotoxy(81, 1);
	printf("SCORE : %d ", point); 

}

void gotoxy(int x, int y) {    
	COORD c = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void draw_ship(int x, int y) {
	setcursor(0);
	gotoxy(x, y);
	setcolor(2, 4);  
	printf("<-0->");

}

void erase_ship(int x, int y) {
	gotoxy(x, y);
	setcolor(0, 0);
	printf("      ");
}

void setcursor(bool visible) {

	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}

void setcolor(int fg, int bg) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}

void erase_shot(int x, int y) {		//ลบรูปกระสุน
	gotoxy(x, y);
	setcolor(0, 0);
	printf(" ");

}

void draw_shot(int x, int y) {		//วาดรูปกระสุน
	gotoxy(x, y);
	setcolor(5, 0);
	printf("|");
}

void draw_star(int x, int y) {   //วาดดาว
	gotoxy(x, y);
	setcolor(6, 0);
	printf("*");
	check_star[x][y] = 1;
}

void erase_star(int x, int y) {		//ลบดาว
	gotoxy(x, y);
	setcolor(0, 0);
	printf(" ");
	check_star[x][y] = 0;
}