/*
 * Sketch to read the distance sensors
 * Returns a string with the following format:
 * "[IR1_value], [IR2_value], [IR3_value]"
 * 
 * Author: Martina Freiholtz
 * 
 * Sources used:
 * https://www.arduino.cc/en/Reference/Wire
 * https://www.arduino.cc/en/Tutorial/ReadAnalogVoltage
 */


#define IR1 A0 //IR pin
#define IR2 A1 //IR pin
#define IR3 A2 //IR pin

void setup() {
  Serial.begin(9600);
}

void loop() {
  String values = readSensors();
  Serial.println(values);
}

/*
 * Reads the sensors and returns a netstring, using helper functions.
 */
String readSensors(){
  int inred1 = voltageToCm(analogRead(IR1));  //Read IR sensors
  int inred2 = voltageToCm(analogRead(IR2));
  int inred3 = voltageToCm(analogRead(IR3));

  String valueString = setString(inred1, inred2, inred3); //Create string containing the sensor values as ints
  
  return valueString;
}



/*
 * Takes 3 integer values and separate them with spaces in a string
 */
String setString(int i_1, int i_2, int i_3){
  String s1 = String(i_1);
  String s2 = String(i_2);
  String s3 = String(i_3);


  String valueS = s1 + "," + s2 + "," + s3;
  return valueS;
}


/*
 * Takes the voltage respresenation read from an analog port, transforms it into
 * voltages, and calculates and returns the distance in cm
 */
int voltageToCm(int voltrep){
  //The value returned from analogRead() is a value between 0 and 1023, representing 0-5 volts
  float voltage = voltrep * (5.0 / 1023.0);
  //Convert voltage to cm by applying the formula derived from the cm-voltage scatterplot in data sheet of the sensor
  float value = 12.5 / voltage;
  //Cast the resulting float as an int
  int i = (int) value;
  //If the value is above the reliable range, return -1
  if (value > 45) return -1;
  //Otherwise, return the resulting value
  return i;
}


