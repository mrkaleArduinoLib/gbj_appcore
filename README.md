<a id="library"></a>

# gbj\_appcore
This is an application library, which is used usually as a project library for particular PlatformIO project. It provides common core methods for project centric application libraries and acts as their parent class.

- Library has no virtual methods, so that it is useful for project libraries without internal timers.
- Library utilizes error handling from the parent class.


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


<a id="results"></a>

#### Result and error codes

- **gbj\_appcore::SUCCESS**: Result code for successful processing.
- **gbj\_appcore::ERROR\_UKNOWN**: Unexpected or not recognized error.
- **gbj\_appcore::ERROR\_NOINIT**: Not initialized yet.
- **gbj\_appcore::ERROR\_NODEVICE**: No device detected.
- **gbj\_appcore::ERROR\_ADDR**: No or wrong address.
- **gbj\_appcore::ERROR\_DATA**: Not or wrong data.
- **gbj\_appcore::ERROR\_CONNECT**: Connection failed.
- **gbj\_appcore::ERROR\_PUBLISH**: Publishing failed.
- **gbj\_appcore::ERROR\_SUBSCRIBE**: Subsribing failed.


<a id="interface"></a>

## Interface
* The methods in bold return [result or error codes](#results).


##### Custom data types

* [gbj\_appcore::ResultCodes](#ResultCodes)


##### Functions

- [**setLastResult()**](#setLastResult)
- [**getLastResult()**](#getLastResult)
- [isSuccess()](#isSuccess)
- [isError()](#isError)


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
- Without input parameter the method sets success internal status with result constant [gbj\_appcore::SUCCESS](#results).

#### Syntax
    ResultCodes setLastResult(ResultCodes lastResult)

#### Parameters
- **lastResult**: Desired result code that should be set as a last result code.
  - *Valid values*: Some of [result or error codes](#results).
  - *Default value*: [gbj\_appcore::SUCCESS](#results)

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


<a id="isSuccess"></a>

## isSuccess()

#### Description
The method returns a flag whether the recent operation was successful.

#### Syntax
    boolean isSuccess()

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
    boolean isError()

#### Parameters
None

#### Returns
Flag about failing of the recent operation.

#### See also
[getLastResult()](#getLastResult)

[isSuccess()](#isSuccess)

[Back to interface](#interface)
