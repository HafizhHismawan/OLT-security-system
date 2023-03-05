//include Library utk jaringan wifi dan http
#include <WiFi.h>
#include <HTTPClient.h>

//Konfigurasi Wifi Hotspot dan passw 
const char* ssid2 = "POCOCU";
const char* pass2 = "99999999";

//siapkan host/server
const char* host = "monitoringminiolt.000webhostapp.com"; //alamat domain hosting atau ip komputer(jika local server)




#include<SPI.h>   // LIBRARY RFID
#include<MFRC522.h>

#include <CTBot.h>  // LIBRARY CTBOT
CTBot myBot;  // OBJEK CTBOT

String ssid = "POCOCU";  // KONFIGURASI WIFI
String pass = "99999999";

String token = "1918378425:AAEOd-7QkKOr3rdY-muoIstbkwh0tupiOwg";  // TOKEN BOT
const int id = -530181893;  // ID TELEGRAM GRUP

#define pinRST 22  // KONFIGURASI RFID DENGAN ESP32
#define pinSS 21

MFRC522 rfid(pinSS, pinRST);  // OBJEK RFID

const int buzzer = 12;  // KONFIGURASI KOMPONEN
const int relay = 26;
const int reed = 14;
const int sirine = 25;

bool relayOn = LOW;  // STATUS RELAY
bool relayOff = HIGH;

int state = 1;  // STATUS LOGIKA UNTUK LOOPING ALARM
int aktif;  // STATUS LOGIKA UNTUK PERANGKAT AKTIF KEMBALI
int pesan = 1;
int reedStatus;



void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();

  pinMode(relay, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(reed, INPUT_PULLUP);  // sensor switch magnet bersifat LOW saat magnet tersambung
  pinMode(sirine, OUTPUT);

  digitalWrite(relay, relayOff);
  digitalWrite(sirine, relayOff);
  digitalWrite(buzzer, LOW);
  Serial.println("TEMPELKAN KARTU ANDA ... \n----------------------------------\n----------------------------------");

  aktif = 1;

  myBot.wifiConnect(ssid, pass);  // KONEKSIKAN ESP32 KE WIFI
  myBot.setTelegramToken(token);

  if(myBot.testConnection()){
    Serial.println("BERHASIL TERSAMBUNG KE TELEGRAM MELALUI WIFI");  // UJI KONEKSI
  }


//Mengkoneksikan ke Wifi
  WiFi.begin(ssid2, pass2);
  Serial.println("Connecting to wifi....");
  while(WiFi.status()!= WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }

  //apabila berhasil terkoneksi
  Serial.println("WiFi Connected");

 


}

void loop() {
  reedStatus = digitalRead(reed);
  Serial.println(reedStatus);
  delay(500);

  if (reedStatus == LOW && aktif == 0){
    Serial.println("PERANGKAT AKTIF KEMBALI");
    aktif = 1;
  }

  else if (reedStatus == HIGH && !rfid.PICC_IsNewCardPresent() && !rfid.PICC_ReadCardSerial() && aktif == 1 && pesan == 1){  // TIDAK ADA KARTU YG MENEMPEL & MAGNET MENJAUH, BUZZER BERBUNYI
   for (int i=0; i<1; i++){
    myBot.sendMessage(id, "PERHATIAN !!! \nINDIKASI VANDALISME !!! \n\nMGPON01-D5-SBU-1SBU3 \n\n192.168.56.187 \n\nMINI OLT SBU  \n\nhttps://maps.app.goo.gl/EfUAbY3fpCQdzdee8");
    // Serial.println("BERHASIL KIRIM KE TELEGRAM");
   }
   kirim_web();
   pesan = 0;
   state = 0;
   sirine_on();
   goto alarm;
                                                                                                                                                                                                                                       
  }

  if (state == 0){
    alarm:
        //digitalWrite(sirine, relayOn);
        /*digitalWrite(buzzer, HIGH);
        delay(500);
        digitalWrite(buzzer, LOW);
        //delay(500);*/
        Serial.println("ALARM BERBUNYI");
        delay(500);
  }

      
  // Melihat kartu baru // Cek salah satu kartu
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()){
    return;
  }

  // Menampilkan UID
  String nomorTag;
  for (int i=0; i<=3; i++){
    nomorTag = nomorTag + (rfid.uid.uidByte[i]<0x10 ? "0" : "") + String(rfid.uid.uidByte[i], HEX) + (i==3 ? "" : ":");
  }
  Serial.println("NOMOR TAG : " + nomorTag);

  // Jika kartu berhasil diidentifikasi dengan suatu nomor TAG
  if (nomorTag == "6b:94:75:1a" || nomorTag == "04:35:45:22"){
    state = 1;
    for (int i=0; i<2; i++){
      digitalWrite(buzzer, HIGH);
      delay(100);
      digitalWrite(buzzer, LOW);
      //delay(100);
    }
    delay(500);
    digitalWrite(relay, relayOn);
    delay(5000);
    digitalWrite(relay, relayOff);
    delay(500);
    digitalWrite(sirine, relayOff);
    delay(500);
    aktif = 0;
    pesan = 1;
    reset_awal();
   
   } else {
    Serial.println("AKSES TERTOLAK ..... ");
    digitalWrite(buzzer, HIGH);
    delay(450);
    digitalWrite(buzzer, LOW);
    //delay(450);
  }
}


void kirim_web(){
  String tandes = "vandalisme";
  String kapasan = "aman";
  String kalianak = "aman";
  
  //kirim data ke server
  WiFiClient client;
  
  //inisialisasi port web server 80
  const int httpPort = 80;
  if(!client.connect(host, httpPort))
  {
    Serial.println("Connection Failed to host");
    return;
  }
   
  //kondisi pasti terkoneksi
  //kirim data sensor ke database/web
  String Link; //link alamat yg akan diakses
  HTTPClient http; //objek yg menandakan alamat mana yg sedang diakses
  Link = "http://" + String(host) + "/kirimdata.php?tandes=" + tandes + "&kapasan" + kapasan + "&kalianak" + kalianak;

  //eksekusi alamat link
  http.begin(Link); 
  http.GET();

  //baca respon setelah berhasil kirim data
  String respon = http.getString();
  Serial.println(respon);
  http.end();

 
  
}


void reset_awal(){

  String tandes = "aman";
  String kapasan = "aman";
  String kalianak = "aman";
  
  //kirim data ke server
  WiFiClient client;
  
  //inisialisasi port web server 80
  const int httpPort = 80;
  if(!client.connect(host, httpPort))
  {
    Serial.println("Connection Failed to host");
    return;
  }
   
  //kondisi pasti terkoneksi
  //kirim data sensor ke database/web
  String Link; //link alamat yg akan diakses
  HTTPClient http; //objek yg menandakan alamat mana yg sedang diakses
  Link = "http://" + String(host) + "/kirimdata.php?tandes=" + tandes + "&kapasan" + kapasan + "&kalianak" + kalianak;

  //eksekusi alamat link
  http.begin(Link); 
  http.GET();

  //baca respon setelah berhasil kirim data
  String respon = http.getString();
  Serial.println(respon);
  http.end();
  
}

void sirine_on(){
  digitalWrite(sirine, LOW);
}
