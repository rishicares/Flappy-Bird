#include <iostream>
#include <graphics.h>
#include <cstdlib>
#include <fstream>
using namespace std;
int score = 0;
bool live = true;

class Pole;
void start();
void menu();
class Player;

int random(int min, int max){
    return min + rand() % (max - min + 1);
}


class Ball
{
    int ball_x;
	float ball_y;

public:
    Ball()
    {
        ball_x = 100;
        ball_y = 300;
    }
    void draw()
    {
        setcolor(WHITE);
        circle(ball_x,ball_y,20);
        setfillstyle(1, RED);
        floodfill(ball_x, ball_y, WHITE);
        ball_y += 5;
    }
    void fly()
    {
    	static int jump_velocity=0;
    	const int gravity = 1;
        if (kbhit())
        {
            int ch = getch();
            
            if (ball_y > 16)
                jump_velocity=-16;   
        }
        jump_velocity +=gravity;
        ball_y +=jump_velocity;
        
        if(ball_y > getmaxy()){
            ball_y = getmaxy() / 2;
            jump_velocity=0;
        }
    }
    friend bool logic(Ball, Pole);
};
class Pole
{
    int width;
    int pole_x, pole_y;
    int gap;
public:
    Pole()
    {
        width = 80;
        pole_x = 600, pole_y = rand()%600;
        gap = random(150,250);
    }
    void get_pole_x_y()
    {
        width = 80;
        pole_x = 600, pole_y = rand()%550;
        gap = random(150,250);
    }
    void draw()
    {
    	setcolor(3);
        rectangle(pole_x, 0, pole_x + width, pole_y);
        setfillstyle(1, LIGHTGREEN);
        floodfill(pole_x + 3, pole_y - 2, 3);
        rectangle(pole_x, pole_y + gap, pole_x + width, pole_y + getmaxy());
        floodfill(pole_x + 3, pole_y + gap + 3, 3);

        pole_x -= 3;
        if (pole_x < -20)
            get_pole_x_y();
    }
    friend bool logic(Ball, Pole);
};
class Player
{
public:
    int score; 
public:
    Player()
    {
        score = 0;
    }
    void print_score()
    {
        char str[100];
        sprintf(str, "Score: %d", score);
        outtextxy(getmaxx() - 100, 10, str);
    }
    void score_up()
    {

       score = score+1;
       fstream outfile;
       outfile.open("score.txt", ios::out);
       outfile << score;
       outfile.close();
    }
    
    friend bool logic(Ball, Pole);
};
bool logic(Ball bb, Pole pp)
{
    char ch;
    char str2[100];
    if (bb.ball_x >= pp.pole_x && bb.ball_x <= pp.pole_x + pp.width)
        if (bb.ball_y < pp.pole_y || bb.ball_y > pp.pole_y + pp.gap)
        {
           
            settextstyle(10, 0, 6);
            outtextxy(280, 200, "Game Over");
            
            fstream infile;
            infile.open("score.txt", ios::in);
            int scorec;
            infile >> scorec;
            sprintf(str2, "Score is:%d", scorec);
            settextstyle(10, 0, 3);
            outtextxy(280, 300, str2);
            infile.close();
            
            getch();
            cleardevice();
            settextstyle(10, 0, 3);
            outtextxy(300, 200, "Play again (y/n)?");

            ch = getch();
            if (ch == 'y' || ch == 'Y')
            {
            		for (int i = 3; i > 0; i--) {
        				cleardevice();
        				settextstyle(10, 0, 6);
       					char str[20];
        				sprintf(str, "%d", i);
        				outtextxy(380, 350, str);
        				delay(1000);
    }
                start();
            }
            else if (ch == 'n' || ch == 'N')
            {
                cleardevice();
                system("cls");
                closegraph();
                menu();
            }
            else
            {
                live = false;
            }
        }
        else
        {
            return true;
        }
    else
        return false;
}
void menu()
{
    int gd1, gm1;
    initgraph(&gd1, &gm1, "");
    initwindow(800, 800, "FLAPPY BIRDS LONG LOST COUSIN!!", 250, 80);
    char uinput;
    settextstyle(10, 0, 5);
    outtextxy(300, 100, "MAIN MENU");
    settextstyle(10, 0, 3);
    outtextxy(300, 150, "Start Game");
    outtextxy(300, 200, "Previous Score");
    outtextxy(300, 250, "Exit");
    
    while(!ismouseclick(WM_LBUTTONDOWN)){
    	delay(100);
	}
    int x = mousex();
    int y = mousey();
    
    if(y>=150&&y<=170){
    	for (int i = 3; i > 0; i--) {
        cleardevice();
        settextstyle(10, 0, 6);
        char str[20];
        sprintf(str, "%d", i);
        outtextxy(380, 350, str);
        delay(1000);
    }
    	cleardevice();
        start();
	}
	else if(y>=200&&y<=220){
		delay(100);
		    int gd2, gm2;
	        initgraph(&gd2, &gm2, "");
	        initwindow(800, 800, "FLAPPY BIRDS LONG LOST COUSIN!!", 250, 80);
	        setbkcolor(8);
	        char str3[100];
	        fstream infile;
	        infile.open("score.txt", ios::in);
	        int scored;
	        infile >> scored;

	        sprintf(str3, "Previous Score is: %d", scored);
	        settextstyle(8, 0, 4);
	        outtextxy(240, 150, str3);
	        infile.close();
	        getch();	
	}
	else if(y>=250&&y<=270){
		delay(100);
		cleardevice();
        closegraph();
        system("cls");
	}
}
void start()
{
    Ball blup;
    Pole pol;
    Player plyr;
    
    int gd, gm;
    initgraph(&gd, &gm, "");
    initwindow(800, 800, "FLAPPY BIRDS LONG LOST COUSIN!!", 250, 80);
    setbkcolor(0);
    cleardevice();
    int page=0;

    while(1)
    {
        plyr.print_score();
        
        setactivepage(page);
         if (logic(blup, pol))
        {
            plyr.score_up();
        }
        setvisualpage(1-page);
    	cleardevice();
    	pol.draw();
        blup.draw();
        blup.fly();
        
      delay(30);   
      page=1-page;
    }
    getch();
    closegraph();
}
int main()
{
    system("cls");
    menu();
}