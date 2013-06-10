#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define LOCK_ADDR (8*1024*1024)

int _main() {

  printf ("Hello FFT!\n");

  return 0;
}

int main2() {
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
	float *RealIn;
	float *ImagIn;
	float *RealOut;
	float *ImagOut;
	float *coeff;
	float *amp;
	int invfft=0;

	volatile const int * lock = (int *) LOCK_ADDR;
    volatile static int proc_index = 0; 
    int current_proc_index = 0;
    int waves_start, size_start;

	/*if (argc<3)
	{
		printf("Usage: fft <waves> <length> -i\n");
		printf("-i performs an inverse fft\n");
		printf("make <waves> random sinusoids");
		printf("<length> is the number of samples\n");
		exit(-1);
	}
	else if (argc==4)
		invfft = !strncmp(argv[3],"-i",2);
	MAXSIZE=atoi(argv[2]);
	MAXWAVES=atoi(argv[1]);*/

    /*printf("Usage: <waves> <length (number of samples)> [i or n]\n");
    printf ("n indicates normal execution, i performs an inverse fft\n");

    scanf("%d %d %s", waves, length, mode);
	invfft = !strncmp(mode,"i",1);
	MAXSIZE=length;
	MAXWAVES=waves;*/

 srand(1);

 RealIn=(float*)malloc(sizeof(float)*MAXSIZE);
 ImagIn=(float*)malloc(sizeof(float)*MAXSIZE);
 RealOut=(float*)malloc(sizeof(float)*MAXSIZE);
 ImagOut=(float*)malloc(sizeof(float)*MAXSIZE);
 coeff=(float*)malloc(sizeof(float)*MAXWAVES);
 amp=(float*)malloc(sizeof(float)*MAXWAVES);

 //Gets a unique index for the current processor.
 while (*lock != 0);
 current_proc_index = proc_index;
 proc_index++;
 printf("Hello FFT! From processor %d\n", proc_index);
 *lock = 0; 

 //Gets a portion of the data for each processor.
 waves_start = current_proc_index * MAXWAVES / 8;
 size_start = current_proc_index * MAXSIZE / 8;


 /* Makes MAXWAVES waves of random amplitude and period */
	for(i = waves_start; i < waves_start + (MAXWAVES/8); i++) 
	{
		coeff[i] = rand()%1000;
		amp[i] = rand()%1000;
	}
 for(i = size_start; i < size_start + (MAXSIZE/8); i++) 
 {
   /*   RealIn[i]=rand();*/
	 RealIn[i]=0;
	 for(j = waves_start; j < waves_start + (MAXWAVES/8); j++) 
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
 
 //Gets one processor to print the result.
 while(*lock != 0);
 if (current_proc_index == 1) {
  printf("RealOut:\n");
  for (i=0;i<MAXSIZE;i++)
    printf("%f \t", RealOut[i]);
  printf("\n");

 printf("ImagOut:\n");
  for (i=0;i<MAXSIZE;i++)
    printf("%f \t", ImagOut[i]);
    printf("\n");
 }
 *lock = 0;

 free(RealIn);
 free(ImagIn);
 free(RealOut);
 free(ImagOut);
 free(coeff);
 free(amp);
 exit(0);


}


