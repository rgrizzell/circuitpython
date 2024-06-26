/*
 * This file is part of the Micro Python project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2021 Dan Halbert for Adafruit Industries
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef MICROPY_INCLUDED_SHARED_BINDINGS_KEYPAD_EVENTQUEUE_H
#define MICROPY_INCLUDED_SHARED_BINDINGS_KEYPAD_EVENTQUEUE_H

#include "shared-module/keypad/Event.h"
#include "shared-module/keypad/EventQueue.h"

extern const mp_obj_type_t keypad_eventqueue_type;

void common_hal_keypad_eventqueue_construct(keypad_eventqueue_obj_t *self, size_t max_events);

void common_hal_keypad_eventqueue_clear(keypad_eventqueue_obj_t *self);
size_t common_hal_keypad_eventqueue_get_length(keypad_eventqueue_obj_t *self);
mp_obj_t common_hal_keypad_eventqueue_get(keypad_eventqueue_obj_t *self);
bool common_hal_keypad_eventqueue_get_into(keypad_eventqueue_obj_t *self, keypad_event_obj_t *event);

bool common_hal_keypad_eventqueue_get_overflowed(keypad_eventqueue_obj_t *self);
void common_hal_keypad_eventqueue_set_overflowed(keypad_eventqueue_obj_t *self, bool overflowed);

void common_hal_keypad_eventqueue_set_event_handler(keypad_eventqueue_obj_t *self, void (*event_handler)(keypad_eventqueue_obj_t *));

#endif  // MICROPY_INCLUDED_SHARED_BINDINGS_KEYPAD_EVENTQUEUE_H
