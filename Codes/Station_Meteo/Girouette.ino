
void girouette() {
  
  int sensorValue = analogRead(GIROUETTE);
  String directionVent;
  if (sensorValue > 3216 && sensorValue <= 3600 )
  {
    directionVent = "Ouest";
  }
  if (sensorValue > 2869 && sensorValue <= 3216)
  {
    directionVent = "Nord Ouest";
  }
  if (sensorValue > 2646 && sensorValue <= 2869)
  {
    directionVent = "Nord Ouest Ouest";
  }
  if (sensorValue > 2417 && sensorValue <= 2646)
  {
    directionVent = "Nord";
  }
  if (sensorValue > 2121 && sensorValue <= 2417)
  {
    directionVent = "Nord Nord Ouest";
  }
  if (sensorValue > 1934 && sensorValue <= 2121)
  {
    directionVent = "Sud Ouest";
  }
  if (sensorValue > 1645 && sensorValue <= 1934)
  {
    directionVent = "Sud Ouest Ouest";
  }
  if (sensorValue > 1312 && sensorValue <= 1645)
  {
    directionVent = "Nord Est";
  }
  if (sensorValue > 1008 && sensorValue <= 1312)
  {
    directionVent = "Nord Nord Est";
  }
  if (sensorValue > 725 && sensorValue <= 1008)
  {
    directionVent = "Sud";
  }
  if (sensorValue > 543 && sensorValue <= 725)
  {
    directionVent = "Sud Sud Ouest";
  }
  if (sensorValue > 338 && sensorValue <= 543)
  {
    directionVent = "Sud Est";
  }
  if (sensorValue > 184 && sensorValue <= 338)
  {
    directionVent = "Sud Sud Est";
  }
  if (sensorValue > 111 && sensorValue <= 184)
  {
    directionVent = "Est";
  }
  if (sensorValue > 64 && sensorValue <= 111)
  {
    directionVent = "Nord Est Est";
  }
  if (sensorValue > 1 && sensorValue <= 64)
  {
    directionVent = "Sud Est Est";
  }
  Serial.print("Direction du vent : ");
  Serial.println(directionVent);
}
