
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

// Rellenar la Matriz con la palabra Vacio para verificar que no haya citas
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
    int k, i, j;
    // EL usuario debe mencionar si desea ingresar una cita
    char resp[4];
    printf("Desea ingresar datos? (si/no):\n");
    fgets(resp, sizeof(resp), stdin);
    resp[strcspn(resp, "\n")] = '\0';
    if (strcmp(resp, "no") == 0)
    {
        return;
    }

    // Eleccion del m'edico
    printf("Ingrese el numero del medico:");
    scanf("%d", &k);
    getchar();
    // Elecion de hora
    printf("Ingrese el número de hora: ");
    scanf("%d", &i);
    getchar();

    printf("Ingrese el número de día : ");
    scanf("%d", &j);
    getchar();

    // Ingresar la información para la cita
    printf("Ingrese la información para la cita del médico %d, hora %d, día %d:\n", k, i, j);
    printf("Nombre del paciente: ");
    fgets(MatrizCitas[k - 1][i - 1][j - 1].paciente, sizeof(MatrizCitas[k - 1][i - 1][j - 1].paciente), stdin);

    // Limpiar el buffer del teclado después de la entrada de datossi

    while (getchar() != '\n')
        ;

    // Eliminar el salto de línea del final de la cadena
    MatrizCitas[k - 1][i - 1][j - 1].paciente[strcspn(MatrizCitas[k - 1][i - 1][j - 1].paciente, "\n")] = '\0';
}

// Creo una matriz 3D para que la profundidad indique los m'edicos , la fila los horarios y la columna los d'ias
// GENERO LAS NOTAS ALEATORIAMENTE

void MedicosGenerales(int medicosG, int horarios, int dias, struct CitaMedica MatrizCitas[medicosG][horarios][dias])
{
    // Dias Semana
    char *SemanaDias[] = {"Lun", "Mar", "Mie", "Jue", "Vie"};
    printf("\t    ");
    for (int d = 0; d < dias; d++)
    {
        printf("%s\t|", SemanaDias[d]);
    }
    printf("\n");
    for (int k = 0; k < medicosG; k++)
    {
        printf("***Medicos %d:\n", k + 1);

        for (int i = 0; i < horarios; i++)
        {
            printf("Hora %d:\t", i + 1);
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
