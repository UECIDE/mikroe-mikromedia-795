/*  mikroe mx7 tft touchscreen demo
 *   touch screen test with touch point scaled to the screen 480 x 272
 *   simple example of buttons and text
 *   
 UECIDE     : v0.8.9-pre14
 Hardware   : mikroe-mikromedia-795
 Core       : chipKIT
 Compiler   : PIC32 Compiler version 1.43
 Programmer : pic32prog
 Other      : 
 Board      : https://shop.mikroe.com/mikromedia-4-pic32mx7
*/
# include <SSD1963.h>                  // tft driver
# include <Liberation.h>                 // font
# include <DSPI.h>
# include <Wire.h>
# include <SPI.h>                            // Note not used but required by <Adafruit_STMPE610.h>
# include <Adafruit_STMPE610.h> // touch driver

Adafruit_STMPE610 touch = Adafruit_STMPE610(-1);

SSD1963 tft(31, 52, 53, 92, 33, 64, 65, 66, 67, 68, 69, 70, 71, 96, 97, 81, 80, 60, 61, 54, 55,TFTBUS24);
 
void buttons();
void screen1();
void screen1();
void screen1();

int count = 0;
int x, y, z, oldx, oldy;
int ledPinRed = 49; // red 49, green 59, blue 51
int ledPinGreen = 50;
int ledPinBlue = 51;
#define TS_MINX 150          // you may change these for better touch accuracy to the screen size
#define TS_MINY 250
#define TS_MAXX 3800
#define TS_MAXY 3800

void setup()
{
  Wire.begin();                 // join i2c bus for the touch 
  Serial.begin(9600);       // start serial for output
  delay(5000);
  Serial.println("mx7 touch test..");

  if (! touch.begin(0x44)) { // Note touch address  0x44
    Serial.println("STMPE not found!");
    while(1) {
      delay(500);
    }
  }
  
  Serial.print("getVersion: 0x"); Serial.println(touch.getVersion(), HEX);
  Serial.print("getMode:    0x"); Serial.println(touch.getMode(), HEX);
  Serial.println("Waiting for touch sense");

    pinMode(ledPinRed, OUTPUT);
    pinMode(ledPinGreen, OUTPUT);
      pinMode(ledPinBlue, OUTPUT);
      
  tft.initializeDevice(SSD1963::MIKROMEDIA);
  delay(20);
  tft.setBacklight(120);
  tft.fillScreen(Color::Blue);
  tft.setTextWrap(false);
 // tft.setRotation(1);
  tft.setTextColor(Color::Green, Color::Blue);
  tft.setCursor(20, 35);
  tft.setFont(Fonts::Liberation20);
  tft.println("mikroE mx7 touch test..");

  buttons();
  delay(2000);
}

void loop()
{
        // note this suits landscape mode
       tft.setTextColor(Color::Green, Color::Blue);
       if (touch.touched())   {                          // screen touch?
            if (touch.bufferEmpty())  {                 //  if no data in queue
                return;                                         //   bail out
                }
           else   {                                            //  touch and data!
                  TS_Point p = touch.getPoint();                  //   so get it!
                  p.x = constrain(p.x,TS_MINX, TS_MAXX);                 // clamp to raw screen area
                  p.y = constrain(p.y,TS_MINY, TS_MAXY);           
                  p.x = map(p.x, TS_MINX, TS_MAXX, 0, 480);               // rotate coordinate system
                  p.y = map(p.y, TS_MINY, TS_MAXY, 0, 272);              // flip it around to match the screen.
                  y = p.y;
                  x = p.x;
                 /*---------------------- put your code here ----------------------------
                   code to detect which button has been pressed can go here
                   then use a case statement to do whatever
                 */
                  if(x > 30 && x < 140){
                    if(y < 260 && y > 220){
                      oldx = x;
                      oldy = y;
                    screen1();
                    }
                  }
               else   if(x > 200 && x < 300){
                    if(y < 260 && y > 220){
                      oldx = x;
                      oldy = y;
                    screen2();
                    }
                  }
               else   if(x > 360 && x < 480){
                    if(y < 260 && y > 220){
                      oldx = x;
                      oldy = y;
                    screen3();
                    }
                  }
                  else{
                    x = oldx;
                    y = oldy;
                    return;                   // take care of touch outside buttons
                  }

 /*------------------------------------- put your code here ----------------------------------------*/                  
                  count = count + 1; // update a counter of number of presses
                 
                  touch.writeRegister8(STMPE_INT_STA, 0xFF); // reset all ints
                                }// end else touch data
                       }// end touch.touched
       else {                                                         // no touch, so ...
               while (!touch.bufferEmpty())               //  drain the buffer
                TS_Point p = touch.getPoint(); 
                return;
               } // end else no touch
      delay(100);
      
}// end loop

void buttons(){
       // button 1
       //   tft.fillRoundRect(x, y, width, height, 4, Color::Yellow);
        tft.fillRoundRect(20,  220, 120, 35, 4, Color::Yellow);
        tft.setTextColor(Color::Black, Color::Yellow);
        tft.setCursor(29, 226);
        tft.setFont(Fonts::Liberation12);
        tft.println("screen 1");
       // button 2  
        tft.fillRoundRect(180, 220, 120, 35, 4, Color::Green);
        tft.setTextColor(Color::Black, Color::Green);
        tft.setCursor(189, 226);
        tft.setFont(Fonts::Liberation12);
        tft.println("screen 2");
       // button 3
        tft.fillRoundRect(340, 220, 120, 35, 4, Color::Red);
        tft.setTextColor(Color::Black, Color::Red);
        tft.setCursor(349, 226);
        tft.setFont(Fonts::Liberation12);
        tft.println("screen 3");  
}

void screen1(){
        tft.fillScreen(Color::Blue);
        buttons();
        Serial.println("screen 1");
        tft.setTextColor(Color::Green, Color::Blue);
        tft.setCursor(20, 35);
        tft.setFont(Fonts::Liberation20);
        tft.println("Screen One   ");
        // write text
        tft.setCursor(20, 75);
        tft.setFont(Fonts::Liberation18);
        tft.println("you pressed yellow!! ");
        tft.setCursor(20, 125);
        tft.setFont(Fonts::Liberation16);
        tft.print("screen 1");
        tft.setCursor(20, 150);   
        tft.print("x = ");  
        tft.print(x);
        tft.print(" and y= ");
        tft.println(y);
        tft.setCursor(20, 175); 
        tft.print("Number of presses "); 
        tft.println(count);   
    digitalWrite(ledPinRed,HIGH);  
    digitalWrite(ledPinGreen,HIGH); 
    digitalWrite(ledPinBlue,LOW);     
}

void screen2(){
        tft.fillScreen(Color::Blue);
        buttons();
        Serial.println("screen 2");
        tft.setTextColor(Color::Green, Color::Blue);
        tft.setCursor(20, 35);
        tft.setFont(Fonts::Liberation20);
        tft.println("Screen Two  ");
        // write text
        tft.setCursor(20, 75);
        tft.setFont(Fonts::Liberation18);
        tft.println("you pressed green!!   ");
        tft.setCursor(20, 125);
        tft.setFont(Fonts::Liberation16);
        tft.print("screen 2   ");
        tft.setCursor(20, 150);   
        tft.print("x = ");  
        tft.print(x);
        tft.print(" and y= ");
        tft.println(y);
        tft.setCursor(20, 175); 
        tft.print("Number of presses "); 
        tft.println(count);    
    digitalWrite(ledPinRed,LOW);  
    digitalWrite(ledPinGreen,HIGH); 
    digitalWrite(ledPinBlue,LOW);    
}

void screen3(){
        tft.fillScreen(Color::Blue);
        buttons();
        Serial.println("screen 3");
        tft.setTextColor(Color::Green, Color::Blue);
        tft.setCursor(20, 35);
        tft.setFont(Fonts::Liberation20);
        tft.println("Screen Three");
        // write text
        tft.setCursor(20, 75);
        tft.setFont(Fonts::Liberation18);
        tft.println("you pressed red!!      ");
        tft.setCursor(20, 125);
        tft.setFont(Fonts::Liberation16);
        tft.print("screen 3");
        tft.setCursor(20, 150);   
        tft.print("x = ");  
        tft.print(x);
        tft.print(" and y= ");
        tft.println(y);
        tft.setCursor(20, 175); 
        tft.print("Number of presses "); 
        tft.println(count);  
    digitalWrite(ledPinRed,HIGH);  
    digitalWrite(ledPinGreen,LOW); 
    digitalWrite(ledPinBlue,LOW);   
}
