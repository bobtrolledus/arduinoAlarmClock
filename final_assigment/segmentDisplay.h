//Creates vars for 7 segment display
const int a = 3;
const int b = 4;
const int c = 5;
const int d = 6;
const int e = 7;
const int f = 8;
const int g = 9;

//Creates functions to clear and output nums on 7 segment display
void clearAll(){
  digitalWrite(a,LOW);
  digitalWrite(b,LOW);
  digitalWrite(c,LOW);
  digitalWrite(d,LOW);
  digitalWrite(e,LOW);
  digitalWrite(f,LOW);
  digitalWrite(g,LOW);
}

void digitZero(){
  clearAll();
  digitalWrite(a,HIGH);
  digitalWrite(b,HIGH);
  digitalWrite(c,HIGH);
  digitalWrite(d,HIGH);
  digitalWrite(e,HIGH);
  digitalWrite(f,HIGH);
}

void digitOne(){
  clearAll();
  digitalWrite(b,HIGH);
  digitalWrite(c,HIGH);
}

void digitTwo(){
  clearAll();
  digitalWrite(a,HIGH);
  digitalWrite(b,HIGH);
  digitalWrite(d,HIGH);
  digitalWrite(e,HIGH);
  digitalWrite(g,HIGH);
}

void digitThree(){
  clearAll();
  digitalWrite(a,HIGH);
  digitalWrite(b,HIGH);
  digitalWrite(c,HIGH);
  digitalWrite(d,HIGH);
  digitalWrite(g,HIGH);
}

void digitFour(){
  clearAll();
  digitalWrite(b,HIGH);
  digitalWrite(c,HIGH);
  digitalWrite(f,HIGH);
  digitalWrite(g,HIGH);
}

void digitFive(){
  clearAll();
  digitalWrite(a,HIGH);
  digitalWrite(c,HIGH);
  digitalWrite(d,HIGH);
  digitalWrite(f,HIGH);
  digitalWrite(g,HIGH);
}
