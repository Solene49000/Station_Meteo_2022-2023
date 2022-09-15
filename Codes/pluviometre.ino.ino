int pluviometre=32 ;
int compt=0 ;
#define MEASURE 13

void setup()
{
pinMode(MEASURE, OUTPUT);
digitalWrite(MEASURE, HIGH);
Serial.begin(115200) ;
attachInterrupt(pluviometre,comptage,FALLING) ;
}
void loop()
{
Serial.println(compt) ;
delay(100) ;
}

void comptage(){
compt ++ ;
}
