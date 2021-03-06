// port of https://github.com/adafruit/Adafruit-VC0706-Serial-Camera-Library/blob/master/Adafruit_VC0706.h for MSP430
#ifndef VC0706_TRY1_H_
#define VC0706_TRY1_H_

#define VC0706_RESET  0x26
#define VC0706_GEN_VERSION 0x11
#define VC0706_SET_PORT 0x24
#define VC0706_READ_FBUF 0x32
#define VC0706_GET_FBUF_LEN 0x34
#define VC0706_FBUF_CTRL 0x36
#define VC0706_DOWNSIZE_CTRL 0x54
#define VC0706_DOWNSIZE_STATUS 0x55
#define VC0706_READ_DATA 0x30
#define VC0706_WRITE_DATA 0x31
#define VC0706_COMM_MOTION_CTRL 0x37
#define VC0706_COMM_MOTION_STATUS 0x38
#define VC0706_COMM_MOTION_DETECTED 0x39
#define VC0706_MOTION_CTRL 0x42
#define VC0706_MOTION_STATUS 0x43
#define VC0706_TVOUT_CTRL 0x44
#define VC0706_OSD_ADD_CHAR 0x45

#define VC0706_STOPCURRENTFRAME 0x0
#define VC0706_STOPNEXTFRAME 0x1
#define VC0706_RESUMEFRAME 0x3
#define VC0706_STEPFRAME 0x2

#define VC0706_640x480 0x00
#define VC0706_320x240 0x11
#define VC0706_160x120 0x22

#define VC0706_MOTIONCONTROL 0x0
#define VC0706_UARTMOTION 0x01
#define VC0706_ACTIVATEMOTION 0x01

#define VC0706_SET_ZOOM 0x52
#define VC0706_GET_ZOOM 0x53

#define CAMERABUFFSIZ 100
#define CAMERADELAY 10

#include "Energia.h"

class VC0706
{
 public:
//#if not defined (_VARIANT_ARDUINO_DUE_X_) && not defined (_VARIANT_ARDUINO_ZERO_)
//  #if ARDUINO >= 100
//    VC0706(SoftwareSerial *ser); // Constructor when using SoftwareSerial
//  #else
//    VC0706(NewSoftSerial  *ser); // Constructor when using NewSoftSerial
//  #endif
//#endif
  VC0706(HardwareSerial *ser); // Constructor when using HardwareSerial
  bool begin(uint16_t baud = 38400);
  bool reset(void);
  bool TVon(void);
  bool TVoff(void);
  bool takePicture(void);
  uint8_t *readPicture(uint8_t n);
  bool resumeVideo(void);
  uint32_t frameLength(void);
  char *getVersion(void);
  uint8_t available();
  uint8_t getDownsize(void);
  bool setDownsize(uint8_t);
  uint8_t getImageSize();
  bool setImageSize(uint8_t);
  bool getMotionDetect();
  uint8_t getMotionStatus(uint8_t);
  bool motionDetected();
  bool setMotionDetect(bool f);
  bool setMotionStatus(uint8_t x, uint8_t d1, uint8_t d2);
  bool cameraFrameBuffCtrl(uint8_t command);
  uint8_t getCompression();
  bool setCompression(uint8_t c);

  bool getPTZ(uint16_t &w, uint16_t &h, uint16_t &wz, uint16_t &hz, uint16_t &pan, uint16_t &tilt);
  bool setPTZ(uint16_t wz, uint16_t hz, uint16_t pan, uint16_t tilt);

  void OSD(uint8_t x, uint8_t y, char *s); // isnt supported by the chip :(


  char* setBaud9600();
  char* setBaud19200();
  char* setBaud38400();
  char* setBaud57600();
  char* setBaud115200();

  private:
   uint8_t  serialNum;
   uint8_t  camerabuff[CAMERABUFFSIZ+1];
   uint8_t  bufferLen;
   uint16_t frameptr;


// #if not defined (_VARIANT_ARDUINO_DUE_X_) && not defined (_VARIANT_ARDUINO_ZERO_)
//   #if ARDUINO >= 100
//     SoftwareSerial *swSerial;
//   #else
//     NewSoftSerial  *swSerial;
//   #endif
// #endif

   // ?? kludge
   HardwareSerial *swSerial;
   // ??

   HardwareSerial *hwSerial;

   void common_init(void);
   bool runCommand(uint8_t cmd, uint8_t args[], uint8_t argn, uint8_t resp, bool flushflag = true);
   void sendCommand(uint8_t cmd, uint8_t args[], uint8_t argn);
   uint8_t readResponse(uint8_t numbytes, uint8_t timeout);
   bool verifyResponse(uint8_t command);
   void printBuff(void);
 };


#endif /* VC0706_TRY1_H_ */
