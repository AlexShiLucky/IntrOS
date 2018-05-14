/******************************************************************************

    @file    IntrOS: osbarrier.c
    @author  Rajmund Szymanski
    @date    13.05.2018
    @brief   This file provides set of functions for IntrOS.

 ******************************************************************************

   Copyright (c) 2018 Rajmund Szymanski. All rights reserved.

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to
   deal in the Software without restriction, including without limitation the
   rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
   sell copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included
   in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
   THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
   FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
   IN THE SOFTWARE.

 ******************************************************************************/

#include "inc/osbarrier.h"

/* -------------------------------------------------------------------------- */
void bar_init( bar_t *bar, unsigned limit )
/* -------------------------------------------------------------------------- */
{
	assert(bar);
	assert(limit);

	port_sys_lock();

	memset(bar, 0, sizeof(bar_t));

	bar->count = limit;
	bar->limit = limit;

	port_sys_unlock();
}

/* -------------------------------------------------------------------------- */
void bar_wait( bar_t *bar )
/* -------------------------------------------------------------------------- */
{
	unsigned signal;

	assert(bar);
	assert(bar->count);

	signal = bar->signal;

	port_sys_lock();

	if (--bar->count == 0)
	{
		bar->count = bar->limit;
		bar->signal++;
	}

	port_sys_unlock();

	while (bar->signal == signal) core_ctx_switch();
}

/* -------------------------------------------------------------------------- */