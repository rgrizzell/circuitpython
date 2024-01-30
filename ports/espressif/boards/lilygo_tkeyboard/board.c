/*
 * This file is part of the MicroPython project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2020 Scott Shawcroft for Adafruit Industries
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (theSoftware"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDEDAS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "supervisor/board.h"
#include "mpconfigboard.h"
#include "shared-bindings/microcontroller/Pin.h"

#include "shared-bindings/busio/SPI.h"
#include "shared-module/displayio/__init__.h"
#include "shared-module/displayio/mipi_constants.h"
#include "shared-bindings/board/__init__.h"

uint8_t display_init_sequence[] = {
    0xFE, 0x00,  // Inter Register Enable1 (FEh)
    0xEF, 0x00,  // Inter Register Enable2 (EFh)
    0x80, 0x01, 0xFF,
    0x81, 0x01, 0xFF,
    0x82, 0x01, 0xFF,
    0x83, 0x01, 0xFF,
    0x84, 0x01, 0xFF,
    0x85, 0x01, 0xFF,
    0x86, 0x01, 0xFF,
    0x87, 0x01, 0xFF,
    0x88, 0x01, 0xFF,
    0x89, 0x01, 0xFF,
    0x8A, 0x01, 0xFF,
    0x8B, 0x01, 0xFF,
    0x8C, 0x01, 0xFF,
    0x8D, 0x01, 0xFF,
    0x8E, 0x01, 0xFF,
    0x8F, 0x01, 0xFF,
    0x3A, 0x01, 0x05,  // COLMOD: Pixel Format Set (3Ah) MCU interface, 16 bits / pixel
    0xEC, 0x01, 0x10,  // Inversion (ECh) DINV=1+2 column for Single Gate (BFh=0)
    0x7E, 0x01, 0x7A,
    0x74, 0x07, 0x02, 0x0E, 0x00, 0x00, 0x28, 0x00, 0x00,
    0x98, 0x01, 0x3E,
    0x99, 0x01, 0x3E,
    0xB5, 0x03, 0x0E, 0x0E, 0x00,  // Blanking Porch Control (B5h) VFP=14 VBP=14 HBP=Off
    0x60, 0x04, 0x38, 0x09, 0x6D, 0x67,
    0x63, 0x05, 0x38, 0xAD, 0x6D, 0x67, 0x05,
    0x64, 0x06, 0x38, 0x0B, 0x70, 0xAB, 0x6D, 0x67,
    0x66, 0x06, 0x38, 0x0F, 0x70, 0xAF, 0x6D, 0x67,
    0x6A, 0x02, 0x00, 0x00,
    0x68, 0x07, 0x3B, 0x08, 0x04, 0x00, 0x04, 0x64, 0x67,
    0x6C, 0x07, 0x22, 0x02, 0x22, 0x02, 0x22, 0x22, 0x50,
    0x6E, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x07, 0x01, 0x13, 0x11, 0x0B, 0x09, 0x16, 0x15, 0x1D, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x1E, 0x1D, 0x15, 0x16, 0x0A, 0x0C, 0x12, 0x14, 0x02, 0x08, 0x00, 0x00, 0x00, 0x00,
    0xA9, 0x01, 0x1B,
    0xA8, 0x01, 0x6B,
    0xA8, 0x01, 0x6D,
    0xA7, 0x01, 0x40,
    0xAD, 0x01, 0x47,
    0xAF, 0x01, 0x73,
    0xAF, 0x01, 0x73,
    0xAC, 0x01, 0x44,
    0xA3, 0x01, 0x6C,
    0xCB, 0x01, 0x00,
    0xCD, 0x01, 0x22,
    0xC2, 0x01, 0x10,
    0xC5, 0x01, 0x00,
    0xC6, 0x01, 0x0E,
    0xC7, 0x01, 0x1F,
    0xC8, 0x01, 0x0E,
    0xBF, 0x01, 0x00,  // Dual-Single Gate Select (BFh) 0=>Single gate
    0xF9, 0x01, 0x20,
    0x9B, 0x01, 0x3B,
    0x93, 0x03, 0x33, 0x7F, 0x00,
    0x70, 0x06, 0x0E, 0x0F, 0x03, 0x0E, 0x0F, 0x03,
    0x71, 0x03, 0x0E, 0x16, 0x03,
    0x91, 0x02, 0x0E, 0x09,
    0xC3, 0x01, 0x2C,  // Vreg1a Voltage Control 2 (C3h) vreg1_vbp_d=0x2C
    0xC4, 0x01, 0x1A,  // Vreg1b Voltage Control 2 (C4h) vreg1_vbn_d=0x1A
    0xF0, 0x06, 0x51, 0x13, 0x0C, 0x06, 0x00, 0x2F,  // SET_GAMMA1 (F0h)
    0xF2, 0x06, 0x51, 0x13, 0x0C, 0x06, 0x00, 0x33,  // SET_GAMMA3 (F2h)
    0xF1, 0x06, 0x3C, 0x94, 0x4F, 0x33, 0x34, 0xCF,  // SET_GAMMA2 (F1h)
    0xF3, 0x06, 0x4D, 0x94, 0x4F, 0x33, 0x34, 0xCF,  // SET_GAMMA4 (F3h)
    0x36, 0x01, 0x00,  // Memory Access Control (36h) MY=0, MX=0, MV=0, ML=0, BGR=0, MH=0
    0x11, 0x80, 0xC8,  // Sleep Out Mode (11h) and delay(200)
    0x29, 0x80, 0x14,  // Display ON (29h) and delay(20)
    0x2C, 0x00,  // Memory Write (2Ch) D=0
};

void board_init(void) {

    fourwire_fourwire_obj_t *bus = &allocate_display_bus()->fourwire_bus;
    busio_spi_obj_t *spi = &bus->inline_bus;

    common_hal_busio_spi_construct(
        spi,
        &pin_GPIO20,    // CLK
        &pin_GPIO10,    // MOSI
        NULL,           // MISO not connected
        false);         // Not half-duplex

    common_hal_busio_spi_never_reset(spi);

    bus->base.type = &fourwire_fourwire_type;

    common_hal_fourwire_fourwire_construct(
        bus,
        spi,
        &pin_GPIO2,     // DC
        NULL,           // CS
        NULL,           // RST
        24000000,       // baudrate (default from the driver)
        0,              // polarity
        0               // phase
        );

    busdisplay_busdisplay_obj_t *display = &allocate_display()->display;
    display->base.type = &busdisplay_busdisplay_type;

    common_hal_busdisplay_busdisplay_construct(
        display,
        bus,
        160,            // width (after rotation)
        40,             // height (after rotation)
        0,              // column start
        0,              // row start
        0,              // rotation
        16,             // color depth
        false,          // grayscale
        false,          // pixels in a byte share a row. Only valid for depths < 8
        1,              // bytes per cell. Only valid for depths < 8
        false,          // reverse_pixels_in_byte. Only valid for depths < 8
        true,           // reverse_pixels_in_word
        MIPI_COMMAND_SET_COLUMN_ADDRESS, // set column command
        MIPI_COMMAND_SET_PAGE_ADDRESS,   // set row command
        MIPI_COMMAND_WRITE_MEMORY_START, // write memory command
        display_init_sequence,
        sizeof(display_init_sequence),
        &pin_GPIO8,    // backlight pin
        NO_BRIGHTNESS_COMMAND,
        1.0f,           // brightness
        false,          // single_byte_bounds
        false,          // data_as_commands
        true,           // auto_refresh
        60,             // native_frames_per_second
        true,           // backlight_on_high
        false,          // SH1107_addressing
        50000           // backlight pwm frequency
        );
}

// Use the MP_WEAK supervisor/shared/board.c versions of routines not defined here.
