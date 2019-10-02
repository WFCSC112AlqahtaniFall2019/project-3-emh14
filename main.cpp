#include <iostream>
#include <vector>
#include <ctime>
#include <cassert>

using namespace std;

// MergeSort function declarations
void mergeSort(vector<int> &a, vector<int> &tmp, int left, int right);

void mergeSortedLists(vector<int> &a, vector<int> &tmp, int leftPos, int rightPos, int rightEnd);

// BubbleSort function declaration
void swap(int *a, int *b);

void bubbleSort(int *a, int n);

int main(int argc, char* argv[]) {
    //begin function with unit test of swap
    int test_a = 1;
    int test_b = 2;
    swap(&test_a, &test_b);
    assert(test_b == 1 && test_a == 2);//will only print if assertion fails


    // get input: first is random seed, second is vector length
    int seed, length;

    //command line arguments
    if (argc == 3){//function, seed, length
        seed = atoi(argv[1]);
        length = atoi(argv[2]);
    }
    // Default to cin if command line argument is not found
    else{
        cin >> seed >> length;
    }
    srand(seed);

    vector<int> v(length); // vector to be sorted
    vector<int> t(length); // temporary workspace

    // define an integer pointer dynamically allocate an array of integers
    int* vPtr = new int[length];

    /*Print data to csv file
    for (int j = 0; j <= 10000; j = j +100) {
        srand(seed);
        length = j;

        vector<int> v(length); // vector to be sorted
        vector<int> t(length); // temporary workspace

        // define an integer pointer dynamically allocate an array of integers
        int* vPtr = new int[length];*/

        // initialize and print input
        cout << "Unsorted:" << endl;
        for (int i = 0; i < v.size(); i++) {
            v.at(i) = rand() % 100;
            cout << v.at(i) << '\t';
        }
        cout << endl;

        // copy the random list of integers from vector to array
        for (int i = 0; i < length; i++) {
            vPtr[i] = v.at(i);
        }

        clock_t start_mergeSort = clock();
        // sort vector using mergeSort
        mergeSort(v, t, 0, v.size() - 1);
        clock_t end_mergeSort = clock();

        // check output, make sure vector is sorted after mergeSort
        for (int i = 1; i < v.size(); i++) {
            assert(v.at(i - 1) <= v.at(i));
        }

        clock_t start_bubbleSort = clock();
        // sort array using bubbleSort
        bubbleSort(vPtr, length);
        clock_t end_bubbleSort = clock();

        // check output, make sure array is sorted after bubbleSort
        //Bubble Sort Unit Test
        for (int i = 1; i < length; i++) {
            assert(vPtr[i - 1] <= vPtr[i]);
        }

        // print sorted vector after mergeSort
        cout << "Sorted (mergeSort):" << endl;
        for (int i = 0; i < v.size(); i++) {
        cout << v.at(i) << '\t';
        }
        cout << endl;

        // print sorted array after bubbleSort
        cout << "Sorted (bubbleSort):" << endl;
        for (int i = 0; i < length; i++) {
        cout << vPtr[i] << '\t';
        }
        cout << endl;

        // print elapsed time for mergeSort and bubbleSort
        double elapsed_mergeSort = double(end_mergeSort - start_mergeSort) / CLOCKS_PER_SEC;
        double elapsed_bubbleSort = double(end_bubbleSort - start_bubbleSort) / CLOCKS_PER_SEC;

        cout << elapsed_mergeSort << "\t" << elapsed_bubbleSort << endl;
    //}

    return 0;
}

void mergeSortedLists(vector<int> &a, vector<int> &tmp, int leftPos, int rightPos, int rightEnd) {
    int leftEnd = rightPos - 1;
    int tempPos = leftPos;
    int numElements = rightEnd - leftPos + 1;

    while (leftPos <= leftEnd && rightPos <= rightEnd) {
        if (a[leftPos] <= a[rightPos]) {
            tmp[tempPos++] = a[leftPos++];
        } else {
            tmp[tempPos++] = a[rightPos++];
        }

    }

    while (leftPos <= leftEnd) {
        tmp[tempPos++] = a[leftPos++];
    }
    while (rightPos <= rightEnd) {
        tmp[tempPos++] = a[rightPos++];
    }

    for (int i = 0; i < numElements; i++, --rightEnd) {
        a[rightEnd] = tmp[rightEnd];
    }
}

void mergeSort(vector<int> &a, vector<int> &tmp, int left, int right) {
    if (left < right) {
        int center = (left + right) / 2;
        mergeSort(a, tmp, left, center);
        mergeSort(a, tmp, center + 1, right);
        mergeSortedLists(a, tmp, left, center + 1, right);
    }
}

// Swap function
void swap(int *a, int *b) {
    int temp = *a; //Save value at a into temp
    *a = *b; //Assign value at a with original value at b
    *b = temp; //Assign value at b with original value at a
}

// BubbleSort function
void bubbleSort(int *a, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (a[j] > a[j+1]){
                swap(a[j], a[j+1]);
            }
        }
    }
}
