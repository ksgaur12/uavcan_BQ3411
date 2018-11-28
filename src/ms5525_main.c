#include <modules/worker_thread/worker_thread.h>
#include <modules/uavcan_debug/uavcan_debug.h>

#define WT hpwork_thread
WORKER_THREAD_DECLARE_EXTERN(WT)


static struct worker_thread_timer_task_s ms5525_test_task;
static void ms5525_task_func(struct worker_thread_timer_task_s* task);

RUN_AFTER(INIT_END) {
    worker_thread_add_timer_task(&WT, &ms5525_test_task, ms5525_task_func, NULL, MS2ST(1000), true);
}

static void ms5525_task_func(struct worker_thread_timer_task_s* task) {
	(void)task;

	uavcan_send_debug_msg(LOG_LEVEL_DEBUG,"", "hello-sky");
}
