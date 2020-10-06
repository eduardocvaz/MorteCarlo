#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "mpi.h"

#define SEED time(NULL)

double montecarlo(double n) {

 srand( SEED );
 int i, count;
 double x,y,z,pi;

 count = 0;

 for(i = 0; i < n; ++i) 
 {

     x = (double)rand() / RAND_MAX;
     y = (double)rand() / RAND_MAX;
     z = x * x + y * y;
     if( z <= 1 ) count++;
 }

 pi = (double) count / n * 4;
 
 return(pi);
}


int main(void)
{

struct timeval start, stop;

double pi;
double n=200000000;

gettimeofday(&start, 0);
pi = montecarlo(n);
gettimeofday(&stop, 0);

FILE *fp;
		char outputFilename[] = "tempo_de_mm.txt";
	
		fp = fopen(outputFilename, "a");
		if (fp == NULL) {
			fprintf(stderr, "Can't open output file %s!\n", outputFilename);
			exit(1);
		}
fprintf(fp, "\t%1.2e ", (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec));

fclose(fp);

printf("Approximate PI = %1.15f\n", pi);
    
    return 0;
}