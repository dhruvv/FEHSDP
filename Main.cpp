#include <FEHUtility.h>
//#include <FEHIO.h>
#include <FEHLCD.h>
/*
class Player(x){
    float x_pos;
    
}
*/
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

void startScreen(int *returnVal){
        LCD.Clear();
        float x, y;
        while (1){
            LCD.SetFontColor(WHITE);
            LCD.DrawRectangle(10, 10, 200, 60);
            LCD.DrawRectangle(10, 70, 200, 60);
            LCD.DrawRectangle(10, 130, 200, 60);
            LCD.DrawRectangle(10, 190, 200, 60);
            //LCD.WriteAt("Welcome To Space-Invaders", 0, 0);
            //LCD.DrawCircle(150,150, 30);
            //LCD.WriteAt("Stats", 150, 150);
            LCD.WriteAt("Play Game", 10, 10);
            LCD.WriteAt("Statistics", 10, 70);
            LCD.WriteAt("Credits", 10, 130);
            LCD.WriteAt("Exit", 10, 190 );
            if(LCD.Touch(&x,&y)){
                if (((x < 200) & (x > 10)) & ((y > 10) & (y < 70))){
                    //LCD.WriteLine("Play Game Recorded");
                    LCD.Clear();
                    *returnVal = 0;
                    LCD.SetBackgroundColor(BLACK);
                    break;
                }
                if (((x < 200) & (x > 10)) & ((y > 70) & (y < 130))){
                    //LCD.WriteLine("Stats Recorded");
                    *returnVal = 1;
                    //LCD.SetBackgroundColor(BLACK);
                    break;
                }
                if (((x < 200) & (x > 10)) & ((y > 130) & (y < 190))){
                    //LCD.WriteLine("Credits Recorded");
                    //LCD.Clear();
                    *returnVal = 2;
                    LCD.SetBackgroundColor(BLACK);
                    break;
                }
                if (((x < 200) & (x > 10)) & ((y > 190) & (y < 250))){
                    //LCD.WriteLine("Exit Recorded");
                    *returnVal = 3;
                    break;
                } else {
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
        }
        if(shouldExit){
            return 1;
        }
   }
}
