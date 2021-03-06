/*
 * Copyright (c) 2018 Jie Zheng
 * the Timer framework will employ HEAP sort algorithm to determine expired
 * timer instance quickly: https://github.com/chillancezen/scalable-timer
 */

#include <x86/include/pit.h>
#include <x86/include/ioport.h>
#include <x86/include/interrupt.h>
#include <kernel/include/printk.h>
#include <kernel/include/task.h>
#include <kernel/include/jiffies.h>
#include <kernel/include/timer.h>

#define TIMER_RESOLUTION_HZ HZ
#define PIT_CHANNEL0_INTERRUPT_VECTOR (0x20 + 0)

static uint32_t pit_ticks = 0;
uint64_t jiffies = 0;

static void
refresh_pit_channel0(void)
{
    int divisor = OSCILLATPR_CHIP_FREQUENCY / TIMER_RESOLUTION_HZ;
    outb(PIT_CONTROL_PORT, 0x6 | 0x30);
    outb(PIT_CHANNEL0_PORT, divisor & 0xff);
    outb(PIT_CHANNEL0_PORT, (divisor >> 8) & 0xff);
}

static uint32_t
pit_handler(struct x86_cpustate * _cpu __used)
{
    uint32_t esp = (uint32_t)_cpu;
    pit_ticks++;
    jiffies++;
    // Schedule timers which is measured by Jiffies variable.
    // the timer resolution is 1 milisecond as it ticks with HZ = 1000
    schedule_timer();
    // Schedule tasks every 2 miliseconds, note we set HZ is 1000
    if (((pit_ticks % 2) == 0) && ready_to_schedule()) {
        esp = schedule(_cpu);
    }
    return esp;
}

void
pit_init(void)
{
    register_interrupt_handler(PIT_CHANNEL0_INTERRUPT_VECTOR,
        pit_handler,
        "Intel 8253 PIT");
    refresh_pit_channel0();
}
