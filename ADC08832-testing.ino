#define CLK 2
#define CS 3
#define DI 4
#define DO 7

#define BAUD_RATE 9600

#define CS_ADDR 0 //=0 -> CH0 is selected and =1 -> CH1 is selected.
#define CLK_CYCLE 1 //Time in milli-seconds.
#define LSB_START 12 //CLK Cycle on which msb starts (at the Falling of that CC).
#define BYTE_SIZE 8

unsigned char msbData = 0;
unsigned char lsbData = 0;

void setup() {
  pinMode(CLK, OUTPUT);
  pinMode(CS, OUTPUT);
  pinMode(DI, OUTPUT);
  pinMode(DO, INPUT);

  Serial.begin(BAUD_RATE);
}

void loop() {
  
  msbData = 0;
  lsbData = 0;
  
  CS_setAddr(1 - CS_ADDR); //CS START BIT
  DI_setRise(); //DI START BIT

  for (int cycle = 0; cycle <= 20; cycle++){
    
    cycleCLK(cycle);
    
    if (cycle == 0){ //ADDRESS MUX SELECT
      CS_setAddr(CS_ADDR);
    }
    
    if (cycle >= 4 && cycle <= 11){ //CLK 4 to 11 (MSB DATA FORM)
      msbData_addBit();
    }
  
    if (cycle == 11){ //the LSB of both forms was at CC 11.
      lsbData = msbData & 0x1;
    }
    
    if (cycle >= 12 && cycle <= 18){ //CLK 12 to 18 (LSB DATA FORM)
      int shift = BYTE_SIZE - cycle + LSB_START + 1;
      lsbData_addBit(shift);
    }
  }

  Serial.print("MSB is: ");
  printData(msbData);
  Serial.print("LSB is: ");
  printData(lsbData);
}

void msbData_addBit(){
  msbData = (msbData << 1) | digitalRead(DO);
}

void lsbData_addBit(int shift){
  lsbData = lsbData | (digitalRead(DO) << shift);
}

unsigned char getDigit(unsigned char data, int shift){
  return (data >> shift) & 0x1;
}

void printData(unsigned char data){
  char res[BYTE_SIZE + 1];
  
  for (int i = 0; i < BYTE_SIZE; i++){
    res[BYTE_SIZE - i - 1] = getDigit(data, i) + '0';
  }

  Serial.println(res);
}

void CKL_setRise() { digitalWrite(CLK, HIGH); }

void CKL_setFall() { digitalWrite(CLK, LOW); }

void cycleCLK(int cycle){
  
  CKL_setRise();
  delay(CLK_CYCLE);
  
  if (cycle % 2 == 0){
    DI_setRise();
  }
  else{
    DI_setFall();
  }
  
  CKL_setFall();
}

void CS_setAddr(int addr) { digitalWrite(CS, addr); }

void DI_setRise() { digitalWrite(DI, HIGH); }

void DI_setFall() { digitalWrite(DI, LOW); }

int DO_getValue() { digitalRead(DO); }
