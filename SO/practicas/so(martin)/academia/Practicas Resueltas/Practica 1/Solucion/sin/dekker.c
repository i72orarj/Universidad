// Soluci�n al problema de la secci�n cr�tica para 2 procesos
// Algoritmo de Dekker

// Variables globales compartidas
typedef enum {
    PRIMERO, SEGUNDO
} TURNO;
BOOLEAN P1QuiereEntrar, P2QuiereEntrar;
TURNO TurnoProceso;

// Inicializaci�n de variables
P1QuiereEntrar = P2QuiereEntrar = FALSE;
TurnoProceso = PRIMERO;

void Proceso1()
{
    extern BOOLEAN P1QuiereEntrar, P2QuiereEntrar;
    extern TURNO TurnoProceso;

    while (TRUE) {
	P1QuiereEntrar = TRUE;
	while (P2QuiereEntrar)
	    if (TurnoProceso == SEGUNDO) {
		P1QuiereEntrar = FALSE;
		while (TurnoProceso == SEGUNDO);
		P1QuiereEntrar = TRUE;
	    }

	//--------------------
	// SECCI�N CR�TICA
	//--------------------

	TurnoProceso = SEGUNDO;
	P1QuiereEntrar = FALSE;

	// Secci�n residual
    }
}

void Proceso2()
{
    extern BOOLEAN P1QuiereEntrar, P2QuiereEntrar;
    extern TURNO TurnoProceso;

    while (TRUE) {
	P2QuiereEntrar = TRUE;
	while (P1QuiereEntrar)
	    if (TurnoProceso == PRIMERO) {
		P2QuiereEntrar = FALSE;
		while (TurnoProceso == PRIMERO);
		P2QuiereEntrar = TRUE;
	    }

	//--------------------
	// SECCI�N CR�TICA
	//--------------------

	TurnoProceso = PRIMERO;
	P2QuiereEntrar = FALSE;

	// Secci�n residual
    }
}
