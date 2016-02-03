#include <stm32f4_discovery.h>
#include <os.h>

sem_t sem = SEM_INIT(0);

void slave()
{
	sem_wait(&sem);

	LED_Tick();
}

void master()
{
	tsk_delay(SEC);

	sem_give(&sem);
}

tsk_t sla = TSK_INIT(slave);
tsk_t mas = TSK_INIT(master);

int main()
{
	LED_Config();

	sys_init();
	tsk_start(&sla);
	tsk_start(&mas);
	tsk_stop();
}
