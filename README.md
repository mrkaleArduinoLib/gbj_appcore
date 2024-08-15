<a id="library"></a>

# gbj\_appcore
This is an application library, which is used usually as a project library for particular PlatformIO project. It encapsulates common core methods for project centric application libraries and acts as their parent class. The encapsulation provides following advantages:

* Functionality is hidden from the main sketch.
* The library is reusable for various projects providing basic functionality.
* Update in library is valid for all involved projects.
* It provides error handling for all derived classes.


## Fundamental functionality

* Unified error handling.
* Enumerated result and error codes.
* Detecting microcontroller restart (boot) reason.
* Rounding float numbers.


<a id="dependency"></a>

## Dependency

#### Arduino platform
* **Arduino.h**: Main include file for the Arduino SDK.
* **avr/pgmspace.h**: Processing flashed strings.
* **inttypes.h**: Integer type conversions. This header file includes the exact-width integer definitions and extends them with additional facilities provided by the implementation.

#### Espressif ESP8266 platform
* **Arduino.h**: Main include file for the Arduino platform.
* **pgmspace.h**: Processing flashed strings.
* **user_interface.h**: Various macros and definitions.

#### Espressif ESP32 platform
* **Arduino.h**: Main include file for the Arduino platform.
* **pgmspace.h**: Processing flashed strings.


<a id="results"></a>

#### Result and error codes
* **ResultCodes::SUCCESS**: Result code for successful processing.
* **ResultCodes::ERROR\_UKNOWN**: Unexpected or not recognized error.
* **ResultCodes::ERROR\_NOINIT**: Not initialized yet.
* **ResultCodes::ERROR\_NODEVICE**: No device detected.
* **ResultCodes::ERROR_PINS**: Wrong GPIO assignment.
* **ResultCodes::ERROR\_ADDR**: No or wrong address.
* **ResultCodes::ERROR\_DATA**: Not or wrong data.
* **ResultCodes::ERROR_ACK**: No acknoledgment for a comunicating device.
* **ResultCodes::ERROR\_CONNECT**: Connection failed.
* **ResultCodes::ERROR\_PUBLISH**: Publishing failed.
* **ResultCodes::ERROR\_SUBSCRIBE**: Subsribing failed.
* **ResultCodes::ERROR\_AUTH**: Authorization failed.


<a id="reasons"></a>

#### Boot reason codes
* **BootReasons::BOOT\_UNKNOWN**: Not detected or unknown.
* **BootReasons::BOOT\_DEFAULT\_RST**: Normal startup by power on.
* **BootReasons::BOOT\_WDT\_RST**: Hardware watch dog reset.
* **BootReasons::BOOT\_EXCEPTION\_RST**: Exception reset, GPIO status won’t change.
* **BootReasons::BOOT\_SOFT\_WDT\_RST**: Software watch dog reset, GPIO status won’t change.
* **BootReasons::BOOT\_INT\_WDT\_RST**: Interrupt watch dog reset.
* **BootReasons::BOOT\_TASK\_WDT\_RST**: Task watch dog reset.
* **BootReasons::BOOT\_SOFT\_RESTART**: Software restart, system restart, GPIO status won’t change.
* **BootReasons::BOOT\_DEEP\_SLEEP\_AWAKE**: Wake up from deep-sleep.
* **BootReasons::BOOT\_EXT\_SYS\_RST**: External system reset (assertion of reset pin).
* **BootReasons::BOOT\_DEEPSLEEP**: After exiting deep sleep mode.
* **BootReasons::BOOT\_BROWNOUT**: Brownout reset (software or hardware).
* **BootReasons::BOOT\_SDIO**: Reset over SDIO.
* **BootReasons::BOOT\_WAKEUP\_UNDEFINED**: Not caused by exit from deep sleep.
* **BootReasons::BOOT\_WAKEUP\_ALL**: Not a wakeup cause.
* **BootReasons::BOOT\_WAKEUP\_EXT0**: Wakeup caused by external signal using RTC\_IO.
* **BootReasons::BOOT\_WAKEUP\_EXT1**: Wakeup caused by external signal using RTC\_CNTL.
* **BootReasons::BOOT\_WAKEUP\_TIMER**: Wakeup caused by timer.
* **BootReasons::BOOT\_WAKEUP\_TOUCHPAD**: Wakeup caused by touchpad.
* **BootReasons::BOOT\_WAKEUP\_ULP**: Wakeup caused by ULP program.
* **BootReasons::BOOT\_WAKEUP\_GPIO**: Wakeup caused by GPIO (light sleep only).
* **BootReasons::BOOT\_WAKEUP\_UART**: Wakeup caused by UART (light sleep only).


<a id="interface"></a>

## Custom data types
* [ResultCodes](#ResultCodes)
* [BootReasons](#BootReasons)

## Interface
The methods in bold return [result or error codes](#results).

* [gbj_appcore()](#gbj_appcore)
* [**setLastResult()**](#setLastResult)
* [**getLastResult()**](#getLastResult)
* [**getResetReason()**](#getResetReason) (valid just for ESP8266, ESP32)
* [getResetName()](#getResetName) (valid just for ESP8266, ESP32)
* [isSuccess()](#isSuccess)
* [isError()](#isError)
* [roundoff()](#roundoff)


<a id="ResultCodes"></a>

## ResultCodes

#### Description
Enumeration with [result and error codes](#results).

#### Syntax
    ResultCodes::<code_name>

[Back to interface](#interface)


<a id="BootReasons"></a>

## BootReasons

#### Description
Enumeration with [boot reason codes](#reasons).

#### Syntax
    BootReasons::<code_name>

[Back to interface](#interface)


<a id="gbj_appcore"></a>

## gbj_appcore()

#### Description
Constructor creates the class instance object, determines microcontroller reset reason, and sets recent result code to [ERROR_NOINIT](#results).

#### Syntax
    gbj_appcore()

#### Parameters
None

#### Returns
Object determining microcontroller reset reason. However, it is not intended to be instantiated as itself, only in form of a child class instance.

[Back to interface](#interface)


<a id="setLastResult"></a>

## setLastResult()

#### Description
The method sets the internal status of recent processing to input value.
* Without input parameter the method sets success internal status with result constant [SUCCESS](#results).

#### Syntax
    ResultCodes setLastResult(ResultCodes lastResult)

#### Parameters

* **lastResult**: Desired result code that should be set as a last result code.
  * *Valid values*: some of [result or error codes](#results)
  * *Default value*: [SUCCESS](#results)

#### Returns
New (actual) result code of the recent operation.

#### See also
[getLastResult()](#getLastResult)

[Back to interface](#interface)


<a id="getLastResult"></a>

## getLastResult()

#### Description
The method returns a result or error code of the recent operation. It is usually called for error handling in a sketch.

#### Syntax
    ResultCodes getLastResult()

#### Parameters
None

#### Returns
Some of [result or error codes](#results).

#### See also
[setLastResult()](#setLastResult)

[Back to interface](#interface)


<a id="getResetReason"></a>

## getResetReason()

#### Description
The method returns a boot reason code of the recent microcontroller restart from [boot reason codes](#reasons).
* The method is valid only for microcontrollers ESP5266 and ESP32. For others it returns always unknown boot reason.

#### Syntax
    BootReasons getResetReason()

#### Parameters
None

#### Returns
Some of [boot reason codes](#reasons).

#### See also
[getResetName()](#getResetName)

[Back to interface](#interface)


<a id="getResetName"></a>

## getResetName()

#### Description
The method returns a pointer to textual name of a boot reason of the recent microcontroller restart.
* The method is valid only for microcontrollers ESP5266 and ESP32. For others it returns always unknown boot reason name.
* The boot reason names are equal to corresponding enumeration literals from [boot reason codes](#reasons).

#### Syntax
    char *getResetName()

#### Parameters
None

#### Returns
Pointer to name of a microcontroller reset reason name.

#### See also
[getResetReason()](#getResetReason)

[Back to interface](#interface)


<a id="isSuccess"></a>

## isSuccess()

#### Description
The overloade method returns a flag whether the recent operation was successful or input argument is a success code.

#### Syntax
    bool isSuccess()
    bool isSuccess(ResultCodes lastResult)

#### Parameters

* **lastResult**: Optional error code as a last result code.
  * *Valid values*: some of [result or error codes](#results)
  * *Default value*: none


#### Returns
Flag about successful processing of the recent operation or input as a success code.

#### See also
[isError()](#isError)

[Back to interface](#interface)


<a id="isError"></a>

## isError()

#### Description
The method returns a flag whether the recent operation failed or input argument is an error code. The corresponding error code can be obtained by the method [getLastResult()](#getLastResult).

#### Syntax
    bool isError()
    bool isError(ResultCodes lastResult)

#### Parameters

* **lastResult**: Optional error code as a last result code.
  * *Valid values*: some of [result or error codes](#results)
  * *Default value*: none


#### Returns
Flag about failing of the recent operation or input as an error code.

#### See also
[getLastResult()](#getLastResult)

[isSuccess()](#isSuccess)

[Back to interface](#interface)


<a id="roundoff"></a>

## roundoff()

#### Description
The method rounds provided rational number to desired decimal places.

#### Syntax
    float roundoff(float value, byte prec)

#### Parameters

* **value**: A number to be rounded.
  * *Valid values*: float numbers
  * *Default value*: none


* **prec**: Rounding precision in number of decimal places.
  * *Valid values*: 0 ~ 255
  * *Default value*: none

#### Returns
Rounded rational number to provided number of decimal places.

[Back to interface](#interface)
