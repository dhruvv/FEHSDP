#include <FEHUtility.h>
//#include <FEHIO.h>
#include <FEHLCD.h>


void startScreen(int *returnVal){
        float x, y;
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
               }
            if (((x < 200) & (x > 10)) & ((y > 70) & (y < 130))){
                LCD.WriteLine("Stats Recorded");
                *returnVal = 1;
                LCD.SetBackgroundColor(BLACK);
            }
            if (((x < 200) & (x > 10)) & ((y > 130) & (y < 190))){
                LCD.WriteLine("Credits Recorded");
                LCD.Clear();
                *returnVal = 2;
                LCD.SetBackgroundColor(BLACK);
            }
            if (((x < 200) & (x > 10)) & ((y > 190) & (y < 250))){
                LCD.WriteLine("Exit Recorded");
                *returnVal = 3;
            }
        }

}

void playGameScreen(){

}
void statScreen(){
    LCD.DrawRectangle(10, 10, 200, 200);
    LCD.WriteAt("Statistics", 100, 10);
    LCD.WriteAt("Lives: 3", 20, 50);
    LCD.WriteAt("Points: 42", 20, 80);
}
void creditScreen(){
    
}


int main(){
    int returnVal;
    while(1){
        startScreen(&returnVal);
        switch (returnVal)
        {
        case 0:
            playGameScreen();
            break;
        case 1:
            statScreen();
            break;
        case 2:
            creditScreen();
            break;
        case 3:
            break;
        default:
            break;
        } 

    }

}
