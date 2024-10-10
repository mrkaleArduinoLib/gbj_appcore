/*
  NAME:
  gbj_appcore

  DESCRIPTION:
  Library provides common core methods for project centric application libraries
  and acts as their parent class.
  - Library has no virtual methods. For them, use derived library gbj_appbase.
  - Library implements basic error handling.

  LICENSE:
  This program is free software; you can redistribute it and/or modify
  it under the terms of the license GNU GPL v3
  http://www.gnu.org/licenses/gpl-3.0.html (related to original code) and MIT
  License (MIT) for added code.

  CREDENTIALS:
  Author: Libor Gabaj
  GitHub: https://github.com/mrkaleArduinoLib/gbj_appcore.git
*/
#ifndef GBJ_APPCORE_H
#define GBJ_APPCORE_H

#if defined(__AVR__)
  #include <Arduino.h>
  #include <avr/pgmspace.h>
  #include <inttypes.h>
#elif defined(ESP8266)
  #include <Arduino.h>
  #include <pgmspace.h>
extern "C"
{
  #include <user_interface.h>
}
#elif defined(ESP32)
  #include <Arduino.h>
  #include <pgmspace.h>
// extern "C"
// {
//   #include <user_interface.h>
// }
#endif

class gbj_appcore
{
public:
  enum ResultCodes : byte
  {
    SUCCESS, // It should be always the first with index 0
    ERROR_UNKNOWN, // Not recognized error
    ERROR_NOINIT, // Not initialized yet
    ERROR_NODEVICE, // No device detected
    ERROR_PINS, // Wrong pin configuration
    ERROR_ADDR, // Wrong address
    ERROR_DATA, // Wrong data
    ERROR_ACK, // Acknowledge failed
    ERROR_CONNECT, // Connection failed
    ERROR_PUBLISH, // Publishing failed
    ERROR_SUBSCRIBE, // Subscribing failed
    ERROR_AUTH, // Authorization failed
  };

  enum BootReasons : byte
  {
    BOOT_UNKNOWN, // Not detected or unknown
    BOOT_DEFAULT_RST, // Normal startup by power on
    BOOT_WDT_RST, // Hardware watch dog reset
    BOOT_EXCEPTION_RST, // Exception reset, GPIO status won’t change
    BOOT_SOFT_WDT_RST, // Software watch dog reset, GPIO status won’t change
    BOOT_INT_WDT_RST, // Interrupt watch dog reset
    BOOT_TASK_WDT_RST, // Task watch dog reset
    BOOT_SOFT_RESTART, // Software restart, system restart, GPIO status won’t
                       // change
    BOOT_DEEP_SLEEP_AWAKE, // Wake up from deep-sleep
    BOOT_EXT_SYS_RST, // External system reset (assertion of reset pin)
    BOOT_DEEPSLEEP, // After exiting deep sleep mode
    BOOT_BROWNOUT, // Brownout reset (software or hardware)
    BOOT_SDIO, // Reset over SDIO
    BOOT_WAKEUP_UNDEFINED, // Not caused by exit from deep sleep
    BOOT_WAKEUP_ALL, // Not a wakeup cause
    BOOT_WAKEUP_EXT0, // Wakeup caused by external signal using RTC_IO
    BOOT_WAKEUP_EXT1, // Wakeup caused by external signal using RTC_CNTL
    BOOT_WAKEUP_TIMER, // Wakeup caused by timer
    BOOT_WAKEUP_TOUCHPAD, // Wakeup caused by touchpad
    BOOT_WAKEUP_ULP, // Wakeup caused by ULP program
    BOOT_WAKEUP_GPIO, // Wakeup caused by GPIO (light sleep only)
    BOOT_WAKEUP_UART, // Wakeup caused by UART (light sleep only)
  };

  gbj_appcore()
  {
    reason();
    setLastResult(ResultCodes::SUCCESS);
  }

  /*
    Rounding to particular decimal places.

    DESCRIPTION:
    The method rounds provided rational number to desired decimal places.

    PARAMETERS:
    value - Number to be rounded.
      - Data type: float
      - Default value: none
      - Limited range: real numbers
    prec - Precision, i.e., number of requested decimal places for a rounded
    value.
      - Data type: byte
      - Default value: none
      - Limited range: 0 ~ 255

    RETURN: Rounded real number.
  */
  inline float roundoff(float value, byte prec)
  {
#if defined(ESP8266) || defined(ESP32)
    float pow_10 = pow10(prec);
#else
    float pow_10 = pow(10.0f, (float)prec);
#endif
    return round(value * pow_10) / pow_10;
  }

  // Setters
  inline ResultCodes setLastResult(
    ResultCodes lastResult = ResultCodes::SUCCESS)
  {
    lastResult_ = lastResult;
    result();
    return lastResult_;
  };
  inline int setLastHttpCode(int lastHttpCode = 0)
  {
    lastHttpCode_ = lastHttpCode;
    return lastHttpCode_;
  };
  inline String setLastHttpText(String lastHttpText = "")
  {
    lastHttpText_ = lastHttpText;
    return lastHttpText_;
  };

  // Getters
  inline ResultCodes getLastResult() { return lastResult_; }
  inline BootReasons getResetReason() { return reasonCode_; }
  inline int getLastHttpCode() { return lastHttpCode_; }
  inline String getLastHttpText() { return lastHttpText_; }
  inline char *getResultName() { return resultName_; }
  inline char *getResetName() { return reasonName_; }
  inline bool isSuccess() { return lastResult_ == ResultCodes::SUCCESS; }
  inline bool isSuccess(ResultCodes lastResult)
  {
    return lastResult == ResultCodes::SUCCESS;
  }
  inline bool isError() { return !isSuccess(); }
  inline bool isError(ResultCodes lastResult) { return !isSuccess(lastResult); }

private:
  ResultCodes lastResult_; // Result of a recent operation
  int lastHttpCode_;
  String lastHttpText_; // HTTP error code description
  char resultName_[20]; // Result descriptive name
  void result(); // Method for determining result name
  void reason(); // Method for determining boot reason and its name
  // Static members for sharing and saving memory across all instances of child
  // classes.
  static char reasonName_[]; // Boot reason descriptive name
  static BootReasons reasonCode_; // Boot reason code
};

#endif
