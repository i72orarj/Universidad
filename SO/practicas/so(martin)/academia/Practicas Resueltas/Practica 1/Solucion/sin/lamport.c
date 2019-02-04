// Soluci�n al problema de la secci�n cr�tica para N procesos
// Algoritmo de Lamport

// Variables globales compartidas
BOOLEAN Eligiendo[N];
int Numero[N];

// Inicializaci�n de variables
Eligiendo[] = {FALSE, FALSE,..., FALSE};
Numero[] = {0, 0,..., 0};

// Proceso I-�simo
void Proceso(int I)
{
    extern BOOLEAN Eligiendo[N];
    extern int Numero[N];
    int j;

    while (TRUE) {
	Eligiendo[I] = TRUE;
	Numero[I] = max(Numero[0], Numero[1],..., Numero[N - 1]) + 1;
	Eligiendo[I] = FALSE;
	for (j = 0; j < N; j++) {
	    while (Eligiendo[j]);
	    while ((Numero[j] != 0) && (Numero[j], j) < (Numero[I], I));
	}

	//--------------------
	// SECCI�N CR�TICA
	//--------------------

	Numero[I] = 0;

	// Secci�n residual
    }
}
