#include <iostream>
#include <cstdlib> // Para generar números aleatorios
#include <ctime>   // Para inicializar la semilla aleatoria
#include <cstring>
#include <cctype>
#include <fstream>
#include <string>
#include "rain.h"

using namespace std;




int main()
{
    int FILE_array_size = 0;
    string path = "C:/UNI/2 nd Parcial/texto.txt";
    string path_2 = "C:/UNI/2 nd Parcial/File with update PRECIPITATION from smallest to largest.txt";
    string path_3 = "C:/UNI/2 nd Parcial/File with update PRECIPITATION from largets to smallest";

    //* create an object of the class RAIN, that when created contains the vector of type struct FILE, to store the elements of the text file.
    
    rain RAIN;
    ifstream value(path);

    // Read the file and store it on the FILE array of struct type
    while (!value.eof())
    {
        RAIN.set_fileVector(value,&FILE_array_size);
        FILE_array_size++;
    }

    //* sort through the FILE array, and update the 6 regions in the PRECIPITATION array with the relevant data
    RAIN.update_PRECIPITATION_array(&FILE_array_size);

    //* Print the results of the PRECIPITACION array after beinng update with relevant data
    RAIN.print_avarages();

    //* Sort from smallest to largest in terms of total rain fall
    RAIN.Ordenar_los_datos_por_el_Registro_Total_de_Lluvias_por_region_de_Menor_aMayor();

    //*create file with data
    RAIN.create_file_with_updated_PRECIPITATION_data(path_2);
    
    //* Sort from smallest to largest in terms of total rain fall
    RAIN.Ordenar_los_datos_por_el_Registro_Total_de_Lluvias_por_region_de_Mayor_a_Menor();

    //* create file with data
    RAIN.create_file_with_updated_PRECIPITATION_data(path_3);

    
}




