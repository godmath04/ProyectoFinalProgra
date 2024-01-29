#include <stdio.h>
#include <string.h>

#define MAX_MEDICOS 3
#define MAX_HORARIOS 6
#define MAX_DIAS 5
#define MAX_ESPECIALIDAD 50

struct CitaMedica
{
    char paciente[50];
    int pacienteEdad;
    char especialidad[MAX_ESPECIALIDAD];
    int dia;
    int hora;
    char nombreMedico[50];
};
// Cada especilidad tiene 3 medicos por lo que se multiplica el valor de la especilidad elegida * MAX medicos 
// De esta forma se obtiene el valor para iniciar el arreglo
// Si es la especilidad es 0 * 3 = 0 se inicia en la posicion 0 hasta la 3
// Especilidad es 3 * 3 se inicia en la posicion 9 

char *Medicos[] = {"General Garcia", "General Comandante", "General Mikaela",
                   "Odonto Luis", "Odonto Manuela", "Odonto Paco",
                   "Cardio Guevara", "Cardio Rafaela", "Cardio Estevez",
                   "Otro Gomez", "Otro Paez", "OtroZapato"};

char *Especialidades[] = {"Medicina General", "Odontologia", "Cardiologia", "Otros"};

void InicializarMatriz(struct CitaMedica MatrizCitas[][MAX_MEDICOS][MAX_HORARIOS][MAX_DIAS], int especialidades, int horarios, int dias);

void MostrarDisponibilidad(char *medicosEspecialidad[], int especialidad, int horarios, int dias, struct CitaMedica MatrizCitas[][MAX_MEDICOS][MAX_HORARIOS][MAX_DIAS]);

void IngresarCitas(char *medicosEspecialidad[], int especialidad, int horarios, int dias, struct CitaMedica MatrizCitas[][MAX_MEDICOS][MAX_HORARIOS][MAX_DIAS]);

void GuardarCitasEnArchivo(const char *nombreArchivo, struct CitaMedica MatrizCitas[][MAX_MEDICOS][MAX_HORARIOS][MAX_DIAS], int especialidades, int horarios, int dias);

void LeerArchivo();

int main()
{
    const int especialidades = 4;
    const int horarios = 6;
    const int dias = 5;
    int menuprincipal;
    struct CitaMedica MatrizCitas[especialidades][MAX_MEDICOS][MAX_HORARIOS][MAX_DIAS];
    printf("*******BIENVENIDO A MEDIPLANNER******\n");
    printf("Que te gustaria realizar hoy?\n");
    printf("1. Ingreso Pacientes\n2. Mostrar pacientes\n3.Salir\n");
    scanf("%d", &menuprincipal);

    while (menuprincipal != 3)
    {
        if (menuprincipal == 1)
        {
            printf("Elija la especialidad:\n1.Medicina General\n2.Odontologia\n3.Cardiologia\n4.Otros\n");
            int especialidadElegida;
            scanf("%d", &especialidadElegida);
            especialidadElegida--;

            if (especialidadElegida >= 0 && especialidadElegida < especialidades)
            {
                InicializarMatriz(MatrizCitas, especialidades, horarios, dias);
                // Se usa la cadena char de Medicos para elegirlos y mostrarlos
                MostrarDisponibilidad(&Medicos[especialidadElegida * MAX_MEDICOS], especialidadElegida, horarios, dias, MatrizCitas);
                IngresarCitas(&Medicos[especialidadElegida * MAX_MEDICOS], especialidadElegida, horarios, dias, MatrizCitas);
                GuardarCitasEnArchivo("DATOS.txt", MatrizCitas, especialidades, horarios, dias);
            }
            else
            {
                printf("Opción no válida.\n");
            }

            printf("Que desea realizar ahora?\n");
            printf("1. Ingreso Pacientes\n2. Mostrar pacientes\n3.Salir\n");
            scanf("%d", &menuprincipal);
        }
        else if (menuprincipal == 2)
        {
            printf("Se mostraran los pacientes.\n");
            LeerArchivo();
            printf("\nFin de la visualizacion de datos.\n");
            printf("Que desea realizar ahora?\n");
            printf("1. Ingreso Pacientes\n2. Mostrar pacientes\n3.Salir\n");
            scanf("%d", &menuprincipal);
        }
        else
        {
            printf("Adios.\n");
        }
    }

    return 0;
}

void InicializarMatriz(struct CitaMedica MatrizCitas[][MAX_MEDICOS][MAX_HORARIOS][MAX_DIAS], int especialidades, int horarios, int dias)
{
    // Abrimos el archivo para verificar si existe y verificar el contenido, caso contrario lo creamos
    FILE *archivo = fopen("DATOS.txt", "r");

    if (archivo != NULL)
    {
        // Si el archivo existe, se carga los datos
        for (int e = 0; e < especialidades; e++)
        {
            for (int k = 0; k < MAX_MEDICOS; k++)
            {
                for (int i = 0; i < horarios; i++)
                {
                    for (int j = 0; j < dias; j++)
                    {
                        fscanf(archivo, "Especialidad: %s\tMedico: %s\tTurno: %d\tDia: %d\tPaciente: %s\tEdad: %d\n",
                                MatrizCitas[e][k][i][j].especialidad, MatrizCitas[e][k][i][j].nombreMedico,
                                &MatrizCitas[e][k][i][j].hora, &MatrizCitas[e][k][i][j].dia,
                                MatrizCitas[e][k][i][j].paciente, &MatrizCitas[e][k][i][j].pacienteEdad);
                    }
                }
            }
            fclose(archivo);
            return; // Cuando los datos se carga, la funcion se cierra aqui
        }
    }

    // Dado que no existe, se inicializa la matriz
    for (int e = 0; e < especialidades; e++)
    {
        for (int k = 0; k < MAX_MEDICOS; k++)
        {
            for (int i = 0; i < horarios; i++)
            {
                for (int j = 0; j < dias; j++)
                {
                    // Es importante inicializar con --- porque dicha cadena sirve para comprobar el ingreso del resto de datos
                    strcpy(MatrizCitas[e][k][i][j].paciente, "---");
                    MatrizCitas[e][k][i][j].pacienteEdad = 0;
                }
            }
        }
    }
}

void MostrarDisponibilidad(char *medicosEspecialidad[], int especialidad, int horarios, int dias, struct CitaMedica MatrizCitas[][MAX_MEDICOS][MAX_HORARIOS][MAX_DIAS])
{
    printf("***** LISTADO DE DOCTORES Y FECHAS DISPONBLES %s*****\n", Especialidades[especialidad]);

    for (int k = 0; k < MAX_MEDICOS; k++)
    {
        printf("%d. Dr/a. '%s':\n", k + 1, medicosEspecialidad[k]);

        for (int i = 0; i < horarios; i++)
        {
            printf("Turno %d:\t", i + 1);
            for (int j = 0; j < dias; j++)
            {
                printf("%-15s|", MatrizCitas[especialidad][k][i][j].paciente);
            }
            printf("\n");
        }
        printf("\n");
    }
}

void IngresarCitas(char *medicosEspecialidad[], int especialidad, int horarios, int dias, struct CitaMedica MatrizCitas[][MAX_MEDICOS][MAX_HORARIOS][MAX_DIAS])
{
    char resp[4];

    do
    {
        int k, i, j;

        printf("Desea ingresar datos? (si/no):\n");
        scanf("%3s", resp);

        if (strcmp(resp, "si") == 0)
        {
            printf("Ingrese el numero del medico: ");
            scanf("%d", &k);

            printf("Ingrese el turno al que desea acceder: ");
            scanf("%d", &i);

            printf("Ingrese el numero de dia (1:Lunes-5:Viernes):\n");
            scanf("%d", &j);

            if (k >= 1 && k <= MAX_MEDICOS && i >= 1 && i <= horarios && j >= 1 && j <= dias)
            {
                if (strcmp(MatrizCitas[especialidad][k - 1][i - 1][j - 1].paciente, "---") == 0)
                {
                    printf("Ingrese la informacion para la cita con el medico '%s', en el turno %d, el dia %d:\n", medicosEspecialidad[k - 1], i, j);
                    printf("Nombre del paciente: ");
                    scanf("%s", MatrizCitas[especialidad][k - 1][i - 1][j - 1].paciente);
                    fflush(stdin);
                    printf("Edad: ");
                    scanf("%d", &MatrizCitas[especialidad][k - 1][i - 1][j - 1].pacienteEdad);

                    strcpy(MatrizCitas[especialidad][k - 1][i - 1][j - 1].especialidad, Especialidades[especialidad]);
                    strcpy(MatrizCitas[especialidad][k - 1][i - 1][j - 1].nombreMedico, medicosEspecialidad[k - 1]);
                }
                else
                {
                    printf("La cita ya esta ocupada. Elija otra.\n");
                }
            }
            else
            {
                printf("Opción no válida. Por favor, elija nuevamente.\n");
            }
        }
    } while (strcmp(resp, "si") == 0);
}

void GuardarCitasEnArchivo(const char *nombreArchivo, struct CitaMedica MatrizCitas[][MAX_MEDICOS][MAX_HORARIOS][MAX_DIAS], int especialidades, int horarios, int dias)
{
    FILE *archivo = fopen(nombreArchivo, "w");
    if (archivo == NULL)
    {
        perror("Error al abrir el archivo");
        return;
    }

    for (int e = 0; e < especialidades; e++)
    {
        for (int k = 0; k < MAX_MEDICOS; k++)
        {
            for (int i = 0; i < horarios; i++)
            {
                for (int j = 0; j < dias; j++)
                {
                    if (strcmp(MatrizCitas[e][k][i][j].paciente, "---") != 0)
                    {
                        fprintf(archivo, "Especialidad: %s\tMedico: %s\tTurno: %d\tDia: %d\tPaciente: %s\tEdad: %d\n",
                                Especialidades[e], Medicos[k], i + 1, j + 1,
                                MatrizCitas[e][k][i][j].paciente, MatrizCitas[e][k][i][j].pacienteEdad);
                    }
                }
            }
        }
    }

    fclose(archivo);
}

void LeerArchivo()
{
    FILE *archivo = fopen("DATOS.txt", "r");

    if (archivo == NULL)
    {
        printf("No se pudo abrir el archivo 'DATOS.txt'\n");
        return;
    }

    printf("Pacientes Agendados:\n");

    char linea[1000];
    while (fgets(linea, sizeof(linea), archivo) != NULL)
    {
        if (strchr(linea, '-') == NULL)
        {
            printf("%s", linea);
        }
    }

    fclose(archivo);
}
