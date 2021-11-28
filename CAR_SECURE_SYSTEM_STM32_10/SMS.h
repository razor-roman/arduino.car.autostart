void sms(String inputString)
  {
  if (inputString.startsWith("+CMT:")) // это смс
      {
      if(inputString.indexOf(PASSWORD,0)>-1) // пароль совпал
        { 
        String phone="+";     
        if (inputString.indexOf("PHONE",0)>-1)
          {          
          func_phone_write_eeprom(inputString);   
          }
        if (inputString.indexOf("PASS",0)>-1)  // смотрим что слово PASS 
          {              
          byte start_indx=inputString.indexOf("_",6)+1;
          String pass=inputString.substring(start_indx,start_indx+6);
          pass+='\0'; //добавляем конец строки
          Serial.println(pass);
          if (pass.length()<7 || pass.length()>7) 
            {
            Serial.println("PASS SHORT OR LONG");
            return;
            }
          writeStringToEEPROM(0,pass);
          PASSWORD=pass;
          Serial.print("PASSWORD=");
          Serial.println(PASSWORD);
          }      
        }      
      if(phone_check(inputString))
        {
        //--------------------------------------автозапуск--------------------------------------------
      if(inputString.indexOf("TURN ON",0)>-1) engine_on(); 
      //------------------------------------выключение--------------------------------------------  
      if(inputString.indexOf("TURN OFF",0)>-1) engine_off();
      //------------------------------------------------------------------------  
      if(inputString.indexOf("TIME",0)>-1) // установка времени запуска
        {
        String pos_str=getValue(inputString,'_',1);
        int pos=pos_str.toInt();
        Serial.println("TIME=");        
        Serial.println(pos);
        writeIntIntoEEPROM(7,pos);    
        }
      if(inputString.indexOf("WARMUP_TIME",0)>-1) // установка времени запуска
        {
        String pos_str=getValue(inputString,'_',2);
        int pos=pos_str.toInt();
        Serial.println("WARMUP_TIME=");        
        Serial.println(pos);
        writeIntIntoEEPROM(11,pos);    
        }
      if(inputString.indexOf("ACC_CHECK",0)>-1) // установка времени запуска
        {
        String pos_str=getValue(inputString,'_',2);
        byte pos=pos_str.toInt();
        Serial.println("ACC_CHECK=");
        Serial.println(pos);
        EEPROM.write(12,pos); // warmup
        }     
       //------------------------------------------------------------------------          
      if (inputString.indexOf("PHONE PRINT")>-1) 
        {
        for (int i=1;i<=PHONE_QTY;i++)
          {
          Serial.print("phone_number[i]=");  
          Serial.println(phone_number[i]);  
          }
        }          
        if (inputString.indexOf("EEPROM_ZERO")>-1) EEPROM_zero();
        if (inputString.indexOf("EEPROM_LIST")>-1) EEPROM_list();        
        if (inputString.indexOf("TEMP")>-1) 
          {
          String pos_str=getValue(inputString,'_',1);
          int pos=pos_str.toInt();
          Serial.println(pos);
          writeIntIntoEEPROM(10,pos);         
          }
        }      
      }
    }
