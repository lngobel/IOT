#include <Arduino.h>

//Firebase Arduino Client Library for ESP8266 and ESP32@
#if defined(ESP32)
  #include <WiFi.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>

//Wi-fi
#define WIFI_SSID "id_wifi"
#define WIFI_PASSWORD "senha_wifi"

//Firebase
#define API_KEY "AIzaSyD5rmDQSAS91M5hT9f1wHVD21J3hMP2pz0"
#define DATABASE_URL "https://fir-iot-b8be3-default-rtdb.firebaseio.com/" //a URL deve ser bem formada https://domÃ­nio/

FirebaseData fbdo; //Define Firebase Data object
FirebaseAuth auth; //Define Firebase Auth object
FirebaseConfig config; //Define Firebase Config object


//Led azul embarcado na placa
#define LED_AZUL 2

//Inicializa o wifi
void wifiSetup(){
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
}

//inicializa e authentica no Firebase
void firebaseSetup(){
  
  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  // Assign the user sign in credentials
  auth.user.email = "teste@teste.com";
  auth.user.password = "Teste123";

  // Initialize the library with the Firebase authentication and config
  Firebase.begin(&config, &auth);

  // Optional, set AP reconnection in setup()
  Firebase.reconnectWiFi(true);
}

void setup() {
  //inicializando o terminal
  Serial.begin(9600);
  //inicializa o Wifi e o Firebase
  Serial.println();
  Serial.println("Setup Wifi e Firebase");
  wifiSetup();
  firebaseSetup();
  pinMode(LED_AZUL,OUTPUT); //seta o pino 2 do led azul para output
}

void loop() {
  delay(2000);
  if (Firebase.ready()){
    Serial.println("Conectou o Firebase");
    //Lendo um Inteiro no RTDB
    Serial.println("Estado da Casa 2");
    //Lendo com get  

    //COZINHA
    Serial.printf("Lampada da cozinha: %s\n", Firebase.RTDB.getInt(&fbdo, F("/casa2/cozinha/lampada"))
    ? String(fbdo.to<int>()).c_str() 
    : fbdo.errorReason().c_str());

    //SERVICO
    Serial.printf("Lampada da area de servico: %s\n", Firebase.RTDB.getInt(&fbdo, F("/casa2/servico/lampada"))
    ? String(fbdo.to<int>()).c_str() 
    : fbdo.errorReason().c_str());

    //DESPENSA
    Serial.printf("Lampada da despensa: %s\n", Firebase.RTDB.getInt(&fbdo, F("/casa2/despensa/lampada"))
    ? String(fbdo.to<int>()).c_str() 
    : fbdo.errorReason().c_str());

    //QUARTO1
    //LAMPADA
    Serial.printf("Lampada do quarto 1: %s\n", Firebase.RTDB.getInt(&fbdo, F("/casa2/quarto1/lampada"))
    ? String(fbdo.to<int>()).c_str() 
    : fbdo.errorReason().c_str());
    //AC
    Serial.printf("AC do quarto 1: %s\n", Firebase.RTDB.getInt(&fbdo, F("/casa2/quarto1/ac"))
    ? String(fbdo.to<int>()).c_str() 
    : fbdo.errorReason().c_str());

    //BWC1
    Serial.printf("Lampada do BWC1: %s\n", Firebase.RTDB.getInt(&fbdo, F("/casa2/bwc1/lampada"))
    ? String(fbdo.to<int>()).c_str() 
    : fbdo.errorReason().c_str());

    //CIRCULACAO
    Serial.printf("Lampada da Circulacao: %s\n", Firebase.RTDB.getInt(&fbdo, F("/casa2/circulacao/lampada"))
    ? String(fbdo.to<int>()).c_str() 
    : fbdo.errorReason().c_str());

    //QUARTO2
    //LAMPADA
    Serial.printf("Lampada do quarto 2: %s\n", Firebase.RTDB.getInt(&fbdo, F("/casa2/quarto2/lampada"))
    ? String(fbdo.to<int>()).c_str() 
    : fbdo.errorReason().c_str());
    //AC
    Serial.printf("AC do quarto 2: %s\n", Firebase.RTDB.getInt(&fbdo, F("/casa2/quarto2/ac"))
    ? String(fbdo.to<int>()).c_str() 
    : fbdo.errorReason().c_str());

    //SUITE
    //LAMPADA
    Serial.printf("Lampada da suite: %s\n", Firebase.RTDB.getInt(&fbdo, F("/casa2/suite/lampada"))
    ? String(fbdo.to<int>()).c_str() 
    : fbdo.errorReason().c_str());
    //AC
    Serial.printf("AC da suite: %s\n", Firebase.RTDB.getInt(&fbdo, F("/casa2/suite/ac"))
    ? String(fbdo.to<int>()).c_str() 
    : fbdo.errorReason().c_str());

    //BANHEIRO SUÍTE
    Serial.printf("Lampada do banheiro da suite: %s\n", Firebase.RTDB.getInt(&fbdo, F("/casa2/suite/bwc/lampada"))
    ? String(fbdo.to<int>()).c_str() 
    : fbdo.errorReason().c_str());

    //SALA
    Serial.printf("Lampada da sala: %s\n", Firebase.RTDB.getInt(&fbdo, F("/casa2/sala/lampada"))
    ? String(fbdo.to<int>()).c_str() 
    : fbdo.errorReason().c_str());

    //GARAGEM
    Serial.printf("Lampada da garagem: %s\n", Firebase.RTDB.getInt(&fbdo, F("/casa2/garagem/lampada"))
    ? String(fbdo.to<int>()).c_str() 
    : fbdo.errorReason().c_str());
  
    //Liga ou desliga o Led Azul conforme o estado lido no Firebase
    fbdo.to<int>() == 0 
      ? digitalWrite(LED_AZUL,LOW) 
      : digitalWrite(LED_AZUL,HIGH); 
}
  else{Serial.println("Não conectou o Firebase");}
}