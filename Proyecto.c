
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Estructura para la cita medica

struct CitaMedica
{
    char paciente[50];
    // int pacienteEdad;
    // char especialidad[50];
    // int dia;
    // int hora;
};

// Rellenar la Matriz con la palabra Vacio para indicar que no hay citas
void InicializarMatriz(struct CitaMedica MatrizCitas[][6][5], int medicosG, int horarios, int dias)
{
    for (int k = 0; k < medicosG; k++)
    {
        for (int i = 0; i < horarios; i++)
        {
            for (int j = 0; j < dias; j++)
            {
                strcpy(MatrizCitas[k][i][j].paciente, "VACIO");
            }
        }
    }
}
void IngresarCitas(int medicosG, int horarios, int dias, struct CitaMedica MatrizCitas[medicosG][horarios][dias])
{
    // Variables
    int k, i, j, d;
    char *Medicos[] = {"Pablo Villota", "Galo Guevara", "Rafalea Yanouch"};
    char *SemanaDias[] = {"1.Lun", "2.Mar", "3.Mie", "4.Jue", "5.Vie"};
    // EL usuario debe mencionar si desea ingresar una cita
    char resp[4];
    do
    {
        printf("Desea ingresar datos? (si/no):\n");
        fgets(resp, sizeof(resp), stdin);
        resp[strcspn(resp, "\n")] = '\0';

        // Limpiar el buffer del teclado después de la entrada de datos
        while (getchar() != '\n')
            ;

        // VERIFICAR QUE YA SE HAYA PUESTO EL NO
         if (strcmp(resp, "si") != 0)
        {
            break;
        }
        // Eleccion del m'edico
        printf("Ingrese el numero del medico:");
        scanf("%d", &k);
        d = k - 1;
        getchar();
        // Elecion de hora
        printf("Ingrese el turno al que desea acceder: ");
        scanf("%d", &i);
        getchar();

        printf("Ingrese el numero de dia:\n1. Lunes\n2.Martes\n3.Miercoles\n4.Jueves\n5.Viernes\n");
        scanf("%d", &j);
        getchar();

        // Ingresar la información para la cita
        printf("Ingrese la informacion para la cita con el medico \'%s\', en el turno %d, el dia %s:\n", Medicos[d], i, SemanaDias[j]);
        printf("Nombre del paciente: ");
        fgets(MatrizCitas[k - 1][i - 1][j - 1].paciente, sizeof(MatrizCitas[k - 1][i - 1][j - 1].paciente), stdin);

        // Limpiar el buffer del teclado después de la entrada de datossi

        while (getchar() != '\n')
            ;

        // Eliminar el salto de línea del final de la cadena
        MatrizCitas[k - 1][i - 1][j - 1].paciente[strcspn(MatrizCitas[k - 1][i - 1][j - 1].paciente, "\n")] = '\0';

    } while (strcmp(resp, "si") == 0);
}

// Creo una matriz 3D para que la profundidad indique los m'edicos , la fila los horarios y la columna los d'ias
// GENERO LAS NOTAS ALEATORIAMENTE

void MedicosGenerales(int medicosG, int horarios, int dias, struct CitaMedica MatrizCitas[medicosG][horarios][dias])
{
    // Dias Semana
    char *SemanaDias[] = {"1.Lun", "2.Mar", "3.Mie", "4.Jue", "5.Vie"};
    char *Medicos[] = {"Pablo Villota", "Galo Guevara", "Rafalea Yanouch"};
    printf("\t    ");
    for (int d = 0; d < dias; d++)
    {
        printf("%s\t|", SemanaDias[d]);
    }
    printf("\n");
    for (int k = 0; k < medicosG; k++)
    {
        printf("%d. Dr \'%s\':\n", k + 1, Medicos[k]);

        for (int i = 0; i < horarios; i++)
        {
            printf("Turno %d:\t", i + 1);
            for (int j = 0; j < dias; j++)
            {
                // MatrizCitas[k][i][j] = rand() % 11;
                printf("%-15s|", MatrizCitas[k][i][j].paciente);
            }
            printf("\n");
        }
        printf("\n");
    }
}

int main(int argc, char const *argv[])
{

    printf("***** LISTADO DE DOCTORES MEDICINA. GENERAL*****\n");
    const int horarios = 6, medicosG = 3, dias = 5;
    struct CitaMedica MatrizCitas[medicosG][horarios][dias];

    InicializarMatriz(MatrizCitas, medicosG, horarios, dias);
    MedicosGenerales(medicosG, horarios, dias, MatrizCitas);
    IngresarCitas(medicosG, horarios, dias, MatrizCitas);
    MedicosGenerales(medicosG, horarios, dias, MatrizCitas);
    printf("\n");

    return 0;
}
