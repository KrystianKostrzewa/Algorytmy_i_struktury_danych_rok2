#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std;

int partition(vector<int>& arr, int low, int high);

int* vec(int size) {
    int* ptr = (int*)malloc(size * sizeof(int));
    return ptr;
}

void randomize(int* tab, int size) {
    for (int i = 0; i < size; i++)
        tab[i] = rand() % 1000;
}

//Sortowanie kube³kowe
void bucketSort(int* arr, int size) {
    int maxVal = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > maxVal) {
            maxVal = arr[i];
        }
    }

    int numBuckets = maxVal / 10 + 1;

    int** buckets = new int* [numBuckets];
    int* bucketSizes = new int[numBuckets]();

    for (int i = 0; i < numBuckets; i++) {
        buckets[i] = new int[size];
    }

    for (int i = 0; i < size; i++) {
        int index = arr[i] / 10;
        if (index >= 0 && index < numBuckets) {
            buckets[index][bucketSizes[index]++] = arr[i];
        }
    }
    int index = 0;
    for (int i = 0; i < numBuckets; i++) {
        for (int j = 0; j < bucketSizes[i]; j++) {
            arr[index++] = buckets[i][j];
        }
        delete[] buckets[i];
    }
    delete[] buckets;
    delete[] bucketSizes;
}

//Deklaracja klasy Person
class Person {
public:
    string name;
    int age;

    Person(std::string n, int a) : name(n), age(a) {}
};

//Funkcja porównuj¹ca po wieku osoby
bool sortByAge(const Person& p1, const Person& p2) {
    return p1.age > p2.age;
}

//Sortowanie tylko k pierwszych elementów
void heapify(vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

//U¿ycie struktury kopca 
vector<int> partialSortHeap(vector<int>& arr, int k) {
    int n = arr.size();
    vector<int> result;

    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i >= n - k; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }

    for (int i = n - 1; i >= n - k; i--)
        result.push_back(arr[i]);

    return result;
}

//Sortowanie przez wstawienie
void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

//Sortowanie szybkie
void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

//Sortowanie przez scalanie
void merge(vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<int>& arr, int l, int r) {
    if (l >= r)
        return;
    int m = l + (r - l) / 2;
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
}

//Wybór sortowania na podstawie d³ugoœci tablicy
void hybridSort(vector<int>& arr) {
    int n = arr.size();
    if (n < 20) {
        insertionSort(arr);
        cout << "Uzyto sortowania przez wstawianie." << endl;
    }
    else if (n < 1000) {
        quickSort(arr, 0, n - 1);
        cout << "Uzyto sortowania szybkiego." << endl;
    }
    else {
        mergeSort(arr, 0, n - 1);
        cout << "Uzyto sortowania przez scalanie." << endl;
    }
}

//Porównanie czasu sortowania dla sortowania dzia³aj¹cego bez i z dodatkow¹ pamiêci¹
void compareSortTimes(int* arr, int size) {
    clock_t start, end;

    vector<int> insertionArr(arr, arr + size);
    start = clock();
    insertionSort(insertionArr);
    end = clock();
    double insertionTime = double(end - start) * 1000.0 / CLOCKS_PER_SEC;


    vector<int> mergeArr(arr, arr + size);
    start = clock();
    mergeSort(mergeArr, 0, size - 1);
    end = clock();
    double mergeTime = double(end - start) * 1000.0 / CLOCKS_PER_SEC;

    cout << "Czas sortowania przez wstawianie: " << insertionTime << " [ms]" << endl;
    cout << "Czas sortowania przez scalanie: " << mergeTime << " [ms]" << endl;
}


int main() {

    //Sortowanie kube³kowe
    srand(time(NULL));

    int size = 10000;
    int* a = vec(size);

    randomize(a, size);

    clock_t start = clock();
    bucketSort(a, size);
    clock_t end = clock();
    double diff = (end - start) * 1000.0 / CLOCKS_PER_SEC;

    cout << "Tablica zostala posortowana w czasie: " << diff << " [ms]" << endl;

    //Sortowanie niestandarowych danych
    vector<Person> people = {
        {"Jan", 25},
        {"Ania", 30},
        {"Michal", 20},
        {"Emilia", 35}
    };

    sort(people.begin(), people.end(), sortByAge);

    for (const auto& person : people) {
        std::cout << person.name << ": Age " << person.age << "\n";
    }

    //Sortowanie cz¹stkowe
    vector<int> arr = { 5, 3, 8, 1, 9, 2 };
    int k = 3;

    vector<int> result = partialSortHeap(arr, k);

    cout << "K najwiekszych elementow: ";
    for (int num : result)
        cout << num << " ";
    cout << endl;

    //Hybrydowy algorytm sortowania
    hybridSort(arr);

    cout << "Lista po sortowaniu:" << endl;
    for (int num : arr)
        cout << num << " ";
    cout << endl;

    //Sortowanie w miejscu
    compareSortTimes(a, size);

    return 0;
}
