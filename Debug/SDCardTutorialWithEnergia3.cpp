#include "Energia.h"

void setup();
void die ( int pff_err	);
void printDec(uint32_t ui);
void loop();

#line 1 "M:/_EE3123_Embedded_Systems/ccs6_workspace/JPEGcameraToSDcardUsingEnergia01/SDCardTutorialWithEnergia3.ino"



























#include "msp430f5529.h"
#include "pffconf.h" 
#include "SPI/SPI.h"
#include "pfatfs.h"
#include "VC0706_try1.h"
#include "HardwareSerial.h"

#define cs_pin      8             
#define read_buffer 128             
#define LOG_DELAY   5000          

unsigned short int bw, br;
char buffer[read_buffer];
int rc;

FILINFO fno;			

uint32_t ui32_ReadTemp = 0;
uint8_t StringLength = 0;
char buf[30];
uint32_t counter = 0;
uint32_t AccStringLength = 0;

VC0706 cam = VC0706(&Serial1); 

void setup()
{
	pinMode(PUSH2, INPUT_PULLUP);
	Serial.begin(9600);                
	analogReference(INTERNAL1V5);
	analogRead(TEMPSENSOR);           
	FatFs.begin(cs_pin);              
	Serial.print("\n\n\n MSP430 Temperature Logger \n\r");
	Serial.println("Press S2 button to start...");
	while(digitalRead(PUSH2)==1){}
	delay(100);
	while(digitalRead(PUSH2)==0){}

	Serial1.begin(38400);

	if (cam.begin())
	{
		Serial.println("Camera Found:");
	}
	else
	{
		Serial.println("No camera found?");
		return;
	}

	
	char *reply = cam.getVersion();
	if (reply == 0)
	{
		Serial.print("Failed to get version");
	}
	else
	{
		Serial.println("-----------------");
		Serial.print(reply);
		Serial.println("-----------------");
	}

	
	cam.setImageSize(VC0706_640x480);
	delay(1000);
	if (! cam.takePicture())
		Serial.println("Failed to snap!");
	else
		Serial.println("Picture taken!");


	rc = FatFs.open("LOG.TXT"); 
	if (rc) die(rc);































	
	

	
	uint16_t jpglen = cam.frameLength();
	Serial.print("Storing ");
	Serial.print(jpglen, DEC);
	Serial.print(" byte image.");

	int32_t time = millis();
	
	
	byte wCount = 0; 
	while (jpglen > 0) {
		
		uint8_t camBufferArray[32];
		uint8_t *camBuffer = camBufferArray;
		uint8_t bytesToRead = min(32, jpglen); 
		camBuffer = cam.readPicture(bytesToRead);
		
		rc = FatFs.write(camBuffer, bytesToRead, &bw);
		if (rc) die(rc);
		if(++wCount >= 64) { 
			Serial.print('.');
			wCount = 0;
		}
		
		jpglen -= bytesToRead;
	}
	
	rc = FatFs.write(0, 0, &bw);  
	if (rc) die(rc);
	rc = FatFs.close();  
	if (rc) die(rc);

	time = millis() - time;
	Serial.println("done!");
	Serial.print(time); Serial.println(" ms elapsed");

}


void die ( int pff_err	)
{
	Serial.println();
	Serial.print("Failed with rc=");
	Serial.print(pff_err,DEC);
	for (;;) ;
}

void printDec(uint32_t ui)
{
	Serial.print(ui/10, DEC);
	Serial.print(".");
	Serial.print(ui%10, DEC);
}




void loop()
{







	ui32_ReadTemp = ((uint32_t)analogRead(TEMPSENSOR)*27069 - 18169625) *10 >> 16;
	sprintf( buf, "%lu Current temperature is %lu.%lu\r\n", counter, ui32_ReadTemp/10, ui32_ReadTemp%10 );
	counter++;
	StringLength =  strlen(buf);
	Serial.println(buf);












#if READ
	delay(100);
	Serial.println();
	Serial.println("Read Temp data from the log file (LOG.txt).");
	delay(100);
	rc = FatFs.open("LOG.TXT");
	if (rc) die(rc);

	delay(100);
	for (;;) {
		rc = FatFs.read(buffer, sizeof(buffer), &br);	
		if (rc || !br) break;			
		for (uint16_t i = 0; i < br; i++)		
			Serial.print(buffer[i]);
		delay(100);
	}
	if (rc) die(rc);
#endif

	
	delay(LOG_DELAY);
}




