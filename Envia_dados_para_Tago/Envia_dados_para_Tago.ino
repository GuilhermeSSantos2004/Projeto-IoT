/*  Library -----------------------------------------------------------*/
#include <math.h>  // math Library
#include "Arduino.h"
#include "WiFi.h"             // WiFi Library 
#include <HTTPClient.h>


HTTPClient client;


const int maxSequenceLength = 10;
char sequence[maxSequenceLength];
int sequenceIndex = 0;

char wifiSsid[] = "Nome da rede";
char wifiPass[] = "Senha";
char serverAddress[] = "https://api.tago.io/data";
char contentHeader[] = "application/json";
char tokenHeader[] = "Insirar o seu token";



int count123 = 0;  // Counter for "123"
int count456 = 0;  // Counter for "456"
int count789 = 0;  // Counter for "789"

void setup() {
  Serial.begin(115200);
  init_wifi();
}

void loop() {
  send_code();
}

void init_wifi(void) {
  Serial.println("Conectando Wifi...");
  Serial.print("SSID: ");
  Serial.println(wifiSsid);
  Serial.print("PASS: ");
  Serial.println(wifiPass);
  WiFi.begin(wifiSsid, wifiPass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi Conectado!");
  Serial.print("IP is ");
  Serial.println(WiFi.localIP());
}

void send_code(void) {
  if (Serial.available() > 0) {
    char incomingByte = Serial.read();
    
    // Check if the received character is a digit (0-9)
    if (isdigit(incomingByte)) {
      // Add the digit to the sequence if there's space
      if (sequenceIndex < maxSequenceLength - 1) {
        sequence[sequenceIndex] = incomingByte;
        sequenceIndex++;
      }
    } else if (sequenceIndex > 0) {
      // If a non-digit character is received and there are digits in the sequence, print the sequence
      sequence[sequenceIndex] = '\0'; // Null-terminate the sequence
      String sequencestr = String(sequence); // Convert char array to String
      
      // Check for specific sequences and increment counters
      if (sequencestr == "123") {
        incrementCount123();
      } else if (sequencestr == "456") {
        incrementCount456();
      } else if (sequencestr == "789") {
        incrementCount789();
      }

      // Print the received sequence and counters
      printReceivedSequence(sequencestr);

      sequenceIndex = 0;
    }
  }
}

void incrementCount123() {
  count123++;
  printCounts();
}

void incrementCount456() {
  count456++;
  printCounts();
}

void incrementCount789() {
  count789++;
  printCounts();
  
}

void printReceivedSequence(String sequencestr) {
  Serial.println("Received Sequence: " + sequencestr);
}

void printCounts() {
    
  char anyData[30];
  char postData[300];
  char anyData1[30];
  char bAny[30];
  int statusCode = 0;

  strcpy(postData, "{\n\t\"variable\": \"Plastico\",\n\t\"value\": ");
  
  dtostrf(count123, 6, 2, anyData);
  strncat(postData, anyData, 100);
  strcpy(anyData1, ",\n\t\"unit\": \"p\"\n\t}\n");
  strncat(postData, anyData1, 100);
  Serial.println(postData);
  client.begin(serverAddress);
  client.addHeader("Content-Type", contentHeader);
  client.addHeader("Device-Token", tokenHeader);
  statusCode = client.POST(postData);

  // read the status code and body of the response
  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.println("End of POST to TagoIO");
  Serial.println();


  strcpy(postData, "{\n\t\"variable\": \"Metal\",\n\t\"value\": ");
  
  dtostrf(count456, 6, 2, anyData);
  strncat(postData, anyData, 100);
  strcpy(anyData1, ",\n\t\"unit\": \"m\"\n\t}\n");
  strncat(postData, anyData1, 100);
  Serial.println(postData);
  client.begin(serverAddress);
  client.addHeader("Content-Type", contentHeader);
  client.addHeader("Device-Token", tokenHeader);
  statusCode = client.POST(postData);

  // read the status code and body of the response
  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.println("End of POST to TagoIO");
  Serial.println();

  strcpy(postData, "{\n\t\"variable\": \"Vidro\",\n\t\"value\": ");
  
  dtostrf(count789, 6, 2, anyData);
  strncat(postData, anyData, 100);
  strcpy(anyData1, ",\n\t\"unit\": \"v\"\n\t}\n");
  strncat(postData, anyData1, 100);
  Serial.println(postData);
  client.begin(serverAddress);
  client.addHeader("Content-Type", contentHeader);
  client.addHeader("Device-Token", tokenHeader);
  statusCode = client.POST(postData);

  // read the status code and body of the response
  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.println("End of POST to TagoIO");
  Serial.println();
}
