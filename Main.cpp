#include <FEHUtility.h>
//#include <FEHIO.h>
#include <FEHLCD.h>
//#include <FEHImages.h>
#include "FEHImages.h"
#include <math.h>
#include <FEHRandom.h>
#include <FEHSD.h>
#define left_bound 0
#define right_bound 320
#define top_bound 0
#define bottom_bound 240
//#define ARR_SIZE(arr) ( sizeof((arr)) / sizeof((arr[0])) )

//Define the Class Bullet
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

//Create the Bullet constructor and pass in the starting coordinates
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

//define the drawSelf function for the bullet
void Bullet::drawSelf(int x, int y)
{
    LCD.DrawRectangle(x, y, 2, 2);
}

//Create the Enemy Class and prototype the necessary functions
class Enemy
{
private:
    int type;

public:
    //initialize all the pulbic data in the the enemy class
    Enemy();
    int x;
    int y;
    void drawSelf();
    bool toRender;
};

//Enemy Constructor, set to reder by default
//All the enemies are rendered at the beginning
Enemy::Enemy()
{
    type = 0;
    toRender = true;
    x = 0;
    y = 0;
}

//Define the drawself function of the enemy class
void Enemy::drawSelf()
{
    //checks to see if it has been set to not render
    //if its set to render, this check passes
    if (toRender)
    {
        //draws the invader
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

//Creates the class Enemies, that stores and array of Enemy
//Collision handeling and random functions are used here
class Enemies
{
public:
    Enemies();
    void drawEnemies();
    void shiftEnemies();
    void shoot(int, int);
    bool checkCollisionWithFloor();
    bool checkCollision(Bullet);
    bool checkPlayerCollision(int, int);
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

//Enemies constructor
Enemies::Enemies()
{
    x = 0;
    y = 30;
    width = 114;
    height = 51;
    //shift_Down set to false by default, informs motion of the enemies
    shift_Down = false;
}

//Defines the shooting function for the enemy
void Enemies::shoot(int playerX, int playerY)
{
    int i = 0;
    int k = 0;
    int count = 0;
    //uses ransom numbers to generate a location to fire from
    int randomNumber;
    int coordinates[11][2];
    //iterates through the enemies to select entrypoint
    for (k = 0; k < 7; k++)
    {
        if (enemiesArray[i][k].toRender)
        {
            coordinates[count][0] = enemiesArray[i][k].x;
            coordinates[count][1] = enemiesArray[i][k].y;
            count++;
        }
    }
    if (count != 0)
    {
        randomNumber = Random.RandInt() % count;
        enemyBullet.x = coordinates[randomNumber][0];
        enemyBullet.y = coordinates[randomNumber][1];
        enemyBullet.drawSelf(enemyBullet.x, enemyBullet.y);
    }
}

//First collision detection software
//Checks if an enemy bullet has collided with the player
//returns true if it has
bool Enemies::checkPlayerCollision(int playerX, int playerY)
{
    if ((abs(enemyBullet.y - playerY) <= 10) & (abs(enemyBullet.x - playerX) <= 10))
    {
        this->shoot(220, 220);
        return true;
    }
    else
    {
        return false;
    }
}

//Collision function 2
//Checks if the enemies pass the "floor" @ y = 220
//This immediately cancles gameplay
bool Enemies::checkCollisionWithFloor()
{
    int i = 0;
    int k = 0;
    //iterates through the enemies list to check position of each individual enemy
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

//3rd collision function
//Checks if the player's bullet hit an enemy
//iterates through enemy positions and compares to bullet position
//if they match, function returns true
bool Enemies::checkCollision(Bullet playerBullet)
{
    int i = 0;
    int k = 0;
    for (i = 0; i < num_enemiesx; i++)
    {
        for (k = 0; k < num_enemiesy; k++)
        {
            //is the enemy touching players bullet
            if (((abs(playerBullet.x - (enemiesArray[i][k].x)) <= 13) & ((abs(playerBullet.y - enemiesArray[i][k].y) <= 13))))
            {
                //if the enemy has already been hit, return false (don't draw)
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

//Function repsonsible for enemy movment
void Enemies::shiftEnemies()
{
    //Shifts the enemies right
    if ((x + 182 != 302) & !shift_Down)
    {
        x += 20;
        shift_Down = false;
    }
    //Shifts the enemies left
    if ((x > 0) & shift_Down)
    {
        x -= 20;
        if (x == 0)
        {
            shift_Down = false;
        }
    }
    //Shift enemies down at right edge of screen
    if (x + 182 == 302)
    {
        y += 20;
        shift_Down = true;
    }
    //Shift enemies down at left edge of screen
    if (x == 0)
    {
        y += 20;
        shift_Down = false;
    }
}

//Creates and array full of Enemy instances
//Draws the enemies in a 11 x 7 grid
void Enemies::drawEnemies()
{
    int j = 0;
    int k = 0;
    int y_pos;
    //this for loop is for rows
    for (int i = 0; i < 7; i++)
    {
        //same y position for every enemy in one whole row
        y_pos = i * 14;
        //this for loop generates columns
        for (k = 0; k < 11; k++)
        {
            enemiesArray[i][k].x = x + 17 * k;
            enemiesArray[i][k].y = y + y_pos;
            enemiesArray[i][k].drawSelf();
        }
    }
}

//Creates the class Player1
class Player1
{
public:
    //sets all the public functions and variables
    Player1();
    void drawSelf(int);
    bool enemyCollision(Enemies *e);
    bool hasWon();
    //lives, score, and pos are all updated vairables
    int lives = 3;
    int pos = 140;
    int score;

private:
    int bullet_pos;
    char name[30];

    int i = 220;
    int x_coordinate;
};

//Checks to see of all the enemies are gone
//Based on the total score
//When all enemies are killed, total score is 530
bool Player1::hasWon()
{
    if (score == 530)
    {
        return true;
    }
    return false;
}

//Collision function to detect enemy - player collisions
bool Player1::enemyCollision(Enemies *e)
{
    int i = 0;
    int k = 0;
    //scans list of enemies to determine if any have the same coordinates of the player
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

//The constructor for Player 1, sets score and lives
Player1::Player1()
{
    score = 0;
    lives = 3;
}

//Draws the spaceship on screen
//Updates position so it tracks mouse
void Player1::drawSelf(int x)
{
    LCD.Clear();
    //position determination
    pos = x;
    if (((x == 0) | (x < 0)))
    {
        pos = 0;
    }
    else if ((x > 300) | (x == 300))
    {
        pos = 300;
    }
    //spaceship rendering
    FEHIMAGE ship;
    ship.Open("SpaceShipFEH.pic");
    ship.Draw(220, pos);
}

//Shows stats and back button during game
//updates the stats dynamically
void playGameUI(Player1 *player)
{
    //draws rectangles and then writes lives and score inside
    LCD.DrawRectangle(0, 0, 320, 30);
    LCD.DrawRectangle(0, 30, 320, 200);
    LCD.DrawRectangle(0, 0, 60, 30);
    LCD.SetFontColor(RED);
    LCD.FillRectangle(0, 0, 60, 30);
    LCD.SetFontColor(WHITE);
    LCD.WriteAt("Back", 2, 6);
    LCD.WriteAt("Lives: ", 60, 6);
    //updates lives based on the value in player class
    LCD.WriteAt(("%f", player->lives), 130, 6);
    LCD.WriteAt("Score: ", 200, 6);
    //updates score based on value in player class
    LCD.WriteAt(("%f", player->score), 270, 6);
}

void readHighestFromSD(int *f, int *m)
{
    int fastest;
    int mostLives;
    FEHFile *fptr = SD.FOpen("stats.txt", "r");
    SD.FScanf(fptr, "%d\n", &fastest);
    SD.FScanf(fptr, "%d", &mostLives);
    *f = fastest;
    *m = mostLives;
    SD.FClose(fptr);
}

void writeHighestToSD(int *f, int *m)
{
    int fastest;
    int mostLives;
    FEHFile *fptr = SD.FOpen("stats.txt", "r");
    SD.FScanf(fptr, "%d\n", &fastest);
    SD.FScanf(fptr, "%d", &mostLives);
    SD.FClose(fptr);
    if ((*f < fastest) & (*m >= mostLives))
    {
        FEHFile *fptr2 = SD.FOpen("stats.txt", "w+");
        SD.FPrintf(fptr2, "%d\n", *f);
        SD.FPrintf(fptr2, "%d\n", *m);
        SD.FClose(fptr2);
    }
}

//The main function of the program
//serves as the while loop to run other commands
void playGameScreen(int *returnVal, int diff, int *finalPoints)
{
    // Time used to measure the Play Time for the stats
    float time3 = TimeNow();
    float x, y;
    bool hasLostLife = true;
    float time;
    float time2 = 0;
    time = TimeNow();
    // Set up variables to time bullets and invader shifts on screen
    float timeElapsed = 0;
    float time2Elapsed = 0;
    // Clear LCD to prepare for new game
    LCD.Clear();
    // Create objects for player and enemies, and draw them.
    Player1 player;
    Enemies e;
    e.drawEnemies();
    int updateTime;
    // Draw game UI using function
    playGameUI(&player);
    // Put game logic here
    player.drawSelf(160);
    Bullet firedBullet(160, 100);
    // For Hard Diff, change the update time so that the updates actually happen in time
    if (diff == 1)
    {
        updateTime = 0.000835;
    }
    else
    {
        updateTime = 0.00167;
    }
    // Main game loop runs continuously unless broken
    while (1)
    {
        // Begin timing
        timeElapsed = TimeNow() - time;
        // Check for touch, and store in pointers to x and y
        if (LCD.Touch(&x, &y))
        {
            // Draw the player wherever they touch (allows the user to drag the player around)
            player.drawSelf(x);
            // Check for back button and return to start if pressed
            if (((x < 30) & (x > 0)) & ((y > 0) & (y < 60)))
            {
                *returnVal = 4;
                break;
            }
        }
        // Check time Elapsed for the bullet - we want the bullet to move up visibly.
        timeElapsed = TimeNow() - time;
        if (timeElapsed > updateTime)
        {
            // Clear LCD to update bullet loc, and then immediately redeaw other static elements
            LCD.Clear();
            player.drawSelf(x);
            // Update locations of both Player bullet and invader bullet
            firedBullet.y = firedBullet.y - 2.67;
            e.enemyBullet.y = e.enemyBullet.y + 2.67;
            // If Player bullet is at the edge of the screen, redraw it at the player so they can "fire" it again
            if (firedBullet.y > 30)
            {
                firedBullet.drawSelf(firedBullet.x, firedBullet.y);
            }
            //LCD.WriteLine("Score update here");
            else // Or, continue to track the bullet up
            {
                firedBullet.y = 220;
                firedBullet.x = player.pos;
                firedBullet.drawSelf(firedBullet.x, firedBullet.y);
            }
            if (e.enemyBullet.y < 220) // Same logic for the enemy bullet
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
        if (time2Elapsed > diff) // Shift the invaders using Enemies::Shift
        {
            e.shiftEnemies();
            e.drawEnemies();
            time2 = TimeNow();
            e.shoot(player.pos, 220);
            hasLostLife = false;
        }
        //Checks to see if the fired bullet hits an enemy
        //if the bullet does, update the gameUI with the new score
        //Also delet the enemy that was hit
        if (e.checkCollision(firedBullet))
        {
            firedBullet.x = player.pos;
            firedBullet.y = 220;
            firedBullet.drawSelf(firedBullet.x, firedBullet.y);
            player.score += 10;
            playGameUI(&player);
        }
        //Checks to see if the player collides with enemy bullet
        //If it does, subtract one from players lives
        if (e.checkPlayerCollision(player.pos, 220))
        {
            if (!hasLostLife)
            {
                player.lives = player.lives - 1;
                hasLostLife = true;
            }
        }
        //checks if player has killed all enemies

        if (player.hasWon())
        {
            int finalTimeElapsed = TimeNow() - time3;
            writeHighestToSD(&finalTimeElapsed, &player.lives);
            *returnVal = 7;
            *finalPoints = player.score;
            break;
        }
        //Check to see if the enemies collide with the floor
        //If they do, send the game to losescreen via returnVal = 6
        if (e.checkCollisionWithFloor() | player.lives == 0)
        {
            *returnVal = 6;
            *finalPoints = player.score;
            break;
        }
    }
}

//Draws the statistics screen
void statScreen(int *returnVal)
{
    int fastest;
    int mostLives;
    //calls function to read from the sd the high score of all time
    readHighestFromSD(&fastest, &mostLives);
    float x, y;
    LCD.Clear();
    while (1)
    {
        //Draws the information loaded from the sd card dynamically
        LCD.DrawRectangle(10, 10, 300, 220);
        LCD.WriteAt("Statistics", 100, 10);
        LCD.WriteAt("Most Lives Remaining: ", 20, 50);
        LCD.WriteAt(("%d", mostLives), 270, 50);
        LCD.WriteAt("Fastest to complete: ", 20, 80);
        LCD.WriteAt(("%d s", fastest), 200, 100);
        LCD.DrawRectangle(10, 10, 60, 25);
        LCD.WriteAt("Back", 10, 10);
        //checks to see if the back button is pressed
        //if it is, returnVal set to 4 to go back to main menu
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

//Draws the credits screen
void creditScreen(int *returnVal)
{
    LCD.Clear();
    float x, y;
    while (1)
    {
        //include back button
        LCD.DrawRectangle(10, 10, 60, 25);
        LCD.WriteAt("Back", 10, 10);
        //draws the names of the creators
        LCD.WriteAt("Dhruv Venkataraman", 10, 70);
        LCD.WriteAt("Nick White", 10, 110);
        //checks for touch on the back button
        //if touched returnVal is set to 4 to go back to main menu
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

//Draws the instruction screen
void instructScreen(int *returnVal)
{
    float x, y;
    LCD.Clear();
    while (1)
    {
        //Instructions drawn here
        LCD.WriteAt("Instructions:", 100, 10);
        LCD.WriteAt("Your objective is to", 10, 40);
        LCD.WriteAt("shoot the enemy coming", 10, 70);
        LCD.WriteAt("towards you. Position", 10, 100);
        LCD.WriteAt("your player using the", 10, 130);
        LCD.WriteAt("mouse, to shoot a laser", 10, 160);
        LCD.WriteAt("at the aliens...But dont", 10, 190);
        LCD.WriteAt("get hit 3 times, youll die.", 10, 220);
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
//Draws the lose screen
void loseScreen(int *returnVal, int *finalPoints)
{
    while (true)
    {
        float x, y;
        //This is the actual drawing of the screen
        //Score values are drawn dynamically
        LCD.Clear();
        LCD.WriteAt("*You Lose*", 85, 10);
        LCD.WriteAt(("Points: "), 85, 40);
        LCD.WriteAt(*finalPoints, 170, 40);
        LCD.DrawRectangle(100, 120, 85, 20);
        LCD.WriteAt("Replay", 105, 121);
        LCD.DrawRectangle(100, 150, 130, 20);
        LCD.WriteAt("Main Menu", 105, 151);
        //checks if the buttons are being touched
        //sets returnVal to correct number depending on selection
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

//Draws the win screen
void winScreen(int *returnVal, int *finalPoints)
{
    while (true)
    {
        float x, y;
        LCD.Clear();
        //Draws the win sceen and updates score dyanmically
        LCD.WriteAt("*You Win*", 90, 10);
        //LCD.WriteAt("High Score: ", 60, 190);
        LCD.WriteAt(("Points:"), 85, 40);
        LCD.WriteAt(*finalPoints, 170, 40);
        LCD.DrawRectangle(100, 120, 85, 20);
        LCD.WriteAt("Replay", 105, 121);
        LCD.DrawRectangle(100, 150, 130, 20);
        LCD.WriteAt("Main Menu", 105, 151);
        //checks to see if the buttons have been touched
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

//Renders the main menu
void startScreen(int *returnVal)
{
    LCD.Clear();
    float x, y;
    while (1)
    {
        //This creates the main menu
        LCD.SetBackgroundColor(BLACK);
        LCD.SetFontColor(RED);
        LCD.WriteAt("*Space Invaders*", 70, 10);
        LCD.SetFontColor(WHITE);
        LCD.DrawRectangle(10, 30, 150, 40);
        LCD.DrawRectangle(10, 70, 150, 40);
        LCD.DrawRectangle(10, 110, 150, 40);
        LCD.DrawRectangle(10, 150, 150, 40);
        LCD.DrawRectangle(10, 190, 150, 40);
        LCD.WriteAt("Play Game", 10, 32);
        LCD.WriteAt("Statistics", 10, 72);
        LCD.WriteAt("Credits", 10, 112);
        LCD.WriteAt("Exit", 10, 152);
        LCD.WriteAt("Instructions", 10, 192);
        //Renders the ship on the right
        FEHIMAGE ship2;
        ship2.Open("SpaceShip21FEH.pic");
        ship2.Draw(75, 180);
        //checks if buttons were pressed
        //If buttons pressed, the appropiate returnVal is set
        if (LCD.Touch(&x, &y))
        {
            if (((x < 300) & (x > 10)) & ((y > 30) & (y < 70)))
            {
                LCD.Clear();
                //sets returnVal to 8, so int main can direct to the correct screen
                *returnVal = 8;
                LCD.SetBackgroundColor(BLACK);
                break;
            }
            if (((x < 150) & (x > 10)) & ((y > 70) & (y < 110)))
            {
                *returnVal = 1;
                break;
            }
            if (((x < 150) & (x > 10)) & ((y > 110) & (y < 150)))
            {
                *returnVal = 2;
                LCD.SetBackgroundColor(BLACK);
                break;
            }
            if (((x < 150) & (x > 10)) & ((y > 150) & (y < 190)))
            {
                *returnVal = 3;
                break;
            }
            if (((x < 150) & (x > 10)) & ((y > 190) & (y < 230)))
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

//Screen where difficulty is selcted
void difficultyScreen(int *returnValue, int *difficultySelector)
{
    LCD.Clear();
    float x, y;
    while (1)
    {
        //This draws the visual menu
        LCD.DrawRectangle(10, 30, 150, 40);
        LCD.DrawRectangle(10, 70, 150, 40);
        LCD.DrawRectangle(10, 110, 150, 40);
        LCD.WriteAt("EASY", 10, 32);
        LCD.WriteAt("MEDIUM", 10, 72);
        LCD.WriteAt("HARD", 10, 112);
        //This checks if the user has pressed a button
        //If button pressed, returnValue is set to 0(i.e. playGame())
        if (LCD.Touch(&x, &y))
        {

            if (((x < 150) & (x > 10)) & ((y > 32) & (y < 72)))
            {
                *returnValue = 0;
                *difficultySelector = 5;
                LCD.SetBackgroundColor(BLACK);
                break;
            }
            if (((x < 150) & (x > 10)) & ((y > 72) & (y < 112)))
            {
                *returnValue = 0;
                *difficultySelector = 3;
                LCD.SetBackgroundColor(BLACK);
                break;
            }
            if (((x < 150) & (x > 10)) & ((y > 112) & (y < 152)))
            {
                *returnValue = 0;
                *difficultySelector = 1;
                LCD.SetBackgroundColor(BLACK);
                break;
            }

            //LCD.WriteLine("Screen reached");
        }
    }
}

//Int main acts as a switch case selection structure
int main()
{
    //other functions manipulate returnValue and change the outcome of the switch
    int returnValue;
    int difficultyValue;
    bool shouldExit;
    int finalPoints;
    startScreen(&returnValue);
    while (1)
    {
        //the switch will direct the game to the correct screen
        //each returnValue is mapped to a different screen / function call
        switch (returnValue)
        {
        case 0:
            playGameScreen(&returnValue, difficultyValue, &finalPoints);
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
            loseScreen(&returnValue, &finalPoints);
            Sleep(.1);
            break;
        case 7:
            winScreen(&returnValue, &finalPoints);
            Sleep(.1);
            break;
        case 8:
            difficultyScreen(&returnValue, &difficultyValue);
            Sleep(.1);
            break;
        }

        if (shouldExit)
        {
            return 1;
        }
    }
}
