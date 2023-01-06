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
#define MaxDistance  150
#define p_gain 0.4
#define er 10
#define dw 300

int nm_sp_L = 80;
int nm_sp_R = 88;

NewPing R_sensor(R_Sonar,R_Sonar,MaxDistance);
float R_Sonar_Error = 0.0;
float R_Sonar_distance = 0.0;
float R_Sonar_distance_old = 0.0;

NewPing L_sensor(L_Sonar,L_Sonar,MaxDistance);
float L_Sonar_Error = 0.0;
float L_Sonar_distance = 0.0;
float L_Sonar_distance_old = 0.0;

NewPing F_sensor(R_Sonar,R_Sonar,MaxDistance);
float F_Sonar_Error = 0.0;
float F_Sonar_distance = 0.0;
float F_Sonar_distance_old = 0.0;


void read_sonar_sensor(void){ //초음파센서 측정
  R_Sonar_distance = R_sensor.ping_cm()*10.0;
  L_Sonar_distance = L_sensor.ping_cm()*10.0;
  F_Sonar_distance = F_sensor.ping_cm()*10.0;
  if(R_Sonar_distance == 0){R_Sonar_distance = MaxDistance * 10.0;}
  if(L_Sonar_distance == 0){L_Sonar_distance = MaxDistance * 10.0;}
  if(F_Sonar_distance == 0){F_Sonar_distance = MaxDistance * 10.0;}
  }

void update_sonar_old(void){ //초음파 센서의 옛날값 저장
   R_Sonar_distance_old = R_Sonar_distance;
   L_Sonar_distance_old = L_Sonar_distance;
   F_Sonar_distance_old = F_Sonar_distance;
  }

void update_sonar_error(void){ //초음파 센서의 옛날값과 현재값의 차이 저장
   R_Sonar_Error = R_Sonar_distance - R_Sonar_distance_old;
   L_Sonar_Error = L_Sonar_distance - L_Sonar_distance_old;
   F_Sonar_Error = F_Sonar_distance - F_Sonar_distance_old;
  }

void setup() {
  Serial.begin(115200);  //스크린프린트를 115200의 속도로 사용
  pinMode(L_InPin_1,OUTPUT); //왼쪽모터1 핀 모드를 아웃풋으로
  pinMode(L_InPin_2,OUTPUT); //왼쪽모터2 핀 모드를 아웃풋으로
  pinMode(R_InPin_1,OUTPUT); //오른쪽모터1 핀 모드를 아웃풋으로
  pinMode(R_InPin_2,OUTPUT); //오른쪽모터2 핀 모드를 아웃풋으로
  analogWrite(L_en,80);  //왼쪽모터 속도 조정
  analogWrite(R_en,80);  //오른쪽모터 속도 조정

  read_sonar_sensor();
}

void runing(int t,int L_sp,int R_sp){
  analogWrite(L_en,L_sp); //왼쪽 모터 속도를 L_sp로 하라
  analogWrite(R_en,R_sp); //오른쪽 모터 속도를 R_sp로 하라
  digitalWrite(L_InPin_1,HIGH);  //왼쪽모터1 핀에 +
  digitalWrite(L_InPin_2,LOW);   //왼쪽모터2 핀에 -
  digitalWrite(R_InPin_1,HIGH);  //오른쪽모터1 핀에 +
  digitalWrite(R_InPin_2,LOW);   //왼쪽모터2 핀에 -
  delay (t);
  }
void Left(int t,float sp){
  analogWrite(L_en,sp);
  analogWrite(R_en,sp);
  digitalWrite(L_InPin_2,HIGH);
  digitalWrite(L_InPin_1,LOW);
  digitalWrite(R_InPin_1,HIGH);
  digitalWrite(R_InPin_2,LOW);
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

  float ck=0;
  float ck_L=0;
  int ck_R=0;
  
void loop() {
  
  read_sonar_sensor();
  update_sonar_error();
  update_sonar_old();
  
  
   ck_L=nm_sp_L-(L_Sonar_distance-R_Sonar_distance)*p_gain;
   ck_R=nm_sp_R+(L_Sonar_distance-R_Sonar_distance)*p_gain;
   
   if(ck_L>=200){
    ck_L=200;
    }
   if(ck_L<=0){
    ck_L=0;
    }
   if(ck_R>=200){
    ck_R=200;
   }
   if(ck_R<=0){
    ck_R=0;
    }

    if(ck_L+8>ck_R){
    ck = 0;
    }
  if(ck_L+8<ck_R){
    ck = 1;
    }
    
  if(320+er*2>=R_Sonar_distance+L_Sonar_distance && R_Sonar_distance==L_Sonar_distance){
    if(R_Sonar_Error > 0){
      nm_sp_L++;
      nm_sp_R--;
      }
    if(R_Sonar_Error < 0){
      nm_sp_L--;
      nm_sp_R++;
      }
    runing(1,ck_L,ck_R);
    }

  else if(R_Sonar_distance<=L_Sonar_distance+er && R_Sonar_distance>=L_Sonar_distance-er){
    if(ck==0){
      while(1){
        read_sonar_sensor();
        Left(1,65);
        if(dw+er*2>=R_Sonar_distance+L_Sonar_distance){
          break;
          }
        }
      }
    else{
      while(1){
        read_sonar_sensor();
        Right(1,65);
        if(dw+er*2>=R_Sonar_distance+L_Sonar_distance){
          break;
          }
        }
      }
    }
  else{
    runing(1,ck_L,ck_R);
  }
  delay(100);

  Serial.print("R-D : ");
  Serial.print(R_Sonar_distance);
  Serial.print("  ");
  Serial.print("L-D : ");
  Serial.print(L_Sonar_distance);
  Serial.print("  \n");
}
