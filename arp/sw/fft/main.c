#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define LOCK_ADDR (8*1024*1024)
#define PSIN_ADDR (9*1024*1024)
#define PCOS_ADDR (10*1024*1024)
#define NUM_PROCS 8

int _main() {
    unsigned MAXSIZE = 8;
    unsigned MAXWAVES = 100;
    int i,j;
    float *RealIn;
    float *ImagIn;
    float *RealOut;
    float *ImagOut;
    float *coeff;
    float *amp;
    int invfft=0;

    volatile const int * lock = (int *) LOCK_ADDR;
    int waves, length;
    char mode[10];

 srand(1);

 RealIn=(float*)malloc(sizeof(float)*MAXSIZE);
 ImagIn=(float*)malloc(sizeof(float)*MAXSIZE);
 RealOut=(float*)malloc(sizeof(float)*MAXSIZE);
 ImagOut=(float*)malloc(sizeof(float)*MAXSIZE);
 coeff=(float*)malloc(sizeof(float)*MAXWAVES);
 amp=(float*)malloc(sizeof(float)*MAXWAVES);

 /* Makes MAXWAVES waves of random amplitude and period */
	for(i=0;i<MAXWAVES;i++) 
	{
		coeff[i] = rand()%1000;
		amp[i] = rand()%1000;
	}
 for(i=0;i<MAXSIZE;i++) 
 {
   /*   RealIn[i]=rand();*/
	 RealIn[i]=0;
	 for(j=0;j<MAXWAVES;j++) 
	 {
		 /* randomly select sin or cos */
		 if (rand()%2)
		 {
		 		RealIn[i]+=coeff[j]*cos(amp[j]*i);
			}
		 else
		 {
		 	RealIn[i]+=coeff[j]*sin(amp[j]*i);
		 }
  	 ImagIn[i]=0;
	 }
 }

 /* regular*/
 fft_float (MAXSIZE,invfft,RealIn,ImagIn,RealOut,ImagOut);
 
 printf("RealOut:\n");
 for (i=0;i<MAXSIZE;i++)
   printf("%f \t", RealOut[i]);
 printf("\n");

printf("ImagOut:\n");
 for (i=0;i<MAXSIZE;i++)
   printf("%f \t", ImagOut[i]);
   printf("\n");

 free(RealIn);
 free(ImagIn);
 free(RealOut);
 free(ImagOut);
 free(coeff);
 free(amp);
 exit(0);

}

int main(int argc, char *argv[]) {
	unsigned MAXSIZE = 8;
	unsigned MAXWAVES = 100;
	int i,j;
	static float *RealIn;
	static float *ImagIn;
	static float *RealOut;
	static float *ImagOut;
	static float *coeff;
	static float *amp;
	int invfft=0;

	volatile const int * lock = (int *) LOCK_ADDR;
    volatile static int proc_index = 0, finished_procs = 0; 
    volatile int current_proc_index = 0;
    int waves_start, size_start;

 //Gets a unique index for each processor.
 while (*lock != 0);
 current_proc_index = proc_index;
 proc_index++;
 printf("Hello FFT! From processor %d\n", proc_index);
 *lock = 0;

 //One processor initializes the data.
 if (current_proc_index == 0) {
  RealIn=(float*)malloc(sizeof(float)*MAXSIZE);
  ImagIn=(float*)malloc(sizeof(float)*MAXSIZE);
  RealOut=(float*)malloc(sizeof(float)*MAXSIZE);
  ImagOut=(float*)malloc(sizeof(float)*MAXSIZE);
  coeff=(float*)malloc(sizeof(float)*MAXWAVES);
  amp=(float*)malloc(sizeof(float)*MAXWAVES);
 }

 //Another processor arrived here.
 finished_procs++;

 //All processors wait for the data to be initialized.
 while (finished_procs < NUM_PROCS);

 //Resets the counter in order to be able to wait for the processors to finish. 
 if (current_proc_index == 0) {
  finished_procs = 0;
 }

 //Gets a different seed for the rand() function for each processor.
 srand(time(NULL) * current_proc_index);
 
 //Gets a portion of the data for each processor.
 waves_start = current_proc_index * MAXWAVES / NUM_PROCS;
 size_start = current_proc_index * MAXSIZE / NUM_PROCS;


 // Makes MAXWAVES waves of random amplitude and period, dividing the work 
 // between all the processors.
	for(i = waves_start; i < waves_start + (MAXWAVES/NUM_PROCS); i++) 
	{
		coeff[i] = rand()%1000;
		amp[i] = rand()%1000;
	}
 for(i = size_start; i < size_start + (MAXSIZE/NUM_PROCS); i++) 
 {
   /*   RealIn[i]=rand();*/
	 RealIn[i]=0;
	 for(j = waves_start; j < waves_start + (MAXWAVES/NUM_PROCS); j++) 
	 {
		 // Randomly select sine or cossine.
		 if (rand()%2)
		 {
		 		RealIn[i]+=coeff[j]*cos(amp[j]*i);
			}
		 else
		 {
		 	RealIn[i]+=coeff[j]*sin(amp[j]*i);
		 }
  	 ImagIn[i]=0;
	 }
 }

 /* regular*/
 if (current_proc_index == 0) {
  fft_float (MAXSIZE,invfft,RealIn,ImagIn,RealOut,ImagOut);
 }

 //Another processor finished.
 finished_procs++;

 //Wait for all processors to finish their part of the data.
 while (finished_procs < NUM_PROCS); 

 //Gets one processor to print the result and free memory.
 if (current_proc_index == 0) {
  printf("RealOut:\n");
  for (i=0;i<MAXSIZE;i++)
    printf("%f \t", RealOut[i]);
  printf("\n");

  printf("ImagOut:\n");
  for (i=0;i<MAXSIZE;i++)
    printf("%f \t", ImagOut[i]);
    printf("\n");
 
  free(RealIn);
  free(ImagIn);
  free(RealOut);
  free(ImagOut);
  free(coeff);
  free(amp);
 }
 
 exit(0);
}


