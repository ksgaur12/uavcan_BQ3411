#include <modules/worker_thread/worker_thread.h>
#include <modules/uavcan_debug/uavcan_debug.h>
#include <modules/driver_bq3411_i2c/driver_bq3411_i2c.h>

#define WT hpwork_thread
WORKER_THREAD_DECLARE_EXTERN(WT)

static struct worker_thread_timer_task_s bq3411_test_task;
static void bq3411_task_func(struct worker_thread_timer_task_s* task);

static const I2CConfig i2cfg2 = {
  STM32_TIMINGR_PRESC(8U)  |            /* 72MHz/9 = 8MHz I2CCLK.           */
  STM32_TIMINGR_SCLDEL(3U) | STM32_TIMINGR_SDADEL(3U) |
  STM32_TIMINGR_SCLH(3U)   | STM32_TIMINGR_SCLL(9U),
  0,
  0
};

BQ3411_dev_t bq3411;

RUN_AFTER(INIT_END) {

    bq3411.bus = &I2CD2;
    bq3411.bus_config = &i2cfg2;
    bq3411.address = BQ3411_I2C_ADDR;

    bq3411_init(&bq3411);

    worker_thread_add_timer_task(&WT, &bq3411_test_task, bq3411_task_func, NULL, MS2ST(10), true);

}

static void bq3411_task_func(struct worker_thread_timer_task_s* task) {
    (void)task;

    blink_leds();
   // bq3411_read_data(&bq3411);
   // get_data(&lis3mdl);
}
