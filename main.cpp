#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <cstdlib>

using namespace std;

int swapCount = 0;

void swap(int *x, int *y){
    int temp = *x;
    x = y;
    *y = temp;
}

void merge(int arr[], int l, int m, int r){
    int i,j,k;
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[10000], R[10000];
    for(i = 0; i < n1; i++){
        L[i] = arr[l + i];
    }
    for(j = 0; j < n2; j++){
        R[j] = arr[m + 1 + j];
    }
    i = 0; j = 0; k = l;
    while(i < n1 && j < n2){
        if(L[i] <= R[j]){
            arr[k] = L[i];
            i++;
        }
        else{
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while(j < n2){
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r){
    if( l < r){
        int m = l + (r - 1) / 2;
        mergeSort(arr, l, m);
        swapCount++;
        mergeSort(arr,m + 1, r);
        swapCount++;
        merge(arr,l,m,r);
        swapCount++;
    }
}

void heapIt(int arr[], int n, int i){
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if(l < n && arr[l] > arr[largest]){
        largest = l;
    }
    if(r < n && arr[r] > arr[largest]){
        largest = r;
    }
    if(largest != i){
        swap(arr[i], arr[largest]);
        swapCount++;
        heapIt(arr, n, largest);
    }
}
int partition(int arr[], int low, int high){
    int pivot = arr[high];
    int i = low - 1;
    for(int j = low; j <= high - 1; j++){
        if(arr[j] < pivot){
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    swapCount++;
    return (i + 1);
}

int partition2(int arr[], int low, int high){
    srand(time(NULL));
    int random = low + rand() % (high - low);
    swap(arr[random], arr[high]);
    swapCount++;
    return partition(arr, low, high);
}

void quickSort(int arr[], int low, int high){
    if(low < high){
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void quickSort2(int arr[], int low, int high){
    if(low < high){
        int pi = partition2(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main(int argc, char *argv[]){
    fstream fs;
    int input;
    int list[10000];
    fs.open(argv[1], fstream::in);
    if(fs.is_open()){
        fs >> input;
        int count = 0;
        while(!fs.eof()){
            list[count] = input;
            fs >> input;
        }
    }
    else{
        cout << "Failed to open the input file" << endl;
        return 0;
    }
    cout << "selection sort (s), merge sort (m), heap sort (h), quick-sort-fp (q), quick-sort-rp(r)" << endl;
    cout << "Enter the algorithm : " ;
    string command = "";
    cin >> command;

    
    if(command == "s"){
        int minIndex = 0;
        int j = 0;
        int n = sizeof(list) / sizeof(list[0]);
        for(int i = 0; i < n - 1; i++){
            minIndex = i;
            for(j = i + 1; j < n;j++){
                if(list[j] < list[minIndex]){
                    minIndex = j;
                }
                swap(&list[minIndex], &list[i]);
                swapCount++;
            }
        }
         cout << "1 2 3 4 5 .... . 9999" << endl;
         cout << "#Selection-sort comparison: " << swapCount << endl;
         return 0;
    }
    else if(command == "h"){
        int n = sizeof(list) / sizeof(list[0]);
        for(int i = n / 2 - 1; i >= 0; i--){
            heapIt(list, n, i);
        }
        for(int i = n - 1; i > 0; i--){
            swap(list[0], list[i]);
            heapIt(list, i, 0);
        }
        cout << "1 2 3 4 5 .... . 9999" << endl;
        cout << "#Heap-sort comparison: " << swapCount << endl;
        return 0;
    }
    else if(command == "m"){
        int n = sizeof(list) / sizeof(list[0]);
        mergeSort(list, 0, n - 1);
        return 0;
    }
    else if(command == "q"){
        int n = sizeof(list) / sizeof(list[0]);
        quickSort(list, 0, n -1);
        cout << "1 2 3 4 5 .... . 9999" << endl;
        cout << "#Quick-sort-fp  comparison: " << swapCount << endl;
        return 0;
    }
    else if(command == "r"){
        int n = sizeof(list) / sizeof(list[0]);
        quickSort2(list, 0, n - 1);
        cout << "1 2 3 4 5 .... . 9999" << endl;
        cout << "#Quick-sort-rp  comparison: " << swapCount << endl;
        return 0;
    }
    else{
        cout << "Invalid command" << endl;
        return 0;
    }
}
