#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <chrono>

using namespace std;
using namespace chrono;

//Funcion para calcular el tiempo que los sorts toman para terminar
void measureExecutionTime(void (*sortFunc)(vector<int>&), vector<int> arr) {
    auto start = high_resolution_clock::now();
    sortFunc(arr);
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(end - start);
    cout << "tuvo un tiempo de ejecucion fue: " << duration.count() << " milisegundos" << endl << endl;
}

//Funcion para leer el archivo y llenar la lista
vector<int> leerDatosDesdeArchivo(const string& nombreArchivo) {
    vector<int> datos;
    ifstream archivo(nombreArchivo);
    if (!archivo) {
        cerr << "Error al abrir el archivo: " << nombreArchivo << endl;
        return datos;
    }
    string linea;

    while (getline(archivo, linea)) { 
        if (linea.empty()) continue;  

        stringstream ss(linea);       
        int numero;
        while (ss >> numero) {        
            datos.push_back(numero);
        }
    }
    archivo.close();
    return datos;
}

int Selection_Sort(vector<int>& arreglo,int n) {
    int min;
    for (int i = 0; i < n; i++) {
        min = i;
        for (int j = i+1; j < n; j++) {
            if (arreglo[j] < arreglo[min]) {
                min = j;
            }
        }
        swap(arreglo[i], arreglo[min]);
    }
    return 0;
}

int Insertion_Sort(vector<int>& arreglo) {
    int n = arreglo.size();
    int key;
    for (int i = 1; i < n; i++) {
        key = arreglo[i];
        int j = i - 1;
        while (j >= 0 && arreglo[j] > key) {
            arreglo[j + 1] = arreglo[j];
            j--;
        }
        arreglo[j + 1] = key;
    }
    return 0;
}

int bubble_Sort(vector<int>& arreglo) {
    int tam = arreglo.size();
    for (int i = 0; i < tam; i++) {
        for (int j = 0; j < tam - i - 1; j++) {
            if (arreglo[j] > arreglo[j + 1])
                swap(arreglo[j], arreglo[j + 1]);
        }
    }
    return 0;
}

void merge(vector<int>& arr, int left, int mid, int right) {
    vector<int> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) temp[k++] = arr[i++];
        else temp[k++] = arr[j++];
    }

    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];
    for (int i = 0; i < temp.size(); i++) arr[left + i] = temp[i];
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void heapify(vector<int>& arreglo, int n, int i) {
    int padre = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arreglo[left] > arreglo[padre]) padre = left;
    if (right < n && arreglo[right] > arreglo[padre]) padre = right;

    if (padre != i) {
        swap(arreglo[i], arreglo[padre]);
        heapify(arreglo, n, padre);
    }
}

void heapSort(vector<int>& arreglo) {
    int n = arreglo.size();

    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arreglo, n, i);
    }
    for (int i = n - 1; i > 0; i--) {
        swap(arreglo[0], arreglo[i]);
        heapify(arreglo, i, 0);
    }
}

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    
    string path = "Arreglo de mil.txt"; //Aqui pone el archivo con los elementos para la lista
    vector<int> arreglo= leerDatosDesdeArchivo(path);
    cout << arreglo.size() << endl;
    //Definiendo lista para usar a todos los algoritmos
    vector<int> arreglo_inser = arreglo;
    vector<int> bubble_sort = arreglo;
    vector<int> merge_sort = arreglo;
    vector<int> heap_sort = arreglo;
    vector<int> quick_sort = arreglo;

    //Selection Sort
    cout << "Selection Sort ";
    measureExecutionTime([](vector<int>& a) { Selection_Sort(a,a.size()); }, arreglo);
   
    
    //Insertion Sort
    cout << "Insertion Sort: ";
    measureExecutionTime([](vector<int>& a) { Insertion_Sort(a); }, arreglo_inser);
    
    
    //Bubble Sort
    cout << "Bubble Sort: ";
    measureExecutionTime([](vector<int>& a) { bubble_Sort(a); }, bubble_sort);
    

    //Merge Sort
    cout << "Merge Sort: ";
    measureExecutionTime([](vector<int>& a) { mergeSort(a, 0, a.size() - 1); }, merge_sort);

    
    //Heap Sort
    cout << "Heap Sort ";
    measureExecutionTime([](vector<int>& a) { heapSort(a); }, heap_sort);
    

    //Quick Sort
    cout << "Quick Sort ";
    measureExecutionTime([](vector<int>& a) { quickSort(a,0,a.size()-1); }, quick_sort);
    return 0;
}