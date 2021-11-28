long warmup_long;

bool engine_check();

bool engine_on()
  { 
  Serial.println("ENGINE START PROCCEDURE");
  Serial.println(averagedRpm);
  //if(logic_check==1 && LOGIC_NEUTRAL==0) return(false); // логическая нейтраль включена, но не взведена   
  if(engine_check()) return(false);
  digitalWrite(RELAY1, LOW); //включаем 
  delay(2000); //
  digitalWrite(RELAY2, LOW); // включаем 
  delay(3000); // что бы бензонасос набрал давление  
  for (int i=1;i<=3;i++)//3 попытки запуска
    {    
    Serial.println("ON");
    digitalWrite(RELAY3, LOW); // стартер
    digitalWrite(RELAY1, HIGH); // зажигание
    long _timeout = millis() + ignition_time; 
    while(millis() < _timeout && sparkFireCount<=5){Serial.println(sparkFireCount);}; //ждем пока от тахометра прийдут показания или пока не пройдёт пауза     
    digitalWrite(RELAY3,HIGH); // стартер
    digitalWrite(RELAY1, LOW); // зажигание  
    if(engine_check())
      {      
      auto_ignition=1; 
      tempeture_cabin=EEPROM.read(7);  
      Serial.println("ENGINE ON");      
      if(Thermister()>=tempeture_cabin) tempeture_cabin=100;
      warmup_long=millis() + warmup_timeout*60*1000;
      if (accum_check==false) 
      return(true); // двигатель включился    
      }   
    delay(1000);
    digitalWrite(RELAY2, HIGH); // зажигание
    delay(2000);
    digitalWrite(RELAY2, LOW); // зажигание
    delay(3000);
    }
  auto_ignition=0;     
  Serial.print("CAN'T START ENGINE"); 
  digitalWrite(RELAY2, HIGH); //выключаем ACC
  delay(1000);
  digitalWrite(RELAY1, HIGH); //выключаем приборку
  delay(1000);  
  return(false);
  }

bool engine_off()
  {   
  Serial.println("ENGINE STOP PROCCEDURE");  
  digitalWrite(RELAY2, HIGH); //выключаем ACC
  delay(1000);
  digitalWrite(RELAY1, HIGH); //выключаем приборку
   // взводим логическую нейтраль, если машина работает(должна быть ещё проверка концевиков, после выключения - что все вышли, и никто ничего не переставит)
  //if(logic_check==1) LOGIC_NEUTRAL=1;
  digitalWrite(RELAY2, HIGH); //выключаем ACC
  delay(1000);
  digitalWrite(RELAY1, HIGH); //выключаем приборку
  delay(1000);
  sparkFireCount = 0;
  averagedRpm=0;
  auto_ignition=0;
  tempeture_cabin=5;
  return(true);   
  }

bool engine_check()
  {  
  averagedRpm=0;
  sparkFireCount=0;    
  long _timeout = millis() + 5000; //
  while(millis() < _timeout && sparkFireCount<=10){}; //ждем пока от тахометра прийдут показания или пока не пройдёт пауза         
  if(averagedRpm>100) return(false); // двигатель работает ничего не делаем
  else return(true);
  }
