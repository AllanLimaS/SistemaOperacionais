#include <omp.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
   int thread_id;

    // inicializa o bloco em paralelo 
    #pragma omp parallel
    {
        // A variavel "thread_id" recebe a identificação de cada thread
        thread_id = omp_get_thread_num();
        printf("I am a parallel region of Thread: %d\n", thread_id);
    }

    return 0;
}
