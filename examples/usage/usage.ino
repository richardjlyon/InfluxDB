/*
 Example usage for InfluxDB library by Richard Lyon.
 */

// InfluxDB credentials
#define USERNAME "kingswood_admin"
#define PASSWORD "Wbtc0rar"

#include "InfluxDB.h"
InfluxDB idb = InfluxDB(USERNAME, PASSWORD);

int photoresistor = A0;
int power = A5;
long int timestamp;
double analogvalue;
double single1, single2, batch1, batch2;

void setup() {
  Serial.begin(9600);
  pinMode(photoresistor,INPUT);
  pinMode(power,OUTPUT);
  digitalWrite(power,HIGH);

  // initialise InfluxDB
  idb.setDatabase("test");        // defaults to 'sensordata'
  idb.setDeviceName("elmon");     // defaults to "particle"
  idb.setDebug(true);             // defaults to false
}

void loop() {
  analogvalue = analogRead(photoresistor) * 1.0;
  // idb.add("photoresistor", analogvalue);
  // idb.add("dummy", 3.1415);
  idb.add("single1", 1.0);
  idb.add("single2", 2.0);

  timestamp = Time.now();
  idb.add("batch1", 1.0, timestamp);
  idb.add("batch2", 1.0, timestamp);

  if (idb.sendAll()) {            // call this to send points to InfluxDB
    Serial.println("InfluxDB updated");
  }
  delay(1000);
}
