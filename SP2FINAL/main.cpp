/*
Nombre: Eduardo Loya Montes de Oca - A01383049
Nombre: Roberto Abraham Perez Iga - A01384237
Nombre: Axel Amos Hernández Cárdenas - A00829837
Fecha de Creación: 04 de Septiembre del 2021

Ultima Versión: 10 0ct 2021

Descripción: El canal de Suez es un canal navegable que conecta el mar 
Mediterráneo con el mar Rojo a través de alrededor de 190 km, uniendo por 
un el lado del mar Mediterráneo desde el puerto Said hasta el golfo de Suez en 
el mar Rojo. Este canal es navegado entre 49 y 97 barcos diariamente.

Objetivos:
1. Solicite el nombre del archivo de entrada (Ej. canal.txt) y lo abra, almacenando los datos en dos 
   listas encadenadas, una para los que entran por el Mar Mediterráneo y otra para los buques que 
   entran por el mar Rojo.
2. Ordene en forma ascendente ambas listas encadenadas por UBI + Fecha
  (primero por UBI, al haber empate ordenar por fecha).
3. Guarde los datos ordenados en dos archivos de salida, cuyos nombres se solicitan al usuario, 
   uno de cada una de las listas encadenadas ordenadas.
4. Solicite al usuario la serie a buscar (los primeros tres caracteres de el UBI).
5. Despliegue mes por mes (empezando por el primer mes que venga un buque de esa serie y terminando en el mes
 de la última entrada) la cantidad de entrada de buques de esa serie por cada una de las entradas con el
 siguiente formato: <mes><año> <cantM> <cantR>
*/

#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// * Struct para la LL que guardara el .txt file
struct registro
{
    string fecha;
    string mes;
    string year;
    string hora;
    char entrada;
    string ubi;
    int fechaInt;
    string triple;
    bool operator>(const registro &otro) const
    {
        if (this->ubi == otro.ubi)
        {
            return this->fechaInt > otro.fechaInt;
        }
        return (this->ubi.compare(otro.ubi) > 0); // * Cuidado como compara 2 strings
    }

    bool operator<(const registro &otro) const
    {
        if (this->triple == otro.ubi.substr(0,3))
        {
            return this->fechaInt < otro.fechaInt;
        }
        return (this->triple.compare(otro.ubi.substr(0,3)) < 0); // * Cuidado como compara 2 strings
    }

    string ubisub(int i)
    {
        string ubic = ubi.substr(0, i);
        return ubic;
    }

    friend ostream &operator<<(ostream &os, const registro &otra);
};

// * Struct para el vector que guardara las entradas por mes
struct registroVect
{
    string mes;
    string year;
    int cantMed;
    int cantRoj;
};

#include "LinkedList.h"

// * Funcion que sobrecarga el operator <<
ostream &operator<<(ostream &os, const registro &otra)
{
    // Instrucciones
    os << otra.ubi << " " << otra.fecha << " "  << otra.hora << " " << otra.entrada << endl;
    return os;
}

// * Funcion que transforma un mes a INT
// ? Complejidad: O(1)
int mestoi(string m)
{

    if (m == "jan")
    {

        return 1;
    }
    if (m == "feb")
    {

        return 2;
    }
    if (m == "mar")
    {

        return 3;
    }
    if (m == "apr")
    {

        return 4;
    }
    if (m == "may")
    {

        return 5;
    }
    if (m == "jun")
    {

        return 6;
    }
    if (m == "jul")
    {

        return 7;
    }
    if (m == "aug")
    {

        return 8;
    }
    if (m == "sep")
    {

        return 9;
    }
    if (m == "oct")
    {

        return 10;
    }
    if (m == "nov")
    {

        return 11;
    }
    return 12;
}

// * Funcion que transforma una fecha string a INT
// ? Complejidad: O(n)
int ftoi(string fecha)
{

    int salida = 0;
    int aux = 0;
    int i = 0;

    while (fecha[i] != '-')
    {

        aux *= 10;
        aux += (fecha[i] - '0'); // * '5' -'0' == 5 como entero (53-48)
        i++;
    }

    salida += aux;
    i++;
    string mes = "";

    while (fecha[i] != '-')
    {

        mes += fecha[i];
        i++;
    }

    salida += (mestoi(mes) * 100);
    aux = 0;
    i++;

    while (i < fecha.length())
    {

        aux *= 10;
        aux += (fecha[i] - '0'); // '5' -'0' == 5 como entero (53-48)
        i++;
    }

    salida += (aux * 10000);
    return salida;
}

int main()
{

    system("cls"); // * Limpiar la terminal

    string date, hour, ub, nomArch;
    int dateInt;
    char entryDate;

    cout << "Archivo de entrada -> ";
    cin >> nomArch;
    cout << endl;

    while (nomArch != "suez.txt")
    {

        cout << "Favor de insertar archivo suez.txt -> ";
        cin >> nomArch;
        cout << endl;
    }

    ifstream datosSuez;
    datosSuez.open("suez.txt");

    LinkedList<registro> buquesM;
    LinkedList<registro> buquesR;

    while (datosSuez >> date >> hour >> entryDate >> ub)
    {
        registro registro;
        int idx = date.find("-");

        registro.fecha = date;
        registro.mes = date.substr(idx + 1, 3);
        registro.year = date.substr(idx + 5, 2);
        registro.hora = hour;
        registro.entrada = entryDate;
        registro.ubi = ub;
        registro.fechaInt = ftoi(date);
        registro.triple = ub.substr(0,3);

        if (registro.entrada == 'M')
        {

            buquesM.addLast(registro);
        }
        else
        {
            buquesR.addLast(registro);
        }
    }

    datosSuez.close();

    cout << "Ordenando Datos..." << endl;
    cout << endl;

    buquesM.sort();
    buquesR.sort();
    
    string archSalida;
    cout << "Nombre de archivo de salida para buques del Mar Mediterraneo -> ";
    cin >> archSalida;
    buquesM.fileout(archSalida);

    cout << "Nombre de archivo de salida para buques del Mar Rojo -> ";
    cin >> archSalida;
    buquesR.fileout(archSalida);
   
    string serieSearch;

    cout << "Serie a buscar -> ";
    cin >> serieSearch;
    

    LinkedList<registro> buquesT(buquesR);
    buquesT += buquesM;
    buquesT.sort();
    //buquesT.sortByMonth(serieSearch);
    
    vector<registroVect> vectorFin = buquesT.busqueda(serieSearch);
    //buquesT.print();

    if(vectorFin.size() > 0){
        for (int i = 0; i < vectorFin.size(); i++)
        {
        cout << vectorFin[i].mes << " " << vectorFin[i].year << " " << vectorFin[i].cantMed << " " << vectorFin[i].cantRoj << endl;
    }
    }
    
    else{
        cout << "No se encontro UBI" << endl;
    }
}

