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

float L_tan,R_tan,L_tan1,R_tan1;
float mi_R_distance=1000;
NewPing F_sensor(F_Sonar,F_Sonar,MaxDistance);
float F_distance; //정면 초음파 센서값을 저장할 변수 선언
float F_distance_D,F_distance1,F_distance2;
NewPing L_sensor(L_Sonar,L_Sonar,MaxDistance);
float L_distance; //왼쪽 초음파 센서값을 저장할 변수 선언
float L_distance_D,L_distance1,L_distance2;
NewPing R_sensor(R_Sonar,R_Sonar,MaxDistance);
float R_distance; //오른쪽 초음파 센서값을 저장할 변수 선언
float R_distance_D,R_distance1,R_distance2;

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

void Stop(int t){
  digitalWrite(L_InPin_1,LOW);
  digitalWrite(L_InPin_2,LOW);
  digitalWrite(R_InPin_2,LOW);
  digitalWrite(R_InPin_1,LOW);
  delay(t);
  }

void runing_chack(int t,int L_sp,int R_sp){
  F_distance1=(float)(F_sensor.ping())*10/US_ROUNDTRIP_CM;
  L_distance1=(float)(L_sensor.ping())*10/US_ROUNDTRIP_CM;
  R_distance1=(float)(R_sensor.ping())*10/US_ROUNDTRIP_CM;
  runing(t,L_sp,R_sp);
  F_distance2=(float)(F_sensor.ping())*10/US_ROUNDTRIP_CM;
  F_distance_D = F_distance1 - F_distance2;
  R_distance2=(float)(R_sensor.ping())*10/US_ROUNDTRIP_CM;
  R_distance_D = R_distance1 - R_distance2;
  L_distance2=(float)(L_sensor.ping())*10/US_ROUNDTRIP_CM;
  L_distance_D = L_distance1 - L_distance2;
  L_tan1=L_distance_D/F_distance_D;
  R_tan1=R_distance_D/F_distance_D;
  L_tan=atan(L_tan1)*180/3.14;
  R_tan=atan(R_tan1)*180/3.14;
  }

void Left_chack(int t,int sp){
  F_distance1=(float)(F_sensor.ping())*10/US_ROUNDTRIP_CM;
  L_distance1=(float)(L_sensor.ping())*10/US_ROUNDTRIP_CM;
  R_distance1=(float)(R_sensor.ping())*10/US_ROUNDTRIP_CM;
  Left(t,sp);
  F_distance2=(float)(F_sensor.ping())*10/US_ROUNDTRIP_CM;
  F_distance_D = F_distance1 - F_distance2;
  R_distance2=(float)(R_sensor.ping())*10/US_ROUNDTRIP_CM;
  R_distance_D = R_distance1 - R_distance2;
  L_distance2=(float)(L_sensor.ping())*10/US_ROUNDTRIP_CM;
  L_distance_D = L_distance1 - L_distance2;
  L_tan1=L_distance_D/F_distance_D;
  R_tan1=R_distance_D/F_distance_D;
  L_tan=atan(L_tan1)*180/3.14;
  R_tan=atan(R_tan1)*180/3.14;
  }

void Right_chack(int t,int sp){
  F_distance1=(float)(F_sensor.ping())*10/US_ROUNDTRIP_CM;
  L_distance1=(float)(L_sensor.ping())*10/US_ROUNDTRIP_CM;
  R_distance1=(float)(R_sensor.ping())*10/US_ROUNDTRIP_CM;
  Right(t,sp);
  F_distance2=(float)(F_sensor.ping())*10/US_ROUNDTRIP_CM;
  F_distance_D = F_distance1 - F_distance2;
  R_distance2=(float)(R_sensor.ping())*10/US_ROUNDTRIP_CM;
  R_distance_D = R_distance1 - R_distance2;
  L_distance2=(float)(L_sensor.ping())*10/US_ROUNDTRIP_CM;
  L_distance_D = L_distance1 - L_distance2;
  L_tan1=L_distance_D/F_distance_D;
  R_tan1=R_distance_D/F_distance_D;
  L_tan=atan(L_tan1)*180/3.14;
  R_tan=atan(R_tan1)*180/3.14;
  }
  
void setup() {
  Serial.begin(115200);  //스크린프린트를 115200의 속도로 사용
  pinMode(L_InPin_1,OUTPUT); //왼쪽모터1 핀 모드를 아웃풋으로
  pinMode(L_InPin_2,OUTPUT); //왼쪽모터2 핀 모드를 아웃풋으로
  pinMode(R_InPin_1,OUTPUT); //오른쪽모터1 핀 모드를 아웃풋으로
  pinMode(R_InPin_2,OUTPUT); //오른쪽모터2 핀 모드를 아웃풋으로
  analogWrite(L_en,80);  //왼쪽모터 속도 조정
  analogWrite(R_en,80);  //오른쪽모터 속도 조정

  Stop(100);
}

void loop() {
  for(int i=0; i<1700; i++){
    R_distance=(float)(R_sensor.ping())*10/US_ROUNDTRIP_CM;
    if(R_distance != 0 && mi_R_distance>=R_distance){
    mi_R_distance=R_distance;
    Serial.println(mi_R_distance);
    }
    Right(1,65);
    }

    Stop(500);

    while(1){
      R_distance=(float)(R_sensor.ping())*10/US_ROUNDTRIP_CM;
      Left(1,65);
      if(R_distance<=(mi_R_distance+10) && R_distance!= 0){break;}
      
      }
while(1){
    Stop(500);
}


 



  
}
