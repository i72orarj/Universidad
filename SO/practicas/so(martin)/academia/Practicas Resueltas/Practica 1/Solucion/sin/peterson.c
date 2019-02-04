// Solución al problema de la sección crítica para 2 procesos
// Algoritmo de Peterson

// Variables globales compartidas
typedef enum {
    PRIMERO, SEGUNDO
} TURNO;
BOOLEAN P1QuiereEntrar, P2QuiereEntrar;
TURNO TurnoProceso;

// Inicialización de variables
P1QuiereEntrar = P2QuiereEntrar = FALSE;
TurnoProceso = PRIMERO;

void Proceso1()
{
    extern BOOLEAN P1QuiereEntrar, P2QuiereEntrar;
    extern TURNO TurnoProceso;

    while (TRUE) {
	P1QuiereEntrar = TRUE;
	TurnoProceso = SEGUNDO;
	while (P2QuiereEntrar && TurnoProceso == SEGUNDO);

	//--------------------
	// SECCIÓN CRÍTICA
	//--------------------

	P1QuiereEntrar = FALSE;

	// Sección residual
    }
}

void Proceso2()
{
    extern BOOLEAN P1QuiereEntrar, P2QuiereEntrar;
    extern TURNO TurnoProceso;

    while (TRUE) {
	P2QuiereEntrar = TRUE;
	TurnoProceso = PRIMERO;
	while (P1QuiereEntrar && TurnoProceso == PRIMERO);

	//--------------------
	// SECCIÓN CRÍTICA
	//--------------------

	P2QuiereEntrar = FALSE;

	// Sección residual
    }
}
