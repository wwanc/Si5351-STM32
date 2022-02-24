#ifndef INC_SI5351_H_
#define INC_SI5351_H_

/*
 * si5351.h - Si5351 library for Arduino
 *
 * Copyright (C) 2015 - 2019 Jason Milldrum <milldrum@gmail.com>
 *                           Dana H. Myers <k6jq@comcast.net>
 *
 * Many defines derived from clk-si5351.h in the Linux kernel.
 * Sebastian Hesselbarth <sebastian.hesselbarth@gmail.com>
 * Rabeeh Khoury <rabeeh@solid-run.com>
 *
 * do_div() macro derived from /include/asm-generic/div64.h in
 * the Linux kernel.
 * Copyright (C) 2003 Bernardo Innocenti <bernie@develer.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <string>
#include "si5351_def.h"

class Si5351
{
public:
  Si5351(I2C_HandleTypeDef *hi2c, uint8_t i2c_addr = SI5351_BUS_BASE_ADDR);
  ~Si5351();
	bool init(uint8_t, uint32_t, int32_t);
	void reset(void);
	uint8_t set_freq(uint64_t, enum si5351_clock);
	uint8_t set_freq_manual(uint64_t, uint64_t, enum si5351_clock);
	void set_pll(uint64_t, enum si5351_pll);
	void set_ms(enum si5351_clock, struct Si5351RegSet, uint8_t, uint8_t, uint8_t);
	void output_enable(enum si5351_clock, uint8_t);
	void drive_strength(enum si5351_clock, enum si5351_drive);
	void update_status(void);
	void set_correction(int32_t, enum si5351_pll_input);
	void set_phase(enum si5351_clock, uint8_t);
	int32_t get_correction(enum si5351_pll_input);
	void pll_reset(enum si5351_pll);
	void set_ms_source(enum si5351_clock, enum si5351_pll);
	void set_int(enum si5351_clock, uint8_t);
	void set_clock_pwr(enum si5351_clock, uint8_t);
	void set_clock_invert(enum si5351_clock, uint8_t);
	void set_clock_source(enum si5351_clock, enum si5351_clock_source);
	void set_clock_disable(enum si5351_clock, enum si5351_clock_disable);
	void set_clock_fanout(enum si5351_clock_fanout, uint8_t);
	void set_pll_input(enum si5351_pll, enum si5351_pll_input);
	void set_vcxo(uint64_t, uint8_t);
  void set_ref_freq(uint32_t, enum si5351_pll_input);
	uint8_t si5351_write_bulk(uint8_t, uint8_t, uint8_t *);
	uint8_t si5351_write(uint8_t, uint8_t);
	uint8_t si5351_read(uint8_t);
	struct Si5351Status dev_status = {.SYS_INIT = 0, .LOL_B = 0, .LOL_A = 0,
    .LOS = 0, .REVID = 0};
	struct Si5351IntStatus dev_int_status = {.SYS_INIT_STKY = 0, .LOL_B_STKY = 0,
    .LOL_A_STKY = 0, .LOS_STKY = 0};
	enum si5351_pll pll_assignment[8];
	uint64_t clk_freq[8];
	uint64_t plla_freq;
	uint64_t pllb_freq;
  enum si5351_pll_input plla_ref_osc;
  enum si5351_pll_input pllb_ref_osc;
	uint32_t xtal_freq[2];
private:
	uint64_t pll_calc(enum si5351_pll, uint64_t, struct Si5351RegSet *, int32_t, uint8_t);
	uint64_t multisynth_calc(uint64_t, uint64_t, struct Si5351RegSet *);
	uint64_t multisynth67_calc(uint64_t, uint64_t, struct Si5351RegSet *);
	void update_sys_status(struct Si5351Status *);
	void update_int_status(struct Si5351IntStatus *);
	void ms_div(enum si5351_clock, uint8_t, uint8_t);
	uint8_t select_r_div(uint64_t *);
	uint8_t select_r_div_ms67(uint64_t *);

	int32_t ref_correction[2];
  uint8_t clkin_div;
  uint8_t i2c_bus_addr;
  bool clk_first_set[8];

  I2C_HandleTypeDef* i2c_port;
};

extern "C" Si5351* Si5351_create(I2C_HandleTypeDef* hi2c, uint8_t i2c_addr)
{
	return new Si5351(hi2c, i2c_addr);
}

extern "C" void Si5351_delelte(Si5351* si5351)
{
	delete si5351;
}

extern "C" bool Si5351_init(Si5351* m, uint8_t xtal_load_c, uint32_t xo_freq, int32_t corr)
{
	return m->init(xtal_load_c, xo_freq, corr);
}

extern "C" uint8_t Si5351_set_freq(Si5351* m, uint64_t freq, enum si5351_clock clk)
{
	return m->set_freq(freq, clk);
}

extern "C" void Si5351_update_status(Si5351* m)
{
	m->update_status();
}

extern "C" struct Si5351Status Si5351_status(Si5351* m)
{
	return m->dev_status;
}

extern "C" void Si5351_output_enable(Si5351* m, enum si5351_clock clk, uint8_t enable)
{
	m->output_enable(clk, enable);
}

extern "C" void Si5351_drive_strength(Si5351* m, enum si5351_clock clk, enum si5351_drive drive)
{
	m->drive_strength(clk, drive);
}

#endif /* INC_SI5351_H_ */
