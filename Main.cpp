#include <FEHUtility.h>
//#include <FEHIO.h>
#include <FEHLCD.h>
//#include <FEHImages.h>
#include "FEHImages.h"
#include <math.h>
#include <FEHRandom.h>
#define left_bound 0
#define right_bound 320
#define top_bound 0
#define bottom_bound 240

class Bullet
{
public:
    Bullet();
    Bullet(int startX, int startY);
    void drawSelf(int, int);
    int x;
    int y;

private:
    int startX;
    int startY;
};
Bullet::Bullet(int startX, int startY)
{
    x = startX;
    y = startY;
}
Bullet::Bullet()
{
    x = 0;
    y = 0;
}
void Bullet::drawSelf(int x, int y)
{
    LCD.DrawRectangle(x + 5, y, 2, 2);
}

class Enemy
{
private:
    int type;

public:
    Enemy();
    int x;
    int y;
    void drawSelf();
    bool toRender;
};

Enemy::Enemy()
{
    type = 0;
    toRender = true;
    x = 0;
    y = 0;
}
void Enemy::drawSelf()
{
    if (toRender)
    {
        FEHIMAGE invader;
        invader.Open("Invader2FEH.pic");
        invader.Draw(y, x);
    }
    else
    {
        LCD.SetFontColor(WHITE);
        //deletes enemy when it's been hit
        // don't do anything now, we're not rendering this
    }
}

class Enemies
{
public:
    Enemies();
    void drawEnemies();
    void shiftEnemies();
    void shoot(int, int);
    bool checkCollisionWithFloor();
    bool checkCollision(Bullet);
    int num_enemiesx = 11;
    int num_enemiesy = 7;
    Enemy enemiesArray[11][7];
    Bullet enemyBullet;

private:
    //Bullet firedBullets;
    int totalEnemiesRemaining;
    int x;
    int y;
    int width;
    int height;
    bool shift_Down;
};
Enemies::Enemies()
{
    x = 0;
    y = 30;
    width = 114;
    height = 51;
    shift_Down = false;
}
/*
bool Enemies::hasWon(&player)
{
    if (player.points == 530){

        return true;
    }
    
    int i = 0;
    int k = 0;
    int checkVal = num_enemiesy * num_enemiesx;
    int sum = 0;
    for (i = 0; i < num_enemiesx; i++)
    {
        for (k = 0; k < num_enemiesy; k++)
        {
            if (!enemiesArray[i][k].toRender)
            {
                sum += 1;
            }
            if (checkVal == sum)
            {
                return true;
            }
        }
    }
    
    return false;
}
*/
void Enemies::shoot(int playerX, int playerY)
{
    int i = 0;
    int k = 0;
    int count = 0;
    int randomNumber;
    Enemy existingEnemies[11];
    for (i = 0; i < 11; i++)
    {
        if (enemiesArray[i][k].toRender)
        {
            existingEnemies[count] = enemiesArray[i][k];
            count++;
        }
    }
    randomNumber = (Random.RandInt() / 32767.0) * 11;
    //LCD.WriteLine(randomNumber);
    //Sleep(10.0);
    //int offset = playerX + count;
    enemyBullet.x = enemiesArray[randomNumber][0].x;
    enemyBullet.y = enemiesArray[randomNumber][0].y;
    LCD.WriteLine(enemyBullet.x);
    enemyBullet.drawSelf(enemyBullet.x, enemyBullet.x);
}

bool Enemies::checkCollisionWithFloor()
{
    int i = 0;
    int k = 0;
    for (i = 0; i < num_enemiesx; i++)
    {
        for (k = 0; k < num_enemiesy; k++)
        {
            if (enemiesArray[i][k].y >= 220)
            {
                if (!enemiesArray[i][k].toRender)
                {
                    return false;
                }
                else
                {
                    return true;
                }
            }
        }
    }
    return false;
}
bool Enemies::checkCollision(Bullet playerBullet)
{
    int i = 0;
    int k = 0;
    for (i = 0; i < num_enemiesx; i++)
    {
        for (k = 0; k < num_enemiesy; k++)
        {
            if (((abs(playerBullet.x - (enemiesArray[i][k].x)) <= 13) & ((abs(playerBullet.y - enemiesArray[i][k].y) <= 13))))
            {
                if (!enemiesArray[i][k].toRender)
                {
                    return false;
                }
                else
                {
                    enemiesArray[i][k].toRender = false;
                    return true;
                }
            }
        }
    }
    return false;
}

void Enemies::shiftEnemies()
{
    if ((x + 182 != 302) & !shift_Down)
    {
        x += 20;
        shift_Down = false;
    }
    if ((x > 0) & shift_Down)
    {
        x -= 20;
        if (x == 0)
        {
            shift_Down = false;
        }
    }
    if (x + 182 == 302)
    {
        y += 20;
        shift_Down = true;
    }
    if (x == 0)
    {
        y += 20;
        shift_Down = false;
    }
}

void Enemies::drawEnemies()
{
    int j = 0;
    int k = 0;
    int y_pos;
    for (int i = 0; i < 7; i++)
    {
        y_pos = i * 14;
        for (k = 0; k < 11; k++)
        {
            enemiesArray[i][k].x = x + 17 * k;
            enemiesArray[i][k].y = y + y_pos;
            enemiesArray[i][k].drawSelf();
        }
    }
}
class Player1
{
public:
    Player1();
    void drawSelf(int);
    bool enemyCollision(Enemies *e);
    bool hasWon();
    //void updatePosition();
    int lives = 3;
    int pos = 140;
    int score;

private:
    int bullet_pos;
    char name[30];
    //int points;
    int i = 220;
    int x_coordinate;
};

bool Player1::hasWon()
{
    if (score == 530)
    {
        return true;
    }
    return false;
}

bool Player1::enemyCollision(Enemies *e)
{
    int i = 0;
    int k = 0;
    for (i = 0; i < e->num_enemiesx; i++)
    {

        for (k = 0; k < e->num_enemiesy; k++)
        {
            if ((e->enemiesArray[i][k].toRender) & (e->enemiesArray[i][k].y > 220))
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
    return false;
}
Player1::Player1()
{
    score = 0;
    lives = 3;
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
    FEHIMAGE ship;
    ship.Open("SpaceShipFEH.pic");
    ship.Draw(220, pos);
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
void SaveDataToSD()
{
}
void LoadAndCheckDataFromSD()
{
}

void playGameUI(Player1 *player)
{

    LCD.DrawRectangle(0, 0, 320, 30);
    LCD.DrawRectangle(0, 30, 320, 200);
    LCD.DrawRectangle(0, 0, 60, 30);
    LCD.SetFontColor(RED);
    LCD.FillRectangle(0, 0, 60, 30);
    LCD.SetFontColor(WHITE);
    LCD.WriteAt("Back", 2, 6);
    LCD.WriteAt("Lives: ", 60, 6);
    LCD.WriteAt(("%f", player->lives), 130, 6);
    LCD.WriteAt("Score: ", 200, 6);
    LCD.WriteAt(("%f", player->score), 270, 6);
}

void playGameScreen(int *returnVal)
{
    float x, y;
    //float bulletY;
    //float bulletX;
    float time;
    float time2 = 0;
    time = TimeNow();
    float timeElapsed = 0;
    float time2Elapsed = 0;
    LCD.Clear();
    Player1 player;
    Enemies e;
    e.drawEnemies();
    playGameUI(&player);
    // Put game logic here
    player.drawSelf(160);
    Bullet firedBullet(160, 100);
    while (1)
    {

        timeElapsed = TimeNow() - time;
        if (LCD.Touch(&x, &y))
        {
            player.drawSelf(x);
            if (((x < 30) & (x > 0)) & ((y > 0) & (y < 60)))
            {
                *returnVal = 4;
                break;
            }
        }
        timeElapsed = TimeNow() - time;
        if (timeElapsed > 0.00167)
        {
            LCD.Clear();
            player.drawSelf(x);
            firedBullet.y = firedBullet.y - 2.67;
            e.enemyBullet.y = e.enemyBullet.y + 2.67;
            if (firedBullet.y > 30)
            {
                firedBullet.drawSelf(firedBullet.x, firedBullet.y);
            }
            //LCD.WriteLine("Score update here");
            else
            {
                firedBullet.y = 220;
                firedBullet.x = player.pos;
                firedBullet.drawSelf(firedBullet.x, firedBullet.y);
            }
            if (e.enemyBullet.y < 220)
            {
                LCD.SetFontColor(RED);
                e.enemyBullet.drawSelf(e.enemyBullet.x, e.enemyBullet.y);
                LCD.SetFontColor(WHITE);
            }
            time = TimeNow();
            e.drawEnemies();
            playGameUI(&player);
        }

        time2Elapsed = TimeNow() - time2;
        if (time2Elapsed > 2.0)
        {
            e.shiftEnemies();
            e.drawEnemies();
            time2 = TimeNow();
            e.shoot(player.pos, 220);
        }
        if (e.checkCollision(firedBullet))
        {
            firedBullet.x = player.pos;
            firedBullet.y = 220;
            firedBullet.drawSelf(firedBullet.x, firedBullet.y);
            player.score += 10;
            playGameUI(&player);
        }
        if (player.enemyCollision(&e))
        {
            player.lives -= 1;
            playGameUI(&player);
        }
        if (player.hasWon())
        {
            *returnVal = 7;
            break;
        }
        if (e.checkCollisionWithFloor())
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
        LCD.WriteAt(("Lives: 3"), 20, 50);
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

    //Enemy enemies;
}

void loseScreen(int *returnVal)
{
    while (true)
    {
        float x, y;
        LCD.Clear();
        LCD.WriteAt("*You Lose*", 85, 10);
        LCD.WriteAt(("Points: 20"), 85, 40);
        LCD.DrawRectangle(100, 120, 85, 20);
        LCD.WriteAt("Replay", 105, 121);
        LCD.DrawRectangle(100, 150, 130, 20);
        LCD.WriteAt("Main Menu", 105, 151);
        if (LCD.Touch(&x, &y))
        {
            if (((x > 100) & (x < 160)) & ((y > 120) & (y < 140)))
            {
                *returnVal = 0;
                break;
            }
            if (((x > 100) & (x < 160)) & ((y > 150) & (y < 170)))
            {
                *returnVal = 4;
                break;
            }
        }
    }
}

void winScreen(int *returnVal)
{
    while (true)
    {
        float x, y;
        LCD.Clear();
        LCD.WriteAt("*You Win*", 90, 10);
        LCD.WriteAt("High Score: ", 60, 190);
        LCD.WriteAt(("Points:"), 85, 40);
        LCD.DrawRectangle(100, 120, 85, 20);
        LCD.WriteAt("Replay", 105, 121);
        LCD.DrawRectangle(100, 150, 130, 20);
        LCD.WriteAt("Main Menu", 105, 151);
        if (LCD.Touch(&x, &y))
        {
            if (((x > 100) & (x < 160)) & ((y > 120) & (y < 140)))
            {
                *returnVal = 0;
                break;
            }
            if (((x > 100) & (x < 160)) & ((y > 150) & (y < 170)))
            {
                *returnVal = 4;
                break;
            }
        }
    }
}

void startScreen(int *returnVal)
{
    LCD.Clear();
    float x, y;
    while (1)
    {
        LCD.SetBackgroundColor(BEIGE);
        LCD.SetFontColor(RED);
        LCD.WriteAt("*Space Invaders*", 70, 10);
        LCD.SetFontColor(BURLYWOOD);
        LCD.DrawRectangle(10, 30, 300, 40);
        LCD.DrawRectangle(10, 70, 300, 40);
        LCD.DrawRectangle(10, 110, 300, 40);
        LCD.DrawRectangle(10, 150, 300, 40);
        LCD.DrawRectangle(10, 190, 300, 40);
        LCD.WriteAt("Play Game", 10, 32);
        LCD.WriteAt("Statistics", 10, 72);
        LCD.WriteAt("Credits", 10, 112);
        LCD.WriteAt("Exit", 10, 152);
        LCD.WriteAt("Instructions", 10, 192);
        if (LCD.Touch(&x, &y))
        {
            if (((x < 300) & (x > 10)) & ((y > 30) & (y < 70)))
            {
                LCD.Clear();
                *returnVal = 0;
                LCD.SetBackgroundColor(BLACK);
                break;
            }
            if (((x < 300) & (x > 10)) & ((y > 70) & (y < 110)))
            {
                *returnVal = 1;
                break;
            }
            if (((x < 300) & (x > 10)) & ((y > 110) & (y < 150)))
            {
                *returnVal = 2;
                LCD.SetBackgroundColor(BLACK);
                break;
            }
            if (((x < 300) & (x > 10)) & ((y > 150) & (y < 190)))
            {
                *returnVal = 3;
                break;
            }
            if (((x < 300) & (x > 10)) & ((y > 190) & (y < 230)))
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
        case 7:
            winScreen(&returnValue);
            Sleep(.1);
            break;
        }
        if (shouldExit)
        {
            return 1;
        }
    }
}
