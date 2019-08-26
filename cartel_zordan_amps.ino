/*
Muestra mensaje en cartel led de 16x32 - HUB12
Conector del cartel:
1   OE  º   º A     2
3   GND º   º B     4
5   GND º   º       6
7   GND º   º CLK   8
9   GND º   º SCLK  10
11  GND º   º DATA  12
13  GND º   º       14
15  GND º   º       16
Pines arduino (esp8266):
OE:2 A:16 B:12 CLK:14 SCLK:0 DATA:4
Puede funcionar en cualquier arduino.
No utiliza ninguna libreria.
Se recomienda enviar el dato con SPI.
Con SPI se puede reemplazar el bucle for de 7 a 0 y bitRead.
Enzo Zordan. 
*/
u8 mensaje[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x94, 0x94, 
0xF5, 0x96, 0xF4, 0x0, 0xFB, 0x42, 0x22, 0x12, 0xFB, 
0x0, 0x0, 0x0, 0x0, 0x0, 0x50, 0x50, 0x5E, 0xD2, 0x5E, 
0x0, 0xD1, 0x52, 0x5F, 0x51, 0xDF, 0x0, 0x0, 0x0, 0x0, 
0x0, 0xF8, 0x8, 0xF8, 0x80, 0xF8, 0x0, 0x72, 0x4A, 0x4B, 
0x4A, 0x73, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
0x0, 0x0, 0x51, 0x53, 0xD5, 0x59, 0xD1};

int a,b,oe,clk,sclk,dato;
int bit;
int i;
int fila;
int x;

void setup() {
  bit = 0;
  a = 16; b = 12; oe = 2;
  clk = 14; sclk = 0; dato = 4;
  pinMode(oe,OUTPUT);
  pinMode(a,OUTPUT);
  pinMode(b,OUTPUT);
  pinMode(clk,OUTPUT);
  pinMode(sclk,OUTPUT);
  pinMode(dato,OUTPUT);

  digitalWrite(oe, LOW);
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(sclk, LOW);
  digitalWrite(clk, LOW);
}

void loop() {
  digitalWrite(oe, LOW);
  if(fila == 0){
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
  }
  if(fila == 1){
      digitalWrite(a, LOW);
      digitalWrite(b, HIGH);
  }
  if(fila == 2){
      digitalWrite(a, HIGH);
      digitalWrite(b, LOW);
  }
  if(fila == 3){
      digitalWrite(a, LOW);
      digitalWrite(b, LOW);
  }
  for(i=0;i<=60;i+=4)
  {
        for(x=7;x>=0;x--)
        {
          bit = bitRead(mensaje[fila+i],x);
          digitalWrite(dato, !bit);
          digitalWrite(clk, HIGH);
          digitalWrite(clk, LOW);
        }
  }
  digitalWrite(sclk, HIGH);
  digitalWrite(sclk, LOW);
  digitalWrite(oe, HIGH);
  delay(2);
  if(fila==3) fila=-1;
  fila++;
}
