# JSONC

`JSONC` is a lightweight implementation of `JSON` Data Interchange Standard for `C++` programming language.

It is an ideal candidate to use with microcontrollers. The library was tested with [`Raspberry Pi Pico and Pico W`](https://www.raspberrypi.com/documentation/microcontrollers/raspberry-pi-pico.html).

`JSON` + `C++` = ❤️

## Add dependency

### CMake

`CMake` provides a convenient way to depend on the library.

```cmake
include(FetchContent)

FetchContent_Declare(
  JSONC
  GIT_REPOSITORY git@github.com:st235/JSONC.git
  GIT_TAG "main"
  GIT_SHALLOW TRUE
  GIT_PROGRESS ON
)
FetchContent_MakeAvailable(JSONC)

target_link_libraries(your-project-target jsonc)
```

See more in [`sample`](./sample/)

## Exploring the API

Everything you may expect is implemented (most likely 😅).

### Types

JSON specification declares 4 types and 3 literals:
- Literals
    - `null`
    - `true`
    - `false`
- Types
    - `number`
    - `string`
    - `array`
    - `object`

All json values are conform to specially defined [`json::Json` type](./include/json.h).
To check for those literals and types `Json` defines special **boolean methods**:

- `Json#isNull`
- `Json#isBool`
- `Json#isNumber`
- `Json#isString`
- `Json#isArray`
- `Json#isObject`

Almost all `is` methods (except `isNull`) has corresponding `as` methods to safely get the content of json file:

- `asBool` -> returns `bool`
- `asNumber` -> `double`
- `asString` -> `std::string`
- `asArray` -> `std::vector<Json>`
- `asObject` -> `std::unordered_map<std::string, Json>`

### Create `Json` object from `std::string`

```cpp
#include "json.h"

...

std::string json_text = ...
const auto& json = json::Json::fromJson(json_text);

...
```

### Declare `Json` object

```cpp
json::Json json = { 
  std::make_pair("a", json::Json({ json::Json(true), json::Json("b") })),
  std::make_pair("b", json::Json(129.1))
}
```


## Json Grammar Rules

The specification of JSON format is available at [_the oficial website_](https://www.json.org/json-en.html) or as [_ECMA-404 The JSON Data Interchange Standard_](https://ecma-international.org/publications-and-standards/standards/ecma-404/).

The grammar specifies 6 entries: `array`, `number`, `object`, `string`, `value`, and `whitespace`.
`value` is the entry point.

I won't cover all the details of the implemention but will provide the most important grammar rules.

| Array | Number | Object |
| ----- | ----- | ----- |
| ![Array](./images/array.png) | ![Number](./images/number.png) | ![Object](./images/object.png) |

| String | Value | Whitespace |
| ----- | ----- | ----- |
| ![String](./images/string.png) | ![Value](./images/value.png) | ![Whitespace](./images/whitespace.png) |

## Contribution

The project is using `CMake` as the build system.

### Building

Use these commands to build the project:

```bash
mkdir build
cmake .. -DASSERT=ON
make
```

`ASSERT=ON` is used to enabled assertions in the codebase. If you're building a release flavour then you may consider to do not specify this setting.

### Running test

A lot of logic in the library heavily relies on _unit_ and _integration_ tests.
To run them you need yo _successfully build the project_ and run the command below:

```bash
ctest --output-on-failure
```
