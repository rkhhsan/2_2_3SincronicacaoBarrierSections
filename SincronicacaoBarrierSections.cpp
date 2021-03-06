/* 2.2.3 Sincronização
 * A sincronização dos threads deve ser evitada sempre que possível, devido a perda de performance
 * em códigos paralelos. Atenção, ela ocorre implicitamente no término da região paralela!
 * No seguinte código, o thread 1 é atrasado em 1 segundo,
 * de forma que ele é o último a imprimir. Verifique!
 */
#include <ctime>
#include <omp.h>
#include <iostream>

using namespace std;

// Variáveis Globais(shared)
char caracter;

int tid = 0;
int nt;
time_t now;
struct tm ts;
char buf[80];

int main(int argc, char *argv[]) {


    // Obtem o tempo corrente
    now = time(NULL);

    // Formata e imprime o tempo, "ddd yyyy-mm-dd hh:mm:ss zzz"
    ts = *localtime(&now);
    strftime(buf, sizeof(buf), "%a %d-%m-%Y %H:%M:%S %Z", &ts);
    printf("\n%s", buf);


#pragma omp parallel private(tid)
    {
        tid = omp_get_thread_num();
        nt = omp_get_num_threads();

        if (tid == nt - 1) {
            // delay 0.001s
            time_t t0 = time(NULL);
            while (time(NULL) - t0 < 0.1) {
            }
        }

        printf("\n Processo %d/%d.", tid, nt);
    }

    cout << "\n\n Tecle uma tecla e apos Enter para finalizar...\n";
    cin >> caracter;

    return 0;
}

