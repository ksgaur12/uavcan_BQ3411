#include <modules/worker_thread/worker_thread.h>
#include <modules/uavcan_debug/uavcan_debug.h>
#include <modules/driver_ms5525_i2c/driver_ms5525_i2c.h>

#define WT hpwork_thread
WORKER_THREAD_DECLARE_EXTERN(WT)


static struct worker_thread_timer_task_s ms5525_test_task;
static void ms5525_task_func(struct worker_thread_timer_task_s* task);


static I2CConfig i2cfg2 = {
  STM32_TIMINGR_PRESC(8U)  |            /* 72MHz/9 = 8MHz I2CCLK.           */
  STM32_TIMINGR_SCLDEL(3U) | STM32_TIMINGR_SDADEL(3U) |
  STM32_TIMINGR_SCLH(3U)   | STM32_TIMINGR_SCLL(9U),
  0,
  0
};

static MS5525_dev_t ms5525;


RUN_AFTER(INIT_END) {

	ms5525.bus = &I2CD2;
	ms5525.bus_config = &i2cfg2;
	ms5525.address = MS5525D0_I2C_ADDR_2;

	ms5525_i2c_init(&ms5525);

	worker_thread_add_timer_task(&WT, &ms5525_test_task, ms5525_task_func, NULL, MS2ST(10), true);

}

static void ms5525_task_func(struct worker_thread_timer_task_s* task) {
	(void)task;

	ms5525_calculate_airspeed(&ms5525);
	broadcast_MS5525(&ms5525);
}
