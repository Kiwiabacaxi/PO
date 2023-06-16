#include <stdlib.h>
#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    int elements, turns;
    int *array = NULL;
    int *turns_array = NULL;

    while (true)
    {
        cin >> elements >> turns;
        if (elements == 0 && turns == 0) break;

        array = (int*)malloc(elements*sizeof(int));
        turns_array = (int*)malloc(turns*sizeof(int));

        for (int i = 0; i < elements; i++)
        {
            array[i] = i + 1;
        }

        for (int i = 0; i < turns; i++)
        {
            cin >> turns_array[i];
        }

        for (int i = turns; i >= 1; i--)
        {
            for (int j = 0; j < turns_array[i - 1]; j++)
            {
                swap(array[i - 1 + j], array[i + j]);
            }
        }

        for (int i = 0; i < elements; i++)
        {
            cout << array[i] << " ";
        }
        cout << "\n";

        free(array);
    }
}