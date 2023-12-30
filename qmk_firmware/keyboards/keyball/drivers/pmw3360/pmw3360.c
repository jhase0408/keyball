/*
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "quantum.h"
#include "pmw3360.h"

#define PMW3360_SPI_MODE 3
#define PMW3360_SPI_DIVISOR (F_CPU / PMW3360_CLOCKS)
#define PMW3360_CLOCKS 2000000

bool pmw3360_spi_start(void) {
    // return spi_start(PMW3360_NCS_PIN, false, PMW3360_SPI_MODE, PMW3360_SPI_DIVISOR);
    if (!spi_start(PMW3360_NCS_PIN, false, 3, PMW3360_SPI_DIVISOR)) {
        spi_stop();
        return false;
    }
    // tNCS-SCLK, 10ns
    wait_us(1);
    return true;
}

uint8_t pmw3360_reg_read(uint8_t addr) {
    if (!pmw3360_spi_start()) {
        return 0;
    }
    spi_write(addr & 0x7f);
    wait_us(160);
    uint8_t data = spi_read();
    wait_us(1);
    spi_stop();
    wait_us(19);
    return data;
}

bool pmw3360_reg_write(uint8_t addr, uint8_t data) {
    if(!pmw3360_spi_start()) {
        return false;
    };
    uint8_t command[2] = {addr | 0x80, data};
    if (spi_transmit(command, sizeof(command)) != SPI_STATUS_SUCCESS) {
        return false;
    }
    wait_us(35);
    spi_stop();
    wait_us(145);
    return true;
}

uint8_t pmw3360_cpi_get(void) {
    return pmw3360_reg_read(pmw3360_Config1);
}

void pmw3360_cpi_set(uint8_t cpi) {
    if (cpi > pmw3360_MAXCPI) {
        cpi = pmw3360_MAXCPI;
    }
    pmw3360_reg_write(pmw3360_Config1, cpi);
}

static uint32_t pmw3360_timer      = 0;
static uint32_t pmw3360_scan_count = 0;
static uint32_t pmw3360_last_count = 0;

void pmw3360_scan_perf_task(void) {
    pmw3360_scan_count++;
    uint32_t now = timer_read32();
    if (TIMER_DIFF_32(now, pmw3360_timer) > 1000) {
#if defined(CONSOLE_ENABLE)
        dprintf("pmw3360 scan frequency: %lu\n", pmw3360_scan_count);
#endif
        pmw3360_last_count = pmw3360_scan_count;
        pmw3360_scan_count = 0;
        pmw3360_timer      = now;
    }
}

uint32_t pmw3360_scan_rate_get(void) {
    return pmw3360_last_count;
}

bool pmw3360_motion_read(pmw3360_motion_t *d) {
#ifdef DEBUG_PMW3360_SCAN_RATE
    pmw3360_scan_perf_task();
#endif
    uint8_t mot = pmw3360_reg_read(pmw3360_Motion);
    if ((mot & 0x88) != 0x80) {
        return false;
    }
    d->x = pmw3360_reg_read(pmw3360_Delta_X_L);
    d->x |= pmw3360_reg_read(pmw3360_Delta_X_H) << 8;
    d->y = pmw3360_reg_read(pmw3360_Delta_Y_L);
    d->y |= pmw3360_reg_read(pmw3360_Delta_Y_H) << 8;
    return true;
}

bool pmw3360_motion_burst(pmw3360_motion_t *d) {
#ifdef DEBUG_PMW3360_SCAN_RATE
    pmw3360_scan_perf_task();
#endif
    pmw3360_spi_start();
    spi_write(pmw3360_Motion_Burst);
    wait_us(35);
    uint8_t mot = spi_read();
    if ((mot & 0x88) != 0x80) {
        spi_stop();
        return false;
    }
    spi_read(); // skip Observation
    d->x = spi_read();
    d->x |= spi_read() << 8;
    d->y = spi_read();
    d->y |= spi_read() << 8;
    spi_stop();
    return true;
}

// uint8_t ball_init_phase = 0;
// uint8_t pmw_pid = 0;
// uint8_t pmw_rev = 0; 

bool pmw3360_init(void) {
    spi_init();
    // ball_init_phase = 1;
    setPinOutput(PMW3360_NCS_PIN);
    // ball_init_phase = 2;
    // reboot
    if (!pmw3360_spi_start()){
        return false;
    }
    // ball_init_phase = 3;

    wait_us(40);
    spi_stop();
    // ball_init_phase = 4;
    wait_us(40);

    if (!pmw3360_reg_write(pmw3360_Power_Up_Reset, 0x5a)) {
        return false;
    };
    // ball_init_phase = 5;
    wait_ms(50);
    // read five registers of motion and discard those values
    pmw3360_reg_read(pmw3360_Motion);
    pmw3360_reg_read(pmw3360_Delta_X_L);
    pmw3360_reg_read(pmw3360_Delta_X_H);
    pmw3360_reg_read(pmw3360_Delta_Y_L);
    pmw3360_reg_read(pmw3360_Delta_Y_H);

    // ball_init_phase = 6;
    // configuration
    if (!pmw3360_reg_write(pmw3360_Config2, 0x00)) {
        return false;
    }
    // ball_init_phase = 7;
    // check product ID and revision ID
    uint8_t pid = pmw3360_reg_read(pmw3360_Product_ID);
    uint8_t rev = pmw3360_reg_read(pmw3360_Revision_ID);
    // ball_init_phase = 8;
    spi_stop();
    // ball_init_phase = 9;
    // pmw_pid = pid;
    // pmw_rev = rev;
    dprintf("pmw3360 init: pid: 0x%x, rev: 0x%x\n");
    // if(pid == 0x42 && rev == 0x01) {
    //   ball_init_phase = 10;
    // }
    return pid == 0x42 && rev == 0x01;
}
