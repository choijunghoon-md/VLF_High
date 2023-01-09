  #include <NewPing.h>

  #define L_InPin_2 2  //왼쪽모터 핀1
  #define L_InPin_1 3  //왼쪽모터 핀2
  #define R_InPin_2 7  //오른쪽모터 핀1
  #define R_InPin_1 4  //오른쪽모터 핀2
  #define L_en 5 //왼쪽모터 속도 제어 핀
  #define R_en 6 //오른쪽모터 속도 제어 핀
  #define F_Sonar 8  //정면부 초음파 센서 연결 핀
  #define R_Sonar 10 //오른쪽 초음파 센서 연결 핀
  #define L_Sonar 11 //왼쪽 초음파 센서 연결 핀
  #define MaxDistance  150
  #define p_gain 0.4
  #define er 10
  #define dw 360

  int index;
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

  NewPing F_sensor(F_Sonar,F_Sonar,MaxDistance);
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

  void Stop(int t){
    digitalWrite(L_InPin_1,LOW);
    digitalWrite(L_InPin_2,LOW);
    digitalWrite(R_InPin_2,LOW);
    digitalWrite(R_InPin_1,LOW);
    delay(t);
  }

  float ck=-1;
  float ck_L=0;
  int ck_R=0;
  int adc=0;
  int line_index;
  int sum=0;

  int read_line_sensor(){
  int i;
  
  sum=0;
  int line_sensor[5]={0,0,0,0,0};
  
  for(i=0;i<5;i++){
    line_sensor[i]=(digitalRead(A0+i));
    sum += line_sensor[i];
    }
  if(sum==0) line_index = 0;
  if(sum==5) line_index = -10;
  if(sum==1){
    if(line_sensor[0]==1) line_index = -4;
    if(line_sensor[1]==1) line_index = -2;
    if(line_sensor[2]==1) line_index = 10;
    if(line_sensor[3]==1) line_index = 2;
    if(line_sensor[4]==1) line_index = 4;
    }
  if(sum==2){
    if(line_sensor[0]==1 && line_sensor[1]==1) line_index = -3;
    if(line_sensor[1]==1 && line_sensor[2]==1) line_index = -1;
    if(line_sensor[2]==1 && line_sensor[3]==1) line_index = 1;
    if(line_sensor[3]==1 && line_sensor[4]==1) line_index = 3;
    }
  Serial.print(line_index);
  Serial.println("");
  return line_index;
  }
  
  void wall_fillowing1(){
    runing(1,nm_sp_L+(L_Sonar_Error*3),nm_sp_R-(L_Sonar_Error*3));    
    }
  void wall_fillowing2(){ 
    ck_L=nm_sp_L-(L_Sonar_distance-R_Sonar_distance)*p_gain;
    ck_R=nm_sp_R+(L_Sonar_distance-R_Sonar_distance)*p_gain;

    
    if(ck_L>=200){
      ck_L=200;
      }
    if(ck_L<=50){
      ck_L=50;
      }
    if(ck_R>=200){
      ck_R=200;
     }
    if(ck_R<=50){
      ck_R=50;
     }

    if(ck_R>ck_L){ck=1;}
    if(ck_R<ck_L){ck=0;}

    if(adc==1){
      wall_fillowing1();
      }

    else if(R_Sonar_distance >= 1400 && L_Sonar_distance <=500){
      wall_fillowing1();
      }
    
    else if(dw+er*3>=R_Sonar_distance+L_Sonar_distance && R_Sonar_distance==L_Sonar_distance){
      wall_fillowing1();
      }

    else if(R_Sonar_distance<=L_Sonar_distance+er && R_Sonar_distance>=L_Sonar_distance-er && L_Sonar_distance != 1500){
      if(ck==0){
        while(1){
          index=read_line_sensor();
          read_sonar_sensor();
          Left(1,65);
          if(dw+er*5>=R_Sonar_distance+L_Sonar_distance || index != 0){
            break;
            adc=1;
          }
        }
      }
    else{
      while(1){
        index=read_line_sensor();
        read_sonar_sensor();
        Right(1,65);
        if(dw+er*5>=R_Sonar_distance+L_Sonar_distance || index != 0){
          break;
          adc=1;
          }
        }
      }
    }
    else{
      runing(1,ck_L,ck_R);
    }  
  }

  


  void loop() {
    read_line_sensor();
    read_sonar_sensor();
    update_sonar_error();
    update_sonar_old();

    float L_control_speed=20;
    float R_control_speed= L_control_speed*1.2;;
    index=read_line_sensor();
    

    

      
    if(index != 0){
      switch(index){
      case -4 : Left(1,65); break;
      case -3 : Left(1,65); break;
      case -2 : Left(1,65); break;
      case -1 : runing(1,0,72); break;
      case 10 : runing(1,50,50); break;
      case 1 : runing(1,60,0); break;
      case 2 : Right(1,65); break;
      case 3 : Right(1,65); break;
      case 4 : Right(1,65); break;
      case -10 : Stop(1); break;
    }
    adc=0;
      }

    else{
      read_sonar_sensor();
      update_sonar_error();
      update_sonar_old();
      wall_fillowing2();
    //  Serial.println(F_Sonar_distance);
      if(F_Sonar_distance<=300){
        while(1){
        index=read_line_sensor();
        read_sonar_sensor();
        Right(1,65);
        if(300>=L_Sonar_distance || index != 0){
          break;
          adc=0;
        }
       }
      }  
      delay(100);
    }


}
