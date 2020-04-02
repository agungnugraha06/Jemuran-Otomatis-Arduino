#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

const int pinRS = D0;

int x=0;
int IN1= D5;                                       //variabel motor
int IN2= D6;
int IN3= D7;
int IN4= D8;

int step = 2000;                                    
int delaytime = 4;

char ssid[] = "wulan"; 
char password[] = "123456789";
#define BOTtoken "975044221:AAEyKu7wzDOwfcK6YIWjbssG8EHDaAQblQU"
String chatid = "689037388";

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

void setup() {
  Serial.begin(9600);
  WifiStatus();

  pinMode(pinRS,INPUT);                           
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

}

float total;
int dataRS=0;

void loop() {
  dataRS = analogRead(pinRS);                     //data sensor hujan yang dibaca dari pin analog RS
  Serial.println("Data RS = ");                   //tampilan data RS di monitor
  Serial.println(dataRS);                         //Nilai dari RS yang akan ditampilkan
  total = (dataRS);
  Serial.println("total");
  Serial.println(total);
  if (total>260)
  { if (x==1){
//     Serial.println("jemuran keluar");
    for (int i=0; i<2500; i++)
    {mundur(); } x=0;}
    bot.sendMessage(chatid, "Jemuran Keluar");
    Serial.println("Pesan Terkirim ke Telegram");
    
  }
  else if (total<160)
  { if(x==0){
//    Serial.println("jemuran masuk");
    for (int i=0; i<2500; i++)
    {maju(); } x=1;}
    bot.sendMessage(chatid, "Jemuran Masuk");
    Serial.println("Pesan Terkirim ke Telegram");
   
}

delay(1000);
}


void WifiStatus() {
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(50);
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(50);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}


void mundur(){
  step4();
  delay(delaytime);
  step3();
  delay(delaytime);
  step2();
  delay(delaytime);
  step1();
  delay(delaytime);
}
void maju(){
  step1();
  delay(delaytime);
  step2();
  delay(delaytime);
  step3();
  delay(delaytime);
  step4();
  delay(delaytime);
}

void step1(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);
}
void step2(){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void step3(){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
void step4(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
