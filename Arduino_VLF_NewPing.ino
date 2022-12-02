#include <NewPing.h>
#define L_InPin_1  2  //왼쪽모터 핀1
#define L_InPin_2  3  //왼쪽모터 핀2
#define R_InPin_1  7  //오른쪽모터 핀1
#define R_InPin_2  4  //오른쪽모터 핀2
#define L_en  5 //왼쪽모터 속도 제어 핀
#define R_en  6 //오른쪽모터 속도 제어 핀
#define F_Sonar  8  //정면부 초음파 센서 연결 핀
#define R_Sonar  10 //오른쪽 초음파 센서 연결 핀
#define L_Sonar  11 //왼쪽 초음파 센서 연결 핀
#define MaxDistance  400
float robot_width = 200; //차량의 폭
float mazor_width = 500; //지나가는 길의 폭
float mazor_width_tolerance = 40; //폭 감지에 오찹범위
int flag_mazor_1 = 0; // 1이면 1번 구간에 내가 위치해 있음

NewPing F_sensor(F_Sonar,F_Sonar,MaxDistance);
float F_distance; //정면 초음파 센서값을 저장할 변수 선언
NewPing L_sensor(L_Sonar,L_Sonar,MaxDistance);
float L_distance; //왼쪽 초음파 센서값을 저장할 변수 선언
NewPing R_sensor(R_Sonar,R_Sonar,MaxDistance);
float R_distance; //오른쪽 초음파 센서값을 저장할 변수 선언

void setup() {
  Serial.begin(115200);  //스크린프린트를 115200의 속도로 사용
  pinMode(L_InPin_1,OUTPUT); //왼쪽모터1 핀 모드를 아웃풋으로
  pinMode(L_InPin_2,OUTPUT); //왼쪽모터2 핀 모드를 아웃풋으로
  pinMode(R_InPin_1,OUTPUT); //오른쪽모터1 핀 모드를 아웃풋으로
  pinMode(R_InPin_2,OUTPUT); //오른쪽모터2 핀 모드를 아웃풋으로
  analogWrite(L_en,80);  //왼쪽모터 속도 조정
  analogWrite(R_en,80);  //오른쪽모터 속도 조정
}

void Stop(int t){
  digitalWrite(L_InPin_1,LOW);
  digitalWrite(L_InPin_2,LOW);
  digitalWrite(R_InPin_2,LOW);
  digitalWrite(R_InPin_1,LOW);
  delay(t);
  }
  
void Right(int t,int sp){
  analogWrite(L_en,sp);
  analogWrite(R_en,sp);
  digitalWrite(L_InPin_1,HIGH);
  digitalWrite(L_InPin_2,LOW);
  digitalWrite(R_InPin_2,HIGH);
  digitalWrite(R_InPin_1,LOW);
  delay(t);
  }
  
 void Left(int t,int sp){
  analogWrite(L_en,sp);
  analogWrite(R_en,sp);
  digitalWrite(L_InPin_2,HIGH);
  digitalWrite(L_InPin_1,LOW);
  digitalWrite(R_InPin_1,HIGH);
  digitalWrite(R_InPin_2,LOW);
  delay(t);
  }

 void runing(int t,int L_sp,int R_sp){
  analogWrite(L_en,L_sp); //왼쪽 모터 속도를 L_sp로 하라
  analogWrite(R_en,R_sp); //오른쪽 모터 속도를 R_sp로 하라
  digitalWrite(L_InPin_1,HIGH);  //왼쪽모터1 핀에 +
  digitalWrite(L_InPin_2,LOW);   //왼쪽모터2 핀에 -
  digitalWrite(R_InPin_1,HIGH);  //오른쪽모터1 핀에 +
  digitalWrite(R_InPin_2,LOW);   //왼쪽모터2 핀에 -
  delay (t);
  }  //모터제어 종합 함수

void loop() {
 int R_moter_speed,L_moter_speed;
  int L_turn_90_timer = 795;
  int R_turn_90_timer = 737;
  F_distance=(F_sensor.ping_cm())/10;  //정면 초음파 센서값을 F_distance에 저장
  L_distance=(L_sensor.ping_cm())/10;  //왼쪽 초음파 센서값을 L_distance에 저장
  R_distance=(R_sensor.ping_cm())/10;  //오른쪽 초음파 센서값을 R_distance에 저장
  float measure_widht=L_distance+R_distance+robot_width; //오른쪽,왼쪽 초음파 센서와 기체폭을 통해 측정한 현재 측정된 길의 폭
  Serial.print("F : ");
  Serial.print(F_distance);
  Serial.print("mm   ");

  

  if(F_distance <= 200){
    R_moter_speed=80;
    L_moter_speed=80;
    Stop(100);
    
    if(L_distance > R_distance){
      Stop(2000);
      Left(L_turn_90_timer,80);
      Stop(2000);
      }
    else{
      Stop(2000);
      Right(R_turn_90_timer,80);
      Stop(2000);   
      }
    }
  else{
    R_moter_speed=95;
    L_moter_speed=80;
    runing(1,L_moter_speed,R_moter_speed);
    }
 

}
