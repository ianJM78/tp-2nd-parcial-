#include <iostream>
#include <cstdlib> // Para generar números aleatorios
#include <ctime>   // Para inicializar la semilla aleatoria
#include <cstring>
#include <cctype>
#include <fstream>
#include <string>
using namespace std;



struct file
{
    int  regionNumber;
    int rainAmount;
    int past_rainAmount;
};

struct precipitation
{
    int region;
    int times_it_rained;
    int totalRain;
    int totalPastRain;


};

class rain
{
private:
    file FILE_ARRAY[100];
    precipitation PRECIPITACION_ARRAY[6];
public:
    rain();
    void set_fileVector(ifstream& value,int* FILE_array_size);
    void update_PRECIPITATION_array(int* FILE_array_size);
    void print_avarages();
    void create_file_with_updated_PRECIPITATION_data(string path);
    void Ordenar_los_datos_por_el_Registro_Total_de_Lluvias_por_region_de_Menor_aMayor();
    void Ordenar_los_datos_por_el_Registro_Total_de_Lluvias_por_region_de_Mayor_a_Menor();

};

rain::rain()
{
    for (int i = 0; i < 6; i++)
    {
        PRECIPITACION_ARRAY[i].region = (i+1);   //! From 1 to 6.
        PRECIPITACION_ARRAY[i].times_it_rained = 0;
        PRECIPITACION_ARRAY[i].totalRain = 0;
        PRECIPITACION_ARRAY[i].totalPastRain = 0;
    }
}

void rain ::set_fileVector(ifstream& value,int* FILE_array_size)
{
    value >> FILE_ARRAY[*FILE_array_size].regionNumber >> FILE_ARRAY[*FILE_array_size].rainAmount >> FILE_ARRAY[*FILE_array_size].past_rainAmount;
}

void rain ::update_PRECIPITATION_array(int* FILE_array_size) 
{
    // for all elmenents is FILE array
    for (int i = 0; i < *FILE_array_size; i++)
    {
        // We get the value of the region at the "i" iteration
        int auxiliary = FILE_ARRAY[i].regionNumber;

        //* if its 1, we access the PRECIPITATION vector at the index equivalent to the region we are on currently itterating on the FILE array (region number - 1) and modify values to the required values in said vector
        PRECIPITACION_ARRAY[auxiliary - 1].totalRain += FILE_ARRAY[i].rainAmount;
        PRECIPITACION_ARRAY[auxiliary - 1].totalPastRain += FILE_ARRAY[i].past_rainAmount;
        PRECIPITACION_ARRAY[auxiliary - 1].times_it_rained++;
    }  
    
}

void rain ::print_avarages()
{
    for (int i = 0; i < 6; i++)
    {
        cout << "Region: " << PRECIPITACION_ARRAY[i].region << "\n"
        << "Amount of times it rained in the region: " << PRECIPITACION_ARRAY[i].times_it_rained << "\n"
        << "Total rain: "  << PRECIPITACION_ARRAY[i].totalRain << "\n"
        << "Total past rain: " << PRECIPITACION_ARRAY[i].totalPastRain << "\n"
        << "Average rain: " << (PRECIPITACION_ARRAY[i].totalRain / PRECIPITACION_ARRAY[i].times_it_rained) << "\n"
        << "Diference between this years and lasts average rain: " 
        << abs((PRECIPITACION_ARRAY[i].totalRain / PRECIPITACION_ARRAY[i].times_it_rained) - (PRECIPITACION_ARRAY[i].totalPastRain / PRECIPITACION_ARRAY[i].times_it_rained)) << "\n" 
        << endl;
    }
    
}

void rain::create_file_with_updated_PRECIPITATION_data(string path)
{
    ofstream values(path);

    for (int i = 0; i < 6; i++)
    {
        values << PRECIPITACION_ARRAY[i].region << " | " << PRECIPITACION_ARRAY[i].totalRain << " | " << (PRECIPITACION_ARRAY[i].totalRain / PRECIPITACION_ARRAY[i].times_it_rained) 
        << " | " << abs((PRECIPITACION_ARRAY[i].totalRain / PRECIPITACION_ARRAY[i].times_it_rained) - (PRECIPITACION_ARRAY[i].totalPastRain / PRECIPITACION_ARRAY[i].times_it_rained)) << endl;
    }
    
    
}


// Function to sort the PRECIPITACION_ARRAY in ascending order based on totalRain
void rain::Ordenar_los_datos_por_el_Registro_Total_de_Lluvias_por_region_de_Menor_aMayor()
{
    // Loop over each element in the array starting from the second element
    for (int i = 1; i < 6; i++)
    {
        // Store the current element as key
        precipitation key = PRECIPITACION_ARRAY[i];
        
        // Initialize j as the previous element's index
        int j = i - 1;
        
        // Move elements of PRECIPITACION_ARRAY[0..i-1], that are greater than key,
        // to one position ahead of their current position
        while (j >= 0 && PRECIPITACION_ARRAY[j].totalRain > key.totalRain)
        {
            PRECIPITACION_ARRAY[j+1] = PRECIPITACION_ARRAY[j];
            j--;
        }
        
        // Place the key in its correct location in the sorted part of the array
        PRECIPITACION_ARRAY[j+1] = key;
    }

    //* This function uses the Insertion Sort algorithm to sort the PRECIPITACION_ARRAY in ascending order based on the totalRain field. 
    //* The Insertion Sort algorithm works by dividing the array into a sorted and an unsorted region. The sorted region starts with the first element at index 0. For each iteration, 
    //* it inserts the first unsorted element into its correct position within the sorted region, thus extending the sorted region by one. This process continues until all elements are sorted.
}


void rain::Ordenar_los_datos_por_el_Registro_Total_de_Lluvias_por_region_de_Mayor_a_Menor()
{

    for (int i = 1; i < 6; i++)
    {

        precipitation key = PRECIPITACION_ARRAY[i];

        int j = i - 1;

        while (j >= 0 && PRECIPITACION_ARRAY[j].totalRain < key.totalRain)
        {
            PRECIPITACION_ARRAY[j+1] = PRECIPITACION_ARRAY[j];
            j--;
        }
        

        PRECIPITACION_ARRAY[j+1] = key;
    }
}

