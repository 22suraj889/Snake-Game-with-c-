#include <bits/stdc++.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
using namespace std;

bool game_over;
const int width = 20, height = 20;
int x, y, score,tail_count;
int fruit_X, fruit_Y;
int tail_X[100], tail_Y[100];
enum direction
{
    STOP = 0,
    UP,
    LEFT,
    RIGHT,
    DOWN
};
direction dir;
void set_data()
{
    game_over = false;
    x = width / 2;
    y = height / 2;
    fruit_X = (rand() % width);
    fruit_Y = (rand() % height);
    dir = STOP;
    score = 0;
}
void draw()
{

    system("CLS");
    for (int i = 0; i < width+2; i++)
        cout<<"-";
        cout<<endl;

    for(int i=0; i<height; i++){

        for(int j=0; j<width; j++){
            if(j==0 && i<=1){
                cout<<" ";
            }
            if(j==0 && i>1)
                cout<<"|";

            if(i==y && j==x)
                cout<<"O";
            else if(i==fruit_Y && j==fruit_X)
                cout<<"F";
            else{
                bool print_tail = false;
                for(int k=0; k<tail_count; k++){
                    if(i==tail_Y[k] && j==tail_X[k]){
                        cout<<"*";
                        print_tail = true;
                    }
                }
                if(!print_tail)
                    cout<<" ";
            }

            if(j==width-1 && i<width-2)
                cout<<"|";
        }
        cout<<endl;
    }
    for (int i = 0; i < width+2; i++)
        cout<<"-";
    cout << "\nScore: " << score << endl;
}

void input()
{

    if (_kbhit())
    {
        switch (getch())
        {
        case 'w':
            dir = UP;
            break;
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            game_over = true;
            break;
        }
    }
}

void logic()
{
    int first_tail_X = tail_X[0];
    int first_tail_Y = tail_Y[0];
    int next_tail_X, next_tail_Y;
    tail_X[0]=x;
    tail_Y[0]=y;
    for(int i=1; i<tail_count; i++){
        next_tail_X = tail_X[i];
        next_tail_Y = tail_Y[i];
        tail_X[i] = first_tail_X;
        tail_Y[i] = first_tail_Y;
        first_tail_X = next_tail_X;
        first_tail_Y = next_tail_Y;
    }
    switch (dir)
    {
    case UP:
        y--;
        break;
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case DOWN:
        y++;
        break;
    }
    if(x>=width && (y==height-1 || y==height-2)){
        x = 0;
        y = 1;
    }
    else if(x<0 && (y==0 || y==1)){
        x = width-1;
        y = height-1;
    }
    if (x > width || x < 0 || y > height || y < 0)
    {
        game_over = true;
    }
    for(int i=0; i<tail_count; i++){
        if(tail_X[i]==x && tail_Y[i]==y){
            game_over = true;
        }
    }

    if (x == fruit_X && y == fruit_Y)
    {
        fruit_X = (rand() % width);
        fruit_Y = (rand() % height);
          score += 10;
          tail_count++;
    }
}

int main()
{
    set_data();
    while (!game_over)
    {
        draw();
        input();
        logic();
        Sleep(30);
    }

    return 0;
}



