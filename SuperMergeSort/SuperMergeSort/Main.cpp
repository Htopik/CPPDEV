#include <future>
#include <chrono>
#include <iostream>
#include <random>

using namespace std;

bool make_thread = true;

void merge(int* arr, int l, int m, int r)
{
    int nl = m - l + 1;
    int nr = r - m;

    // make temporal values
    int* left = new int[nl];
    int* right = new int[nr];

    // copy data into temp mas
    for (int i = 0; i < nl; i++)
        left[i] = arr[l + i];
    for (int j = 0; j < nr; j++)
        right[j] = arr[m + 1 + j];

    int i = 0, j = 0;
    int k = l;  // start of left part

    while (i < nl && j < nr) {
        // write the minimum elements back to the input array
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        }
        else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }
    // write down the remaining elements of the left part
    while (i < nl) {
        arr[k] = left[i];
        i++;
        k++;
    }
    // write down the remaining elements of the right part
    while (j < nr) {
        arr[k] = right[j];
        j++;
        k++;
    }
    delete[] left;
    delete[] right;
}

void mergeSort(int* arr, int l, int r)
{
    if (l >= r)
        return;
    int mid = (l + r - 1) / 2;
    if (make_thread && (r - l > 10000))
    {
        auto f = async(launch::async, [&]() {
            mergeSort(arr, l, mid);
            });
        mergeSort(arr, mid + 1, r); // give a task for the main stream
        f.get();
        //Both recursive calls must be completed before calling the merge function
        merge(arr, l, mid, r);
    }
    else {
        mergeSort(arr, l, mid);
        mergeSort(arr, mid + 1, r);
        merge(arr, l, mid, r);
    }
}

int main()
{
    srand(0);
    size_t arr_size = 10;
    int* arr = new int[arr_size];

    for (long i = 0; i < arr_size; i++) {
        arr[i] = rand() % 500000;
    }
    time_t start, end;

    // multiple launch
    time(&start);
    mergeSort(arr, 0, arr_size - 1);
    time(&end);
    double seconds = difftime(end, start);
    printf("The time: %f seconds\n", seconds);

    for (long i = 0; i < arr_size - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            cout << "Unsorted" << endl;
            break;
        }
    }

    for (long i = 0; i < arr_size; i++) {
        arr[i] = rand() % 500000;
    }
    // base launch
    make_thread = false;
    time(&start);
    mergeSort(arr, 0, arr_size - 1);
    time(&end);
    for (long i = 0; i < arr_size - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            cout << "Unsorted" << endl;
            break;
        }
    }
    seconds = difftime(end, start);
    printf("The time: %f seconds\n", seconds);
    delete[] arr;
    cout << thread::hardware_concurrency();
    return 0;
}