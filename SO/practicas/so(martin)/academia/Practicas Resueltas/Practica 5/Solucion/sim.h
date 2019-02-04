/* Límites. */
#define M 	20
#define N 	100
#define LAST_ID	1000
#define N_PLAN	2
#define FCFS	0
#define SJF	1

/* Tipos de datos. */
typedef struct
{
  int id;
  int tservicio;
  int stllegada;
  int ftllegada;
} tPROC;  

typedef enum
{
  algSJF, algFCFS
} tPLANIFICADOR;  

typedef struct
{
  tPLANIFICADOR tipo;
  int tespera;
} tINFO;  

/* Prototipos. */
void * GenerarProcesos (void *);
void * fcfs (void *);
void *sjf (void *);
void * Estadisticas (void *);
