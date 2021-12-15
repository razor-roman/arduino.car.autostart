// ПЕРЕДЕЛАТЬ ПРОВЕРИТЬ
/*
 * МАКСИМУМ 256 БАЙТ на STM32
 * 0-6 пароль
 * 7 температура салона
 * 8-9 зажигание время стартера
 * 10 логическая нейтраль bool
 * 11 время прогрева таймаут
 * 12 проверка аккумулятора bool
 * 15-165 телефоны
 */ 
 #include <EEPROM.h>
//----------------------------------------------- заместо EEPROM временно
byte auto_ignition=0;
String PASSWORD="123456";
String Temp_Phone="+79536879874";
uint16_t action_timeout=10000;
const String Phone="PHONE";
bool LOGIC_NEUTRAL=false;
bool logic_check=false;
byte tempeture_cabin=100;
int ignition_time=2000;
byte warmup_timeout=30;
bool accum_check=false;
int voltage=12;

#define PASS_LENGTH 6
#define PHONE_LENGTH 15
#define PHONE_QTY 1

String phone_number[2]={"79536879874","79536879874"}; // номер телефона

bool func_phone_read_eeprom();

  
void writeStringToEEPROM(int addrOffset,String strToWrite)
{    
  byte lengh=strToWrite.length();    
  EEPROM.write(addrOffset,lengh);
  for (int i = 0; i < lengh+1; i++)
    {
    EEPROM.write(addrOffset+i+1, strToWrite[i]);
    }
}

String readStringFromEEPROM(int addrOffset)
{
byte lengh=EEPROM.read(addrOffset);  
char data[lengh];
for (int i = 0; i < lengh+1; i++)
    {
    data[i] = EEPROM.read(addrOffset+i+1);  
    }
data[lengh+1] = '\0';    
//Serial.println(String(data));      
return String(data);
}

void writeIntIntoEEPROM(int address, int number)
{ 
  byte byte1 = number >> 8;
  byte byte2 = number & 0xFF;
  EEPROM.write(address, byte1);
  delay(50);
  EEPROM.write(address + 1, byte2);
}

int readIntFromEEPROM(int address)
{
  byte byte1 = EEPROM.read(address);
  delay(50);
  byte byte2 = EEPROM.read(address + 1);
  return (byte1 << 8) + byte2;
}


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool func_phone_write_eeprom(String inputString) //если не успешно ищем по + номер телефона и возвращаем false
  {
  byte start_indx=inputString.indexOf("+",6)+1; // номер начинается с плюса  
  String str=inputString.substring(start_indx,start_indx+15); // берем подстроку от + следующие 15 символов  
  String pos_str=getValue(inputString,'_',1);
  int pos=pos_str.toInt();
  if(pos<1 || pos>5) 
    {
    Serial.println("ONLY 1-5");
    return(false);
    }
  pos=pos*15; // позиция номера в памяти
  Serial.println(pos); 
  Serial.println(str); 
  writeStringToEEPROM(pos,str);
  Serial.println("PHONE RECORD");
  func_phone_read_eeprom(); 
  return(true);
  }
//----------------------------------------------------
bool func_phone_read_eeprom() //если не успешно ищем по + номер телефона и возвращаем false
  {  
  for(byte j=1;j<=PHONE_QTY;j++) // количество телефонных номеров считываемых из памяти
    {    
    int k = j*15;
    phone_number[j]=readStringFromEEPROM(j*15);
    Serial.print("phone=");
    Serial.println(phone_number[j]);
    }   
  }

void EEPROM_list()
  {
  //---------------------------
  /*func_phone_read_eeprom();
  PASSWORD=readStringFromEEPROM(0);
  tempeture_cabin=EEPROM.read(7);
  logic_check=EEPROM.read(10); // bool
  ignition_time=readIntFromEEPROM(8); // int
  if(ignition_time<=0) ignition_time=1000;
  warmup_timeout=EEPROM.read(11);  */
  Serial.print("ignition_time=");
  Serial.println(ignition_time);
  Serial.print("logic_check=");
  Serial.println(logic_check);
  Serial.print("tempeture_cabin=");
  Serial.println(tempeture_cabin);
  Serial.print("Thermister()=");
  Serial.println(Thermister());
  if(PASSWORD==NULL) PASSWORD="123456";
  Serial.print("PASSWORD=");
  Serial.println(PASSWORD);
  }
  
void EEPROM_zero()
  {    
  for (int i=0;i<=1024;i++) EEPROM.write(i,0); 
  }  
