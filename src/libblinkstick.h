#include <libusb.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

struct rgb_color;
typedef struct rgb_color rgb_color;

struct rgb_color {
  int red;
  int green;
  int blue;
  unsigned char * bytes;
};

rgb_color* rgb_color_factory(int red, int green, int blue);
unsigned char *rgb_to_char(rgb_color *color);
void destroy_color(rgb_color *color);

static int const BLINKSTICK_VENDOR_ID = 8352; //"0X20A0";
static int const BLINKSTICK_PRODUCT_ID = 16869; //"0X41E5";
static int const COLOR_PACKET_SIZE = 4;
static int const COLOR_PACKET_SIZE_BY_INDEX = 6;
static uint8_t const SINGLE_LED_BYTE = 1; //"0x01";
// libusb_control_transfer parameters
static uint8_t const REQUEST_TYPE = 32; //"0x20";
static uint8_t const REQUEST = 9; //"0x9";
static uint16_t const VALUE = 1; //"0x0001";
static uint16_t const VALUE_BY_INDEX = 5; //"0x0005";
static uint16_t const INDEX = 0; //"0x0000";
static int const TIMEOUT = 2; //2 milli seconds

struct blinkstick_device;
typedef struct blinkstick_device blinkstick_device;

struct blinkstick_device {
  libusb_device_handle* handle;
  libusb_context* usb_context;
  unsigned char *serial_number;
};

struct blinkstick_device_list;
typedef struct blinkstick_device_list blinkstick_device_list;

struct blinkstick_device_list {
  int num_of_devices;
  blinkstick_device **blinkstick_device_list;
};

// PUBLIC
void set_debug_true();
void find_blinksticks(blinkstick_device_list* list_of_devices);
// blinkstick_device** find_all();
void set_color(int index, rgb_color *color, blinkstick_device *device);
void off(int index, blinkstick_device *device);

// PRIVATE
void destroy_blinksticks(blinkstick_device_list *device_list);
blinkstick_device* blinkstick_factory(libusb_device_handle *handle,           \
                        libusb_context *context, unsigned char *serial_number);
blinkstick_device_list* blinkstick_list_factory(int num_of_devices);
