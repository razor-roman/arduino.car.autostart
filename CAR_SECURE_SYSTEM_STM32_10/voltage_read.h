int inPin = PB0; 
float voltage_read() {
  // put your main code here, to run repeatedly:
int sensorValue = analogRead(inPin);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (5 / 1023.0);
  // print out the value you read:
  return(voltage);
}
