#include <iostream>
#include <functional>
#include <time.h>
#include <vector>
#include "timer.h"

void testSort(int size, std::function<void(std::vector< double >&, int)>& func);
void checkSort(std::vector< double >& array, int size);
void straightFill(std::vector< double >& array, int size);
void reversFill(std::vector< double >& array, int size);
void halfFill(std::vector< double >& array, int size);
void randomFill(std::vector< double >& array, int size);
void bubbleSort(std::vector< double >& array, int size);
void mergeSort(std::vector< double >& array, int size);
void merge(std::vector< double >& array, int arr1, int arr2, int size1, int size2);

int main()
{
	srand(time(nullptr));
    std::function<void(std::vector< double >&, int)> bubble = bubbleSort;
    std::function<void(std::vector< double >&, int)> merge = mergeSort;
	int size[7] = { 10, 100, 1000, 10000, 20000, 30000, 50000 };
    std::cout << "      <<Merge sorting>>";
    for (int i = 0; i < 7; i++)
    {
        std::cout << "\n\n      Size: " << size[i] << "\n";

        std::cout << "\n    Bubble sorting:\n";
        testSort(size[i], bubble);

        std::cout << "\n\n  Merge Sorting:\n";
        testSort(size[i], merge);
    }
	return 0;
}

void testSort(int size, std::function<void(std::vector< double >&, int)>& func)
{
    std::vector< double > array(size);
    std::cout << "Straight filling: ";
    straightFill(array, size);
    func(array, size);
    checkSort(array, size);
    std::cout << "Half straight filling: ";
    halfFill(array, size);
    func(array, size);
    checkSort(array, size);
    std::cout << "Revers filling: ";
    reversFill(array, size);
    func(array, size);
    checkSort(array, size);
    std::cout << "Random filling: ";
    randomFill(array, size);
    func(array, size);
    checkSort(array, size);
}

void checkSort(std::vector< double >& array, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        if (array[i] > array[i + 1])
        {
            std::cout << ", WRONG\n";
            return;
        }
    }
    std::cout << ", RIGHT\n";
}

void straightFill(std::vector< double >& array, int size)
{
    for (int i = 0; i < size; i++)
    {
        array[i] = i;
    }
}

void halfFill(std::vector< double >& array, int size)
{
    for (int i = 0; i < size / 2; i++)
    {
        array[i] = i;
    }
    for (int i = 0; i < size /2; i++)
    {
        array[size / 2 + i] = size - i - 1;
    }
}

void reversFill(std::vector< double >& array, int size)
{
    for (int i = size - 1; i >= 0; i--)
    {
        array[size - 1 - i] = i;
    }
}

void randomFill(std::vector< double >& array, int size)
{
    for (int i = 0; i < size; i++)
    {
        array[i] = rand() % size;
    }
}

void bubbleSort(std::vector< double >& array, int size)
{
    SimpleTimer timer;
    int k = 1, t, c;
    while (true)
    {
        c = 0;
        for (int i = 0; i < size - k; i++)
        {
            if (array[i] > array[i + 1])
            {
                t = array[i];
                array[i] = array[i + 1];
                array[i + 1] = t;
                c++;
            }
        }
        if (c == 0)
            break;
        k++;
    }
}

void mergeSort(std::vector< double >& array, int size)
{
    SimpleTimer timer;
    if (size < 2)
    {
        return;
    }
    int n = 1, k, ost;
    while (n < size) 
    {
        k = 0;
        while (k < size)
        {
            if (k + n >= size)
            {
                break;
            }
            ost = (k + n * 2 > size) ? (size - (k + n)) : n;
            merge(array, k, k + n, n, ost);
            k += n * 2;
        }
        n *= 2;
    }
}

void merge(std::vector< double >& array, int arr1, int arr2, int size1, int size2)
{
    std::vector< double > buf(size1 + size2);
    int n = 0;
    int start = arr1;
    while (size1 && size2)
    {
        if (array[arr1] < array[arr2])
        {
            buf[n] = array[arr1];
            ++arr1;
            --size1;
        }
        else 
        {
            buf[n] = array[arr2];
            ++arr2;
            --size2;
        }
        ++n;
    }
    if (size1 == 0) 
    {
        for (int i = 0; i < size2; ++i) 
        {
            buf[n++] = array[arr2++];
        }
    }
    else 
    { 
        for (int i = 0; i < size1; ++i) 
        {
            buf[n++] = array[arr1++];
        }
    }
    for (int i = 0; i < n; ++i)
    {
        array[start + i] = buf[i];
    }
}