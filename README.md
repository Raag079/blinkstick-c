libBlinkStick
=============

A [blinkstick](http://www.blinkstick.com/) library in C with few dependencies.

I added features to [libblinkstick](https://github.com/ebenoist/libblinkstick)
  library, please see to commit history to know more.

## Requirements
- libusb,
    ```brew install libusb``` on Mac OS X,
    ```sudo apt-get install libusb-1.0-0-dev``` on Ubuntu
- clang
- cmake,
    ```brew install cmake``` on Mac OS X,
    ```sudo apt-get install cmake``` on Ubuntu

## Running tests
- ```script/test```

## To build the test app - Mac
- ```script/build``` or
  ```script/build --disable-tests``` to disable the unit tests.
- ```./target/blinkstick --color 255 0 0```

## To build the test app - Ubuntu
- Delete ```-arch x86_64``` in Line 18 and Line 19 of CMakeLists.txt
- ```script/build``` or
  ```script/build --disable-tests``` to disable the unit tests.
- ```./target/blinkstick --color 255 0 0```

## Example

```C
#include <libblinkstick.h>

int main(int argc, char **argv) {
  rgb_color *color = parse_args(argv);
  int number_of_devices = 2;
  blinkstick_device_list *devices = blinkstick_list_factory(number_of_devices);

  find_blinksticks(devices);

  int i, j;
  for(i = 0; i < number_of_devices; i++)
  {
    if(devices->blinkstick_device_list[i] != NULL) {
      for(j = 0; j < 8; j++)
      {
        set_color(j, color, devices->blinkstick_device_list[i]);
        usleep(20000);
        off(j, devices->blinkstick_device_list[i]);
        usleep(20000);
      }
    }
  }
  destroy_color(color);
  destroy_blinksticks(devices);
  return 0;
}

```
