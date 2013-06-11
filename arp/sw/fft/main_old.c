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

    int waves, length;
    char mode[10];
    volatile static int proc_number = 1;

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

 /* Makes MAXWAVES waves of random amplitude and period */
	for(i=0;i<MAXWAVES;i++) 
	{
		coeff[i] = rand()%1000;
		amp[i] = rand()%1000;
	}
 i=-1;
 while(1) 
 {
	/*critical region*/
	while(*lock != 0);
	i++;
	if(i > MAXSIZE){
	   *lock = 0;
	   break;
    }

	*lock = 0;
	/*end of CR*/

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
 
 //Only one processor prints.
 while(*lock != 0);
 if (proc_number == 1) {
     proc_number++;
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

