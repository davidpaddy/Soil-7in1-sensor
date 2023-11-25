#include <AltSoftSerial.h>

// RO to pin 8 & DI to pin 9 when using AltSoftSerial
#define RE 6
#define DE 7
//Inquiry frame
const byte nitro[] = {0x01, 0x03, 0x00, 0x1e, 0x00, 0x01, 0xe4, 0x0c};
const byte phos[] = {0x01, 0x03, 0x00, 0x1f, 0x00, 0x01, 0xb5, 0xcc};
const byte pota[] = {0x01, 0x03, 0x00, 0x20, 0x00, 0x01, 0x85, 0xc0};
const byte soil_moist[] = {0x01, 0x03, 0x00, 0x12, 0x00, 0x01, 0x24, 0x0f};
const byte temp[] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x04, 0x44, 0x09};
const byte ec[] = {0x01, 0x03, 0x00, 0x15, 0x00, 0x01, 0x95, 0xce};
const byte ph[]={0x01, 0x03, 0x00, 0x06, 0x00,0x01, 0x64, 0x0B};

byte values[11];
AltSoftSerial mod;

void setup() {
  Serial.begin(9600);
  mod.begin(4800);
  pinMode(RE, OUTPUT);
  pinMode(DE, OUTPUT);

  // put RS-485 into receive mode
  digitalWrite(DE, LOW);
  digitalWrite(RE, LOW);

  delay( 1000 );
}

void loop() {
  byte val1, val2, val3, val4, val5, val6;
  Serial.print("   Nitrogen: ");
  val1 = nitrogen();
  //Serial.print(" = ");
  Serial.print(val1);
  Serial.println(" mg/kg");
  delay(250);

  Serial.print("Phosphorous: ");
  val2 = phosphorous();
 // Serial.print(" = ");
  Serial.print(val2);
  Serial.println(" mg/kg");
  delay(250);

  Serial.print("  Potassium: ");
  val3 = potassium();
  //Serial.print(" = ");
  Serial.print(val3);
  Serial.print(" mg/kg");
  delay(250);

  //Serial.print("  Temp_humidity_combined reading: ");
  val5 = soiltemp();
  Serial.println();
  delay(250);

  Serial.print("  PH: ");
  val6 = soilph();
  Serial.println();
  delay(250);

  soilec();
  Serial.println();
  delay(250);
}

byte nitrogen() {
  // clear the receive buffer
  mod.flushInput();

  // switch RS-485 to transmit mode
  digitalWrite(DE, HIGH);
  digitalWrite(RE, HIGH);
  delay(1);

  // write out the message
  for (uint8_t i = 0; i < sizeof(nitro); i++ ) mod.write( nitro[i] );

  // wait for the transmission to complete
  mod.flush();
  
  // switch RS-485 to receive mode
  digitalWrite(DE, LOW);
  digitalWrite(RE, LOW);

  // crude delay to allow response bytes to be received!
  delay(100);

  // read in the received bytes
  for (byte i = 0; i < 7; i++) {
    values[i] = mod.read();
    //Serial.print(values[i], HEX);
    //Serial.print(' ');
  }
  return values[4];
}

byte phosphorous() {
  mod.flushInput();
  digitalWrite(DE, HIGH);
  digitalWrite(RE, HIGH);
  delay(1);
  for (uint8_t i = 0; i < sizeof(phos); i++ ) mod.write( phos[i] );
  mod.flush();
  digitalWrite(DE, LOW);
  digitalWrite(RE, LOW);

  delay(100);
  for (byte i = 0; i < 7; i++) {
    values[i] = mod.read();
    ////Serial.print(values[i], HEX);
   // Serial.print(' ');
  }
  return values[4];
}

byte potassium() {
  mod.flushInput();
  digitalWrite(DE, HIGH);
  digitalWrite(RE, HIGH);
  delay(1);
  for (uint8_t i = 0; i < sizeof(pota); i++ ) mod.write( pota[i] );
  mod.flush();
  digitalWrite(DE, LOW);
  digitalWrite(RE, LOW);

  delay(100);
  for (byte i = 0; i < 7; i++) {
    values[i] = mod.read();
    //Serial.print(values[i], HEX);
    //Serial.print(' ');
  }
  return values[4];
}

byte soiltemp() {
  mod.flushInput();
  digitalWrite(DE, HIGH);
  digitalWrite(RE, HIGH);
  delay(1);
  for (uint8_t i = 0; i < sizeof(temp); i++ ) mod.write( temp[i] );
  mod.flush();
  digitalWrite(DE, LOW);
  digitalWrite(RE, LOW);

  delay(100);
  for (byte i = 0; i < 9; i++) {
    values[i] = mod.read();
  }
    for(byte i=0;i<7;i++)
  { 
    ////Serial.print(values[i], HEX);
    //Serial.print(' ');
  }
  delay(200);
uint16_t humidity = values[3]; // MSB is the 3rd byte in the array
humidity = (humidity << 8) | values[4]; // Add the LSB (4th byte in the array)

// Combine the temperature bytes into a single 16-bit value
uint16_t temperature = values[5]; // MSB is the 5th byte in the array
temperature = (temperature << 8) | values[6]; // Add the LSB (6th byte in the array)

// Print the humidity and temperature in hexadecimal form
Serial.println();
Serial.print("Humidity: ");
//Serial.print("0x");
//Serial.print(humidity, HEX); // Prints the hexadecimal value directly
//Serial.print(" (");
Serial.print(humidity/10);
Serial.print("%");
 // Prints the decimal value
//Serial.println(")");
Serial.println();
//Serial.print("Temperature: ");
//Serial.print("0x");
//Serial.print(temperature, HEX); // Prints the hexadecimal value directly
//Serial.print(" (");
Serial.print("Temperature: ");
Serial.print(temperature/10); // Prints the decimal value
  return values[4];
}
byte soilec()
{
  mod.flushInput();
  digitalWrite(DE, HIGH);
  digitalWrite(RE, HIGH);
  delay(1);
  for (uint8_t i = 0; i < sizeof(ph); i++ ) mod.write( ec[i] );
  mod.flush();
  digitalWrite(DE, LOW);
  digitalWrite(RE, LOW);
  delay(100);
  for (byte i = 0; i < 7; i++) {
    values[i] = mod.read();
    //Serial.print(values[i], HEX);
    //Serial.print(' ');
  }
    uint16_t ec = values[3]; // MSB is the 3rd byte in the array
    ec = (ec << 8) | values[4]; // Add the LSB (4th byte in the array)
    Serial.print("Electrical Conductivity:");
    Serial.println(ec);
    Serial.println("EC_END"); 
}
byte soilph() {
  mod.flushInput();
  digitalWrite(DE, HIGH);
  digitalWrite(RE, HIGH);
  delay(1);
  for (uint8_t i = 0; i < sizeof(ph); i++ ) mod.write( ph[i] );
  mod.flush();
  digitalWrite(DE, LOW);
  digitalWrite(RE, LOW);

  delay(100);
  for (byte i = 0; i < 7; i++) {
    values[i] = mod.read();
    //Serial.print(values[i], HEX);
   // Serial.print(' ');
  }
  uint16_t ph = values[3]; // MSB is the 3rd byte in the array
ph = (ph << 8) | values[4]; // Add the LSB (4th byte in the array)
//Serial.print("PH:");
Serial.print(ph/10.0);
  return values[4];
}

