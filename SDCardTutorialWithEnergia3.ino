// Written by Tim Gilmour, May 13, 2016
// First draft of connecting to Adafruit VC0706 JPEG video camera (porting Arduino library)
// This draft does work successfully...
// uses PetitFS, so requires a pre-created 'log.txt' file on an SD card, filled up with (more bytes than expected of) some generic character like spaces...
// this code takes a snapshot when you press the S2 pushbutton, then transfers the data to SD card "log.txt" file (in jpg format)
// open this file in a hex editor like HexEdit, remove all the extraneous spaces at the end, and resave as *.jpg file
// Based on earlier project that combines Energia code with PetitFS file system, to store temperature
// using MSP430F5529 Launchpad, and Adafruit SD card module
// connections to SD card: ground, 3V vcc, CS cs_pin or ground, "DI" to P3.0, "DO" to P3.1, "CLK" to P3.2
// MSP430F5529LP P3.4 to camera "TX", P3.3 to camera RX, and 3.3V power and ground
// https://learn.adafruit.com/ttl-serial-camera/
// https://github.com/adafruit/Adafruit-VC0706-Serial-Camera-Library

/*----------------------------------------------------------------------*/
/* Petit FatFs sample project for generic uC  (C)ChaN, 2010             */
/*----------------------------------------------------------------------*/
/*-----------------------------------------------------------------------
   Ported to Energia by calinp
   Copy the file LOG.txt from this file's location to the root of the 
   SD-Card.

   12/21/2013
   Modified by bluehash(43oh) to log temperature data from the MSP430G2553
   internal temperature sensor and log it to a file on the SD-Card
   References:
   http://forum.43oh.com/topic/3209-energia-library-petit-fatfs-sd-card-library/
 */

#include "msp430f5529.h"
#include "pffconf.h" 
#include "SPI/SPI.h"
#include "pfatfs.h"
#include "VC0706_try1.h"
#include "HardwareSerial.h"

#define cs_pin      8             // chip select pin
#define read_buffer 128             // size (in bytes) of read buffer
#define LOG_DELAY   5000          // 5000ms -> 5sec

unsigned short int bw, br;//, i;
char buffer[read_buffer];
int rc;
//DIR dir;				/* Directory object */
FILINFO fno;			/* File information object */

uint32_t ui32_ReadTemp = 0;
uint8_t StringLength = 0;
char buf[30];
uint32_t counter = 0;
uint32_t AccStringLength = 0;

VC0706 cam = VC0706(&Serial1); // MSP430F5529LP P3.4 to camera "TX", P3.3 to camera RX, and 3.3V power and ground

void setup()
{
	pinMode(PUSH2, INPUT_PULLUP);
	Serial.begin(9600);                // initialize the serial terminal
	analogReference(INTERNAL1V5);
	analogRead(TEMPSENSOR);           // first reading usually wrong
	FatFs.begin(cs_pin);              // initialize FatFS library calls
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

	// Print out the camera version information (optional)
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

	//cam.setImageSize(VC0706_160x120);
	cam.setImageSize(VC0706_640x480);
	delay(1000);
	if (! cam.takePicture())
		Serial.println("Failed to snap!");
	else
		Serial.println("Picture taken!");


	rc = FatFs.open("LOG.TXT"); // for appending...?
	if (rc) die(rc);

//	delay(100);
//	bw=0;
//	ui32_ReadTemp = ((uint32_t)analogRead(TEMPSENSOR)*27069 - 18169625) *10 >> 16;
//	sprintf( buf, "%lu Current temperature is %lu.%lu\r\n", counter, ui32_ReadTemp/10, ui32_ReadTemp%10 );
//	counter++;
//	StringLength =  strlen(buf);
//	Serial.println(buf);
//
//	rc = FatFs.lseek(  AccStringLength );
//	if (rc) die(rc);
//	AccStringLength =  AccStringLength + 512;
//	rc = FatFs.write(buf, StringLength,&bw);
//	if (rc) die(rc);
//	rc = FatFs.write(0, 0, &bw);  //Finalize write
//	if (rc) die(rc);
//	rc = FatFs.close();  //Close file
//	if (rc) die(rc);

//	// Create an image with the name IMAGExx.JPG
//	char filename[13];
//	strcpy(filename, "IMAGE00.JPG");
//	for (int i = 0; i < 100; i++) {
//		filename[5] = '0' + i/10;
//		filename[6] = '0' + i%10;
//		// create if does not exist, do not open existing, write, sync after write
//		if (! SD.exists(filename)) {
//			break;
//		}
//	}

	// Open the file for writing
	//File imgFile = SD.open(filename, FILE_WRITE);

	// Get the size of the image (frame) taken
	uint16_t jpglen = cam.frameLength();
	Serial.print("Storing ");
	Serial.print(jpglen, DEC);
	Serial.print(" byte image.");

	int32_t time = millis();
	//pinMode(8, OUTPUT);
	// Read all the data up to # bytes!
	byte wCount = 0; // For counting # of writes
	while (jpglen > 0) {
		// read 32 bytes at a time;
		uint8_t camBufferArray[32];
		uint8_t *camBuffer = camBufferArray;
		uint8_t bytesToRead = min(32, jpglen); // change 32 to 64 for a speedup but may not work with all setups!
		camBuffer = cam.readPicture(bytesToRead);
		//imgFile.write(buffer, bytesToRead);
		rc = FatFs.write(camBuffer, bytesToRead, &bw);
		if (rc) die(rc);
		if(++wCount >= 64) { // Every 2K, give a little feedback so it doesn't appear locked up
			Serial.print('.');
			wCount = 0;
		}
		//Serial.print("Read ");  Serial.print(bytesToRead, DEC); Serial.println(" bytes");
		jpglen -= bytesToRead;
	}
	//imgFile.close();
	rc = FatFs.write(0, 0, &bw);  //Finalize write
	if (rc) die(rc);
	rc = FatFs.close();  //Close file
	if (rc) die(rc);

	time = millis() - time;
	Serial.println("done!");
	Serial.print(time); Serial.println(" ms elapsed");

}

/* Stop with dying message */
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

/*-----------------------------------------------------------------------*/
/* Program Main                                                          */
/*-----------------------------------------------------------------------*/
void loop()
{


//	rc = FatFs.open("LOG.TXT");
//	if (rc) die(rc);
//
//	delay(100);
//	bw=0;
	ui32_ReadTemp = ((uint32_t)analogRead(TEMPSENSOR)*27069 - 18169625) *10 >> 16;
	sprintf( buf, "%lu Current temperature is %lu.%lu\r\n", counter, ui32_ReadTemp/10, ui32_ReadTemp%10 );
	counter++;
	StringLength =  strlen(buf);
	Serial.println(buf);

//	rc = FatFs.lseek(  AccStringLength );
//	if (rc) die(rc);
//	AccStringLength =  AccStringLength + 512;
//	rc = FatFs.write(buf, StringLength,&bw);
//	if (rc) die(rc);
//	rc = FatFs.write(0, 0, &bw);  //Finalize write
//	if (rc) die(rc);
//	rc = FatFs.close();  //Close file
//	if (rc) die(rc);


#if READ
	delay(100);
	Serial.println();
	Serial.println("Read Temp data from the log file (LOG.txt).");
	delay(100);
	rc = FatFs.open("LOG.TXT");
	if (rc) die(rc);

	delay(100);
	for (;;) {
		rc = FatFs.read(buffer, sizeof(buffer), &br);	/* Read a chunk of file */
		if (rc || !br) break;			/* Error or end of file */
		for (uint16_t i = 0; i < br; i++)		/* Type the data */
			Serial.print(buffer[i]);
		delay(100);
	}
	if (rc) die(rc);
#endif

	// Log delay
	delay(LOG_DELAY);
}

