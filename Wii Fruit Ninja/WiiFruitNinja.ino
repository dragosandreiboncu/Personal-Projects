#include <TFT.h>
#include <SPI.h>
#include <Wire.h>
#define lcd_cs   10
#define lcd_dc   8
#define lcd_rst  9
#define buttonPin1 7
#define buttonPin2 5
#define ledPin1 2
#define ledPin2 4
#define ledPin3 12
#define buzzer 6
#define MPU_ADDR 0x68

TFT LCD = TFT(lcd_cs, lcd_dc, lcd_rst);

int16_t acc_x1, acc_y1, acc_z1;
int16_t acc_x2, acc_y2, acc_z2; 

int lifes;
int score;
bool cut;
bool correctCut;
int pointerDirection = 0;
int fruit = 0;
bool gameStarted;

int buttonState1;
int buttonState2;

void setup() 
{
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  LCD.begin();
  LCD.background(255, 255, 255);
  LCD.stroke(0, 0, 0);
  LCD.text("Press reset button to start", 0, 64);
  gameStarted = false;
}

void loop() 
{
  if(gameStarted)
  {
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_ADDR, 7*2, true);
    acc_x1 = Wire.read()<<8 | Wire.read();
    acc_y1 = Wire.read()<<8 | Wire.read();
    acc_z1 = Wire.read()<<8 | Wire.read();
    /*Serial.print("aX1 = "); Serial.print(acc_x1);
    Serial.print(" | aY1 = "); Serial.print(acc_y1);
    Serial.print(" | aZ1 = "); Serial.print(acc_z1);
    Serial.println();*/
  }
  delay(2000);
  if(gameStarted && buttonState1 == LOW)
  {
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_ADDR, 7*2, true);
    acc_x2 = Wire.read()<<8 | Wire.read();
    acc_y2 = Wire.read()<<8 | Wire.read();
    acc_z2 = Wire.read()<<8 | Wire.read();
    if(acc_x2 > acc_x1)
    {
      cut = true;
      if(pointerDirection == 1)
        correctCut = true;
    }
    if(acc_x2 < acc_x1)
    {
      cut = true;
      if(pointerDirection == 0)
        correctCut = true;
    }
    /*Serial.print("aX2 = "); Serial.print(acc_x2);
    Serial.print(" | aY2 = "); Serial.print(acc_y2);
    Serial.print(" | aZ2 = "); Serial.print(acc_z2);
    Serial.println();
    Serial.println();
    Serial.println(cut);
    Serial.println();
    Serial.println(correctCut);
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();*/
  }
  
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  if(correctCut && fruit != 1)
  {
    score++;
    if(lifes < 3)
      lifes++;
    if(lifes == 3)
      digitalWrite(ledPin3, HIGH);
    else if(lifes == 2)
      digitalWrite(ledPin2, HIGH);
    else if(lifes == 1)
      digitalWrite(ledPin1, HIGH);
  }
  if(gameStarted && ((!correctCut && fruit != 1) || (cut && fruit == 1)))
  {
    tone(buzzer, 75);
    lifes--;
    if(lifes == 2)
      digitalWrite(ledPin3, LOW);
    else if(lifes == 1)
      digitalWrite(ledPin2, LOW);
    else if(lifes == 0)
      digitalWrite(ledPin1, LOW);
    delay(250);
    noTone(buzzer);
  }
  if(buttonState2 == LOW)
  {
    if(gameStarted)
    {
      gameDone();
      LCD.text("Press reset button to start", 0, 64);
    }
    else
      reset();
  }
  if(!gameStarted)
    return;
  if(score == 40)
  {
    gameDone();
    LCD.text("You won!", 60, 60);
    LCD.text("Press reset to play again", 3, 70);
    return;
  }
  if(!lifes)
  {
    gameDone();
    LCD.text("You lost!", 60, 60);
    LCD.text("Press reset to play again", 3, 70);
    return;
  }
  LCD.background(255, 255, 255);
  drawFruit();
  drawPointer();
  drawScore();
  cut = false;
  correctCut = false;
}

void reset()
{
  digitalWrite(ledPin1, HIGH);
  digitalWrite(ledPin2, HIGH);
  digitalWrite(ledPin3, HIGH);
  lifes = 3;
  score = 0;
  correctCut = false;
  gameStarted = true;
}
void drawFruit()
{
  fruit = random(0, 6);
  if(fruit == 0)
    drawApple();
  if(fruit == 1)
    drawBomb();
  if(fruit == 2)
    drawBanana();
  if(fruit == 3)
    drawOrange();
  if(fruit == 4)
    drawGrapes();
  if(fruit == 5)
    drawWatermelon();
}
void drawApple()
{
  LCD.stroke(0, 0, 255);
  LCD.circle(120, 64, 34);
  LCD.stroke(0, 0, 0);
  LCD.line(120, 30, 120, 14);
  LCD.stroke(0, 255, 0);
  LCD.rect(121, 16, 12, 8);
}
void drawBomb()
{
  LCD.stroke(0, 0, 0);
  LCD.circle(120, 64, 24);
  LCD.stroke(0, 0, 0);
  LCD.line(128, 44, 140, 24);
}
void drawBanana()
{
  LCD.stroke(0, 255, 255);
  LCD.rect(120, 34, 16, 60);
  LCD.stroke(0, 0, 0);
  LCD.line(128, 34, 136, 24);
}
void drawOrange()
{
  LCD.stroke(0, 155, 255);
  LCD.circle(120, 64, 34);
  LCD.stroke(0, 0, 0);
  LCD.line(120, 30, 120, 14);
  LCD.stroke(0, 255, 0);
  LCD.rect(108, 16, 12, 8);
}
void drawGrapes()
{
  LCD.stroke(255, 0, 175);
  LCD.circle(120, 40, 10);
  LCD.circle(130, 60, 10);
  LCD.circle(110, 60, 10);
  LCD.circle(120, 80, 10);
  LCD.circle(100, 80, 10);
  LCD.circle(140, 80, 10);
  LCD.circle(130, 100, 10);
  LCD.circle(110, 100, 10);
  LCD.stroke(0, 0, 0);
  LCD.line(120, 30, 120, 14);
  LCD.stroke(0, 255, 0);
  LCD.rect(108, 16, 12, 8);
}
void drawWatermelon()
{
  LCD.stroke(0, 255, 0);
  LCD.circle(120, 64, 34);
  LCD.stroke(0, 0, 0);
  LCD.line(120, 31, 120, 97);
  LCD.line(135, 34, 135, 94);
  LCD.line(105, 34, 105, 94);
  LCD.line(150, 50, 150, 79);
  LCD.line(90, 50, 90, 79);
}
void drawPointer()
{
  pointerDirection = random(0, 2);
  LCD.stroke(0, 0, 0);
  if(pointerDirection == 0)
  {
    LCD.line(20, 64, 60, 64);
    LCD.line(50, 70, 60, 64);
    LCD.line(50, 58, 60, 64);
  }
  if(pointerDirection == 1)
  {
    LCD.line(20, 64, 60, 64);
    LCD.line(20, 64, 30, 58);
    LCD.line(20, 64, 30, 70);
  }
}
void drawScore()
{
  LCD.stroke(0, 0, 0);
  LCD.text("Score: ", 1, 118);
  for(int i = 1; i <= score; i++)
    LCD.line(35 + i * 3, 126, 35 + i * 3, 118);
}
void gameDone()
{
  gameStarted = false;
  LCD.background(255, 255, 255);
  LCD.stroke(0, 0, 0);
  digitalWrite(ledPin3, LOW);
  digitalWrite(ledPin2, LOW);
  digitalWrite(ledPin1, LOW);
}
