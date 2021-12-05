#include <FEHUtility.h>
//#include <FEHIO.h>
#include <FEHLCD.h>
/*
class Bullet
{
public:
    Bullet();
    void render_bullet();
    void render();

private:
    int bullet_pos;
    int pos = 140;
    int x;
};
Bullet::Bullet(){

}

void Bullet::render_bullet(){
    LCD.Clear();
    pos = x;
    if (((x == 0) | (x < 0)))
    {
        pos = 0;
    }
    else if ((x > 300) | (x == 300))
    {
        pos = 300;
    }
}

void Bullet::render(){

}
*/
class Player1
{
public:
    Player1();
    void drawSelf(int);
    //void updatePosition();
    void shoot();
    void shoot2();

private:
    int pos = 140;
    int bullet_pos;
    char name[30];
    int points;
    int i;
    int lives = 3;
    int x_coordinate;
};
Player1::Player1()
{
}
void Player1::drawSelf(int x)
{
    LCD.Clear();
    pos = x;
    if (((x == 0) | (x < 0)))
    {
        pos = 0;
    }
    else if ((x > 300) | (x == 300))
    {
        pos = 300;
    }
    LCD.DrawRectangle(pos, 220, 10, 10);
    LCD.FillRectangle(pos, 220, 10, 10);
    LCD.DrawCircle(bullet_pos, i, 1);
}
/*
void Player1::updatePosition(){
    float x, y;
    pos = 140;
    while(LCD.Touch(&x, &y)){
        if(((x < 30) & (x > 0)) & ((y < 220) & (y > 240))){
            pos -= 1;
            LCD.Clear();
            LCD.DrawRectangle(pos ,220, 20, 20);
            LCD.FillRectangle(pos , 220, 20, 20);
        }
        else if(((x < 320) & (x > 290)) & ((y < 220) & (y > 240))){
            pos += 1;
            LCD.Clear();
            LCD.DrawRectangle(pos ,220, 20, 20);
            LCD.FillRectangle(pos , 220, 20, 20);
        }
    }
}
*/

void Player1::shoot()
{
    bullet_pos = pos + 4;
}

void Player1::shoot2()
{

    LCD.DrawCircle(bullet_pos, 210, 1);
    for (i = 210; i > 0; i--)
    {
        LCD.Clear();
        LCD.DrawCircle(bullet_pos, i, 1);
        Sleep(1);
        LCD.SetFontColor(WHITE);
    }
    if (i <= 0)
    {
        LCD.Clear();
    }
}

class Player2
{
public:
    Player2(int *initLocation);
    void drawSelf();

private:
    int points;
    int lives;
    int x_coordinate;
};

Player2::Player2(int *initLocation)
{
}

class allEnemies
{
};
class Ememy
{
public:
    void drawSelf()
    {
    }

private:
    int type;
};

void playGameScreen(int *returnVal)
{
    float x, y;
    LCD.Clear();
    Player1 player;
    // Put game logic here
    player.drawSelf(160);
    while (1)
    {
        if (LCD.Touch(&x, &y))
        {
            player.drawSelf(x);
            player.shoot();
            player.shoot2();
            /*
        LCD.WriteAt("Back", 10, 10);
        LCD.WriteAt("Gameplay goes here", 150,150);
        if (LCD.Touch(&x, &y)){
            if(((x < 70) & (x > 10)) &((y < 35) & (y > 10))){
                *returnVal = 4;
                break;
            } 
        }
        */
        }
    }
}
void statScreen(int *returnVal)
{
    float x, y;
    LCD.Clear();
    while (1)
    {
        LCD.DrawRectangle(10, 10, 200, 200);
        LCD.WriteAt("Statistics", 100, 10);
        LCD.WriteAt("Lives: 3", 20, 50);
        LCD.WriteAt("Points: 42", 20, 80);
        LCD.DrawRectangle(10, 10, 60, 25);
        LCD.WriteAt("Back", 10, 10);
        if (LCD.Touch(&x, &y))
        {
            if (((x < 70) & (x > 10)) & ((y < 35) & (y > 10)))
            {
                *returnVal = 4;
                break;
            }
        }
    }
}

void creditScreen(int *returnVal)
{
    LCD.Clear();
    float x, y;
    while (1)
    {
        LCD.DrawRectangle(10, 10, 60, 25);
        LCD.WriteAt("Back", 10, 10);
        LCD.WriteAt("Credits screen", 10, 150);
        if (LCD.Touch(&x, &y))
        {
            if (((x < 70) & (x > 10)) & ((y < 35) & (y > 10)))
            {
                *returnVal = 4;
                break;
            }
        }
    }
}
void instructScreen(int *returnVal)
{
    float x, y;
    LCD.Clear();
    while (1)
    {
        LCD.WriteAt("Instructions:", 100, 10);
        LCD.WriteAt("Your objective is to", 10, 40);
        LCD.WriteAt("shoot the enemy coming", 10, 70);
        LCD.WriteAt("towards you. Use the", 10, 100);
        LCD.WriteAt("Fire button to shoot a", 10, 130);
        LCD.WriteAt("laser. Use the left and", 10, 160);
        LCD.WriteAt("right arrows to change", 10, 190);
        LCD.WriteAt("direction.", 10, 220);
        LCD.WriteAt("Back", 10, 10);
        if (LCD.Touch(&x, &y))
        {
            if (((x < 70) & (x > 10)) & ((y < 35) & (y > 10)))
            {
                *returnVal = 4;
                break;
            }
        }
    }
}

void loseScreen(int *returnVal)
{

    float x, y;
    LCD.Clear();
    LCD.WriteAt("*You Lose*", 80, 10);
    LCD.WriteAt(("Points: 20"), 20, 40);
    LCD.DrawRectangle(100, 120, 60, 20);
    LCD.WriteAt("Replay", 105, 121);
    LCD.DrawRectangle(100, 150, 60, 20);
    LCD.WriteAt("Main Menu", 105, 151);
    if (LCD.Touch(&x, &y))
    {
        if (((x > 100) & (x < 160)) & ((y > 120) & (y < 140)))
        {
            *returnVal = 0;
        }
        if (((x > 100) & (x < 160)) & ((y > 150) & (y < 170)))
        {
            *returnVal = 4;
        }
    }
}

void winScreen(int *returnVal)
{

    float x, y;
    LCD.Clear();
    LCD.WriteAt("*You Win*", 80, 10);
    LCD.WriteAt("High Score: ", 20, 190);
    LCD.WriteAt(("Points: 20"), 20, 40);
    LCD.DrawRectangle(100, 120, 60, 20);
    LCD.WriteAt("Replay", 105, 121);
    LCD.DrawRectangle(100, 150, 60, 20);
    LCD.WriteAt("Main Menu", 105, 151);
    if (LCD.Touch(&x, &y))
    {
        if (((x > 100) & (x < 160)) & ((y > 120) & (y < 140)))
        {
            *returnVal = 0;
        }
        if (((x > 100) & (x < 160)) & ((y > 150) & (y < 170)))
        {
            *returnVal = 4;
        }
    }
}

void startScreen(int *returnVal)
{
    LCD.Clear();
    float x, y;
    while (1)
    {
        LCD.SetBackgroundColor(GRAY);
        LCD.SetFontColor(RED);
        LCD.WriteAt("*Space Invaders*", 75, 10);
        LCD.SetFontColor(WHITE);
        LCD.DrawRectangle(10, 30, 310, 40);
        LCD.DrawRectangle(10, 70, 310, 40);
        LCD.DrawRectangle(10, 110, 310, 40);
        LCD.DrawRectangle(10, 150, 310, 40);
        LCD.DrawRectangle(10, 190, 310, 40);
        //LCD.WriteAt("Welcome To Space-Invaders", 0, 0);
        //LCD.DrawCircle(150,150, 30);
        //LCD.WriteAt("Stats", 150, 150);
        LCD.WriteAt("Play Game", 10, 30);
        LCD.WriteAt("Statistics", 10, 70);
        LCD.WriteAt("Credits", 10, 110);
        LCD.WriteAt("Exit", 10, 150);
        LCD.WriteAt("Instructions", 10, 190);
        if (LCD.Touch(&x, &y))
        {
            if (((x < 310) & (x > 10)) & ((y > 30) & (y < 70)))
            {
                //LCD.WriteLine("Play Game Recorded");
                LCD.Clear();
                *returnVal = 0;
                LCD.SetBackgroundColor(BLACK);
                break;
            }
            if (((x < 310) & (x > 10)) & ((y > 70) & (y < 110)))
            {
                *returnVal = 1;
                break;
            }
            if (((x < 310) & (x > 10)) & ((y > 110) & (y < 150)))
            {
                *returnVal = 2;
                LCD.SetBackgroundColor(BLACK);
                break;
            }
            if (((x < 310) & (x > 10)) & ((y > 150) & (y < 190)))
            {
                *returnVal = 3;
                break;
            }
            if (((x < 310) & (x > 10)) & ((y > 190) & (y < 230)))
            {
                *returnVal = 5;
                break;
            }
            else
            {
                *returnVal = 4;
                break;
            }
        }
    }
}

int main()
{
    int returnValue;
    bool shouldExit;
    startScreen(&returnValue);
    while (1)
    {
        switch (returnValue)
        {
        case 0:
            playGameScreen(&returnValue);
            Sleep(.1);
            break;
        case 1:
            statScreen(&returnValue);
            Sleep(.1);
            break;
        case 2:
            creditScreen(&returnValue);
            Sleep(.1);
            break;
        case 3:
            shouldExit = true;
            break;
        case 4:
            startScreen(&returnValue);
            Sleep(.1);
            break;
        case 5:
            instructScreen(&returnValue);
            Sleep(.1);
            break;
        }
        if (shouldExit)
        {
            return 1;
        }
    }
}
