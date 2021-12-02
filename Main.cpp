#include <FEHUtility.h>
//#include <FEHIO.h>
#include <FEHLCD.h>

class Player1{
    public:
        Player1();
        void drawSelf();
        
        
    private:
        int points;
        int lives;
        int x_coordinate;

    
};

class Player2 {
    public:
        Player2();
        void drawSelf();
        
    private:
        int points;
        int lives;
        int x_coordinate;

};

class allEnemies{
    
};
class Ememy{
    public:
        void drawSelf(){
            
        }

    private:
        int type;

};

void playGameScreen(int *returnVal){
    float x,y;
    LCD.Clear();
    // Put game logic here
    while (1){
        LCD.DrawRectangle(10, 10, 60, 25);
        LCD.WriteAt("Back", 10, 10);
        LCD.WriteAt("Gameplay goes here", 150,150);
        if (LCD.Touch(&x, &y)){
            if(((x < 70) & (x > 10)) &((y < 35) & (y > 10))){
                *returnVal = 4;
                break;
            } 
        }
    }
    
}
void statScreen(int *returnVal){
    float x,y;
    LCD.Clear();
    while (1){
        LCD.DrawRectangle(10, 10, 200, 200);
        LCD.WriteAt("Statistics", 100, 10);
        LCD.WriteAt("Lives: 3", 20, 50);
        LCD.WriteAt("Points: 42", 20, 80);
        LCD.DrawRectangle(10, 10, 60, 25);
        LCD.WriteAt("Back", 10, 10);
        if (LCD.Touch(&x, &y)){
            if(((x < 70) & (x > 10)) &((y < 35) & (y > 10))){
                *returnVal = 4;
                break;
            } 
        }
    }
}
    
    

void creditScreen(int *returnVal){
    LCD.Clear();
    float x,y;
    while(1){
        LCD.DrawRectangle(10, 10, 60, 25);
        LCD.WriteAt("Back", 10, 10);
        LCD.WriteAt("Credits screen", 10, 150);
        if (LCD.Touch(&x, &y)){
            if(((x < 70) & (x > 10)) &((y < 35) & (y > 10))){
                *returnVal = 4;
                break;
            } 
        }
    }
}
void instructScreen(int *returnVal){
    float x,y;
    LCD.Clear();
    LCD.SetBackgroundColor(RED);
    while (1){
        LCD.WriteAt("Instructions:", 100, 10);
        LCD.WriteAt("Your objective is to", 10, 40);
        LCD.WriteAt("shoot the enemy coming", 10, 70);
        LCD.WriteAt("towards you. Use the", 10, 100);
        LCD.WriteAt("Fire button to shoot a", 10, 130);
        LCD.WriteAt("laser. Use the left and", 10, 160);
        LCD.WriteAt("right arrows to change", 10, 190);
        LCD.WriteAt("direction.", 10, 220);
        LCD.WriteAt("Back", 10, 10);
        if (LCD.Touch(&x, &y)){
            if(((x < 70) & (x > 10)) &((y < 35) & (y > 10))){
                *returnVal = 4;
                break;
            } 
        }
    }
}


void startScreen(int *returnVal){
        LCD.Clear();
        float x, y;
        while (1){
            LCD.SetFontColor(RED);
            LCD.WriteAt("*Space Invaders*", 100, 10);
            LCD.SetFontColor(WHITE);
            LCD.DrawRectangle(10, 30, 310, 40);
            LCD.DrawRectangle(10, 70, 310, 40);
            LCD.DrawRectangle(10, 110, 310, 40);
            LCD.DrawRectangle(10, 150, 310, 40);
            LCD.DrawRectangle(10, 190, 310, 40);
            //LCD.WriteAt("Welcome To Space-Invaders", 0, 0);
            //LCD.DrawCircle(150,150, 30);
            //LCD.WriteAt("Stats", 150, 150);
            LCD.WriteAt("Play Game", 10, 10);
            LCD.WriteAt("Statistics", 10, 50);
            LCD.WriteAt("Credits", 10, 90);
            LCD.WriteAt("Exit", 10, 130 );
            LCD.WriteAt("Instructions", 10, 170);
            if(LCD.Touch(&x,&y)){
                if (((x < 310) & (x > 10)) & ((y > 30) & (y < 70))){
                    //LCD.WriteLine("Play Game Recorded");
                    LCD.Clear();
                    *returnVal = 0;
                    LCD.SetBackgroundColor(BLACK);
                    break;
                }
                if (((x < 310) & (x > 10)) & ((y > 70) & (y < 110))){
                    *returnVal = 1;
                    break;
                }
                if (((x < 310) & (x > 10)) & ((y > 110) & (y < 150))){
                    *returnVal = 2;
                    LCD.SetBackgroundColor(BLACK);
                    break;
                }
                if (((x < 310) & (x > 10)) & ((y > 150) & (y < 190))){
                    *returnVal = 3;
                    break;
                } 
                if (((x < 310) & (x > 10)) & ((y > 190) & (y < 230))){
                    *returnVal = 5;
                    break;
                }else {
                    *returnVal = 4;
                    break;
                }
            }
        }

}



int main(){
    int returnValue;
    bool shouldExit;
    startScreen(&returnValue);
    while(1){
        switch (returnValue){
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
        if(shouldExit){
            return 1;
        }
   }
}
