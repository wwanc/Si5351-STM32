# Si5351 C++ Library for STM32
This is a C++ library for Si5351 to be used with STM32 HAL, ported directly from the [library for Arduino](https://github.com/etherkit/Si5351Arduino). Almost all interfaces are the same as those in the Arduino library. Differences are self-explanatory. Refer to the Arduino project for the complete reference of the interfaces.

C wrapper functions for a few of the essential C++ interfaces are provided and they can be called from C files (for example main.c in a project created in STM32Cube).
# Usage
Modify the include line below in si5351_def.h according to the device family:
```
/* si5351_def.h */
#include "stm32f1xx_hal.h"
```
Include si5351_c_wrapper.h, for exmaple in main.c:
```
/* main.c */
#include "si5351_c_wrapper.h"
```
Create and initialize a Si5351 struct after the initialization of the I2C interfaces:
```
/* after the initialization of the I2C interfaces */
struct Si5351* si5351 = Si5351_create(&hi2c1, SI5351_BUS_BASE_ADDR);
Si5351_init(si5351, SI5351_CRYSTAL_LOAD_10PF, 0, 0);
```
Set output frequency and enable clock output:
```
uint64_t freq_Hz = 1000000; /* 4 kHz< freq < 225 Mhz */
uint8_t set_freq_result = Si5351_set_freq(si5351, i*100, SI5351_CLK0);
Si5351_output_enable(si5351, SI5351_CLK0, 1);
```
Check status registers:
```
HAL_Delay(500); /* Insert a delay if Si5351_update_status() is called right after Si5351 settings are changed */
Si5351_update_status(si5351);
struct Si5351Status status5351 = Si5351_status(si5351);
```
Set drive strength if desired:

```
Si5351_drive_strength(si5351, SI5351_CLK0, SI5351_DRIVE_6MA);
```
