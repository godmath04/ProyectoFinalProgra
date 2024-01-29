#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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

char *MedicosGenerales[] = {"Alvaro Roldan", "Naye Garcia", "Mikaela Suarez"};
char *MedicosOdonto[] = {"Luis Pineda", "Paco Manuel", "Natalia Remache"};
char *MedicosCardiologos[] = {"Galo Guevara", "Rafaela Yanouch", "Mikaela Estevez"};
char *MedicosOtros[] = {"Galo Manuel", "Estefania Paez", "Mikaela Estevez", "Luciana Zapato"};
char *Especialidades[] = {"Medicina General", "Odontologia", "Cardiologia", "Otros"};

void InicializarMatriz(struct CitaMedica MatrizCitas[][MAX_MEDICOS][MAX_HORARIOS][MAX_DIAS], int especialidades, int medicosPorEspecialidad, int horarios, int dias)
{
    for (int e = 0; e < especialidades; e++)
    {
        for (int k = 0; k < medicosPorEspecialidad; k++)
        {
            for (int i = 0; i < horarios; i++)
            {
                for (int j = 0; j < dias; j++)
                {
                    strcpy(MatrizCitas[e][k][i][j].paciente, "---");
                    MatrizCitas[e][k][i][j].pacienteEdad = 0;
                }
            }
        }
    }
}

void VaciosGenerales(char *medicosEspecialidad[], int especialidad, int medicosPorEspecialidad, int horarios, int dias, struct CitaMedica MatrizCitas[][MAX_MEDICOS][MAX_HORARIOS][MAX_DIAS])
{
    char *SemanaDias[] = {"1.Lun", "2.Mar", "3.Mie", "4.Jue", "5.Vie"};

    printf("%-15s", "");
    for (int d = 0; d < dias; d++)
    {
        printf("%-15s|", SemanaDias[d]);
    }
    printf("\n");

    for (int k = 0; k < medicosPorEspecialidad; k++)
    {
        printf("%d. Dr '%s' (%s):\n", k + 1, medicosEspecialidad[k], MatrizCitas[especialidad][k][0][0].especialidad);

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

void IngresarCitas(char *medicosEspecialidad[], int especialidad, int medicosPorEspecialidad, int horarios, int dias, struct CitaMedica MatrizCitas[][MAX_MEDICOS][MAX_HORARIOS][MAX_DIAS])
{
    char resp[4];
    char *SemanaDias[] = {"1.Lun", "2.Mar", "3.Mie", "4.Jue", "5.Vie"};

    do
    {
        int k, i, j, d;

        printf("Desea ingresar datos? (si/no):\n");
        scanf("%3s", resp);

        while (getchar() != '\n')
            ;

        if (strcmp(resp, "si") == 0)
        {
            printf("Ingrese el numero del medico: ");
            scanf("%d", &k);
            d = k - 1;
            getchar();

            printf("Ingrese el turno al que desea acceder: ");
            scanf("%d", &i);
            getchar();

            printf("Ingrese el numero de dia:\n1. Lunes\n2.Martes\n3.Miercoles\n4.Jueves\n5.Viernes\n");
            scanf("%d", &j);
            getchar();

            if (k >= 1 && k <= medicosPorEspecialidad && i >= 1 && i <= horarios && j >= 1 && j <= dias)
            {
                if (strcmp(MatrizCitas[especialidad][k - 1][i - 1][j - 1].paciente, "---") == 0)
                {
                    printf("Ingrese la informacion para la cita con el medico '%s', en el turno %d, el dia %s:\n", medicosEspecialidad[k - 1], i, SemanaDias[j-1]);
                    printf("Nombre del paciente: ");
                    fgets(MatrizCitas[especialidad][k - 1][i - 1][j - 1].paciente, sizeof(MatrizCitas[especialidad][k - 1][i - 1][j - 1].paciente), stdin);

                    while (getchar() != '\n')
                        ;

                    MatrizCitas[especialidad][k - 1][i - 1][j - 1].paciente[strcspn(MatrizCitas[especialidad][k - 1][i - 1][j - 1].paciente, "\n")] = '\0';

                    printf("Edad: ");
                    scanf("%d", &MatrizCitas[especialidad][k - 1][i - 1][j - 1].pacienteEdad);
                    getchar();
                    while (getchar() != '\n')
                        ;
                    strcpy(MatrizCitas[especialidad][k - 1][i - 1][j - 1].especialidad, medicosEspecialidad[especialidad]);
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

void MostrarCitas(char *medicosEspecialidad[], int especialidad, int medicosPorEspecialidad, int horarios, int dias, struct CitaMedica MatrizCitas[][MAX_MEDICOS][MAX_HORARIOS][MAX_DIAS])
{
    char *SemanaDias[] = {"1.Lun", "2.Mar", "3.Mie", "4.Jue", "5.Vie"};

    printf("%-10s", "");
    for (int d = 0; d < dias; d++)
    {
        printf("%-10s\t|", SemanaDias[d]);
    }
    printf("\n");

    for (int k = 0; k < medicosPorEspecialidad; k++)
    {
        printf("%d. Dr/a. '%s':\n", k + 1, medicosEspecialidad[k], MatrizCitas[especialidad][k][0][0].especialidad);

        for (int i = 0; i < horarios; i++)
        {
            printf("Turno %d:\t", i + 1);
            for (int j = 0; j < dias; j++)
            {
                printf("\'%s\' |", MatrizCitas[especialidad][k][i][j].paciente);
            }
            printf("\n");
        }
        printf("\n");
    }
}

void GuardarCitasEnArchivo(const char *nombreArchivo, struct CitaMedica MatrizCitas[][MAX_MEDICOS][MAX_HORARIOS][MAX_DIAS], int especialidades, int medicosPorEspecialidad, int horarios, int dias)
{
    FILE *archivo = fopen(nombreArchivo, "a");

    if (archivo == NULL)
    {
        perror("Error al abrir el archivo");
        return;
    }

    for (int e = 0; e < especialidades; e++)
    {
        for (int k = 0; k < medicosPorEspecialidad; k++)
        {
            for (int i = 0; i < horarios; i++)
            {
                for (int j = 0; j < dias; j++)
                {
                    if (strcmp(MatrizCitas[e][k][i][j].paciente, "---") != 0)
                    {
                        fprintf(archivo, "Especialidad: %s\tMedico: %s\tTurno: %d\tDia: %d\tPaciente: %s\tEdad: %d\n",
                                Especialidades[e], // Utilizar el array de especialidades
                                MatrizCitas[e][k][i][j].nombreMedico,
                                i + 1,
                                j + 1,
                                MatrizCitas[e][k][i][j].paciente,
                                MatrizCitas[e][k][i][j].pacienteEdad);
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

int main()
{
    const int especialidades = 4;
    const int medicosPorEspecialidad = 3;
    const int horarios = 6;
    const int dias = 5;
    int menuprincipal;
    struct CitaMedica MatrizCitas[especialidades][MAX_MEDICOS][MAX_HORARIOS][MAX_DIAS];
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

            switch (especialidadElegida)
            {
            case 0:
                printf("***** LISTADO DE DOCTORES Y FECHAS DISPONBLES MEDICINA GENERAL*****\n");
                break;
            case 1:
                printf("***** LISTADO DE DOCTORES Y FECHAS DISPONBLES ODONTOLOGIA*****\n");
                break;
            case 2:
                printf("***** LISTADO DE DOCTORES Y FECHAS DISPONBLES CARDIOLOGIA*****\n");
                break;
            case 3:
                printf("***** LISTADO DE DOCTORES Y FECHAS DISPONBLES OTRAS ESPECIALIDADES*****\n");
                break;
            default:
                printf("Opción no valida.\n");
                return 1;
            }

            char **medicosEspecialidad;
            switch (especialidadElegida)
            {
            case 0:
                medicosEspecialidad = MedicosGenerales;
                break;
            case 1:
                medicosEspecialidad = MedicosOdonto;
                break;
            case 2:
                medicosEspecialidad = MedicosCardiologos;
                break;
            case 3:
                medicosEspecialidad = MedicosOtros;
                break;
            default:
                printf("Opción no valida.\n");
                return 1;
            }

            InicializarMatriz(MatrizCitas, especialidades, medicosPorEspecialidad, horarios, dias);
            VaciosGenerales(medicosEspecialidad, especialidadElegida, medicosPorEspecialidad, horarios, dias, MatrizCitas);
            IngresarCitas(medicosEspecialidad, especialidadElegida, medicosPorEspecialidad, horarios, dias, MatrizCitas);
            MostrarCitas(medicosEspecialidad, especialidadElegida, medicosPorEspecialidad, horarios, dias, MatrizCitas);
            GuardarCitasEnArchivo("DATOS.txt", MatrizCitas, especialidades, medicosPorEspecialidad, horarios, dias);

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