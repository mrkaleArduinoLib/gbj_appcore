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
  #include <inttypes.h>
#elif defined(ESP8266) || defined(ESP32)
  #include <Arduino.h>
extern "C"
{
  #include "user_interface.h"
}
#elif defined(PARTICLE)
  #include <Particle.h>
#endif

class gbj_appcore
{
public:
  //------------------------------------------------------------------------------
  // Public constants
  //------------------------------------------------------------------------------
  static const String VERSION;
  static const String NA;
  enum ResultCodes : byte
  {
    SUCCESS, // It should be always the first with index 0
    ERROR_UKNOWN, // Not recognized error
    ERROR_NOINIT, // Not initialized yet
    ERROR_NODEVICE, // No device detected
    ERROR_PINS, // Wrong pin configuration
    ERROR_ADDR, // Wrong address
    ERROR_DATA, // Wrong data
    ERROR_ACK, // Acknowledge failed
    ERROR_CONNECT, // Connection failed
    ERROR_PUBLISH, // Publishing failed
    ERROR_SUBSCRIBE, // Subsribing failed
    BOOT_DEFAULT_RST, // Normal startup by power on
    BOOT_UNKNOWN, // Reset reason not detected or unknown
    BOOT_WDT_RST, // Hardware watch dog reset
    BOOT_EXCEPTION_RST, // Exception reset
    BOOT_SOFT_WDT_RST, // Software watch dog reset
    BOOT_SOFT_RESTART, // Software restart, system restart
    BOOT_DEEP_SLEEP_AWAKE, // Wake up from deep-sleep
    BOOT_EXT_SYS_RST, // External system reset (assertion of reset pin)
  };

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
    float pow_10 = pow(10.0f, (float)prec);
    return round(value * pow_10) / pow_10;
  }

  // Setters
  inline ResultCodes setLastResult(
    ResultCodes lastResult = ResultCodes::SUCCESS)
  {
    return _lastResult = lastResult;
  };

  // Getters
  /*
    Reset reason.

    DESCRIPTION:
    The method detects recent rebooting reason of the microcontroller.

    PARAMETERS: None

    RETURN: Result code
  */
  inline ResultCodes getResetReason()
  {
    setLastResult(ResultCodes::BOOT_UNKNOWN);
#if defined(ESP8266) || defined(ESP32)
    switch (ESP.getResetInfoPtr()->reason)
    {

      case REASON_DEFAULT_RST:
        setLastResult(ResultCodes::BOOT_DEFAULT_RST);
        break;

      case REASON_WDT_RST:
        setLastResult(ResultCodes::BOOT_WDT_RST);
        break;

      case REASON_EXCEPTION_RST:
        setLastResult(ResultCodes::BOOT_EXCEPTION_RST);
        break;

      case REASON_SOFT_WDT_RST:
        setLastResult(ResultCodes::BOOT_SOFT_WDT_RST);
        break;

      case REASON_SOFT_RESTART:
        setLastResult(ResultCodes::BOOT_SOFT_RESTART);
        break;

      case REASON_DEEP_SLEEP_AWAKE:
        setLastResult(ResultCodes::BOOT_DEEP_SLEEP_AWAKE);
        break;

      case REASON_EXT_SYS_RST:
        setLastResult(ResultCodes::BOOT_EXT_SYS_RST);
        break;
    }
#endif
    return getLastResult();
  }

  // Getters
  inline ResultCodes getLastResult() { return _lastResult; };
  inline bool isSuccess() { return _lastResult == ResultCodes::SUCCESS; };
  inline bool isError() { return !isSuccess(); };

private:
  ResultCodes _lastResult =
    ResultCodes::ERROR_NOINIT; // Result of a recent operation
};

#endif
