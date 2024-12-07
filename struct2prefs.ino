/* Struct2Prefs - An example for the Arduino Preferences library of how to store and read back a struct with various data types */

#include <Preferences.h>
Preferences prefs;

typedef struct pref_t { // an arbitrary struct (from my bitcoin ticker project)
  double btc;
  int8_t tz;
  String ssid, pass;
  byte ip[4], gw[4];
};

struct pref_t s;  // we'll save the data we set in struct s
struct pref_t s2; // and read it back to struct s2

void setup() {
  Serial.begin(115200);
  prefs.begin("settings");  // arbitrary namespace used to store the settings in non-volatile storage (flash)
                            // it should be unique if you want to keep data from different sketches 

  // Assign values to struct members all at once
  s = {0.12345678, -8, "your-ssid", "your-password", {192,168,1,234}, {192,168,1,1} };

  // Save the struct data to nvs
  prefs.putDouble("coins", s.btc);
  prefs.putChar("timezone", s.tz);
  prefs.putString("ssid", s.ssid); 
  prefs.putString("pass", s.pass);
  prefs.putBytes("ip", s.ip, sizeof(s.ip));
  prefs.putBytes("gw", s.gw, sizeof(s.gw));

  // Print what was saved
  Serial.printf("Data saved:  Coins = %f, TZ = %d, SSID = \"%s\", Password = \"%s\", IP = %d.%d.%d.%d, GW = %d.%d.%d.%d\n", 
    s.btc, s.tz, s.ssid, s.pass, s.ip[0],s.ip[1],s.ip[2],s.ip[3], s.gw[0],s.gw[1],s.gw[2],s.gw[3]);

  // Restore the struct data from nvs
  s2.btc  = prefs.getDouble("coins");
  s2.tz   = prefs.getChar("timezone");
  s2.ssid = prefs.getString("ssid");
  s2.pass = prefs.getString("pass");
  prefs.getBytes("ip", s2.ip, sizeof(s2.ip)); // syntax for reading multiple bytes is different
  prefs.getBytes("gw", s2.gw, sizeof(s2.gw));

  // Verify that all the values were restored properly
  Serial.printf("Data loaded: Coins = %f, TZ = %d, SSID = \"%s\", Password = \"%s\", IP = %d.%d.%d.%d, GW = %d.%d.%d.%d\n", 
    s2.btc, s2.tz, s2.ssid, s2.pass, s2.ip[0],s2.ip[1],s2.ip[2],s2.ip[3], s2.gw[0],s2.gw[1],s2.gw[2],s2.gw[3]);

  // Use this remove a single key/value
  prefs.remove(coins); 
  // or use clear() to remove everything stored as "settings", which is the
  // currently active namespace as specified with prefs.begin("settings")
  Serial.println("Settings from flash " + prefs.clear() ? "cleared" : "could not be cleared");

  prefs.end(); // not necesssary unless another namespace needs to be activated
} // end of setup()

void loop() {
  delay(100); // nothing to do here
}
