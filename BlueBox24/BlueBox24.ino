// CÓDIGO BLUEBOX 24 - AGENDA DE JOGOS DA COPA DO MUNDO
// AUTOR: FILIPEFLOP
// Versão de 06/12/2022 - Wilson Luiz Prosdocimo

// Bibliotecas utilizadas no código
#include <Arduino.h>
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiUdp.h>
#include <ArduinoJson.h>
#include <U8g2lib.h>
#include <NTPClient.h>
#include <WiFiClient.h>

// informações da rede WiFi
const char *ssid = "";
const char *password = "";

// Informações sobre a API football-data.org
#define API_KEY ""

// Definição dos pinos de conexão entre os componentes e a placa
#define X_JOYSTICK A0
#define SW_JOYSTICK 5
#define MOTOR 4

// Variáveis globais utilizadas no código
int tela1 = 0;
int tela2 = 0;
int Hora;
int Minuto;
int Dia;
int Mes;

String jogo1_home;
String jogo1_away;
String jogo2_home;
String jogo2_away;
String jogo3_home;
String jogo3_away;
String jogo4_home;
String jogo4_away;
String jogo5_home;
String jogo5_away;
String jogo6_home;
String jogo6_away;

String jogo7_home;
String jogo7_away;
String jogo8_home;
String jogo8_away;
String jogo9_home;
String jogo9_away;
String jogo10_home;
String jogo10_away;
String jogo11_home;
String jogo11_away;
String jogo12_home;
String jogo12_away;

String jogo13_home;
String jogo13_away;
String jogo14_home;
String jogo14_away;
String jogo15_home;
String jogo15_away;
String jogo16_home;
String jogo16_away;
String jogo17_home;
String jogo17_away;
String jogo18_home;
String jogo18_away;

String jogo19_home;
String jogo19_away;
String jogo20_home;
String jogo20_away;
String jogo21_home;
String jogo21_away;
String jogo22_home;
String jogo22_away;
String jogo23_home;
String jogo23_away;
String jogo24_home;
String jogo24_away;

String jogo25_home;
String jogo25_away;
String jogo26_home;
String jogo26_away;
String jogo27_home;
String jogo27_away;
String jogo28_home;
String jogo28_away;
String jogo29_home;
String jogo29_away;
String jogo30_home;
String jogo30_away;

String jogo31_home;
String jogo31_away;
String jogo32_home;
String jogo32_away;
String jogo33_home;
String jogo33_away;
String jogo34_home;
String jogo34_away;
String jogo35_home;
String jogo35_away;
String jogo36_home;
String jogo36_away;

String jogo37_home;
String jogo37_away;
String jogo38_home;
String jogo38_away;
String jogo39_home;
String jogo39_away;
String jogo40_home;
String jogo40_away;
String jogo41_home;
String jogo41_away;
String jogo42_home;
String jogo42_away;

String jogo43_home;
String jogo43_away;
String jogo44_home;
String jogo44_away;
String jogo45_home;
String jogo45_away;
String jogo46_home;
String jogo46_away;
String jogo47_home;
String jogo47_away;
String jogo48_home;
String jogo48_away;

String jogo49_home;
String jogo49_away;
String jogo49_times;
String jogo50_home;
String jogo50_away;
String jogo50_times;
String jogo51_home;
String jogo51_away;
String jogo51_times;
String jogo52_home;
String jogo52_away;
String jogo52_times;
String jogo53_home;
String jogo53_away;
String jogo53_times;
String jogo54_home;
String jogo54_away;
String jogo54_times;
String jogo55_home;
String jogo55_away;
String jogo55_times;
String jogo56_home;
String jogo56_away;
String jogo56_times;

String jogo57_home;
String jogo57_away;
String jogo57_times;
String jogo58_home;
String jogo58_away;
String jogo58_times;
String jogo59_home;
String jogo59_away;
String jogo59_times;
String jogo60_home;
String jogo60_away;
String jogo60_times;

String jogo61_home;
String jogo61_away;
String jogo61_times;
String jogo62_home;
String jogo62_away;
String jogo62_times;

String jogo63_home;
String jogo63_away;
String jogo63_times;

String jogo64_home;
String jogo64_away;
String jogo64_times;

const unsigned char logo_FWC[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x1F, 0xE0, 0x38, 0x07, 0x83, 0x8F, 0xFE, 0x7F, 0x80, 0x0F, 0x07, 0x83, 0x80, 0x0F, 0x80, 0x0C,
  0x1F, 0xF8, 0x38, 0x07, 0x83, 0x8F, 0xFE, 0x7F, 0xE0, 0x3F, 0xC3, 0x87, 0x80, 0x1F, 0xC0, 0x1C,
  0x1F, 0xFC, 0x38, 0x07, 0x83, 0x8F, 0xFE, 0x7F, 0xF0, 0xFF, 0xE1, 0xC7, 0x00, 0x3C, 0xE0, 0x3C,
  0x1E, 0x1C, 0x38, 0x07, 0x83, 0x8F, 0x00, 0x78, 0x70, 0xF0, 0xE1, 0xEF, 0x00, 0x38, 0xE0, 0x7C,
  0x1E, 0x1C, 0x38, 0x07, 0x83, 0x8F, 0x00, 0x78, 0x71, 0xE0, 0xF0, 0xFE, 0x00, 0x00, 0xE0, 0xEC,
  0x1E, 0x38, 0x38, 0x07, 0x83, 0x8F, 0xFC, 0x78, 0xE1, 0xE0, 0x70, 0x7C, 0x00, 0x00, 0xE1, 0xCC,
  0x1F, 0xF8, 0x38, 0x07, 0x83, 0x8F, 0xFC, 0x7F, 0xE1, 0xE0, 0x70, 0x7C, 0x00, 0x01, 0xC1, 0x8C,
  0x1F, 0xFC, 0x38, 0x07, 0x83, 0x8F, 0x00, 0x7F, 0xF1, 0xE0, 0x70, 0x7C, 0x00, 0x07, 0x83, 0x0C,
  0x1E, 0x1E, 0x38, 0x07, 0x83, 0x8F, 0x00, 0x78, 0x79, 0xE0, 0xF0, 0xFE, 0x00, 0x0F, 0x07, 0xFF,
  0x1E, 0x1E, 0x38, 0x03, 0x87, 0x8F, 0x00, 0x78, 0x78, 0xE0, 0xF1, 0xEF, 0x00, 0x1E, 0x07, 0xFF,
  0x1E, 0x3E, 0x3F, 0xE3, 0xCF, 0x0F, 0x00, 0x78, 0xF8, 0xFB, 0xE1, 0xC7, 0x00, 0x3C, 0x07, 0xFF,
  0x1F, 0xFC, 0x3F, 0xE1, 0xFF, 0x0F, 0xFE, 0x7F, 0xF0, 0x7F, 0xC3, 0x87, 0x80, 0x3F, 0xF0, 0x0C,
  0x1F, 0xF8, 0x3F, 0xE0, 0xFC, 0x0F, 0xFE, 0x7F, 0xE0, 0x3F, 0x87, 0x83, 0xC0, 0x7F, 0xF0, 0x0C,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x07, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x1F, 0xF8, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x07, 0xE0, 0x0F, 0xC0, 0x3F, 0x01, 0xF8,
  0x3C, 0x7C, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xF0, 0x3F, 0xF0, 0xFF, 0x83, 0xFC,
  0x38, 0x1C, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x18, 0x78, 0x78, 0x78, 0x83, 0xC4, 0x1E,
  0x70, 0x0E, 0x07, 0xF1, 0xFF, 0x00, 0x01, 0xFC, 0x70, 0x80, 0x38, 0x70, 0x38, 0x01, 0xC0, 0x0E,
  0x70, 0x0E, 0x1F, 0xF3, 0xFF, 0x00, 0x07, 0xFC, 0x71, 0x80, 0x1C, 0xE0, 0x1C, 0x01, 0xC0, 0x0E,
  0x70, 0x0E, 0x38, 0x73, 0xFE, 0x00, 0x0E, 0x1C, 0x73, 0x80, 0x18, 0xE0, 0x1C, 0x01, 0xC0, 0x0E,
  0x70, 0x0E, 0x30, 0x70, 0x60, 0x00, 0x0C, 0x1C, 0x76, 0x00, 0x38, 0xE3, 0x1C, 0x01, 0xC0, 0x0E,
  0x70, 0x0E, 0x70, 0x70, 0x60, 0x00, 0x1C, 0x1C, 0x7C, 0x00, 0x30, 0xE3, 0x1C, 0x01, 0x80, 0x0C,
  0x70, 0x0C, 0x70, 0x70, 0x60, 0x00, 0x1C, 0x3C, 0x78, 0x00, 0x60, 0xE0, 0x1C, 0x03, 0x00, 0x18,
  0x38, 0x18, 0x70, 0xF0, 0x60, 0x00, 0x1C, 0x3C, 0x78, 0x00, 0xC0, 0x60, 0x18, 0x0E, 0x00, 0x70,
  0x3E, 0x30, 0x70, 0x70, 0x60, 0x00, 0x1C, 0x1C, 0x78, 0x03, 0x00, 0x60, 0x18, 0x18, 0x00, 0xC0,
  0x1F, 0x40, 0x79, 0x70, 0x70, 0x00, 0x1C, 0x5C, 0x78, 0x00, 0x00, 0x30, 0x30, 0x40, 0x02, 0x00,
  0x07, 0xC0, 0x3E, 0x70, 0x7F, 0xFF, 0xFF, 0x9C, 0x70, 0x1F, 0xFC, 0x18, 0x60, 0xFF, 0xE7, 0xFF,
  0x03, 0xF0, 0x3C, 0x70, 0x3F, 0xFF, 0xFF, 0x1C, 0x70, 0x1F, 0xFC, 0x0C, 0xC1, 0xFF, 0xCF, 0xFF,
  0x00, 0xFC, 0x18, 0x70, 0x0F, 0xFF, 0xFC, 0x1C, 0x70, 0x1F, 0xFC, 0x03, 0x01, 0xFF, 0xC7, 0xFE,
  0x00, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x0F, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x03, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// Criação dos objetos para as bibliotecas
U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R2, 14, 13, 15, U8X8_PIN_NONE);
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");
ESP8266WiFiMulti WiFiMulti;
WiFiClient wifiClient;

//----------SETUP----------
void setup() {

  // Incialização da comunicação Serial
  Serial.begin(115200);

  // Inicialição dos pinos como entrada ou saída
  pinMode(X_JOYSTICK, INPUT);
  pinMode(SW_JOYSTICK, INPUT_PULLUP);
  pinMode(MOTOR, OUTPUT);

  // Inicialização da conexão com a rede WiFi
  Serial.print("Conectando ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Inicialização da comunição com o protocolo NTP
  timeClient.begin();
  timeClient.setTimeOffset(-10800);

  // Inicialização da display LCD
  u8g2.begin();

  // Faz o download das informações dos jogos
  update();
  delay(500);
  // Chama a função FWC, que mostra a arte para a copa do mundo
  FWC();
}

//----------LOOP----------
void loop() {

  // Verifica se o joystick foi posicionado para a direita
  if (analogRead(X_JOYSTICK) > 970) {
    delay(50);
    tela2 = 0;
    tela1++;
  }

  // Verifica se o joystick foi posicionado para a esquerda
  if (analogRead(X_JOYSTICK) < 100) {
    delay(50);
    tela2 = 0;
    tela1--;
  }

  if (tela1 == 16) { tela1 = 1; }
  if (tela1 == -1) { tela1 = 15; }

  // Muda as informações da tela conforme comandos do joystick
  switch (tela1) {
    case 1:
      GrupoA();
      break;
    case 2:
      GrupoB();
      break;
    case 3:
      GrupoC();
      break;
    case 4:
      GrupoD();
      break;
    case 5:
      GrupoE();
      break;
    case 6:
      GrupoF();
      break;
    case 7:
      GrupoG();
      break;
    case 8:
      GrupoH();
      break;
    case 9:
      Oitavas1();
      break;
    case 10:
      Oitavas2();
      break;
    case 11:
      Quartas();
      break;
    case 12:
      SemiFinal();
      break;
    case 13:
      TerceiroLugar();
      break;
    case 14:
      Final();
      break;
  }

  // Verifica se o botão do joystick foi pressionado
  if (digitalRead(SW_JOYSTICK) == LOW) {
    delay(200);
    tela1 = 0;
    tela2++;
    if (tela2 > 4) { tela2 = 1; }
  }
  // Muda as informações da tela conforme comandos do joystick
  if (tela2 == 1) { JogosHoje(); }
  if (tela2 == 2) { RelogioGrande(); }
  if (tela2 == 3) { FWC(); }

  JogosAgora();
}

void FWC() {

  u8g2.clearBuffer();
  u8g2.drawBitmap(0, 12, 16, 40, logo_FWC);
  u8g2.sendBuffer();
  delay(500);
}

void GrupoA() {

  u8g2.clearBuffer();
  u8g2.setFontMode(1);
  u8g2.setFont(u8g2_font_5x7_tf);

  RelogioPequeno();

  u8g2.setCursor(47, 6);
  u8g2.print("GRUPO A");

  u8g2.setCursor(1, 18);
  u8g2.print("CATxEQU");
  u8g2.setCursor(1, 27);
  u8g2.print("SENxHOL");
  u8g2.setCursor(1, 36);
  u8g2.print("CATxSEN");
  u8g2.setCursor(1, 45);
  u8g2.print("HOLxEQU");
  u8g2.setCursor(1, 54);
  u8g2.print("HOLxCAT");
  u8g2.setCursor(1, 63);
  u8g2.print("EQUxSEN");

  u8g2.setCursor(45, 18);
  u8g2.print(jogo1_home[50]);
  u8g2.print("x");
  u8g2.print(jogo1_away[50]);
  u8g2.setCursor(45, 27);
  u8g2.print(jogo2_home[50]);
  u8g2.print("x");
  u8g2.print(jogo2_away[50]);
  u8g2.setCursor(45, 36);
  u8g2.print(jogo3_home[50]);
  u8g2.print("x");
  u8g2.print(jogo3_away[50]);
  u8g2.setCursor(45, 45);
  u8g2.print(jogo4_home[50]);
  u8g2.print("x");
  u8g2.print(jogo4_away[50]);
  u8g2.setCursor(45, 54);
  u8g2.print(jogo5_home[50]);
  u8g2.print("x");
  u8g2.print(jogo5_away[50]);
  u8g2.setCursor(45, 63);
  u8g2.print(jogo6_home[50]);
  u8g2.print("x");
  u8g2.print(jogo6_away[50]);

  u8g2.setCursor(72, 18);
  u8g2.print("20/11 13:00");
  u8g2.setCursor(72, 27);
  u8g2.print("21/11 13:00");
  u8g2.setCursor(72, 36);
  u8g2.print("25/11 10:00");
  u8g2.setCursor(72, 45);
  u8g2.print("25/11 13:00");
  u8g2.setCursor(72, 54);
  u8g2.print("29/11 12:00");
  u8g2.setCursor(72, 63);
  u8g2.print("29/11 12:00");

  u8g2.sendBuffer();
  delay(500);
}

void GrupoB() {
  u8g2.clearBuffer();
  u8g2.setFontMode(1);
  u8g2.setFont(u8g2_font_5x7_tf);

  RelogioPequeno();

  u8g2.setCursor(47, 6);
  u8g2.print("GRUPO B");

  u8g2.setCursor(1, 18);
  u8g2.print("INGxIRA");
  u8g2.setCursor(1, 27);
  u8g2.print("EUAxGAL");
  u8g2.setCursor(1, 36);
  u8g2.print("GALxIRA");
  u8g2.setCursor(1, 45);
  u8g2.print("INGxEUA");
  u8g2.setCursor(1, 54);
  u8g2.print("IRAxEUA");
  u8g2.setCursor(1, 63);
  u8g2.print("GALxING");

  u8g2.setCursor(45, 18);
  u8g2.print(jogo7_home[50]);
  u8g2.print("x");
  u8g2.print(jogo7_away[50]);
  u8g2.setCursor(45, 27);
  u8g2.print(jogo8_home[50]);
  u8g2.print("x");
  u8g2.print(jogo8_away[50]);
  u8g2.setCursor(45, 36);
  u8g2.print(jogo9_home[50]);
  u8g2.print("x");
  u8g2.print(jogo9_away[50]);
  u8g2.setCursor(45, 45);
  u8g2.print(jogo10_home[50]);
  u8g2.print("x");
  u8g2.print(jogo10_away[50]);
  u8g2.setCursor(45, 54);
  u8g2.print(jogo11_home[50]);
  u8g2.print("x");
  u8g2.print(jogo11_away[50]);
  u8g2.setCursor(45, 63);
  u8g2.print(jogo12_home[50]);
  u8g2.print("x");
  u8g2.print(jogo12_away[50]);

  u8g2.setCursor(72, 18);
  u8g2.print("21/11 10:00");
  u8g2.setCursor(72, 27);
  u8g2.print("21/11 16:00");
  u8g2.setCursor(72, 36);
  u8g2.print("25/11 07:00");
  u8g2.setCursor(72, 45);
  u8g2.print("25/11 16:00");
  u8g2.setCursor(72, 54);
  u8g2.print("29/11 16:00");
  u8g2.setCursor(72, 63);
  u8g2.print("29/11 16:00");

  u8g2.sendBuffer();
  delay(500);
}

void GrupoC() {
  u8g2.clearBuffer();
  u8g2.setFontMode(1);
  u8g2.setFont(u8g2_font_5x7_tf);

  RelogioPequeno();

  u8g2.setCursor(47, 6);
  u8g2.print("GRUPO C");

  u8g2.setCursor(1, 18);
  u8g2.print("ARGxARA");
  u8g2.setCursor(1, 27);
  u8g2.print("MEXxPOL");
  u8g2.setCursor(1, 36);
  u8g2.print("POLxARA");
  u8g2.setCursor(1, 45);
  u8g2.print("ARGxMEX");
  u8g2.setCursor(1, 54);
  u8g2.print("POLxARG");
  u8g2.setCursor(1, 63);
  u8g2.print("ARAxMEX");

  u8g2.setCursor(45, 18);
  u8g2.print(jogo13_home[50]);
  u8g2.print("x");
  u8g2.print(jogo13_away[50]);
  u8g2.setCursor(45, 27);
  u8g2.print(jogo14_home[50]);
  u8g2.print("x");
  u8g2.print(jogo14_away[50]);
  u8g2.setCursor(45, 36);
  u8g2.print(jogo15_home[50]);
  u8g2.print("x");
  u8g2.print(jogo15_away[50]);
  u8g2.setCursor(45, 45);
  u8g2.print(jogo16_home[50]);
  u8g2.print("x");
  u8g2.print(jogo16_away[50]);
  u8g2.setCursor(45, 54);
  u8g2.print(jogo17_home[50]);
  u8g2.print("x");
  u8g2.print(jogo17_away[50]);
  u8g2.setCursor(45, 63);
  u8g2.print(jogo18_home[50]);
  u8g2.print("x");
  u8g2.print(jogo18_away[50]);

  u8g2.setCursor(72, 18);
  u8g2.print("22/11 07:00");
  u8g2.setCursor(72, 27);
  u8g2.print("22/11 13:00");
  u8g2.setCursor(72, 36);
  u8g2.print("26/11 10:00");
  u8g2.setCursor(72, 45);
  u8g2.print("26/11 16:00");
  u8g2.setCursor(72, 54);
  u8g2.print("30/11 16:00");
  u8g2.setCursor(72, 63);
  u8g2.print("30/11 16:00");

  u8g2.sendBuffer();
  delay(500);
}

void GrupoD() {
  u8g2.clearBuffer();
  u8g2.setFontMode(1);
  u8g2.setFont(u8g2_font_5x7_tf);

  RelogioPequeno();

  u8g2.setCursor(47, 6);
  u8g2.print("GRUPO D");

  u8g2.setCursor(1, 18);
  u8g2.print("DINxTUN");
  u8g2.setCursor(1, 27);
  u8g2.print("FRAxAUS");
  u8g2.setCursor(1, 36);
  u8g2.print("TUNxAUS");
  u8g2.setCursor(1, 45);
  u8g2.print("FRAxDIN");
  u8g2.setCursor(1, 54);
  u8g2.print("TUNxFRA");
  u8g2.setCursor(1, 63);
  u8g2.print("AUSxDIN");

  u8g2.setCursor(45, 18);
  u8g2.print(jogo19_home[50]);
  u8g2.print("x");
  u8g2.print(jogo19_away[50]);
  u8g2.setCursor(45, 27);
  u8g2.print(jogo20_home[50]);
  u8g2.print("x");
  u8g2.print(jogo20_away[50]);
  u8g2.setCursor(45, 36);
  u8g2.print(jogo21_home[50]);
  u8g2.print("x");
  u8g2.print(jogo21_away[50]);
  u8g2.setCursor(45, 45);
  u8g2.print(jogo22_home[50]);
  u8g2.print("x");
  u8g2.print(jogo22_away[50]);
  u8g2.setCursor(45, 54);
  u8g2.print(jogo23_home[50]);
  u8g2.print("x");
  u8g2.print(jogo23_away[50]);
  u8g2.setCursor(45, 63);
  u8g2.print(jogo24_home[50]);
  u8g2.print("x");
  u8g2.print(jogo24_away[50]);

  u8g2.setCursor(72, 18);
  u8g2.print("22/11 10:00");
  u8g2.setCursor(72, 27);
  u8g2.print("22/11 16:00");
  u8g2.setCursor(72, 36);
  u8g2.print("26/11 07:00");
  u8g2.setCursor(72, 45);
  u8g2.print("26/11 13:00");
  u8g2.setCursor(72, 54);
  u8g2.print("30/11 12:00");
  u8g2.setCursor(72, 63);
  u8g2.print("30/11 12:00");

  u8g2.sendBuffer();
  delay(500);
}

void GrupoE() {
  u8g2.clearBuffer();
  u8g2.setFontMode(1);
  u8g2.setFont(u8g2_font_5x7_tf);

  RelogioPequeno();

  u8g2.setCursor(47, 6);
  u8g2.print("GRUPO E");

  u8g2.setCursor(1, 18);
  u8g2.print("ALExJAP");
  u8g2.setCursor(1, 27);
  u8g2.print("ESPxCRC");
  u8g2.setCursor(1, 36);
  u8g2.print("JAPxCRC");
  u8g2.setCursor(1, 45);
  u8g2.print("ESPxALE");
  u8g2.setCursor(1, 54);
  u8g2.print("JAPxESP");
  u8g2.setCursor(1, 63);
  u8g2.print("CRCxALE");

  u8g2.setCursor(45, 18);
  u8g2.print(jogo25_home[50]);
  u8g2.print("x");
  u8g2.print(jogo25_away[50]);
  u8g2.setCursor(45, 27);
  u8g2.print(jogo26_home[50]);
  u8g2.print("x");
  u8g2.print(jogo26_away[50]);
  u8g2.setCursor(45, 36);
  u8g2.print(jogo27_home[50]);
  u8g2.print("x");
  u8g2.print(jogo27_away[50]);
  u8g2.setCursor(45, 45);
  u8g2.print(jogo28_home[50]);
  u8g2.print("x");
  u8g2.print(jogo28_away[50]);
  u8g2.setCursor(45, 54);
  u8g2.print(jogo29_home[50]);
  u8g2.print("x");
  u8g2.print(jogo29_away[50]);
  u8g2.setCursor(45, 63);
  u8g2.print(jogo30_home[50]);
  u8g2.print("x");
  u8g2.print(jogo30_away[50]);

  u8g2.setCursor(72, 18);
  u8g2.print("23/11 10:00");
  u8g2.setCursor(72, 27);
  u8g2.print("23/11 13:00");
  u8g2.setCursor(72, 36);
  u8g2.print("27/11 07:00");
  u8g2.setCursor(72, 45);
  u8g2.print("27/11 16:00");
  u8g2.setCursor(72, 54);
  u8g2.print("01/12 16:00");
  u8g2.setCursor(72, 63);
  u8g2.print("01/12 16:00");

  u8g2.sendBuffer();
  delay(500);
}

void GrupoF() {
  u8g2.clearBuffer();
  u8g2.setFontMode(1);
  u8g2.setFont(u8g2_font_5x7_tf);

  RelogioPequeno();

  u8g2.setCursor(47, 6);
  u8g2.print("GRUPO F");

  u8g2.setCursor(1, 18);
  u8g2.print("MARxCRO");
  u8g2.setCursor(1, 27);
  u8g2.print("BELxCAN");
  u8g2.setCursor(1, 36);
  u8g2.print("BELxMAR");
  u8g2.setCursor(1, 45);
  u8g2.print("CROxCAN");
  u8g2.setCursor(1, 54);
  u8g2.print("CROxBEL");
  u8g2.setCursor(1, 63);
  u8g2.print("CANxMAR");

  u8g2.setCursor(45, 18);
  u8g2.print(jogo31_home[50]);
  u8g2.print("x");
  u8g2.print(jogo31_away[50]);
  u8g2.setCursor(45, 27);
  u8g2.print(jogo32_home[50]);
  u8g2.print("x");
  u8g2.print(jogo32_away[50]);
  u8g2.setCursor(45, 36);
  u8g2.print(jogo33_home[50]);
  u8g2.print("x");
  u8g2.print(jogo33_away[50]);
  u8g2.setCursor(45, 45);
  u8g2.print(jogo34_home[50]);
  u8g2.print("x");
  u8g2.print(jogo34_away[50]);
  u8g2.setCursor(45, 54);
  u8g2.print(jogo35_home[50]);
  u8g2.print("x");
  u8g2.print(jogo35_away[50]);
  u8g2.setCursor(45, 63);
  u8g2.print(jogo36_home[50]);
  u8g2.print("x");
  u8g2.print(jogo36_away[50]);

  u8g2.setCursor(72, 18);
  u8g2.print("23/11 07:00");
  u8g2.setCursor(72, 27);
  u8g2.print("23/11 16:00");
  u8g2.setCursor(72, 36);
  u8g2.print("27/11 10:00");
  u8g2.setCursor(72, 45);
  u8g2.print("27/11 13:00");
  u8g2.setCursor(72, 54);
  u8g2.print("01/12 12:00");
  u8g2.setCursor(72, 63);
  u8g2.print("01/12 12:00");

  u8g2.sendBuffer();
  delay(500);
}

void GrupoG() {
  u8g2.clearBuffer();
  u8g2.setFontMode(1);
  u8g2.setFont(u8g2_font_5x7_tf);

  RelogioPequeno();

  u8g2.setCursor(47, 6);
  u8g2.print("GRUPO G");

  u8g2.setCursor(1, 18);
  u8g2.print("SUIxCAM");
  u8g2.setCursor(1, 27);
  u8g2.print("BRAxSER");
  u8g2.setCursor(1, 36);
  u8g2.print("CAMxSER");
  u8g2.setCursor(1, 45);
  u8g2.print("BRAxSUI");
  u8g2.setCursor(1, 54);
  u8g2.print("CAMxBRA");
  u8g2.setCursor(1, 63);
  u8g2.print("SERxSUI");

  u8g2.setCursor(45, 18);
  u8g2.print(jogo37_home[50]);
  u8g2.print("x");
  u8g2.print(jogo37_away[50]);
  u8g2.setCursor(45, 27);
  u8g2.print(jogo38_home[50]);
  u8g2.print("x");
  u8g2.print(jogo38_away[50]);
  u8g2.setCursor(45, 36);
  u8g2.print(jogo39_home[50]);
  u8g2.print("x");
  u8g2.print(jogo39_away[50]);
  u8g2.setCursor(45, 45);
  u8g2.print(jogo40_home[50]);
  u8g2.print("x");
  u8g2.print(jogo40_away[50]);
  u8g2.setCursor(45, 54);
  u8g2.print(jogo41_home[50]);
  u8g2.print("x");
  u8g2.print(jogo41_away[50]);
  u8g2.setCursor(45, 63);
  u8g2.print(jogo42_home[50]);
  u8g2.print("x");
  u8g2.print(jogo42_away[50]);

  u8g2.setCursor(72, 18);
  u8g2.print("24/11 07:00");
  u8g2.setCursor(72, 27);
  u8g2.print("24/11 16:00");
  u8g2.setCursor(72, 36);
  u8g2.print("28/11 07:00");
  u8g2.setCursor(72, 45);
  u8g2.print("28/11 13:00");
  u8g2.setCursor(72, 54);
  u8g2.print("02/12 16:00");
  u8g2.setCursor(72, 63);
  u8g2.print("02/12 16:00");

  u8g2.sendBuffer();
  delay(500);
}

void GrupoH() {
  u8g2.clearBuffer();
  u8g2.setFontMode(1);
  u8g2.setFont(u8g2_font_5x7_tf);

  RelogioPequeno();

  u8g2.setCursor(47, 6);
  u8g2.print("GRUPO H");

  u8g2.setCursor(1, 18);
  u8g2.print("URUxCOR");
  u8g2.setCursor(1, 27);
  u8g2.print("PORxGAN");
  u8g2.setCursor(1, 36);
  u8g2.print("CORxGAN");
  u8g2.setCursor(1, 45);
  u8g2.print("PORxURU");
  u8g2.setCursor(1, 54);
  u8g2.print("CORxPOR");
  u8g2.setCursor(1, 63);
  u8g2.print("GANxURU");

  u8g2.setCursor(45, 18);
  u8g2.print(jogo43_home[50]);
  u8g2.print("x");
  u8g2.print(jogo43_away[50]);
  u8g2.setCursor(45, 27);
  u8g2.print(jogo44_home[50]);
  u8g2.print("x");
  u8g2.print(jogo44_away[50]);
  u8g2.setCursor(45, 36);
  u8g2.print(jogo45_home[50]);
  u8g2.print("x");
  u8g2.print(jogo45_away[50]);
  u8g2.setCursor(45, 45);
  u8g2.print(jogo46_home[50]);
  u8g2.print("x");
  u8g2.print(jogo46_away[50]);
  u8g2.setCursor(45, 54);
  u8g2.print(jogo47_home[50]);
  u8g2.print("x");
  u8g2.print(jogo47_away[50]);
  u8g2.setCursor(45, 63);
  u8g2.print(jogo48_home[50]);
  u8g2.print("x");
  u8g2.print(jogo48_away[50]);

  u8g2.setCursor(72, 18);
  u8g2.print("24/11 10:00");
  u8g2.setCursor(72, 27);
  u8g2.print("24/11 13:00");
  u8g2.setCursor(72, 36);
  u8g2.print("28/11 10:00");
  u8g2.setCursor(72, 45);
  u8g2.print("28/11 16:00");
  u8g2.setCursor(72, 54);
  u8g2.print("02/12 12:00");
  u8g2.setCursor(72, 63);
  u8g2.print("02/12 12:00");

  u8g2.sendBuffer();
  delay(500);
}

void Oitavas1() {
  u8g2.clearBuffer();
  u8g2.setFontMode(1);
  u8g2.setFont(u8g2_font_5x7_tf);

  RelogioPequeno();

  u8g2.setCursor(11, 6);
  u8g2.print("OITAVAS DE FINAL");

  u8g2.setCursor(1, 18);
  u8g2.print(jogo49_times);
  u8g2.setCursor(1, 27);
  u8g2.print(jogo50_times);
  u8g2.setCursor(1, 36);
  u8g2.print(jogo51_times);
  u8g2.setCursor(1, 45);
  u8g2.print(jogo52_times);
  u8g2.setCursor(1, 54);
  u8g2.print(jogo53_times);
  u8g2.setCursor(0, 63);
  u8g2.print(jogo54_times);

  u8g2.setCursor(45, 18);
  u8g2.print(jogo49_home);
  u8g2.print("x");
  u8g2.print(jogo49_away);
  u8g2.setCursor(45, 27);
  u8g2.print(jogo50_home);
  u8g2.print("x");
  u8g2.print(jogo50_away);
  u8g2.setCursor(45, 36);
  u8g2.print(jogo51_home);
  u8g2.print("x");
  u8g2.print(jogo51_away);
  u8g2.setCursor(45, 45);
  u8g2.print(jogo52_home);
  u8g2.print("x");
  u8g2.print(jogo52_away);
  u8g2.setCursor(45, 54);
  u8g2.print(jogo53_home);
  u8g2.print("x");
  u8g2.print(jogo53_away);
  u8g2.setCursor(45, 63);
  u8g2.print(jogo54_home);
  u8g2.print("x");
  u8g2.print(jogo54_away);

  u8g2.setCursor(72, 18);
  u8g2.print("03/12 12:00");
  u8g2.setCursor(72, 27);
  u8g2.print("03/12 16:00");
  u8g2.setCursor(72, 36);
  u8g2.print("05/12 12:00");
  u8g2.setCursor(72, 45);
  u8g2.print("05/12 16:00");
  u8g2.setCursor(72, 54);
  u8g2.print("04/12 16:00");
  u8g2.setCursor(72, 63);
  u8g2.print("04/12 12:00");

  u8g2.sendBuffer();
  delay(500);
}

void Oitavas2() {
  u8g2.clearBuffer();
  u8g2.setFontMode(1);
  u8g2.setFont(u8g2_font_5x7_tf);

  RelogioPequeno();

  u8g2.setCursor(11, 6);
  u8g2.print("OITAVAS DE FINAL");

  u8g2.setCursor(1, 18);
  u8g2.print(jogo55_times);
  u8g2.setCursor(1, 27);
  u8g2.print(jogo56_times);

  u8g2.setCursor(45, 18);
  u8g2.print(jogo55_home);
  u8g2.print("x");
  u8g2.print(jogo55_away);
  u8g2.setCursor(45, 27);
  u8g2.print(jogo56_home);
  u8g2.print("x");
  u8g2.print(jogo56_away);

  u8g2.setCursor(72, 18);
  u8g2.print("06/12 12:00");
  u8g2.setCursor(72, 27);
  u8g2.print("06/12 16:00");

  u8g2.sendBuffer();
  delay(500);
}

void Quartas() {
  u8g2.clearBuffer();
  u8g2.setFontMode(1);
  u8g2.setFont(u8g2_font_5x7_tf);

  RelogioPequeno();

  u8g2.setCursor(11, 6);
  u8g2.print("QUARTAS DE FINAL");

  u8g2.setCursor(1, 18);
  u8g2.print(jogo57_times);
  u8g2.setCursor(1, 27);
  u8g2.print(jogo58_times);
  u8g2.setCursor(1, 36);
  u8g2.print(jogo59_times);
  u8g2.setCursor(1, 45);
  u8g2.print(jogo60_times);

  u8g2.setCursor(45, 18);
  u8g2.print(jogo57_home);
  u8g2.print("x");
  u8g2.print(jogo57_away);
  u8g2.setCursor(45, 27);
  u8g2.print(jogo58_home);
  u8g2.print("x");
  u8g2.print(jogo58_away);
  u8g2.setCursor(45, 36);
  u8g2.print(jogo59_home);
  u8g2.print("x");
  u8g2.print(jogo59_away);
  u8g2.setCursor(45, 45);
  u8g2.print(jogo60_home);
  u8g2.print("x");
  u8g2.print(jogo60_away);

  u8g2.setCursor(72, 18);
  u8g2.print("09/12 12:00");
  u8g2.setCursor(72, 27);
  u8g2.print("09/12 16:00");
  u8g2.setCursor(72, 36);
  u8g2.print("10/12 12:00");
  u8g2.setCursor(72, 45);
  u8g2.print("10/12 16:00");

  u8g2.sendBuffer();
  delay(500);
}

void SemiFinal() {
  u8g2.clearBuffer();
  u8g2.setFontMode(1);
  u8g2.setFont(u8g2_font_5x7_tf);

  RelogioPequeno();

  u8g2.setCursor(42, 6);
  u8g2.print("SEMIFINAL");

  u8g2.setCursor(1, 18);
  u8g2.print(jogo61_times);
  u8g2.setCursor(1, 27);
  u8g2.print(jogo62_times);

  u8g2.setCursor(45, 18);
  u8g2.print(jogo61_home);
  u8g2.print("x");
  u8g2.print(jogo61_away);
  u8g2.setCursor(45, 27);
  u8g2.print(jogo62_home);
  u8g2.print("x");
  u8g2.print(jogo62_away);
  u8g2.setCursor(45, 54);

  u8g2.setCursor(72, 18);
  u8g2.print("13/12 16:00");
  u8g2.setCursor(72, 27);
  u8g2.print("14/12 16:00");

  u8g2.sendBuffer();
  delay(500);
}

void TerceiroLugar() {
  u8g2.clearBuffer();
  u8g2.setFontMode(1);
  u8g2.setFont(u8g2_font_5x7_tf);

  RelogioPequeno();

  u8g2.setCursor(29, 6);
  u8g2.print("TERCEIRO LUGAR");

  u8g2.setCursor(1, 18);
  u8g2.print(jogo63_times);

  u8g2.setCursor(45, 18);
  u8g2.print(jogo63_home);
  u8g2.print("x");
  u8g2.print(jogo63_away);

  u8g2.setCursor(72, 18);
  u8g2.print("17/12 12:00");

  u8g2.sendBuffer();
  delay(500);
}

void Final() {
  u8g2.clearBuffer();
  u8g2.setFontMode(1);
  u8g2.setFont(u8g2_font_5x7_tf);

  RelogioPequeno();

  u8g2.setCursor(52, 6);
  u8g2.print("FINAL");

  u8g2.setCursor(1, 18);
  u8g2.print(jogo64_times);

  u8g2.setCursor(45, 18);
  u8g2.print(jogo64_home);
  u8g2.print("x");
  u8g2.print(jogo64_away);

  u8g2.setCursor(72, 18);
  u8g2.print("18/12 12:00");

  u8g2.sendBuffer();
  delay(500);
}

void Data() {

  timeClient.update();
  Hora = timeClient.getHours();
  Minuto = timeClient.getMinutes();
  time_t epochTime = timeClient.getEpochTime();
  struct tm *ptm = gmtime((time_t *)&epochTime);
  Dia = ptm->tm_mday;
  Mes = ptm->tm_mon + 1;

  if (Minuto == 30) {
    setup();
  }
}

void RelogioPequeno() {

  Data();

  u8g2.setCursor(102, 6);

  if (Hora < 10) {
    u8g2.print("0");
    u8g2.print(Hora);
  } else {
    u8g2.print(Hora);
  }

  u8g2.print(":");

  if (Minuto < 10) {
    u8g2.print("0");
    u8g2.print(Minuto);
  } else {
    u8g2.print(Minuto);
  }
  delay(500);
}
void RelogioGrande() {

  Data();

  u8g2.clearBuffer();
  u8g2.setFontMode(1);
  u8g2.setFont(u8g2_font_logisoso42_tr);

  u8g2.setCursor(0, 53);

  if (Hora < 10) {
    u8g2.print("0");
    u8g2.print(Hora);
  } else {
    u8g2.print(Hora);
  }

  u8g2.print(":");

  if (Minuto < 10) {
    u8g2.print("0");
    u8g2.print(Minuto);
  } else {
    u8g2.print(Minuto);
  }

  u8g2.sendBuffer();

  delay(500);
}

void JogosAgora() {

  if (Dia == 20) {
    if (Hora == 13 && Minuto == 0) {
      u8g2.clearBuffer();
      u8g2.setFontMode(1);
      u8g2.setFont(u8g2_font_5x7_tf);

      RelogioPequeno();

      u8g2.setCursor(39, 6);
      u8g2.print("COMECOU!");
      u8g2.setCursor(1, 18);
      u8g2.print("QATxEQU");
      u8g2.setCursor(72, 18);
      u8g2.print("20/11 13:00");
      u8g2.sendBuffer();

      digitalWrite(MOTOR, HIGH);
      delay(5000);
      digitalWrite(MOTOR, LOW);
      delay(5000);
    }
  }

  if (Dia == 21) {
    if (Hora == 13 && Minuto == 0) {
      u8g2.clearBuffer();
      u8g2.setFontMode(1);
      u8g2.setFont(u8g2_font_5x7_tf);

      RelogioPequeno();

      u8g2.setCursor(1, 18);
      u8g2.print("SENxHOL");
      u8g2.setCursor(72, 18);
      u8g2.print("21/11 13:00");
      u8g2.sendBuffer();

      digitalWrite(MOTOR, HIGH);
      delay(5000);
      digitalWrite(MOTOR, LOW);
      delay(5000);
    }
    if (Hora == 10 && Minuto == 0) {
      u8g2.clearBuffer();
      u8g2.setFontMode(1);
      u8g2.setFont(u8g2_font_5x7_tf);

      RelogioPequeno();

      u8g2.setCursor(1, 27);
      u8g2.print("INGxIRA");
      u8g2.setCursor(72, 27);
      u8g2.print("21/11 10:00");
      u8g2.sendBuffer();

      digitalWrite(MOTOR, HIGH);
      delay(5000);
      digitalWrite(MOTOR, LOW);
      delay(5000);
    }
    if (Hora == 16 && Minuto == 0) {
      u8g2.clearBuffer();
      u8g2.setFontMode(1);
      u8g2.setFont(u8g2_font_5x7_tf);

      RelogioPequeno();

      u8g2.setCursor(1, 36);
      u8g2.print("EUAxGAL");
      u8g2.setCursor(72, 36);
      u8g2.print("21/11 16:00");
      u8g2.sendBuffer();

      digitalWrite(MOTOR, HIGH);
      delay(5000);
      digitalWrite(MOTOR, LOW);
      delay(5000);
    }
  }

  if (Dia == 22) {
    if (Hora == 7 && Minuto == 0) {
      u8g2.clearBuffer();
      u8g2.setFontMode(1);
      u8g2.setFont(u8g2_font_5x7_tf);

      RelogioPequeno();

      u8g2.setCursor(1, 18);
      u8g2.print("ARGxSAL");
      u8g2.setCursor(72, 18);
      u8g2.print("22/11 07:00");
      u8g2.sendBuffer();

      digitalWrite(MOTOR, HIGH);
      delay(5000);
      digitalWrite(MOTOR, LOW);
      delay(5000);
    }
    if (Hora == 13 && Minuto == 0) {
      u8g2.clearBuffer();
      u8g2.setFontMode(1);
      u8g2.setFont(u8g2_font_5x7_tf);

      RelogioPequeno();

      u8g2.setCursor(1, 27);
      u8g2.print("MEXxPOL");
      u8g2.setCursor(72, 27);
      u8g2.print("22/11 13:00");
      u8g2.sendBuffer();

      digitalWrite(MOTOR, HIGH);
      delay(5000);
      digitalWrite(MOTOR, LOW);
      delay(5000);
    }
    if (Hora == 10 && Minuto == 0) {
      u8g2.clearBuffer();
      u8g2.setFontMode(1);
      u8g2.setFont(u8g2_font_5x7_tf);

      RelogioPequeno();

      u8g2.setCursor(1, 36);
      u8g2.print("DINxTUN");
      u8g2.setCursor(72, 36);
      u8g2.print("22/11 10:00");
      u8g2.sendBuffer();

      digitalWrite(MOTOR, HIGH);
      delay(5000);
      digitalWrite(MOTOR, LOW);
      delay(5000);
    }
    if (Hora == 16 && Minuto == 0) {
      u8g2.clearBuffer();
      u8g2.setFontMode(1);
      u8g2.setFont(u8g2_font_5x7_tf);

      RelogioPequeno();

      u8g2.setCursor(1, 45);
      u8g2.print("FRAxAUS");
      u8g2.setCursor(72, 45);
      u8g2.print("22/11 16:00");
      u8g2.sendBuffer();

      digitalWrite(MOTOR, HIGH);
      delay(5000);
      digitalWrite(MOTOR, LOW);
      delay(5000);
    }
  }

  if (Dia == 23) {
    if (Hora == 10 && Minuto == 0) {
      u8g2.clearBuffer();
      u8g2.setFontMode(1);
      u8g2.setFont(u8g2_font_5x7_tf);

      RelogioPequeno();

      u8g2.setCursor(1, 18);
      u8g2.print("ALExSJAP");
      u8g2.setCursor(72, 18);
      u8g2.print("23/11 10:00");
      u8g2.sendBuffer();

      digitalWrite(MOTOR, HIGH);
      delay(5000);
      digitalWrite(MOTOR, LOW);
      delay(5000);
    }
    if (Hora == 13 && Minuto == 0) {
      u8g2.clearBuffer();
      u8g2.setFontMode(1);
      u8g2.setFont(u8g2_font_5x7_tf);

      RelogioPequeno();

      u8g2.setCursor(1, 27);
      u8g2.print("ESPxCOS");
      u8g2.setCursor(72, 27);
      u8g2.print("23/11 13:00");
      u8g2.sendBuffer();

      digitalWrite(MOTOR, HIGH);
      delay(5000);
      digitalWrite(MOTOR, LOW);
      delay(5000);
    }
    if (Hora == 7 && Minuto == 0) {
      u8g2.clearBuffer();
      u8g2.setFontMode(1);
      u8g2.setFont(u8g2_font_5x7_tf);

      RelogioPequeno();

      u8g2.setCursor(1, 36);
      u8g2.print("MARxCRO");
      u8g2.setCursor(72, 36);
      u8g2.print("23/11 07:00");
      u8g2.sendBuffer();

      digitalWrite(MOTOR, HIGH);
      delay(5000);
      digitalWrite(MOTOR, LOW);
      delay(5000);
    }
    if (Hora == 16 && Minuto == 0) {
      u8g2.clearBuffer();
      u8g2.setFontMode(1);
      u8g2.setFont(u8g2_font_5x7_tf);

      RelogioPequeno();

      u8g2.setCursor(1, 45);
      u8g2.print("BELxCAN");
      u8g2.setCursor(72, 45);
      u8g2.print("23/11 16:00");
      u8g2.sendBuffer();

      digitalWrite(MOTOR, HIGH);
      delay(5000);
      digitalWrite(MOTOR, LOW);
      delay(5000);
    }
  }

  if (Dia == 24) {
    if (Hora == 7 && Minuto == 0) {
      u8g2.clearBuffer();
      u8g2.setFontMode(1);
      u8g2.setFont(u8g2_font_5x7_tf);

      RelogioPequeno();

      u8g2.setCursor(1, 18);
      u8g2.print("SUIxCAM");
      u8g2.setCursor(72, 18);
      u8g2.print("24/11 07:00");
      u8g2.sendBuffer();

      digitalWrite(MOTOR, HIGH);
      delay(5000);
      digitalWrite(MOTOR, LOW);
      delay(5000);
    }
    if (Hora == 16 && Minuto == 0) {
      u8g2.clearBuffer();
      u8g2.setFontMode(1);
      u8g2.setFont(u8g2_font_5x7_tf);

      RelogioPequeno();

      u8g2.setCursor(1, 27);
      u8g2.print("BRAxSBR");
      u8g2.setCursor(72, 27);
      u8g2.print("24/11 16:00");
      u8g2.sendBuffer();

      digitalWrite(MOTOR, HIGH);
      delay(5000);
      digitalWrite(MOTOR, LOW);
      delay(5000);
    }
    if (Hora == 10 && Minuto == 0) {
      u8g2.clearBuffer();
      u8g2.setFontMode(1);
      u8g2.setFont(u8g2_font_5x7_tf);

      RelogioPequeno();

      u8g2.setCursor(1, 36);
      u8g2.print("URUxCDS");
      u8g2.setCursor(72, 36);
      u8g2.print("24/11 10:00");
      u8g2.sendBuffer();

      digitalWrite(MOTOR, HIGH);
      delay(5000);
      digitalWrite(MOTOR, LOW);
      delay(5000);
    }
    if (Hora == 13 && Minuto == 0) {
      u8g2.clearBuffer();
      u8g2.setFontMode(1);
      u8g2.setFont(u8g2_font_5x7_tf);

      RelogioPequeno();

      u8g2.setCursor(1, 45);
      u8g2.print("PORxGAN");
      u8g2.setCursor(72, 45);
      u8g2.print("24/11 13:00");
      u8g2.sendBuffer();

      digitalWrite(MOTOR, HIGH);
      delay(5000);
      digitalWrite(MOTOR, LOW);
      delay(5000);
    }
  }

  if (Dia == 25) {
    if (Hora == 10 && Minuto == 0) {
      u8g2.clearBuffer();
      u8g2.setFontMode(1);
      u8g2.setFont(u8g2_font_5x7_tf);

      RelogioPequeno();

      u8g2.setCursor(1, 18);
      u8g2.print("QATxSEN");
      u8g2.setCursor(72, 18);
      u8g2.print("25/11 10:00");
      u8g2.sendBuffer();

      digitalWrite(MOTOR, HIGH);
      delay(5000);
      digitalWrite(MOTOR, LOW);
      delay(5000);
    }
    if (Hora == 13 && Minuto == 0) {
      u8g2.clearBuffer();
      u8g2.setFontMode(1);
      u8g2.setFont(u8g2_font_5x7_tf);

      RelogioPequeno();

      u8g2.setCursor(1, 27);
      u8g2.print("HOLxEQU");
      u8g2.setCursor(72, 27);
      u8g2.print("25/11 13:00");
      u8g2.sendBuffer();

      digitalWrite(MOTOR, HIGH);
      delay(5000);
      digitalWrite(MOTOR, LOW);
      delay(5000);
    }
    if (Hora == 7 && Minuto == 0) {
      u8g2.clearBuffer();
      u8g2.setFontMode(1);
      u8g2.setFont(u8g2_font_5x7_tf);

      RelogioPequeno();

      u8g2.setCursor(1, 36);
      u8g2.print("GALxIRA");
      u8g2.setCursor(72, 36);
      u8g2.print("25/11 07:00");
      u8g2.sendBuffer();

      digitalWrite(MOTOR, HIGH);
      delay(5000);
      digitalWrite(MOTOR, LOW);
      delay(5000);
    }
    if (Hora == 16 && Minuto == 0) {
      u8g2.clearBuffer();
      u8g2.setFontMode(1);
      u8g2.setFont(u8g2_font_5x7_tf);

      RelogioPequeno();

      u8g2.setCursor(1, 45);
      u8g2.print("INGxEUA");
      u8g2.setCursor(72, 45);
      u8g2.print("25/11 16:00");
      u8g2.sendBuffer();

      digitalWrite(MOTOR, HIGH);
      delay(5000);
      digitalWrite(MOTOR, LOW);
      delay(5000);
    }
  }

  if (Dia == 26) {
    if (Hora == 10 && Minuto == 0) {
      u8g2.clearBuffer();
      u8g2.setFontMode(1);
      u8g2.setFont(u8g2_font_5x7_tf);

      RelogioPequeno();

      u8g2.setCursor(1, 18);
      u8g2.print("POLxSAU");
      u8g2.setCursor(72, 18);
      u8g2.print("26/11 10:00");
      u8g2.sendBuffer();

      digitalWrite(MOTOR, HIGH);
      delay(5000);
      digitalWrite(MOTOR, LOW);
      delay(5000);
    }
    if (Hora == 16 && Minuto == 0) {
      u8g2.clearBuffer();
      u8g2.setFontMode(1);
      u8g2.setFont(u8g2_font_5x7_tf);

      RelogioPequeno();

      u8g2.setCursor(1, 27);
      u8g2.print("ARGxMEX");
      u8g2.setCursor(72, 27);
      u8g2.print("26/11 16:00");
      u8g2.sendBuffer();

      digitalWrite(MOTOR, HIGH);
      delay(5000);
      digitalWrite(MOTOR, LOW);
      delay(5000);
    }
    if (Hora == 7 && Minuto == 0) {
      u8g2.clearBuffer();
      u8g2.setFontMode(1);
      u8g2.setFont(u8g2_font_5x7_tf);

      RelogioPequeno();

      u8g2.setCursor(1, 36);
      u8g2.print("TUNxAUS");
      u8g2.setCursor(72, 36);
      u8g2.print("26/11 07:00");
      u8g2.sendBuffer();

      digitalWrite(MOTOR, HIGH);
      delay(5000);
      digitalWrite(MOTOR, LOW);
      delay(5000);
    }
    if (Hora == 13 && Minuto == 0) {
      u8g2.clearBuffer();
      u8g2.setFontMode(1);
      u8g2.setFont(u8g2_font_5x7_tf);

      RelogioPequeno();

      u8g2.setCursor(1, 45);
      u8g2.print("GRAxDIN");
      u8g2.setCursor(72, 45);
      u8g2.print("26/11 13:00");
      u8g2.sendBuffer();

      digitalWrite(MOTOR, HIGH);
      delay(5000);
      digitalWrite(MOTOR, LOW);
      delay(5000);
    }
  }

  if (Dia == 27) {
    if (Hora == 7 && Minuto == 0) {
      u8g2.clearBuffer();
      u8g2.setFontMode(1);
      u8g2.setFont(u8g2_font_5x7_tf);

      RelogioPequeno();

      u8g2.setCursor(1, 18);
      u8g2.print("JAPxCOS");
      u8g2.setCursor(72, 18);
      u8g2.print("27/11 07:00");
      u8g2.sendBuffer();

      digitalWrite(MOTOR, HIGH);
      delay(5000);
      digitalWrite(MOTOR, LOW);
      delay(5000);
    }
    if (Hora == 16 && Minuto == 0) {
      u8g2.clearBuffer();
      u8g2.setFontMode(1);
      u8g2.setFont(u8g2_font_5x7_tf);

      RelogioPequeno();

      u8g2.setCursor(1, 27);
      u8g2.print("ESPxALE");
      u8g2.setCursor(72, 27);
      u8g2.print("27/11 16:00");
      u8g2.sendBuffer();

      digitalWrite(MOTOR, HIGH);
      delay(5000);
      digitalWrite(MOTOR, LOW);
      delay(5000);
    }
    if (Hora == 10 && Minuto == 0) {
      u8g2.clearBuffer();
      u8g2.setFontMode(1);
      u8g2.setFont(u8g2_font_5x7_tf);

      RelogioPequeno();

      u8g2.setCursor(1, 36);
      u8g2.print("BELxMAR");
      u8g2.setCursor(72, 36);
      u8g2.print("27/11 10:00");
      u8g2.sendBuffer();

      digitalWrite(MOTOR, HIGH);
      delay(5000);
      digitalWrite(MOTOR, LOW);
      delay(5000);
    }
    if (Hora == 13 && Minuto == 0) {
      u8g2.clearBuffer();
      u8g2.setFontMode(1);
      u8g2.setFont(u8g2_font_5x7_tf);

      RelogioPequeno();

      u8g2.setCursor(1, 45);
      u8g2.print("CROxCAN");
      u8g2.setCursor(72, 45);
      u8g2.print("27/11 13:00");
      u8g2.sendBuffer();

      digitalWrite(MOTOR, HIGH);
      delay(5000);
      digitalWrite(MOTOR, LOW);
      delay(5000);
    }
  }

  if (Dia == 28) {
    if (Hora == 7 && Minuto == 0) {
      u8g2.clearBuffer();
      u8g2.setFontMode(1);
      u8g2.setFont(u8g2_font_5x7_tf);

      RelogioPequeno();

      u8g2.setCursor(1, 18);
      u8g2.print("CAMxSBR");
      u8g2.setCursor(72, 18);
      u8g2.print("28/11 07:00");
      u8g2.sendBuffer();

      digitalWrite(MOTOR, HIGH);
      delay(5000);
      digitalWrite(MOTOR, LOW);
      delay(5000);
    }
    if (Hora == 13 && Minuto == 0) {
      u8g2.clearBuffer();
      u8g2.setFontMode(1);
      u8g2.setFont(u8g2_font_5x7_tf);

      RelogioPequeno();

      u8g2.setCursor(1, 27);
      u8g2.print("BRAxSUI");
      u8g2.setCursor(72, 27);
      u8g2.print("28/11 13:00");
      u8g2.sendBuffer();

      digitalWrite(MOTOR, HIGH);
      delay(5000);
      digitalWrite(MOTOR, LOW);
      delay(5000);
    }
    if (Hora == 10 && Minuto == 0) {
      u8g2.clearBuffer();
      u8g2.setFontMode(1);
      u8g2.setFont(u8g2_font_5x7_tf);

      RelogioPequeno();

      u8g2.setCursor(1, 36);
      u8g2.print("CDSxGAN");
      u8g2.setCursor(72, 36);
      u8g2.print("28/11 10:00");
      u8g2.sendBuffer();

      digitalWrite(MOTOR, HIGH);
      delay(5000);
      digitalWrite(MOTOR, LOW);
      delay(5000);
    }
    if (Hora == 16 && Minuto == 0) {
      u8g2.clearBuffer();
      u8g2.setFontMode(1);
      u8g2.setFont(u8g2_font_5x7_tf);

      RelogioPequeno();

      u8g2.setCursor(1, 45);
      u8g2.print("PORxURU");
      u8g2.setCursor(72, 45);
      u8g2.print("28/11 16:00");
      u8g2.sendBuffer();

      digitalWrite(MOTOR, HIGH);
      delay(5000);
      digitalWrite(MOTOR, LOW);
      delay(5000);
    }
  }

  if (Dia == 29) {
    if (Hora == 12 && Minuto == 0) {
      u8g2.clearBuffer();
      u8g2.setFontMode(1);
      u8g2.setFont(u8g2_font_5x7_tf);

      RelogioPequeno();

      u8g2.setCursor(1, 18);
      u8g2.print("HOLxQAT");
      u8g2.setCursor(72, 18);
      u8g2.print("29/11 12:00");
      u8g2.setCursor(1, 27);
      u8g2.print("EQUxSEN");
      u8g2.setCursor(72, 27);
      u8g2.print("29/11 12:00");
      u8g2.sendBuffer();

      digitalWrite(MOTOR, HIGH);
      delay(5000);
      digitalWrite(MOTOR, LOW);
      delay(5000);
    }
    if (Hora == 16 && Minuto == 0) {
      u8g2.clearBuffer();
      u8g2.setFontMode(1);
      u8g2.setFont(u8g2_font_5x7_tf);

      RelogioPequeno();

      u8g2.setCursor(1, 36);
      u8g2.print("GALxING");
      u8g2.setCursor(72, 36);
      u8g2.print("29/11 16:00");
      u8g2.setCursor(1, 45);
      u8g2.print("IRAxEUA");
      u8g2.setCursor(72, 45);
      u8g2.print("29/11 16:00");
      u8g2.sendBuffer();

      digitalWrite(MOTOR, HIGH);
      delay(5000);
      digitalWrite(MOTOR, LOW);
      delay(5000);
    }
  }

  if (Dia == 30) {

    if (Hora == 16 && Minuto == 0) {
      u8g2.clearBuffer();
      u8g2.setFontMode(1);
      u8g2.setFont(u8g2_font_5x7_tf);

      RelogioPequeno();

      u8g2.setCursor(1, 18);
      u8g2.print("POLxARG");
      u8g2.setCursor(72, 18);
      u8g2.print("30/11 16:00");
      u8g2.setCursor(1, 27);
      u8g2.print("SAUxMEX");
      u8g2.setCursor(72, 27);
      u8g2.print("30/11 16:00");
      u8g2.sendBuffer();

      digitalWrite(MOTOR, HIGH);
      delay(5000);
      digitalWrite(MOTOR, LOW);
      delay(5000);
    }

    if (Hora == 12 && Minuto == 0) {
      u8g2.clearBuffer();
      u8g2.setFontMode(1);
      u8g2.setFont(u8g2_font_5x7_tf);

      RelogioPequeno();

      u8g2.setCursor(1, 36);
      u8g2.print("TUNxFRA");
      u8g2.setCursor(72, 36);
      u8g2.print("30/11 12:00");
      u8g2.setCursor(1, 45);
      u8g2.print("AUSxDIN");
      u8g2.setCursor(72, 45);
      u8g2.print("30/11 12:00");
      u8g2.sendBuffer();

      digitalWrite(MOTOR, HIGH);
      delay(5000);
      digitalWrite(MOTOR, LOW);
      delay(5000);
    }
  }

  if (Dia == 01) {

    if (Hora == 16 && Minuto == 0) {
      u8g2.clearBuffer();
      u8g2.setFontMode(1);
      u8g2.setFont(u8g2_font_5x7_tf);

      RelogioPequeno();

      u8g2.setCursor(1, 18);
      u8g2.print("JAPxESP");
      u8g2.setCursor(72, 18);
      u8g2.print("01/12 16:00");
      u8g2.setCursor(1, 27);
      u8g2.print("COSxALE");
      u8g2.setCursor(72, 27);
      u8g2.print("01/12 16:00");
      u8g2.sendBuffer();

      digitalWrite(MOTOR, HIGH);
      delay(5000);
      digitalWrite(MOTOR, LOW);
      delay(5000);
    }
    if (Hora == 12 && Minuto == 0) {
      u8g2.clearBuffer();
      u8g2.setFontMode(1);
      u8g2.setFont(u8g2_font_5x7_tf);

      RelogioPequeno();

      u8g2.setCursor(1, 36);
      u8g2.print("CROxBEL");
      u8g2.setCursor(72, 36);
      u8g2.print("01/12 12:00");
      u8g2.setCursor(1, 45);
      u8g2.print("CANxMAR");
      u8g2.setCursor(72, 45);
      u8g2.print("01/12 12:00");
      u8g2.sendBuffer();

      digitalWrite(MOTOR, HIGH);
      delay(5000);
      digitalWrite(MOTOR, LOW);
      delay(5000);
    }
  }

  if (Dia == 02) {
    if (Hora == 16 && Minuto == 0) {
      u8g2.clearBuffer();
      u8g2.setFontMode(1);
      u8g2.setFont(u8g2_font_5x7_tf);

      RelogioPequeno();

      u8g2.setCursor(1, 18);
      u8g2.print("CAMxBRA");
      u8g2.setCursor(72, 18);
      u8g2.print("02/12 16:00");
      u8g2.setCursor(1, 27);
      u8g2.print("SBRxSUI");
      u8g2.setCursor(72, 27);
      u8g2.print("02/12 16:00");
      u8g2.sendBuffer();

      digitalWrite(MOTOR, HIGH);
      delay(5000);
      digitalWrite(MOTOR, LOW);
      delay(5000);
    }
    if (Hora == 12 && Minuto == 0) {
      u8g2.clearBuffer();
      u8g2.setFontMode(1);
      u8g2.setFont(u8g2_font_5x7_tf);

      RelogioPequeno();

      u8g2.setCursor(1, 36);
      u8g2.print("CDSxPOR");
      u8g2.setCursor(72, 36);
      u8g2.print("02/12 12:00");
      u8g2.setCursor(1, 45);
      u8g2.print("GANxURU");
      u8g2.setCursor(72, 45);
      u8g2.print("02/12 12:00");
      u8g2.sendBuffer();

      digitalWrite(MOTOR, HIGH);
      delay(5000);
      digitalWrite(MOTOR, LOW);
      delay(5000);
    }
  }
  if (Dia == 09) {
    if (Hora == 16 && Minuto == 0) {
      alertaAgora(Dia, Hora, jogo58_times);
    }
    if (Hora == 12 && Minuto == 0) {
      alertaAgora(Dia, Hora, jogo57_times);
    }
  }
  if (Dia == 10) {
    if (Hora == 16 && Minuto == 0) {
      alertaAgora(Dia, Hora, jogo60_times);
    }
    if (Hora == 12 && Minuto == 0) {
      alertaAgora(Dia, Hora, jogo59_times);
    }
  }
  if (Dia == 13) {
    if (Hora == 16 && Minuto == 0) {
      alertaAgora(Dia, Hora, jogo61_times);
    }
  }
  if (Dia == 14) {
    if (Hora == 16 && Minuto == 0) {
      alertaAgora(Dia, Hora, jogo62_times);
    }
  }
  if (Dia == 17) {
    if (Hora == 12 && Minuto == 0) {
      alertaAgora(Dia, Hora, jogo63_times);
    }
  }
  if (Dia == 18) {
    if (Hora == 12 && Minuto == 0) {
      alertaAgora(Dia, Hora, jogo64_times);
    }
  }
}

void alertaAgora(int dia, int hora, String times){
  u8g2.clearBuffer();
      u8g2.setFontMode(1);
      u8g2.setFont(u8g2_font_5x7_tf);

      RelogioPequeno();

      u8g2.setCursor(1, 18);
      u8g2.print(times);
      u8g2.setCursor(72, 18);
      u8g2.print(dia + "/12 " + hora + ":00");
      u8g2.sendBuffer();

      digitalWrite(MOTOR, HIGH);
      delay(5000);
      digitalWrite(MOTOR, LOW);
      delay(5000);
}

void JogosHoje() {

  u8g2.clearBuffer();
  u8g2.setFontMode(1);
  u8g2.setFont(u8g2_font_5x7_tf);

  RelogioPequeno();

  u8g2.setCursor(39, 6);
  u8g2.print("JOGOS HOJE");

  if (Dia == 20) {
    u8g2.setCursor(1, 18);
    u8g2.print("QATxEQU");
    u8g2.setCursor(72, 18);
    u8g2.print("20/11 13:00");
  }

  if (Dia == 21) {
    u8g2.setCursor(1, 18);
    u8g2.print("SENxHOL");
    u8g2.setCursor(72, 18);
    u8g2.print("21/11 13:00");
    u8g2.setCursor(1, 27);
    u8g2.print("INGxIRA");
    u8g2.setCursor(72, 27);
    u8g2.print("21/11 10:00");
    u8g2.setCursor(1, 36);
    u8g2.print("EUAxGAL");
    u8g2.setCursor(72, 36);
    u8g2.print("21/11 16:00");
  }

  if (Dia == 22) {
    u8g2.setCursor(1, 18);
    u8g2.print("ARGxSAL");
    u8g2.setCursor(72, 18);
    u8g2.print("22/11 07:00");
    u8g2.setCursor(1, 27);
    u8g2.print("MEXxPOL");
    u8g2.setCursor(72, 27);
    u8g2.print("22/11 13:00");
    u8g2.setCursor(1, 36);
    u8g2.print("DINxTUN");
    u8g2.setCursor(72, 36);
    u8g2.print("22/11 10:00");
    u8g2.setCursor(1, 45);
    u8g2.print("FRAxAUS");
    u8g2.setCursor(72, 45);
    u8g2.print("22/11 16:00");
  }

  if (Dia == 23) {
    u8g2.setCursor(1, 18);
    u8g2.print("ALExSJAP");
    u8g2.setCursor(72, 18);
    u8g2.print("23/11 10:00");
    u8g2.setCursor(1, 27);
    u8g2.print("ESPxCOS");
    u8g2.setCursor(72, 27);
    u8g2.print("23/11 13:00");
    u8g2.setCursor(1, 36);
    u8g2.print("MARxCRO");
    u8g2.setCursor(72, 36);
    u8g2.print("23/11 07:00");
    u8g2.setCursor(1, 45);
    u8g2.print("BELxCAN");
    u8g2.setCursor(72, 45);
    u8g2.print("23/11 16:00");
  }

  if (Dia == 24) {
    u8g2.setCursor(1, 18);
    u8g2.print("SUIxCAM");
    u8g2.setCursor(72, 18);
    u8g2.print("24/11 07:00");
    u8g2.setCursor(1, 27);
    u8g2.print("BRAxSBR");
    u8g2.setCursor(72, 27);
    u8g2.print("24/11 16:00");
    u8g2.setCursor(1, 36);
    u8g2.print("URUxCDS");
    u8g2.setCursor(72, 36);
    u8g2.print("24/11 10:00");
    u8g2.setCursor(1, 45);
    u8g2.print("PORxGAN");
    u8g2.setCursor(72, 45);
    u8g2.print("24/11 13:00");
  }

  if (Dia == 25) {
    u8g2.setCursor(1, 18);
    u8g2.print("QATxSEN");
    u8g2.setCursor(72, 18);
    u8g2.print("25/11 10:00");
    u8g2.setCursor(1, 27);
    u8g2.print("HOLxEQU");
    u8g2.setCursor(72, 27);
    u8g2.print("25/11 13:00");
    u8g2.setCursor(1, 36);
    u8g2.print("GALxIRA");
    u8g2.setCursor(72, 36);
    u8g2.print("25/11 07:00");
    u8g2.setCursor(1, 45);
    u8g2.print("INGxEUA");
    u8g2.setCursor(72, 45);
    u8g2.print("25/11 16:00");
  }

  if (Dia == 26) {
    u8g2.setCursor(1, 18);
    u8g2.print("POLxSAU");
    u8g2.setCursor(72, 18);
    u8g2.print("26/11 10:00");
    u8g2.setCursor(1, 27);
    u8g2.print("ARGxMEX");
    u8g2.setCursor(72, 27);
    u8g2.print("26/11 16:00");
    u8g2.setCursor(1, 36);
    u8g2.print("TUNxAUS");
    u8g2.setCursor(72, 36);
    u8g2.print("26/11 07:00");
    u8g2.setCursor(1, 45);
    u8g2.print("GRAxDIN");
    u8g2.setCursor(72, 45);
    u8g2.print("26/11 13:00");
  }

  if (Dia == 27) {
    u8g2.setCursor(1, 18);
    u8g2.print("JAPxCOS");
    u8g2.setCursor(72, 18);
    u8g2.print("27/11 07:00");
    u8g2.setCursor(1, 27);
    u8g2.print("ESPxALE");
    u8g2.setCursor(72, 27);
    u8g2.print("27/11 16:00");
    u8g2.setCursor(1, 36);
    u8g2.print("BELxMAR");
    u8g2.setCursor(72, 36);
    u8g2.print("27/11 10:00");
    u8g2.setCursor(1, 45);
    u8g2.print("CROxCAN");
    u8g2.setCursor(72, 45);
    u8g2.print("27/11 13:00");
  }

  if (Dia == 28) {
    u8g2.setCursor(1, 18);
    u8g2.print("CAMxSBR");
    u8g2.setCursor(72, 18);
    u8g2.print("28/11 07:00");
    u8g2.setCursor(1, 27);
    u8g2.print("BRAxSUI");
    u8g2.setCursor(72, 27);
    u8g2.print("28/11 13:00");
    u8g2.setCursor(1, 36);
    u8g2.print("CDSxGAN");
    u8g2.setCursor(72, 36);
    u8g2.print("28/11 10:00");
    u8g2.setCursor(1, 45);
    u8g2.print("PORxURU");
    u8g2.setCursor(72, 45);
    u8g2.print("28/11 16:00");
  }

  if (Dia == 29) {
    u8g2.setCursor(1, 18);
    u8g2.print("HOLxQAT");
    u8g2.setCursor(72, 18);
    u8g2.print("29/11 12:00");
    u8g2.setCursor(1, 27);
    u8g2.print("EQUxSEN");
    u8g2.setCursor(72, 27);
    u8g2.print("29/11 12:00");
    u8g2.setCursor(1, 36);
    u8g2.print("GALxING");
    u8g2.setCursor(72, 36);
    u8g2.print("29/11 16:00");
    u8g2.setCursor(1, 45);
    u8g2.print("IRAxEUA");
    u8g2.setCursor(72, 45);
    u8g2.print("29/11 16:00");
  }

  if (Dia == 30) {
    u8g2.setCursor(1, 18);
    u8g2.print("POLxARG");
    u8g2.setCursor(72, 18);
    u8g2.print("30/11 16:00");
    u8g2.setCursor(1, 27);
    u8g2.print("SAUxMEX");
    u8g2.setCursor(72, 27);
    u8g2.print("30/11 16:00");
    u8g2.setCursor(1, 36);
    u8g2.print("TUNxFRA");
    u8g2.setCursor(72, 36);
    u8g2.print("30/11 12:00");
    u8g2.setCursor(1, 45);
    u8g2.print("AUSxDIN");
    u8g2.setCursor(72, 45);
    u8g2.print("30/11 12:00");
  }

  if (Dia == 01) {
    u8g2.setCursor(1, 18);
    u8g2.print("JAPxESP");
    u8g2.setCursor(72, 18);
    u8g2.print("01/12 16:00");
    u8g2.setCursor(1, 27);
    u8g2.print("COSxALE");
    u8g2.setCursor(72, 27);
    u8g2.print("01/12 16:00");
    u8g2.setCursor(1, 36);
    u8g2.print("CROxBEL");
    u8g2.setCursor(72, 36);
    u8g2.print("01/12 12:00");
    u8g2.setCursor(1, 45);
    u8g2.print("CANxMAR");
    u8g2.setCursor(72, 45);
    u8g2.print("01/12 12:00");
  }

  if (Dia == 02) {
    u8g2.setCursor(1, 18);
    u8g2.print("CAMxBRA");
    u8g2.setCursor(72, 18);
    u8g2.print("02/12 16:00");
    u8g2.setCursor(1, 27);
    u8g2.print("SBRxSUI");
    u8g2.setCursor(72, 27);
    u8g2.print("02/12 16:00");
    u8g2.setCursor(1, 36);
    u8g2.print("CDSxPOR");
    u8g2.setCursor(72, 36);
    u8g2.print("02/12 12:00");
    u8g2.setCursor(1, 45);
    u8g2.print("GANxURU");
    u8g2.setCursor(72, 45);
    u8g2.print("02/12 12:00");
  }

  if (Dia == 09) {
    u8g2.setCursor(1, 18);
    u8g2.print(jogo57_times);
    u8g2.setCursor(72, 18);
    u8g2.print("09/12 12:00");
    u8g2.setCursor(1, 27);
    u8g2.print(jogo58_times);
    u8g2.setCursor(72, 27);
    u8g2.print("09/12 16:00");
  }

  if (Dia == 10) {
    u8g2.setCursor(1, 18);
    u8g2.print(jogo59_times);
    u8g2.setCursor(72, 18);
    u8g2.print("10/12 12:00");
    u8g2.setCursor(1, 27);
    u8g2.print(jogo60_times);
    u8g2.setCursor(72, 27);
    u8g2.print("10/12 16:00");
  }

  if (Dia == 13) {
    u8g2.setCursor(1, 18);
    u8g2.print(jogo61_times);
    u8g2.setCursor(72, 18);
    u8g2.print("13/12 16:00");
  }
  
  if (Dia == 14) {
    u8g2.setCursor(1, 18);
    u8g2.print(jogo62_times);
    u8g2.setCursor(72, 18);
    u8g2.print("14/12 16:00");
  }

  if (Dia == 17) {
    u8g2.setCursor(1, 18);
    u8g2.print(jogo63_times);
    u8g2.setCursor(72, 18);
    u8g2.print("17/12 12:00");
  }

  if (Dia == 18) {
    u8g2.setCursor(1, 18);
    u8g2.print(jogo64_times);
    u8g2.setCursor(72, 18);
    u8g2.print("18/12 12:00");
  }

  u8g2.sendBuffer();
  delay(500);
}

String* extractResult(String payload, String (& results)[3]) {

  StaticJsonDocument<200> filterH;
  filterH["score"]["fullTime"]["home"] = true;
  filterH["homeTeam"]["tla"] = true;
  StaticJsonDocument<400> score_home;
  deserializeJson(score_home, payload, DeserializationOption::Filter(filterH));
  String tlaH = score_home["homeTeam"]["tla"];
  String home;
  serializeJsonPretty(score_home["score"]["fullTime"]["home"], home);

  StaticJsonDocument<200> filterA;
  filterA["score"]["fullTime"]["away"] = true;
  filterA["awayTeam"]["tla"] = true;
  StaticJsonDocument<400> score_away;
  deserializeJson(score_away, payload, DeserializationOption::Filter(filterA));
  String tlaA = score_away["awayTeam"]["tla"];
  String away;
  serializeJsonPretty(score_away["score"]["fullTime"]["away"], away);

  String teams = ((tlaH != "null") ? tlaH : "   ") + "x" + ((tlaA != "null") ? tlaA : "   ");
  results[0] = teams;
  results[1] = (home != "null") ? home : " ";
  results[2] = (away != "null") ? away : " ";

  return results;
}

void updateJogo1() {
  Serial.println();
  String results[3] = {"   x   ", " ", " "};

  String payload = download("http://api.football-data.org/v4/matches/391882");
  delay(5000);
  
  extractResult(payload, results);

  Serial.print(results[0]);
  jogo1_home = results[1];
  jogo1_away = results[2];
}

void updateJogo2() {

  String payload = download("http://api.football-data.org/v4/matches/391881");
  delay(5000);

  StaticJsonDocument<200> filterH;
  filterH["score"]["fullTime"]["home"] = true;
  StaticJsonDocument<400> score_home;
  deserializeJson(score_home, payload, DeserializationOption::Filter(filterH));
  serializeJsonPretty(score_home, jogo2_home);

  StaticJsonDocument<200> filterA;
  filterA["score"]["fullTime"]["away"] = true;
  StaticJsonDocument<400> score_away;
  deserializeJson(score_away, payload, DeserializationOption::Filter(filterA));
  serializeJsonPretty(score_away, jogo2_away);
}

void updateJogo3() {

  String payload = download("http://api.football-data.org/v4/matches/391883");
  delay(5000);

  StaticJsonDocument<200> filterH;
  filterH["score"]["fullTime"]["home"] = true;
  StaticJsonDocument<400> score_home;
  deserializeJson(score_home, payload, DeserializationOption::Filter(filterH));
  serializeJsonPretty(score_home, jogo3_home);

  StaticJsonDocument<200> filterA;
  filterA["score"]["fullTime"]["away"] = true;
  StaticJsonDocument<400> score_away;
  deserializeJson(score_away, payload, DeserializationOption::Filter(filterA));
  serializeJsonPretty(score_away, jogo3_away);
}

void updateJogo4() {

  String payload = download("http://api.football-data.org/v4/matches/391884");
  delay(5000);

  StaticJsonDocument<200> filterH;
  filterH["score"]["fullTime"]["home"] = true;
  StaticJsonDocument<400> score_home;
  deserializeJson(score_home, payload, DeserializationOption::Filter(filterH));
  serializeJsonPretty(score_home, jogo4_home);

  StaticJsonDocument<200> filterA;
  filterA["score"]["fullTime"]["away"] = true;
  StaticJsonDocument<400> score_away;
  deserializeJson(score_away, payload, DeserializationOption::Filter(filterA));
  serializeJsonPretty(score_away, jogo4_away);
}

void updateJogo5() {

  String payload = download("http://api.football-data.org/v4/matches/391885");
  delay(5000);

  StaticJsonDocument<200> filterH;
  filterH["score"]["fullTime"]["home"] = true;
  StaticJsonDocument<400> score_home;
  deserializeJson(score_home, payload, DeserializationOption::Filter(filterH));
  serializeJsonPretty(score_home, jogo5_home);

  StaticJsonDocument<200> filterA;
  filterA["score"]["fullTime"]["away"] = true;
  StaticJsonDocument<400> score_away;
  deserializeJson(score_away, payload, DeserializationOption::Filter(filterA));
  serializeJsonPretty(score_away, jogo5_away);
}

void updateJogo6() {

  String payload = download("http://api.football-data.org/v4/matches/391886");
  delay(5000);

  StaticJsonDocument<200> filterH;
  filterH["score"]["fullTime"]["home"] = true;
  StaticJsonDocument<400> score_home;
  deserializeJson(score_home, payload, DeserializationOption::Filter(filterH));
  serializeJsonPretty(score_home, jogo6_home);

  StaticJsonDocument<200> filterA;
  filterA["score"]["fullTime"]["away"] = true;
  StaticJsonDocument<400> score_away;
  deserializeJson(score_away, payload, DeserializationOption::Filter(filterA));
  serializeJsonPretty(score_away, jogo6_away);
}

void updateJogo7() {

  String payload = download("http://api.football-data.org/v4/matches/391887");
  delay(5000);

  StaticJsonDocument<200> filterH;
  filterH["score"]["fullTime"]["home"] = true;
  StaticJsonDocument<400> score_home;
  deserializeJson(score_home, payload, DeserializationOption::Filter(filterH));
  serializeJsonPretty(score_home, jogo7_home);

  StaticJsonDocument<200> filterA;
  filterA["score"]["fullTime"]["away"] = true;
  StaticJsonDocument<400> score_away;
  deserializeJson(score_away, payload, DeserializationOption::Filter(filterA));
  serializeJsonPretty(score_away, jogo7_away);
}

void updateJogo8() {

  String payload = download("http://api.football-data.org/v4/matches/391888");
  delay(5000);

  StaticJsonDocument<200> filterH;
  filterH["score"]["fullTime"]["home"] = true;
  StaticJsonDocument<400> score_home;
  deserializeJson(score_home, payload, DeserializationOption::Filter(filterH));
  serializeJsonPretty(score_home, jogo8_home);

  StaticJsonDocument<200> filterA;
  filterA["score"]["fullTime"]["away"] = true;
  StaticJsonDocument<400> score_away;
  deserializeJson(score_away, payload, DeserializationOption::Filter(filterA));
  serializeJsonPretty(score_away, jogo8_away);
}

void updateJogo9() {

  String payload = download("http://api.football-data.org/v4/matches/391889");
  delay(5000);

  StaticJsonDocument<200> filterH;
  filterH["score"]["fullTime"]["home"] = true;
  StaticJsonDocument<400> score_home;
  deserializeJson(score_home, payload, DeserializationOption::Filter(filterH));
  serializeJsonPretty(score_home, jogo9_home);

  StaticJsonDocument<200> filterA;
  filterA["score"]["fullTime"]["away"] = true;
  StaticJsonDocument<400> score_away;
  deserializeJson(score_away, payload, DeserializationOption::Filter(filterA));
  serializeJsonPretty(score_away, jogo9_away);
}

void updateJogo10() {

  String payload = download("http://api.football-data.org/v4/matches/391890");
  delay(5000);

  StaticJsonDocument<200> filterH;
  filterH["score"]["fullTime"]["home"] = true;
  StaticJsonDocument<400> score_home;
  deserializeJson(score_home, payload, DeserializationOption::Filter(filterH));
  serializeJsonPretty(score_home, jogo10_home);

  StaticJsonDocument<200> filterA;
  filterA["score"]["fullTime"]["away"] = true;
  StaticJsonDocument<400> score_away;
  deserializeJson(score_away, payload, DeserializationOption::Filter(filterA));
  serializeJsonPretty(score_away, jogo10_away);
}

void updateJogo11() {

  String payload = download("http://api.football-data.org/v4/matches/391891");
  delay(5000);

  StaticJsonDocument<200> filterH;
  filterH["score"]["fullTime"]["home"] = true;
  StaticJsonDocument<400> score_home;
  deserializeJson(score_home, payload, DeserializationOption::Filter(filterH));
  serializeJsonPretty(score_home, jogo11_home);

  StaticJsonDocument<200> filterA;
  filterA["score"]["fullTime"]["away"] = true;
  StaticJsonDocument<400> score_away;
  deserializeJson(score_away, payload, DeserializationOption::Filter(filterA));
  serializeJsonPretty(score_away, jogo11_away);
}

void updateJogo12() {

  String payload = download("http://api.football-data.org/v4/matches/391892");
  delay(5000);

  StaticJsonDocument<200> filterH;
  filterH["score"]["fullTime"]["home"] = true;
  StaticJsonDocument<400> score_home;
  deserializeJson(score_home, payload, DeserializationOption::Filter(filterH));
  serializeJsonPretty(score_home, jogo12_home);

  StaticJsonDocument<200> filterA;
  filterA["score"]["fullTime"]["away"] = true;
  StaticJsonDocument<400> score_away;
  deserializeJson(score_away, payload, DeserializationOption::Filter(filterA));
  serializeJsonPretty(score_away, jogo12_away);
}

void updateJogo13() {

  String payload = download("http://api.football-data.org/v4/matches/391893");
  delay(5000);

  StaticJsonDocument<200> filterH;
  filterH["score"]["fullTime"]["home"] = true;
  StaticJsonDocument<400> score_home;
  deserializeJson(score_home, payload, DeserializationOption::Filter(filterH));
  serializeJsonPretty(score_home, jogo13_home);

  StaticJsonDocument<200> filterA;
  filterA["score"]["fullTime"]["away"] = true;
  StaticJsonDocument<400> score_away;
  deserializeJson(score_away, payload, DeserializationOption::Filter(filterA));
  serializeJsonPretty(score_away, jogo13_away);
}

void updateJogo14() {

  String payload = download("http://api.football-data.org/v4/matches/391894");
  delay(5000);

  StaticJsonDocument<200> filterH;
  filterH["score"]["fullTime"]["home"] = true;
  StaticJsonDocument<400> score_home;
  deserializeJson(score_home, payload, DeserializationOption::Filter(filterH));
  serializeJsonPretty(score_home, jogo14_home);

  StaticJsonDocument<200> filterA;
  filterA["score"]["fullTime"]["away"] = true;
  StaticJsonDocument<400> score_away;
  deserializeJson(score_away, payload, DeserializationOption::Filter(filterA));
  serializeJsonPretty(score_away, jogo14_away);
}

void updateJogo15() {

  String payload = download("http://api.football-data.org/v4/matches/391895");
  delay(5000);

  StaticJsonDocument<200> filterH;
  filterH["score"]["fullTime"]["home"] = true;
  StaticJsonDocument<400> score_home;
  deserializeJson(score_home, payload, DeserializationOption::Filter(filterH));
  serializeJsonPretty(score_home, jogo15_home);

  StaticJsonDocument<200> filterA;
  filterA["score"]["fullTime"]["away"] = true;
  StaticJsonDocument<400> score_away;
  deserializeJson(score_away, payload, DeserializationOption::Filter(filterA));
  serializeJsonPretty(score_away, jogo15_away);
}

void updateJogo16() {

  String payload = download("http://api.football-data.org/v4/matches/391896");
  delay(5000);

  StaticJsonDocument<200> filterH;
  filterH["score"]["fullTime"]["home"] = true;
  StaticJsonDocument<400> score_home;
  deserializeJson(score_home, payload, DeserializationOption::Filter(filterH));
  serializeJsonPretty(score_home, jogo16_home);

  StaticJsonDocument<200> filterA;
  filterA["score"]["fullTime"]["away"] = true;
  StaticJsonDocument<400> score_away;
  deserializeJson(score_away, payload, DeserializationOption::Filter(filterA));
  serializeJsonPretty(score_away, jogo16_away);
}

void updateJogo17() {

  String payload = download("http://api.football-data.org/v4/matches/391892");
  delay(5000);

  StaticJsonDocument<200> filterH;
  filterH["score"]["fullTime"]["home"] = true;
  StaticJsonDocument<400> score_home;
  deserializeJson(score_home, payload, DeserializationOption::Filter(filterH));
  serializeJsonPretty(score_home, jogo17_home);

  StaticJsonDocument<200> filterA;
  filterA["score"]["fullTime"]["away"] = true;
  StaticJsonDocument<400> score_away;
  deserializeJson(score_away, payload, DeserializationOption::Filter(filterA));
  serializeJsonPretty(score_away, jogo17_away);
}

void updateJogo18() {

  String payload = download("http://api.football-data.org/v4/matches/391898");
  delay(5000);

  StaticJsonDocument<200> filterH;
  filterH["score"]["fullTime"]["home"] = true;
  StaticJsonDocument<400> score_home;
  deserializeJson(score_home, payload, DeserializationOption::Filter(filterH));
  serializeJsonPretty(score_home, jogo18_home);

  StaticJsonDocument<200> filterA;
  filterA["score"]["fullTime"]["away"] = true;
  StaticJsonDocument<400> score_away;
  deserializeJson(score_away, payload, DeserializationOption::Filter(filterA));
  serializeJsonPretty(score_away, jogo18_away);
}

void updateJogo19() {

  String payload = download("http://api.football-data.org/v4/matches/391899");
  delay(5000);

  StaticJsonDocument<200> filterH;
  filterH["score"]["fullTime"]["home"] = true;
  StaticJsonDocument<400> score_home;
  deserializeJson(score_home, payload, DeserializationOption::Filter(filterH));
  serializeJsonPretty(score_home, jogo19_home);

  StaticJsonDocument<200> filterA;
  filterA["score"]["fullTime"]["away"] = true;
  StaticJsonDocument<400> score_away;
  deserializeJson(score_away, payload, DeserializationOption::Filter(filterA));
  serializeJsonPretty(score_away, jogo19_away);
}

void updateJogo20() {

  String payload = download("http://api.football-data.org/v4/matches/391900");
  delay(5000);

  StaticJsonDocument<200> filterH;
  filterH["score"]["fullTime"]["home"] = true;
  StaticJsonDocument<400> score_home;
  deserializeJson(score_home, payload, DeserializationOption::Filter(filterH));
  serializeJsonPretty(score_home, jogo20_home);

  StaticJsonDocument<200> filterA;
  filterA["score"]["fullTime"]["away"] = true;
  StaticJsonDocument<400> score_away;
  deserializeJson(score_away, payload, DeserializationOption::Filter(filterA));
  serializeJsonPretty(score_away, jogo20_away);
}

void updateJogo21() {

  String payload = download("http://api.football-data.org/v4/matches/391901");
  delay(5000);

  StaticJsonDocument<200> filterH;
  filterH["score"]["fullTime"]["home"] = true;
  StaticJsonDocument<400> score_home;
  deserializeJson(score_home, payload, DeserializationOption::Filter(filterH));
  serializeJsonPretty(score_home, jogo21_home);

  StaticJsonDocument<200> filterA;
  filterA["score"]["fullTime"]["away"] = true;
  StaticJsonDocument<400> score_away;
  deserializeJson(score_away, payload, DeserializationOption::Filter(filterA));
  serializeJsonPretty(score_away, jogo21_away);
}

void updateJogo22() {

  String payload = download("http://api.football-data.org/v4/matches/391902");
  delay(5000);

  StaticJsonDocument<200> filterH;
  filterH["score"]["fullTime"]["home"] = true;
  StaticJsonDocument<400> score_home;
  deserializeJson(score_home, payload, DeserializationOption::Filter(filterH));
  serializeJsonPretty(score_home, jogo22_home);

  StaticJsonDocument<200> filterA;
  filterA["score"]["fullTime"]["away"] = true;
  StaticJsonDocument<400> score_away;
  deserializeJson(score_away, payload, DeserializationOption::Filter(filterA));
  serializeJsonPretty(score_away, jogo22_away);
}

void updateJogo23() {

  String payload = download("http://api.football-data.org/v4/matches/391903");
  delay(5000);

  StaticJsonDocument<200> filterH;
  filterH["score"]["fullTime"]["home"] = true;
  StaticJsonDocument<400> score_home;
  deserializeJson(score_home, payload, DeserializationOption::Filter(filterH));
  serializeJsonPretty(score_home, jogo23_home);

  StaticJsonDocument<200> filterA;
  filterA["score"]["fullTime"]["away"] = true;
  StaticJsonDocument<400> score_away;
  deserializeJson(score_away, payload, DeserializationOption::Filter(filterA));
  serializeJsonPretty(score_away, jogo23_away);
}

void updateJogo24() {

  String payload = download("http://api.football-data.org/v4/matches/391904");
  delay(5000);

  StaticJsonDocument<200> filterH;
  filterH["score"]["fullTime"]["home"] = true;
  StaticJsonDocument<400> score_home;
  deserializeJson(score_home, payload, DeserializationOption::Filter(filterH));
  serializeJsonPretty(score_home, jogo24_home);

  StaticJsonDocument<200> filterA;
  filterA["score"]["fullTime"]["away"] = true;
  StaticJsonDocument<400> score_away;
  deserializeJson(score_away, payload, DeserializationOption::Filter(filterA));
  serializeJsonPretty(score_away, jogo24_away);
}

void updateJogo25() {

  String payload = download("http://api.football-data.org/v4/matches/391905");
  delay(5000);

  StaticJsonDocument<200> filterH;
  filterH["score"]["fullTime"]["home"] = true;
  StaticJsonDocument<400> score_home;
  deserializeJson(score_home, payload, DeserializationOption::Filter(filterH));
  serializeJsonPretty(score_home, jogo25_home);

  StaticJsonDocument<200> filterA;
  filterA["score"]["fullTime"]["away"] = true;
  StaticJsonDocument<400> score_away;
  deserializeJson(score_away, payload, DeserializationOption::Filter(filterA));
  serializeJsonPretty(score_away, jogo25_away);
}

void updateJogo26() {

  String payload = download("http://api.football-data.org/v4/matches/391906");
  delay(5000);

  StaticJsonDocument<200> filterH;
  filterH["score"]["fullTime"]["home"] = true;
  StaticJsonDocument<400> score_home;
  deserializeJson(score_home, payload, DeserializationOption::Filter(filterH));
  serializeJsonPretty(score_home, jogo26_home);

  StaticJsonDocument<200> filterA;
  filterA["score"]["fullTime"]["away"] = true;
  StaticJsonDocument<400> score_away;
  deserializeJson(score_away, payload, DeserializationOption::Filter(filterA));
  serializeJsonPretty(score_away, jogo26_away);
}

void updateJogo27() {

  String payload = download("http://api.football-data.org/v4/matches/391907");
  delay(5000);

  StaticJsonDocument<200> filterH;
  filterH["score"]["fullTime"]["home"] = true;
  StaticJsonDocument<400> score_home;
  deserializeJson(score_home, payload, DeserializationOption::Filter(filterH));
  serializeJsonPretty(score_home, jogo27_home);

  StaticJsonDocument<200> filterA;
  filterA["score"]["fullTime"]["away"] = true;
  StaticJsonDocument<400> score_away;
  deserializeJson(score_away, payload, DeserializationOption::Filter(filterA));
  serializeJsonPretty(score_away, jogo27_away);
}

void updateJogo28() {

  String payload = download("http://api.football-data.org/v4/matches/391908");
  delay(5000);

  StaticJsonDocument<200> filterH;
  filterH["score"]["fullTime"]["home"] = true;
  StaticJsonDocument<400> score_home;
  deserializeJson(score_home, payload, DeserializationOption::Filter(filterH));
  serializeJsonPretty(score_home, jogo28_home);

  StaticJsonDocument<200> filterA;
  filterA["score"]["fullTime"]["away"] = true;
  StaticJsonDocument<400> score_away;
  deserializeJson(score_away, payload, DeserializationOption::Filter(filterA));
  serializeJsonPretty(score_away, jogo28_away);
}

void updateJogo29() {

  String payload = download("http://api.football-data.org/v4/matches/391909");
  delay(5000);

  StaticJsonDocument<200> filterH;
  filterH["score"]["fullTime"]["home"] = true;
  StaticJsonDocument<400> score_home;
  deserializeJson(score_home, payload, DeserializationOption::Filter(filterH));
  serializeJsonPretty(score_home, jogo29_home);

  StaticJsonDocument<200> filterA;
  filterA["score"]["fullTime"]["away"] = true;
  StaticJsonDocument<400> score_away;
  deserializeJson(score_away, payload, DeserializationOption::Filter(filterA));
  serializeJsonPretty(score_away, jogo29_away);
}

void updateJogo30() {

  String payload = download("http://api.football-data.org/v4/matches/391910");
  delay(5000);

  StaticJsonDocument<200> filterH;
  filterH["score"]["fullTime"]["home"] = true;
  StaticJsonDocument<400> score_home;
  deserializeJson(score_home, payload, DeserializationOption::Filter(filterH));
  serializeJsonPretty(score_home, jogo30_home);

  StaticJsonDocument<200> filterA;
  filterA["score"]["fullTime"]["away"] = true;
  StaticJsonDocument<400> score_away;
  deserializeJson(score_away, payload, DeserializationOption::Filter(filterA));
  serializeJsonPretty(score_away, jogo30_away);
}

void updateJogo31() {

  String payload = download("http://api.football-data.org/v4/matches/391911");
  delay(5000);

  StaticJsonDocument<200> filterH;
  filterH["score"]["fullTime"]["home"] = true;
  StaticJsonDocument<400> score_home;
  deserializeJson(score_home, payload, DeserializationOption::Filter(filterH));
  serializeJsonPretty(score_home, jogo31_home);

  StaticJsonDocument<200> filterA;
  filterA["score"]["fullTime"]["away"] = true;
  StaticJsonDocument<400> score_away;
  deserializeJson(score_away, payload, DeserializationOption::Filter(filterA));
  serializeJsonPretty(score_away, jogo31_away);
}

void updateJogo32() {

  String payload = download("http://api.football-data.org/v4/matches/391912");
  delay(5000);

  StaticJsonDocument<200> filterH;
  filterH["score"]["fullTime"]["home"] = true;
  StaticJsonDocument<400> score_home;
  deserializeJson(score_home, payload, DeserializationOption::Filter(filterH));
  serializeJsonPretty(score_home, jogo32_home);

  StaticJsonDocument<200> filterA;
  filterA["score"]["fullTime"]["away"] = true;
  StaticJsonDocument<400> score_away;
  deserializeJson(score_away, payload, DeserializationOption::Filter(filterA));
  serializeJsonPretty(score_away, jogo32_away);
}

void updateJogo33() {

  String payload = download("http://api.football-data.org/v4/matches/391913");
  delay(5000);

  StaticJsonDocument<200> filterH;
  filterH["score"]["fullTime"]["home"] = true;
  StaticJsonDocument<400> score_home;
  deserializeJson(score_home, payload, DeserializationOption::Filter(filterH));
  serializeJsonPretty(score_home, jogo33_home);

  StaticJsonDocument<200> filterA;
  filterA["score"]["fullTime"]["away"] = true;
  StaticJsonDocument<400> score_away;
  deserializeJson(score_away, payload, DeserializationOption::Filter(filterA));
  serializeJsonPretty(score_away, jogo33_away);
}

void updateJogo34() {

  String payload = download("http://api.football-data.org/v4/matches/391914");
  delay(5000);

  StaticJsonDocument<200> filterH;
  filterH["score"]["fullTime"]["home"] = true;
  StaticJsonDocument<400> score_home;
  deserializeJson(score_home, payload, DeserializationOption::Filter(filterH));
  serializeJsonPretty(score_home, jogo34_home);

  StaticJsonDocument<200> filterA;
  filterA["score"]["fullTime"]["away"] = true;
  StaticJsonDocument<400> score_away;
  deserializeJson(score_away, payload, DeserializationOption::Filter(filterA));
  serializeJsonPretty(score_away, jogo34_away);
}

void updateJogo35() {

  String payload = download("http://api.football-data.org/v4/matches/391915");
  delay(5000);

  StaticJsonDocument<200> filterH;
  filterH["score"]["fullTime"]["home"] = true;
  StaticJsonDocument<400> score_home;
  deserializeJson(score_home, payload, DeserializationOption::Filter(filterH));
  serializeJsonPretty(score_home, jogo35_home);

  StaticJsonDocument<200> filterA;
  filterA["score"]["fullTime"]["away"] = true;
  StaticJsonDocument<400> score_away;
  deserializeJson(score_away, payload, DeserializationOption::Filter(filterA));
  serializeJsonPretty(score_away, jogo35_away);
}

void updateJogo36() {

  String payload = download("http://api.football-data.org/v4/matches/391916");
  delay(5000);

  StaticJsonDocument<200> filterH;
  filterH["score"]["fullTime"]["home"] = true;
  StaticJsonDocument<400> score_home;
  deserializeJson(score_home, payload, DeserializationOption::Filter(filterH));
  serializeJsonPretty(score_home, jogo36_home);

  StaticJsonDocument<200> filterA;
  filterA["score"]["fullTime"]["away"] = true;
  StaticJsonDocument<400> score_away;
  deserializeJson(score_away, payload, DeserializationOption::Filter(filterA));
  serializeJsonPretty(score_away, jogo36_away);
}

void updateJogo37() {

  String payload = download("http://api.football-data.org/v4/matches/391917");
  delay(5000);

  StaticJsonDocument<200> filterH;
  filterH["score"]["fullTime"]["home"] = true;
  StaticJsonDocument<400> score_home;
  deserializeJson(score_home, payload, DeserializationOption::Filter(filterH));
  serializeJsonPretty(score_home, jogo37_home);

  StaticJsonDocument<200> filterA;
  filterA["score"]["fullTime"]["away"] = true;
  StaticJsonDocument<400> score_away;
  deserializeJson(score_away, payload, DeserializationOption::Filter(filterA));
  serializeJsonPretty(score_away, jogo37_away);
}

void updateJogo38() {

  String payload = download("http://api.football-data.org/v4/matches/391918");
  delay(5000);

  StaticJsonDocument<200> filterH;
  filterH["score"]["fullTime"]["home"] = true;
  StaticJsonDocument<400> score_home;
  deserializeJson(score_home, payload, DeserializationOption::Filter(filterH));
  serializeJsonPretty(score_home, jogo38_home);

  StaticJsonDocument<200> filterA;
  filterA["score"]["fullTime"]["away"] = true;
  StaticJsonDocument<400> score_away;
  deserializeJson(score_away, payload, DeserializationOption::Filter(filterA));
  serializeJsonPretty(score_away, jogo38_away);
}

void updateJogo39() {

  String payload = download("http://api.football-data.org/v4/matches/391919");
  delay(5000);

  StaticJsonDocument<200> filterH;
  filterH["score"]["fullTime"]["home"] = true;
  StaticJsonDocument<400> score_home;
  deserializeJson(score_home, payload, DeserializationOption::Filter(filterH));
  serializeJsonPretty(score_home, jogo39_home);

  StaticJsonDocument<200> filterA;
  filterA["score"]["fullTime"]["away"] = true;
  StaticJsonDocument<400> score_away;
  deserializeJson(score_away, payload, DeserializationOption::Filter(filterA));
  serializeJsonPretty(score_away, jogo39_away);
}

void updateJogo40() {

  String payload = download("http://api.football-data.org/v4/matches/391920");
  delay(5000);

  StaticJsonDocument<200> filterH;
  filterH["score"]["fullTime"]["home"] = true;
  StaticJsonDocument<400> score_home;
  deserializeJson(score_home, payload, DeserializationOption::Filter(filterH));
  serializeJsonPretty(score_home, jogo40_home);

  StaticJsonDocument<200> filterA;
  filterA["score"]["fullTime"]["away"] = true;
  StaticJsonDocument<400> score_away;
  deserializeJson(score_away, payload, DeserializationOption::Filter(filterA));
  serializeJsonPretty(score_away, jogo40_away);
}

void updateJogo41() {

  String payload = download("http://api.football-data.org/v4/matches/391921");
  delay(5000);

  StaticJsonDocument<200> filterH;
  filterH["score"]["fullTime"]["home"] = true;
  StaticJsonDocument<400> score_home;
  deserializeJson(score_home, payload, DeserializationOption::Filter(filterH));
  serializeJsonPretty(score_home, jogo41_home);

  StaticJsonDocument<200> filterA;
  filterA["score"]["fullTime"]["away"] = true;
  StaticJsonDocument<400> score_away;
  deserializeJson(score_away, payload, DeserializationOption::Filter(filterA));
  serializeJsonPretty(score_away, jogo41_away);
}

void updateJogo42() {

  String payload = download("http://api.football-data.org/v4/matches/391922");
  delay(5000);

  StaticJsonDocument<200> filterH;
  filterH["score"]["fullTime"]["home"] = true;
  StaticJsonDocument<400> score_home;
  deserializeJson(score_home, payload, DeserializationOption::Filter(filterH));
  serializeJsonPretty(score_home, jogo42_home);

  StaticJsonDocument<200> filterA;
  filterA["score"]["fullTime"]["away"] = true;
  StaticJsonDocument<400> score_away;
  deserializeJson(score_away, payload, DeserializationOption::Filter(filterA));
  serializeJsonPretty(score_away, jogo42_away);
}

void updateJogo43() {

  String payload = download("http://api.football-data.org/v4/matches/391923");
  delay(5000);

  StaticJsonDocument<200> filterH;
  filterH["score"]["fullTime"]["home"] = true;
  StaticJsonDocument<400> score_home;
  deserializeJson(score_home, payload, DeserializationOption::Filter(filterH));
  serializeJsonPretty(score_home, jogo43_home);

  StaticJsonDocument<200> filterA;
  filterA["score"]["fullTime"]["away"] = true;
  StaticJsonDocument<400> score_away;
  deserializeJson(score_away, payload, DeserializationOption::Filter(filterA));
  serializeJsonPretty(score_away, jogo43_away);
}

void updateJogo44() {

  String payload = download("http://api.football-data.org/v4/matches/391924");
  delay(5000);

  StaticJsonDocument<200> filterH;
  filterH["score"]["fullTime"]["home"] = true;
  StaticJsonDocument<400> score_home;
  deserializeJson(score_home, payload, DeserializationOption::Filter(filterH));
  serializeJsonPretty(score_home, jogo44_home);

  StaticJsonDocument<200> filterA;
  filterA["score"]["fullTime"]["away"] = true;
  StaticJsonDocument<400> score_away;
  deserializeJson(score_away, payload, DeserializationOption::Filter(filterA));
  serializeJsonPretty(score_away, jogo44_away);
}

void updateJogo45() {

  String payload = download("http://api.football-data.org/v4/matches/391925");
  delay(5000);

  StaticJsonDocument<200> filterH;
  filterH["score"]["fullTime"]["home"] = true;
  StaticJsonDocument<400> score_home;
  deserializeJson(score_home, payload, DeserializationOption::Filter(filterH));
  serializeJsonPretty(score_home, jogo45_home);

  StaticJsonDocument<200> filterA;
  filterA["score"]["fullTime"]["away"] = true;
  StaticJsonDocument<400> score_away;
  deserializeJson(score_away, payload, DeserializationOption::Filter(filterA));
  serializeJsonPretty(score_away, jogo45_away);
}

void updateJogo46() {

  String payload = download("http://api.football-data.org/v4/matches/391926");
  delay(5000);

  StaticJsonDocument<200> filterH;
  filterH["score"]["fullTime"]["home"] = true;
  StaticJsonDocument<400> score_home;
  deserializeJson(score_home, payload, DeserializationOption::Filter(filterH));
  serializeJsonPretty(score_home, jogo46_home);

  StaticJsonDocument<200> filterA;
  filterA["score"]["fullTime"]["away"] = true;
  StaticJsonDocument<400> score_away;
  deserializeJson(score_away, payload, DeserializationOption::Filter(filterA));
  serializeJsonPretty(score_away, jogo46_away);
}

void updateJogo47() {

  String payload = download("http://api.football-data.org/v4/matches/391927");
  delay(5000);

  StaticJsonDocument<200> filterH;
  filterH["score"]["fullTime"]["home"] = true;
  StaticJsonDocument<400> score_home;
  deserializeJson(score_home, payload, DeserializationOption::Filter(filterH));
  serializeJsonPretty(score_home, jogo47_home);

  StaticJsonDocument<200> filterA;
  filterA["score"]["fullTime"]["away"] = true;
  StaticJsonDocument<400> score_away;
  deserializeJson(score_away, payload, DeserializationOption::Filter(filterA));
  serializeJsonPretty(score_away, jogo47_away);
}

void updateJogo48() {

  String payload = download("http://api.football-data.org/v4/matches/391928");
  delay(5000);

  String results[3] = {"   x   ", " ", " "};
  extractResult(payload, results);

  Serial.println(results[0]);
  jogo48_home = results[1];
  jogo48_away = results[2];
}

void updateJogo49() {

  String payload = download("http://api.football-data.org/v4/matches/391929");
  delay(5000);

  String results[3] = {"   x   ", " ", " "};
  extractResult(payload, results);

  jogo49_times = results[0];
  jogo49_home = results[1];
  jogo49_away = results[2];
  Serial.println(jogo49_times);
}

void updateJogo50() {

  String payload = download("http://api.football-data.org/v4/matches/391930");
  delay(5000);

  String results[3] = {"   x   ", " ", " "};
  extractResult(payload, results);

  jogo50_times = results[0];
  jogo50_home = results[1];
  jogo50_away = results[2];
  Serial.println(jogo50_times);
}

void updateJogo51() {

  String payload = download("http://api.football-data.org/v4/matches/391931");
  delay(5000);

  String results[3] = {"   x   ", " ", " "};
  extractResult(payload, results);

  jogo51_times = results[0];
  jogo51_home = results[1];
  jogo51_away = results[2];
  Serial.println(jogo51_times);
}

void updateJogo52() {

  String payload = download("http://api.football-data.org/v4/matches/391932");
  delay(5000);

  String results[3] = {"   x   ", " ", " "};
  extractResult(payload, results);

  jogo52_times = results[0];
  jogo52_home = results[1];
  jogo52_away = results[2];
  Serial.println(jogo52_times);
}

void updateJogo53() {

  String payload = download("http://api.football-data.org/v4/matches/391933");
  delay(5000);

  String results[3] = {"   x   ", " ", " "};
  extractResult(payload, results);

  jogo53_times = results[0];
  jogo53_home = results[1];
  jogo53_away = results[2];
  Serial.println(jogo53_times);
}

void updateJogo54() {

  String payload = download("http://api.football-data.org/v4/matches/391934");
  delay(5000);

  String results[3] = {"   x   ", " ", " "};
  extractResult(payload, results);

  jogo54_times = results[0];
  jogo54_home = results[1];
  jogo54_away = results[2];
  Serial.println(jogo54_times);
}

void updateJogo55() {

  String payload = download("http://api.football-data.org/v4/matches/391935");
  delay(5000);

  String results[3] = {"   x   ", " ", " "};
  extractResult(payload, results);

  jogo55_times = results[0];
  jogo55_home = results[1];
  jogo55_away = results[2];
  Serial.println(jogo55_times);
}

void updateJogo56() {

  String payload = download("http://api.football-data.org/v4/matches/391936");
  delay(5000);

  String results[3] = {"   x   ", " ", " "};
  extractResult(payload, results);

  jogo56_times = results[0];
  jogo56_home = results[1];
  jogo56_away = results[2];
  Serial.println(jogo56_times);
}

void updateJogo57() {

  String payload = download("http://api.football-data.org/v4/matches/391937");
  delay(5000);

  String results[3] = {"   x   ", " ", " "};
  extractResult(payload, results);

  jogo57_times = results[0];
  jogo57_home = results[1];
  jogo57_away = results[2];
  Serial.println(jogo57_times);
}

void updateJogo58() {

  String payload = download("http://api.football-data.org/v4/matches/391938");
  delay(5000);

  String results[3] = {"   x   ", " ", " "};
  extractResult(payload, results);

  jogo58_times = results[0];
  jogo58_home = results[1];
  jogo58_away = results[2];
  Serial.println(jogo58_times);
}

void updateJogo59() {

  String payload = download("http://api.football-data.org/v4/matches/391939");
  delay(5000);

  String results[3] = {"   x   ", " ", " "};
  extractResult(payload, results);

  jogo59_times = results[0];
  jogo59_home = results[1];
  jogo59_away = results[2];
  Serial.println(jogo59_times);
}

void updateJogo60() {

  String payload = download("http://api.football-data.org/v4/matches/391940");
  delay(5000);

  String results[3] = {"   x   ", " ", " "};
  extractResult(payload, results);

  jogo60_times = results[0];
  jogo60_home = results[1];
  jogo60_away = results[2];
  Serial.println(jogo60_times);
}

void updateJogo61() {

  String payload = download("http://api.football-data.org/v4/matches/391941");
  delay(5000);

  String results[3] = {"   x   ", " ", " "};
  extractResult(payload, results);

  jogo61_times = results[0];
  jogo61_home = results[1];
  jogo61_away = results[2];
  Serial.println(jogo61_times);
}

void updateJogo62() {

  String payload = download("http://api.football-data.org/v4/matches/391942");
  delay(5000);

  String results[3] = {"   x   ", " ", " "};
  extractResult(payload, results);

  jogo62_times = results[0];
  jogo62_home = results[1];
  jogo62_away = results[2];
  Serial.println(jogo62_times);
}

void updateJogo63() {

  String payload = download("http://api.football-data.org/v4/matches/391943");
  delay(5000);

  String results[3] = {"   x   ", " ", " "};
  extractResult(payload, results);

  jogo63_times = results[0];
  jogo63_home = results[1];
  jogo63_away = results[2];
  Serial.println(jogo63_times);
}

void updateJogo64() {

  String payload = download("http://api.football-data.org/v4/matches/391944");
  delay(5000);

  String results[3] = {"   x   ", " ", " "};
  extractResult(payload, results);

  jogo64_times = results[0];
  jogo64_home = results[1];
  jogo64_away = results[2];
  Serial.println(jogo64_times);
}

void update() {

  u8g2.clearBuffer();
  u8g2.setFontMode(1);
  u8g2.setFont(u8g2_font_5x7_tf);
  u8g2.setCursor(0, 26);
  u8g2.print("Aguarde download dos jogos...");
  u8g2.setCursor(3, 38);
  u8g2.print("O processo demora 10 min");
  u8g2.sendBuffer();
  delay(500);

  Serial.print("Atualizando jogos...");

  updateJogo1();
  updateJogo2();
  updateJogo3();
  updateJogo4();
  updateJogo5();
  updateJogo6();
  updateJogo7();
  updateJogo8();
  updateJogo9();
  updateJogo10();
  Serial.print(" .");
  updateJogo11();
  updateJogo12();
  updateJogo13();
  updateJogo14();
  updateJogo15();
  updateJogo16();
  updateJogo17();
  updateJogo18();
  updateJogo19();
  updateJogo20();
  Serial.print(" .");
  updateJogo21();
  updateJogo22();
  updateJogo23();
  updateJogo24();
  updateJogo25();
  updateJogo26();
  updateJogo27();
  updateJogo28();
  updateJogo29();
  updateJogo30();
  Serial.print(" .");
  updateJogo31();
  updateJogo32();
  updateJogo33();
  updateJogo34();
  updateJogo35();
  updateJogo36();
  updateJogo37();
  updateJogo38();
  updateJogo39();
  updateJogo40();
  Serial.print(" .");
  updateJogo41();
  updateJogo42();
  updateJogo43();
  updateJogo44();
  updateJogo45();
  updateJogo46();
  updateJogo47();
  updateJogo48();
  updateJogo49();
  updateJogo50();
  Serial.print(" .");
  updateJogo51();
  updateJogo52();
  updateJogo53();
  updateJogo54();
  updateJogo55();
  updateJogo56();
  updateJogo57();
  updateJogo58();
  updateJogo59();
  updateJogo60();
  Serial.print(" .");
  updateJogo61();
  updateJogo62();
  updateJogo63();
  updateJogo64();

  u8g2.clearBuffer();
  u8g2.setFontMode(1);
  u8g2.setFont(u8g2_font_5x7_tf);
  u8g2.setCursor(46, 26);
  u8g2.print("Pronto!");
  u8g2.sendBuffer();
  delay(500);
}

String download(const char *url) {
  HTTPClient http;
  http.begin(wifiClient, url);
  http.addHeader("X-Auth-Token", API_KEY);
  int httpCode = http.GET();
  if (httpCode <= 0) {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    http.end();
    return "";
  }
  if (httpCode != HTTP_CODE_OK) {
    Serial.printf("[HTTP] HTTP Code is not OK, got code %d\n", httpCode);
    http.end();
    return "";
  }
  String payload = http.getString();
  http.end();
  return payload;
}
