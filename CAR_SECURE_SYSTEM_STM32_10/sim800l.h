
String waitResponse() {                                           // Функция ожидания ответа и возврата полученного результата
  String _resp = "";                                              // Переменная для хранения результата
  long _timeout = millis() + 10000;                               // Переменная для отслеживания таймаута (10 секунд)
  while (!SIM800.available() && millis() < _timeout)  {};         // Ждем ответа 10 секунд, если пришел ответ или наступил таймаут, то...
  if (SIM800.available()) {                                       // Если есть, что считывать...
    _resp = SIM800.readString();                                  // ... считываем и запоминаем 
  }
  else {                                                          // Если пришел таймаут, то...
    Serial.println("Timeout...");                                 // ... оповещаем об этом и...
  }
  return _resp;                                                   // ... возвращаем результат. Пусто, если проблема
}

String sendATCommand(String cmd, bool waiting) {
  String _resp = "";                                              // Переменная для хранения результата
  Serial.println(cmd);                                            // Дублируем команду в монитор порта
  SIM800.println(cmd);                                            // Отправляем команду модулю
  if (waiting) {                                                  // Если необходимо дождаться ответа...
    _resp = waitResponse();                                       // ... ждем, когда будет передан ответ
    // Если Echo Mode выключен (ATE0), то эти 3 строки можно закомментировать
    if (_resp.startsWith(cmd)) {                                  // Убираем из ответа дублирующуюся команду
      _resp = _resp.substring(_resp.indexOf("\r", cmd.length()) + 2);
    }
    Serial.println(_resp);                                        // Дублируем ответ в монитор порта
  }
  return _resp;                                                   // Возвращаем результат. Пусто, если проблема
}

void sim800_init() // ПЕРЕДЕЛАТЬ
  {
 String resp="";
 resp=sendATCommand("AT",true);
 if(resp.indexOf("OK",0)<=-1)
  {
     do
     {
     resp=sendATCommand("AT+CREG?",true);
     } while (resp.indexOf("+CREG: 0,1",0)<=-1); 
      sendATCommand("AT+CMGF=1",true); //Текстовый режим включить  
      sendATCommand("AT+CNMI=1,2,0,0,0",true);
      sendATCommand("AT+CLIP=1",true); //АОН
      sendATCommand("AT+DDET=1",true); //DTFM включаем   
      sendATCommand("AT+COLP=1",true); //ожидание статуса звонка
      //sendATCommand("AT+CSCLK=1",true); // устанавливает спящий режим
   }
  else return;  
  }
  

void Voice(int Track){
    SIM800.print("AT+CREC=4,\"C:\\User\\"), SIM800.print(Track), SIM800.println(".amr\",0,95");}
