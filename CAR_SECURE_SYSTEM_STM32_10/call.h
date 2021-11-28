
bool MakeCall(String phone_number,byte file);
bool phone_check(String str);

void calls(String inputString)
  {
  if(inputString.indexOf("RING",0)>-1 && phone_check(inputString)) 
    {
    sendATCommand("ATA",true);    
    sendATCommand("AT+DDET=1",true); //DTFM включаем  
    inputString="";
    Voice(0);    
    }   
  if (inputString.startsWith("+DTMF:"))
      { 
      String symbol = inputString.substring(7, 8); // Выдергиваем символ с 7 позиции длиной 1 (по 8)
      Serial.println("Key: " + symbol);
      if (symbol=="1")
        {
        Serial.println("1");
        Voice(1);
        delay(3000);
        sendATCommand("ATH",true);   
        if(engine_on()) MakeCall(Temp_Phone,4); 
        else MakeCall(Temp_Phone,5);   
        return;   
        }
      if (symbol=="2")
        {
        Serial.println("2");
        Voice(2);
        delay(3000);     
        engine_off();
        sendATCommand("ATH",true); 
        return;     
        }
      if (symbol=="3")
        {
        return;     
        }
      if (symbol=="4")
        {
        return;     
        }
      if (symbol=="5")
        { 
        return;  
        }
      if (symbol=="6")
        {        
        return;   
        }
      if (symbol=="7")
        {
        return;   
        }
      if (symbol=="8")
        {
        return;  
        }
      if (symbol=="9")
        {
        return;  
        }
      return;
      } 
  }  

bool MakeCall(String phone_number,byte file)
  {
  long _timeout = millis() + 20000;
  Serial.println("Calling...");  
  SIM800.println("ATD+ " + phone_number + ";"); //  change ZZ with country code and xxxxxxxxxxx with phone number to dial
  while(waitResponse().indexOf("OK",0)==-1 && millis() < _timeout) {};
  Serial.println("HANG!");  
  Voice(file);
  delay(3000);
  sendATCommand("ATH",true); 
  }
  
bool phone_check(String str) 
  {     
   for(byte i=1;i<=PHONE_QTY;i++)
        {
        Serial.println(phone_number[i]);
        if (str.indexOf(phone_number[i],0)>-1 && phone_number[i]!="")
          {
          Temp_Phone=phone_number[i]; // для прозвона по температуре 
          return(true);
          }       
        }
  return(false);
  }    
