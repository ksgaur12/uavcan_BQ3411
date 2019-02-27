#include <modules/worker_thread/worker_thread.h>
#include <modules/uavcan_debug/uavcan_debug.h>
#include <modules/driver_lis3mdl_i2c/driver_lis3mdl_i2c.h>

#define WT hpwork_thread
WORKER_THREAD_DECLARE_EXTERN(WT)

static struct worker_thread_timer_task_s mmc3416_test_task;
static void mmc3416_task_func(struct worker_thread_timer_task_s* task);

static const I2CConfig i2cfg2 = {
  STM32_TIMINGR_PRESC(8U)  |            /* 72MHz/9 = 8MHz I2CCLK.           */
  STM32_TIMINGR_SCLDEL(3U) | STM32_TIMINGR_SDADEL(3U) |
  STM32_TIMINGR_SCLH(3U)   | STM32_TIMINGR_SCLL(9U),
  0,
  0
};

LIS3MDL_dev_t lis3mdl;

RUN_AFTER(INIT_END) {

    lis3mdl.bus = &I2CD2;
    lis3mdl.bus_config = &i2cfg2;
    lis3mdl.address = LIS3MDL_I2C_ADDR;

    lis3mdl_init(&lis3mdl);

    worker_thread_add_timer_task(&WT, &mmc3416_test_task, mmc3416_task_func, NULL, MS2ST(10), true);

}

static void mmc3416_task_func(struct worker_thread_timer_task_s* task) {
    (void)task;

    blink_leds();
    get_data(&lis3mdl);
}
