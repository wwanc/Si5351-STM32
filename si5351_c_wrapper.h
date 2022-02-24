#ifndef INC_SI5351_C_WRAPPER_H_
#define INC_SI5351_C_WRAPPER_H_

#include "si5351_def.h"
#include <stdbool.h>

struct Si5351;

/* Create a Si5351 object and returns a pointer for it which can be used by other functions */
struct Si5351* Si5351_create(I2C_HandleTypeDef* hi2c, uint8_t i2c_addr);

/* Destroy the Si5351 object */
void Si5351_delelte(struct Si5351* si5351);

/* Si5351::init */
bool Si5351_init(struct Si5351* m, uint8_t xtal_load_c, uint32_t xo_freq, int32_t corr);

/* Si5351::set_freq */
uint8_t Si5351_set_freq(struct Si5351* m, uint64_t freq, enum si5351_clock clk);

/* Si5351::update_status */
void Si5351_update_status(struct Si5351* m);

/* Si5351::status */
struct Si5351Status Si5351_status(struct Si5351* m);

/* Si5351::output_enable */
void Si5351_output_enable(struct Si5351* m, enum si5351_clock clk, uint8_t enable);

/* Si5351::drive_strenght */
void Si5351_drive_strength(struct Si5351* m, enum si5351_clock clk, enum si5351_drive drive);

#endif /* INC_SI5351_C_WRAPPER_H_ */
