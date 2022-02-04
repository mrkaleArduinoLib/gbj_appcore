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
* **inttypes.h**: Integer type conversions. This header file includes the exact-width integer definitions and extends them with additional facilities provided by the implementation.

#### Espressif ESP8266 platform
* **Arduino.h**: Main include file for the Arduino platform.

#### Espressif ESP32 platform
* **Arduino.h**: Main include file for the Arduino platform.

#### Particle platform
* **Particle.h**: Includes alternative (C++) data type definitions.


<a id="constants"></a>

## Constants

* **VERSION**: Name and semantic version of the library.
* **NA**: Generic string for `not-applicable` marking.


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


<a id="reasons"></a>

#### Boot reason codes
* **BootReasons::BOOT\_UNKNOWN**: Unknown boot reason.
* **BootReasons::BOOT\_DEFAULT\_RST**: Normal startup by power on.
* **BootReasons::BOOT\_WDT\_RST**: Hardware watch dog reset.
* **BootReasons::BOOT\_EXCEPTION\_RST**: Exception reset.
* **BootReasons::BOOT\_SOFT\_WDT\_RST**: Software watch dog reset.
* **BootReasons::BOOT\_SOFT\_RESTART**: Software or system restart.
* **BootReasons::BOOT\_DEEP\_SLEEP\_AWAKE**: Wake up from deep-sleep.
* **BootReasons::BOOT\_EXT\_SYS\_RST**: External system reset (by reset pin).


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
The method returns a flag whether the recent operation was successful.

#### Syntax
    bool isSuccess()

#### Parameters
None

#### Returns
Flag about successful processing of the recent operation.

#### See also
[isError()](#isError)

[Back to interface](#interface)


<a id="isError"></a>

## isError()

#### Description
The method returns a flag whether the recent operation failed. The corresponding error code can be obtained by the method [getLastResult()]((#getLastResult).

#### Syntax
    bool isError()

#### Parameters
None

#### Returns
Flag about failing of the recent operation.

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
