#define  F_Sonar  8  //정면부 초음파 센서 연결 핀
#define  R_Sonar  10 //오른쪽 초음파 센서 연결 핀
#define  L_Sonar  11 //왼쪽 초음파 센서 연결 핀
float robot_width = 200; //차량의 폭
float mazor_width = 500; //지나가는 길의 폭
float mazor_width_tolerance = 40; //폭 감지에 오찹범위
int flag_mazor_1 = 0; // 1이면 1번 구간에 내가 위치해 있음

void setup()
{
  pinMode(F_Sonar, OUTPUT); //정면부 초음파 센서 핀 모드를 아웃풋으로
  pinMode(L_Sonar, OUTPUT); //오른쪽 초음파 센서 핀 모드를 아웃풋으로
  pinMode(R_Sonar, OUTPUT); //왼쪽 초음파 센서 핀 모드를 아웃풋으로
  Serial.begin(115200);  //스크린프린트를 115200의 속도로 사용
}

float F_sonar(void){
  
  float duration=0.0; //감지하는 값
  float distance=0.0; //계산된 실제 거리(mm)
  pinMode(F_Sonar, OUTPUT);   //정면부 초음파 센서 핀 모드를 아웃풋으로
  digitalWrite(F_Sonar,LOW);  //정면부 초음파 센서의 출력은 없다
  digitalWrite(F_Sonar,HIGH); //정면부 초음파 센서의 출력이 있다
  delay(10);                  //이를 0.01초 동안 해라
  digitalWrite(F_Sonar,LOW);  //정면부 초음파 센서의 출력은 없다
  pinMode(F_Sonar, INPUT);    //정면부 초음파 센서의 핀 모드를 인풋으로
  duration=pulseIn(F_Sonar,HIGH);  //정면부 초음파 센서의 펄스 길이를 측정하여 duration에 넣어라
  distance=((float)(340*duration)/1000)/2;  //duration을 mm로 계산해 distance로 넣어라
  return distance;  //distance값을 함수 밖으로 내보내라
} //정면부 초음파 센서 거리 측정 함수

float R_sonar(void){
  
  float duration=0.0; //감지하는 값
  float distance=0.0; //계산된 실제 거리(mm)
  pinMode(R_Sonar, OUTPUT);   //오른쪽 초음파 센서 핀 모드를 아웃풋으로
  digitalWrite(R_Sonar,LOW);  //오른쪽 초음파 센서의 출력은 없다
  digitalWrite(R_Sonar,HIGH); //오른쪽 초음파 센서의 출력이 있다
  delay(10);                  //이를 0.01초 동안 해라
  digitalWrite(R_Sonar,LOW);  //오른쪽 초음파 센서의 출력은 없다
  pinMode(R_Sonar, INPUT);    //오른쪽 초음파 센서의 핀 모드를 인풋으로
  duration=pulseIn(R_Sonar,HIGH);  //오른쪽 초음파 센서의 펄스 길이를 측정하여 duration에 넣어라
  distance=((float)(340*duration)/1000)/2;  //duration을 mm로 계산해 distance로 넣어라
  return distance;  //distance값을 함수 밖으로 내보내라
} //오른쪽 초음파 센서 거리 측정 함수

float L_sonar(void){
  
  float duration=0.0; //감지하는 값
  float distance=0.0; //계산된 실제 거리(mm)
  pinMode(L_Sonar, OUTPUT);   //왼쪽 초음파 센서 핀 모드를 아웃풋으로
  digitalWrite(L_Sonar,LOW);  //왼쪽 초음파 센서의 출력은 없다
  digitalWrite(L_Sonar,HIGH); //왼쪽 초음파 센서의 출력이 있다
  delay(10);                  //이를 0.01초 동안 해라
  digitalWrite(L_Sonar,LOW);  //왼쪽 초음파 센서의 출력은 없다
  pinMode(L_Sonar, INPUT);    //왼쪽 초음파 센서의 핀 모드를 인풋으로
  duration=pulseIn(L_Sonar,HIGH);  //왼쪽 초음파 센서의 펄스 길이를 측정하여 duration에 넣어라
  distance=((float)(340*duration)/1000)/2;  //duration을 mm로 계산해 distance로 넣어라
  return distance;  //distance값을 함수 밖으로 내보내라
} //왼쪽 초음파 센서 거리 측정 함수



void loop()
{
  float angle;
  float F_distance,R_distance,L_distance; //정면,오른쪽,왼쪽 초음파 센서값을 저장할 변수 선언
  F_distance=F_sonar();  //정면 초음파 센서값을 F_distance에 저장
  L_distance=L_sonar();  //왼쪽 초음파 센서값을 L_distance에 저장
  R_distance=R_sonar();  //오른쪽 초음파 센서값을 R_distance에 저장
  Serial.print("F : ");
  Serial.print(F_distance);
  Serial.print("mm   ");  //"F : (F_distance에 저장된 값)mm" 를 스크린 프린터에 출력해라
  Serial.print("R : ");
  Serial.print(R_distance);
  Serial.print("mm   ");  //"R : (R_distance에 저장된 값)mm" 를 스크린 프린터에 출력해라
  Serial.print("L : ");
  Serial.print(L_distance);
  Serial.print("mm   \n");  //"L : (L_distance에 저장된 값)mm" 를 스크린 프린터에 출력해라
  Serial.print(flag_mazor_1);
  Serial.print("\n");  //1번 구간에 있는지 없는지를 출력(1과 0으로 구분)
  float measure_widht=L_distance+R_distance+robot_width; //오른쪽,왼쪽 초음파 센서와 기체폭을 통해 측정한 현재 측정된 길의 폭
  
  if((measure_widht >= (mazor_width-mazor_width_tolerance)) && (measure_widht <= (mazor_width+mazor_width_tolerance))){
    Serial.print("gogo\n");
    if((F_distance>mazor_width) && (F_distance<mazor_width+400)){
      flag_mazor_1 = 1;
    }//정면부 초음파 센서의 값이 폭의 길이보다 크고 폭에 길이에서 400mm보다는 작다면 1번 구간에 기체가 존재한다.
    else{
      if(L_distance>R_distance){
        Serial.print("right_robot ");
        angle=(acos(mazor_width/measure_widht))*180/3.14;
        Serial.print(angle);
        Serial.print("angle.\n\n");        
      }
      else if(L_distance>R_distance){
        Serial.print("left robot ");
        angle=(acos(mazor_width/measure_widht))*180/3.14;
        Serial.print(angle);
        Serial.print("angle.\n\n");
      }
      flag_mazor_1 = 0;
    }//위의 조건이 아닌경우 1번 구간에 존재하지 않는다.
  }//현제 측정된 폭이 오차범위 내에 존재할시
  else{
    if(L_distance>R_distance){
        Serial.print("right_robot ");
        angle=(acos(mazor_width/measure_widht))*180/3.14;
        Serial.print(angle);
        Serial.print("angle.\n");        
      }
      else if(L_distance>R_distance){
        Serial.print("left robot ");
        angle=(acos(mazor_width/measure_widht))*180/3.14;
        Serial.print(angle);
        Serial.print("angle.\n");
      }
    flag_mazor_1 = 0;
  }//프로그램이 정상작동하는지 확인하기위해 임의로 초기화를 해 한번 값이 1번이면 1번으로 유지되는것이 아닌 초기화를 하기 위한 조건
  
}