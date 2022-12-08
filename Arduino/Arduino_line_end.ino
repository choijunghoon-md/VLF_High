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
  } //모터를 t동안 정지
  
void Right(int t,float sp){
  analogWrite(L_en,sp);
  analogWrite(R_en,sp*1.2);
  digitalWrite(L_InPin_1,HIGH);
  digitalWrite(L_InPin_2,LOW);
  digitalWrite(R_InPin_2,HIGH);
  digitalWrite(R_InPin_1,LOW);
  delay(t);
  } //모터를 t동안 제자리에서 오른쪽 회전
  
 void Left(int t,float sp){
  analogWrite(L_en,sp);
  analogWrite(R_en,sp*1.2);
  digitalWrite(L_InPin_2,HIGH);
  digitalWrite(L_InPin_1,LOW);
  digitalWrite(R_InPin_1,HIGH);
  digitalWrite(R_InPin_2,LOW);
  delay(t);
  } //모터를 t동안 제자리에서 왼쪽 회전

 void runing(int t,int L_sp,int R_sp){
  
  analogWrite(L_en,L_sp); //왼쪽 모터 속도를 L_sp로 하라
  analogWrite(R_en,R_sp); //오른쪽 모터 속도를 R_sp로 하라

  digitalWrite(L_InPin_1,HIGH);  //왼쪽모터1 핀에 +
  digitalWrite(L_InPin_2,LOW);   //왼쪽모터2 핀에 -
  digitalWrite(R_InPin_1,HIGH);  //오른쪽모터1 핀에 +
  digitalWrite(R_InPin_2,LOW);   //왼쪽모터2 핀에 -
  delay (t);
  }  //모터제어 종합 함수

 int line_sensor[5]={0,0,0,0,0};
 
 int read_line_sensor(){
  int line_index;
  int i;
  int sum=0;
  for(i=0;i<5;i++){
    line_sensor[i]=(digitalRead(A0+i));
    sum += line_sensor[i];
    Serial.print(line_sensor[i]);
    Serial.print("  ");
    }
  Serial.println("");
  if(sum==5) line_index = -10;
  if(sum==1){
    if(line_sensor[0]==1) line_index = -4;
    if(line_sensor[1]==1) line_index = -2;
    if(line_sensor[2]==1) line_index = 0;
    if(line_sensor[3]==1) line_index = 2;
    if(line_sensor[4]==1) line_index = 4;
    }
  if(sum==2){
    if(line_sensor[0]==1 && line_sensor[1]==1) line_index = -3;
    if(line_sensor[1]==1 && line_sensor[2]==1) line_index = -1;
    if(line_sensor[2]==1 && line_sensor[3]==1) line_index = 1;
    if(line_sensor[3]==1 && line_sensor[4]==1) line_index = 3;
    }
  if(sum==0){line_index = 0;}
  Serial.print(line_index);
  Serial.println("");
  return line_index;
  }


  

void loop() {
  int index;
  float L_control_speed=50;
  float R_control_speed= L_control_speed*1.2;
  index=read_line_sensor();
  switch(index){
    case -4 : runing(1,-100,120); break;
    case -3 : runing(1,100+L_control_speed*index,120); break;
    case -2 : runing(1,100+L_control_speed*index,120); break;
    case -1 : runing(1,100+L_control_speed*index,120); break;
    case 0 : runing(1,100,120); break;
    case 1 : runing(1,100,120-R_control_speed*index); break;
    case 2 : runing(1,100,120-R_control_speed*index); break;
    case 3 : runing(1,100,120-R_control_speed*index); break;
    case 4 : runing(1,100,-120); break;
    case -10 : Stop(1); break;
    default : runing(1,100,120); break;
    }
  














  
 /*int R_moter_speed,L_moter_speed;
  F_distance=(float)(F_sensor.ping())*10/US_ROUNDTRIP_CM;  //정면 초음파 센서값을 실수로 F_distance에 저장_mm단위
  L_distance=(float)(L_sensor.ping())*10/US_ROUNDTRIP_CM;  //왼쪽 초음파 센서값을 실수로 L_distance에 저장_mm단위
  R_distance=(float)(R_sensor.ping())*10/US_ROUNDTRIP_CM;  //오른쪽 초음파 센서값을 실수로 R_distance에 저장_mm단위
  
  float measure_widht=L_distance+R_distance+robot_width; //오른쪽,왼쪽 초음파 센서와 기체폭을 통해 측정한 현재 측정된 길의 폭
  */
  /*
  Serial.print("F : ");
  Serial.print(F_distance);
  Serial.print("mm   ");  //"F : (F_distance에 저장된 값)mm" 를 스크린 프린터에 출력해라
  Serial.print("R : ");
  Serial.print(R_distance);
  Serial.print("mm   ");  //"R : (R_distance에 저장된 값)mm" 를 스크린 프린터에 출력해라
  Serial.print("L : ");
  Serial.print(L_distance);
  Serial.print("mm   \n");  //"L : (L_distance에 저장된 값)mm" 를 스크린 프린터에 출력해라
  */
  /*
  Serial.print(flag_mazor_1);
  Serial.print("\n");  //1번 구간에 있는지 없는지를 출력(1과 0으로 구분)
  */
/*
  float turn_90_mm=120;
  if(F_distance<=170 && F_distance!=0){
    Stop(200);  // 0.2초동안 정지
    if(L_distance>R_distance || L_distance==0){
      while(1){
        if((float)(R_sensor.ping())*10/US_ROUNDTRIP_CM <= turn_90_mm - 5 && (float)(R_sensor.ping())*10/US_ROUNDTRIP_CM != 0){
          break;
          }
        else{
          Left(1,70);
          }
        } //왼쪽으로 계속 회전하라 오른쪽 초음파 센서가 90도로 회전시 입력받는 거리가 될때 까지
        Stop(200); // 0.2초동안 정지
      } //만약 왼쪽이 감지되지 않거나 왼쪽이 오른쪽보다 큰 값으로 인식되면
    else if(L_distance<R_distance || R_distance==0){
      while(1){
        if((float)(L_sensor.ping())*10/US_ROUNDTRIP_CM <= turn_90_mm && (float)(L_sensor.ping())*10/US_ROUNDTRIP_CM != 0){
          break;
          }
        else{
          Right(1,70);
          }
        } //오른쪽으로 계속 회전하라 왼쪽 초음파 센서가 90도로 회전시 입력받는 거리가 될때 까지
        Stop(200); // 0.2초동안 정지
      } //만약 오른쪽이 감지되지 않거나 오른쪽이 왼쪽보다 큰 값으로 인식되면
    
    }// 전면부 초음파 센서가 170mm이하로 감지가 되었을시
  else{
    runing(1,80,95);
    }  
*/
}
