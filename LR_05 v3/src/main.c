#include "../inc/list_work.h"
#include "../inc/list_model.h"
int main()
{
	//double time_time = 0;
	srand(time(NULL));
	simulation();
	/*for (int i = 0 ; i < 100; i++)
	{
		time_time = random_time(0, 7);
		//printf("%lf, %d, %lf\n", time_time, rand(), ((double)rand())/RAND_MAX);
	}*/
	return OK;
}