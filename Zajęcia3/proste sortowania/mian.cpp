#include <iostream>
#include <cstdlib>
#include <time.h>

#define SIZE 30000

using namespace std;

void fill_table(int tab[])
{
    for (int i = 0; i < SIZE; i++)
    {
        tab[i] = rand() % SIZE*2;
    }
}

void copy_table(int tableFrom[], int tableTo[])
{
    for (int i = 0; i < SIZE; i++)
    {
        tableTo[i] = tableFrom[i];
    }
}

void bubble_sort(int tab[])
{
    for (int i = 0; i < SIZE - 1; i++) 
    {
        for (int j = 0; j < SIZE - i - 1; j++) 
        {
            if (tab[j] > tab[j + 1]) 
            {
                swap(tab[j], tab[j + 1]);
            }
        }
    }
}

void insert_sort(int tab[])
{
    int pom, j;
    for (int i = 1; i < SIZE; i++)
    {
        pom = tab[i];
        j = i - 1;

        while (j >= 0 && tab[j] > pom)
        {
            tab[j + 1] = tab[j];
            --j;
        }
        tab[j + 1] = pom;
    }
}

void selection_sort(int tab[])
{
    int mn_index;
    for (int i = 0; i < SIZE - 1; i++)
    {
        mn_index = i;
        for (int j = i + 1; j < SIZE; j++)
            if (tab[j] < tab[mn_index])
                mn_index = j;

        swap(tab[i], tab[mn_index]);
    }
}

void comb_sort(int tab[])
{
    int gap = SIZE;
    bool replace = true;

    while (gap > 1 || replace)
    {
        gap = gap * 10 / 13;
        if (gap == 0)
            gap = 1;

        replace = false;
        for (int i = 0; i + gap < SIZE; i++)
        {
            if (tab[i + gap] < tab[i])
            {
                swap(tab[i], tab[i + gap]);
                replace = true;
            }
        }
    }
}

void shell_sort(int tab[])
{
    for (int gap = SIZE / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < SIZE; i += 1)
        {
            int temp = tab[i];
            int j;
            for (j = i; j >= gap && tab[j - gap] > temp; j -= gap)
            {
                tab[j] = tab[j - gap];
            }
            tab[j] = temp;
        }
    }
}

int main()
{
    srand(time(NULL));
    clock_t start, stop;

    int unsortedTable[SIZE];
    fill_table(unsortedTable);
    int table[SIZE];

    //=========================================================

    copy_table(unsortedTable, table);

    start = clock();
    bubble_sort(table);
    stop = clock();

    cout << "\nTime of operation bubble_sort: " << stop - start << "ms";

    //=========================================================

    copy_table(unsortedTable, table);

    start = clock();
    insert_sort(table);
    stop = clock();

    cout << "\nTime of operation insert_sort: " << stop - start << "ms";

    //=========================================================

    copy_table(unsortedTable, table);

    start = clock();
    selection_sort(table);
    stop = clock();

    cout << "\nTime of operation selection_sort: " << stop - start << "ms";

    //=========================================================

    copy_table(unsortedTable, table);

    start = clock();
    comb_sort(table);
    stop = clock();

    cout << "\nTime of operation comb_sort: " << stop - start << "ms";

    //=========================================================

    copy_table(unsortedTable, table);

    start = clock();
    shell_sort(table);
    stop = clock();

    cout << "\nTime of operation shell_sort: " << stop - start << "ms";

	return 0;
}
