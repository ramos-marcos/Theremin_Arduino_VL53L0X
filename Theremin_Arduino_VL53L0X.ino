#include <Wire.h>
#include <VL53L0X.h>

// Instancia dois sensores
VL53L0X sensor, sensor2;

#define SHUT_1 6
#define SHUT_2 7

float med1 = 0;
float med2 = 0;

void setup()
{
  Serial.begin(9600);
  Wire.begin();

  // Define o sensor 2 como entrada para fazer o pino SHUT_2 ficar em nível alto
  pinMode(SHUT_1, OUTPUT);
  pinMode(SHUT_2, INPUT);

  // "Desliga" o sensor 1
  digitalWrite(SHUT_1, LOW);
  delay(2);

  // Altera o endereço do sensor 2
  sensor2.setAddress(0x32);

  // Religa o sensor 1 definindo ele como entrada
  pinMode(SHUT_1, INPUT);
 
  // Inicializa sensores
  sensor.init();
  sensor2.init();
  sensor.setTimeout(500);
  sensor2.setTimeout(500);
  sensor.setMeasurementTimingBudget(30000);
}

void loop()
{
  //Realiza a medição das distâncias e retornam o valor em milímetros
  float dist1 = sensor.readRangeSingleMillimeters();
  float dist2 = sensor2.readRangeSingleMillimeters();   
  
//---------------Bloco responsável por tratar os dados do sensor 1------------------------------------------------
  if(57<=dist1 && dist2<=777)//Verifica se os valores lidos estão no intervalo desejado
  {
    med1 = 36 - (((dist1 - 57)/20));
  }else
       med1 = -1;//Atribui 0 à variável    
  if(med1<0)//Garante que valores menores que zero não sejam enviados
    {
      med1 = -1;
    }         
//---------------Bloco responsável por tratar os dados do sensor 2------------------------------------------------
  if(75<=dist2 && dist2<=275)//Verifica se os valores lidos estão no intervalo desejado
  {
    med2 = map(dist2, 75, 275, 0, 100);//Converte o intervalo medido a um novo intervalo de 0 à 100
  }else
       med2=0;//Atribui 0 à variável
 if (med2<0)//Garante que valores menores que zero não sejam enviados
    {
      med2 = 0;
    }      
//---------------Envia o valor dos sensores à porta serial--------------------------------------------------------
  Serial.print(med1);
  Serial.print("/");
  Serial.println(med2);
}
