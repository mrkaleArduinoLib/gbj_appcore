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
- **Arduino.h**: Main include file for the Arduino SDK.
- **inttypes.h**: Integer type conversions. This header file includes the exact-width integer definitions and extends them with additional facilities provided by the implementation.

#### Espressif ESP8266 platform
- **Arduino.h**: Main include file for the Arduino platform.

#### Espressif ESP32 platform
- **Arduino.h**: Main include file for the Arduino platform.

#### Particle platform
- **Particle.h**: Includes alternative (C++) data type definitions.


<a id="constants"></a>

## Constants

- **gbj\_appcore::VERSION**: Name and semantic version of the library.
- **gbj\_appcore::NA**: Generic string for `not-applicable` marking.


<a id="results"></a>

#### Result and error codes

- **gbj\_appcore::SUCCESS**: Result code for successful processing.
- **gbj\_appcore::ERROR\_UKNOWN**: Unexpected or not recognized error.
- **gbj\_appcore::ERROR\_NOINIT**: Not initialized yet.
- **gbj\_appcore::ERROR\_NODEVICE**: No device detected.
- **ERROR_PINS**: Wrong GPIO assignment.
- **gbj\_appcore::ERROR\_ADDR**: No or wrong address.
- **gbj\_appcore::ERROR\_DATA**: Not or wrong data.
- **ERROR_ACK**: No acknoledgment for a comunicating device.
- **gbj\_appcore::ERROR\_CONNECT**: Connection failed.
- **gbj\_appcore::ERROR\_PUBLISH**: Publishing failed.
- **gbj\_appcore::ERROR\_SUBSCRIBE**: Subsribing failed.
- **BOOT_UNKNOWN**: Unknown boot reason.
- **BOOT_DEFAULT_RST**: Normal startup by power on.
- **BOOT_WDT_RST**: Hardware watch dog reset.
- **BOOT_EXCEPTION_RST**: Exception reset.
- **BOOT_SOFT_WDT_RST**: Software watch dog reset.
- **BOOT_SOFT_RESTART**: Software or system restart.
- **BOOT_DEEP_SLEEP_AWAKE**: Wake up from deep-sleep.
- **BOOT_EXT_SYS_RST**: External system reset (by reset pin).


<a id="interface"></a>

## Interface
* The methods in bold return [result or error codes](#results).


##### Custom data types

* [ResultCodes](#ResultCodes)


##### Functions

- [**setLastResult()**](#setLastResult)
- [**getLastResult()**](#getLastResult)
- [**getResetReason()**](#getResetReason) (valid just for ESP8266, ESP32)
- [isSuccess()](#isSuccess)
- [isError()](#isError)
- [roundoff()](#roundoff)


<a id="ResultCodes"></a>

## ResultCodes

#### Description
Enumeration with [result and error codes](#results).

#### Syntax
    ResultCodes::<code_name>

[Back to interface](#interface)


<a id="setLastResult"></a>

## setLastResult()

#### Description
The method sets the internal status of recent processing to input value.
- Without input parameter the method sets success internal status with result constant [SUCCESS](#results).

#### Syntax
    ResultCodes setLastResult(ResultCodes lastResult)

#### Parameters

- **lastResult**: Desired result code that should be set as a last result code.
  - *Valid values*: some of [result or error codes](#results)
  - *Default value*: [SUCCESS](#results)

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
The method returns a boot reason of the recent microcontroller from [result codes](#results) begining with _BOOT\__.
* The method is valid only for microcontrollers ESP5266 and ESP32. For other it returns always unknown boot reason.

#### Syntax
    ResultCodes getResetReason()

#### Parameters
None

#### Returns
Some of [result or error codes](#results) begining with _BOOT\__.

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

- **value**: A number to be rounded.
  - *Valid values*: float numbers
  - *Default value*: none


- **prec**: Rounding precision in number of decimal places.
  - *Valid values*: 0 ~ 255
  - *Default value*: none

#### Returns
Rounded rational number to provided number of decimal places.

[Back to interface](#interface)
