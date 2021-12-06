#include <FEHUtility.h>
//#include <FEHIO.h>
#include <FEHLCD.h>
#include <pthread.h>
#define left_bound 0
#define right_bound 320 
#define top_bound 0
#define bottom_bound 240
class Enemy{
    public:
    void drawSelf();
    void shapeSelect();
    
    private:
    int bullet_pos = 0;
    
    
};
class Bullet
{
    public:
        Bullet(int startX, int startY);
        void drawSelf(int, int);
        bool doesExist();
    private:
        int startX;
        int startY;
        int x;
        int y;

};
Bullet::Bullet(int startX, int startY){
    x = startX;
    y = startY;
}
void Bullet::drawSelf(int x, int y)
{
    LCD.DrawCircle(x, y, 1);
}
bool Bullet::doesExist(){
    if (y > 30){
        return true;
    } else {
        return false;
    }
}


class Player1
{
public:
    Player1();
    void drawSelf(int);
    //void updatePosition();
    void shoot();
    void shoot2();
    int lives = 3;

private:
    int pos = 140;
    int bullet_pos;
    char name[30];
    int points;
    int i = 220;
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
    else if ((x > 310) | (x == 300))
    {
        pos = 310;
    }
    LCD.DrawRectangle(pos, 220, 10, 10);
    LCD.FillRectangle(pos, 220, 10, 10);
    LCD.DrawCircle(bullet_pos, i, 1);

    
}
/*
void Player1::shoot()
{
    bullet_pos = pos + 4;
}
*/
void Player1::shoot2()
{
    bullet_pos = pos + 4;
    
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


void playGameScreen(int *returnVal)
{
    float x, y;
    float bulletY;
    float bulletX;
    float time;
    time = TimeNow();
    float timeElapsed = 0;
    LCD.Clear();
    Player1 player;
    // Put game logic here
    player.drawSelf(160);
    Bullet firedBullet(160, 100);
    while (1)
    {
        timeElapsed = TimeNow() - time;
        if (LCD.Touch(&x, &y))
        {
            player.drawSelf(x);
        }
        timeElapsed = TimeNow() - time;
        if (timeElapsed > 0.0167) {
            LCD.Clear();
            player.drawSelf(x);
            bulletY = bulletY - 2.67;
            if (bulletY > 30){
                firedBullet.drawSelf(bulletX, bulletY);
            } else {
                bulletY = 220;
                bulletX = x;
                firedBullet.drawSelf(bulletX, bulletY);
            }
            time = TimeNow();
        }
        if (player.lives == 0)
        {
            *returnVal = 6;
            break;
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
        case 6:
            loseScreen(&returnValue);
            Sleep(.1);
            break;
        }
        if (shouldExit)
        {
            return 1;
        }
    }
}
