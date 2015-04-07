#include <SPI.h>
#include <DHT.h>
#include <Adafruit_CC3000.h>

Adafruit_CC3000 cc3000 = Adafruit_CC3000(10, 3, 5, SPI_CLOCK_DIVIDER); 

#define IDLE_TIMEOUT_MS  3000 

uint32_t ip;

DHT dht(2, DHT22);

void setup() {
  Serial.begin(9600); 
  Serial.println("DHTxx test!");
  
  pinMode(0, OUTPUT);
  digitalWrite(0, LOW);
  pinMode(1, OUTPUT);
  digitalWrite(1, HIGH);
  
  dht.begin();

  /* Initialise the module */
/*  Serial.println(F("\nInitializing..."));
  if (!cc3000.begin())
  {
    Serial.println(F("Couldn't begin()! Check your wiring?"));
    while(1);
  }
  
  if (!cc3000.connectToAP("metis", "19850325", WLAN_SEC_WPA2)) {
    Serial.println(F("Failed!"));
    while(1);
  }
  Serial.println(F("Connected!"));
*/}

void loop() {
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  Serial.print("Humidity: "); 
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: "); 
  Serial.print(t);
  Serial.println(" *C");
  
  delay(5000);
    
/*
  // check if returns are valid, if they are NaN (not a number) then something went wrong!
  if (isnan(t) || isnan(h)) {
    Serial.println("Failed to read from DHT");
  } else {
    Serial.print("Humidity: "); 
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Temperature: "); 
    Serial.print(t);
    Serial.println(" *C");
    
    Adafruit_CC3000_Client www = cc3000.connectTCP(ip, 80);
    if (www.connected()) {
      www.fastrprint(F("PUT "));
      www.fastrprint(WEBPAGE);
      www.fastrprint(F(" HTTP/1.1\r\n"));
      www.fastrprint(F("Host: ")); www.fastrprint(WEBSITE); www.fastrprint(F("\r\n"));
      www.fastrprint(F("X-ApiKey: ")); www.fastrprint(xivelyKey); www.fastrprint(F("\r\n"));
    
      sprintf(buf_body, "home_humi,%d\nhome_temp,%d\n", h, t);
      sprintf(buf_len, "Content-Length: %d", strlen(buf_body));
      www.fastrprint(buf_len); www.fastrprint(F("\r\n"));
      www.fastrprint(F("\r\n"));
      
      www.fastrprint(buf_body);
    } else {
      Serial.println(F("Connection failed"));    
      return;
    }
  
    Serial.println(F("-------------------------------------"));
    */
    /* Read data until either the connection is closed, or the idle timeout is reached. */ 
    /*unsigned long lastRead = millis();
    while (www.connected() && (millis() - lastRead < IDLE_TIMEOUT_MS)) {
      while (www.available()) {
        char c = www.read();
        Serial.print(c);
        lastRead = millis();
      }
    }
    www.close();
  
    delay(20000);
  }*/
}


/**************************************************************************/
/*!
    @brief  Tries to read the IP address and other connection details
*/
/**************************************************************************/
bool displayConnectionDetails(void)
{
  uint32_t ipAddress, netmask, gateway, dhcpserv, dnsserv;
  
  if(!cc3000.getIPAddress(&ipAddress, &netmask, &gateway, &dhcpserv, &dnsserv))
  {
    Serial.println(F("Unable to retrieve the IP Address!\r\n"));
    return false;
  }
  else
  {
    Serial.print(F("\nIP Addr: ")); cc3000.printIPdotsRev(ipAddress);
    Serial.print(F("\nNetmask: ")); cc3000.printIPdotsRev(netmask);
    Serial.print(F("\nGateway: ")); cc3000.printIPdotsRev(gateway);
    Serial.print(F("\nDHCPsrv: ")); cc3000.printIPdotsRev(dhcpserv);
    Serial.print(F("\nDNSserv: ")); cc3000.printIPdotsRev(dnsserv);
    Serial.println();
    return true;
  }
}
