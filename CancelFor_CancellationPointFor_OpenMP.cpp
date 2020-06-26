#include <iostream>
#include <omp.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>

using namespace std;


int main()
{

	//const int dimensione=100000000;

	int* vettore = new int [100000000];

	for (int i=0;i<100000000;i++)
		{
			vettore[i]=i;
		}

	double startTime = omp_get_wtime();
	int obiettivo = 5000000;
	omp_set_num_threads(4);

	#pragma omp parallel
	{
		#pragma omp for
		for (int i=0;i<100000000;i++)
		{
			if (vettore[i]==obiettivo)
				{
					#pragma omp cancel for//break;
				}
			#pragma omp cancellation point for//cancel point
		}
	}
	double stopTime=omp_get_wtime();
	cout << "Tempo impiegato: " << (stopTime - startTime) * 1000 << " millisecondi";

	delete[]vettore;
	return 0;
}
