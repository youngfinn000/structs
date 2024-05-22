#include <stdio.h>
#include <stdlib.h>
#include "string.h"

/// estructura /////////////////////////////////////////
typedef struct
{
    int matricula;
    char nombre[30];
    char genero; // m, f, o
} stAlumno;

///   PROTOTIPADO ///////////////////////////

///1//////////////////////////////////////////////////////
stAlumno CargarAlumno();
int CargarArrStruct(stAlumno A[], int dimension);
///2//////////////////////////////////////////////////////
void MostrarAlumno(stAlumno A);
void MostarArrStruct(stAlumno A[], int validos);
///3//////////////////////////////////////////////////////
void BuscarAlumno(stAlumno A[], int validos, int matricula);
///4//////////////////////////////////////////////////////
void OrdenarPorSeleccion(stAlumno A[], int  validos);
void MostarArrStruct(stAlumno A[], int validos);
///5//////////////////////////////////////////////////////
void MostarGenero(stAlumno A[], int validos, char Eleccion);
///6//////////////////////////////////////////////////////
void agregarAlumno(stAlumno A[], int *validos);
///7//////////////////////////////////////////////////////
void OrdenarPorInserccion(stAlumno A[], int validos);
///8
int ContarGenero(stAlumno A[], int validos, char genero);

int main()
{
    int validos=0, opcion=0, matricula=0, resul=0, flag=0;
    char continuar='s', GeneroBuscado;

    stAlumno ArrAlumno[30];

    do
    {
        printf("---MENU---");
        printf("\n1.Cargar Alumnos\n2.Mostrar Alumnos\n3.Buscar Alumno\n4.Ordenar Alumnos.\n5.Filtrar alumnos por genero.\n");
        printf("6.Agregar Alumno.\n7.Ordenar Por Inserccion.\n8.Contar un genero especifico.\n");
        printf("\nIngrese la opcion que desea realizar: \n");
        scanf("%d", &opcion);

        switch(opcion)
        {
        case 1:///1//////////////////////////////////////////////////////
            validos= CargarArrStruct(ArrAlumno, 30);
            printf("\nSe cargaron %d alumnos.\n", validos);
            break;
        case 2:///2//////////////////////////////////////////////////////
            MostarArrStruct(ArrAlumno, validos);
            break;
        case 3:///3//////////////////////////////////////////////////////
            printf("\nIngrese la matricula que desea buscar: \n");
            scanf("%d", &matricula);

            BuscarAlumno(ArrAlumno, validos, matricula);
            break;
        case 4:///4//////////////////////////////////////////////////////
            printf("\nOrdenando alumnos.\n");
            OrdenarPorSeleccion(ArrAlumno, validos);
            MostarArrStruct(ArrAlumno, validos);
            break;
        case 5:///5//////////////////////////////////////////////////////
            printf("\nIngrese el genero que desea mostrar: (m/f/o)\n");
            fflush(stdin);
            scanf("%c", &GeneroBuscado);

            MostarGenero(ArrAlumno, validos, GeneroBuscado);
            break;
        case 6:///6//////////////////////////////////////////////////////
            agregarAlumno(ArrAlumno, &validos);
            MostarArrStruct(ArrAlumno, validos);
            break;
        case 7:///7//////////////////////////////////////////////////////
            OrdenarPorInserccion(ArrAlumno, validos);
            MostarArrStruct(ArrAlumno, validos);
            break;
        case 8:///8//////////////////////////////////////////////////////
            printf("\nQue genero desea contar? (m/f/o)\n");
            fflush(stdin);
            scanf("%c", &GeneroBuscado);

            resul=ContarGenero(ArrAlumno, validos, GeneroBuscado);
            printf("\nSe encontraron %d del mismo genero.\n", resul);
            break;
        default:
            printf("\nERROR: Ingrese una opcion valida\n");
            break;
        }
    }
    while(continuar=='s');

    return 0;
}

///**/////////////////////////////////////////////////////////////
///**FUNCIONES////////////////////////////////////////////////////
///**/////////////////////////////////////////////////////////////

///1/////////////////////////////////////////////////
stAlumno CargarAlumno()
{
    stAlumno A;

    printf("\nIngrese la matricula del alumno: \n");
    scanf("%d", &A.matricula);

    printf("\nIngrese el nombre del alumno: \n");
    fflush(stdin);
    gets(A.nombre);

    printf("\nIngrese el genero del alumno (m/f/o)\n");
    fflush(stdin);
    scanf("%c", &A.genero);

    return A;
}

int CargarArrStruct(stAlumno A[], int dimension)
{
    int validos=0;
    char continuar='s';

    while(validos<dimension && continuar=='s')
    {
        A[validos]=CargarAlumno();
        validos++;

        printf("\Desea seguir cargando alumnos? (s|n)");
        fflush(stdin);
        scanf("%c", &continuar);
    }
    return validos;
}

///2////////////////////////////////////////////////
void MostrarAlumno(stAlumno A)
{
    printf("\nLa matricula del alumno es: %d\n", A.matricula);
    printf("\nEl nombre del alumno es: %s\n", A.nombre);
    printf("\nEl genero del alumno es: %c\n", A.genero);
}

void MostarArrStruct(stAlumno A[], int validos)
{
    int i=0;

    for(i=0; i<validos; i++)
    {
        MostrarAlumno(A[i]);
        printf("\n--------------------\n");
    }
}

///3////////////////////////////////////////////////
void BuscarAlumno(stAlumno A[], int validos, int matricula)
{
    int i=0;

    while(i<validos)
    {
        if(A[i].matricula==matricula)
        {
            printf("\n--------------------\n");
            MostrarAlumno(A[i]);
            printf("\n--------------------\n");
            return 0;
        }
        else
        {
            i++;
        }
    }
}

///4////////////////////////////////////////////////
int SubFuncion(stAlumno A[], int validos,int pos)
{
    int menor=A[pos].matricula;
    int PosMenor=pos;
    int index=pos+1;

    while(index<validos)
    {
        if(menor>A[index].matricula)
        {
            menor=A[index].matricula;
            PosMenor=index;
        }
        else
        {
            index++;
        }
    }
    return PosMenor;
}

void OrdenarPorSeleccion(stAlumno A[], int  validos)
{
    int aux;
    int Posmenor;
    int i=0;

    while(i<validos-1)
    {
        Posmenor= SubFuncion(A, validos, i);

        aux=A[Posmenor].matricula;

        A[Posmenor].matricula=A[i].matricula;

        A[i].matricula=aux;

        i++;
    }
}

///5////////////////////////////////////////////////
int SubFuncionG(stAlumno A[], int validos, char Eleccion)
{
    int flag=0;
    int i=0;

    for(i=0; i<validos; i++)
    {
        if(A[i].genero==Eleccion && flag==0)
        {
            flag=1;
        }
    }
    return flag;
}

void MostarGenero(stAlumno A[], int validos, char Eleccion)
{
    int i=0,flag=0;

    flag=SubFuncionG(A, validos, Eleccion);

    if(flag==1)
    {
        for(i=0; i<validos; i++)
        {
            if(A[i].genero == Eleccion)
            {
                MostrarAlumno(A[i]);
            }
        }
    }
}

///6//////////////////////////////////////////////////
void agregarAlumno(stAlumno A[], int *validos)
{
    A[*validos] = CargarAlumno(A[*validos]);
    (*validos)++;
}

///7//////////////////////////////////////////////////
void OrdenarPorInserccion(stAlumno A[], int validos)
{
    int i, j; //Variables para recorrer
    stAlumno temp;//Crear espacio de alumno temporal

    for(i=1; i<validos; i++) //Se recorre desde la pos 1, ya que la pos 0 sera guardada
    {
        temp=A[i];//Se guarda para la pos 0
        j = i -1;// j sera la ultima posicion del arreglo

        while(j>=0 && strcmp(A[j].nombre, temp.nombre) > 0) // Para que j no se pase del inicio del arreglo y compara el nombre siguiente con el temporal
        {
            A[j+1] = A[j];//Mueve el elemento A[j] hacia adelante para crear un espacio e insertar temp en la pos correcta
            j--;//Decrece el valor de j un numero hacia atras
        }
        A[j+1]=temp;//Inserta temp en la pos correcta
    }
}

///8//////////////////////////////////////////////////
int ContarGenero(stAlumno A[], int validos, char genero)
{
    int i=0, contador=0;


    for(i=0; i<validos; i++)
    {
        if(A[i].genero==genero)
        {
            contador++;
        }
    }
    return contador;
}
