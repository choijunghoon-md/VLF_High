int L_InPin_1 = 2;
int L_InPin_2 = 3;
int R_InPin_1 = 7;
int R_InPin_2 = 4;
int L_en = 5;
int R_en = 6;

void setup() {
  pinMode(L_InPin_1,OUTPUT);
  pinMode(L_InPin_2,OUTPUT);
  pinMode(R_InPin_1,OUTPUT);
  pinMode(R_InPin_2,OUTPUT);
  analogWrite(L_en,80);
  analogWrite(R_en,80);
  Serial.begin(9600);
  Serial.print("Start !! \n\n");
}

void Front(int t,int sp){
  analogWrite(L_en,sp);
  analogWrite(R_en,sp);
  digitalWrite(L_InPin_1,HIGH);
  digitalWrite(L_InPin_2,LOW);
  digitalWrite(R_InPin_1,HIGH);
  digitalWrite(R_InPin_2,LOW);
  delay(t);
  }

void Back(int t,int sp){
  analogWrite(L_en,sp);
  analogWrite(R_en,sp);
  digitalWrite(L_InPin_2,HIGH);
  digitalWrite(L_InPin_1,LOW);
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
 
void loop() {
 if(Serial.available()){
  char in_data;
  in_data = Serial.read();
  Serial.print("data : ");
  Serial.println(in_data);

  if(in_data == '1'){Front(500,80);}
  else if(in_data == '2'){Back(500,80);}
  else if(in_data == '3'){Right(500,80);}
  else if(in_data == '4'){Left(1500,80);}
  else if(in_data == '5'){Stop(500);}
  }
}
