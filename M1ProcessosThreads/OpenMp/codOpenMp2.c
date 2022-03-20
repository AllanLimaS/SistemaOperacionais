#include <stdio.h>
#include <omp.h>

int main(int argc, char *argv[])
{
    int i, thread_id;
    int glob_nloops, priv_nloops;
    glob_nloops = 0;

    // Inicializa bloco de codigos em paralelo com variaveis privadas
    #pragma omp parallel private(priv_nloops, thread_id)
    {
        priv_nloops = 0;
        thread_id = omp_get_thread_num();

        #pragma omp for
        for (i=0; i<100000; ++i)
        {
            ++priv_nloops;
        }

        // utilizando a diretiva "critical", apenas uma thread poderá
		// executar este bloco de código por vez. 
        #pragma omp critical
        {
            printf("Thread %d is adding its iterations (%d) to sum (%d), ",
                   thread_id, priv_nloops, glob_nloops);
            // Os contadores privados são somados na variavel global.
			glob_nloops += priv_nloops;
            printf(" total nloops is now %d.\n", glob_nloops);
        }
    }
    printf("Total # loop iterations is %d\n",
           glob_nloops);
    return 0;
}