// Lab 14 Yeana Bond
// quick sort is designed to use either Insertion sort or Bubble sort if the array size is equal to or less than 5

#include <iostream>
#include <chrono>
#include <ctime>
#include <cstdlib>

using namespace std;

int get_pivot_position(int data[], int low, int high);
int partition(int data[], int low, int high);
void quick_sort(int data[], int low, int high);
void fill_array_random(int data[], int size, int lbounds, int ubounds);
void fill_array_inc(int data[], int size);
void fill_array_dec(int data[], int size);
void quick_time();
void swap(int *xp, int *yp);
void insertion_sort(int data[], int low, int high);
void show_array(int data[], int size);
void bubble_sort(int data[], int low, int high);

int main()

{
    srand(time(NULL));

    cout << endl << "Quick sort & Insertion sort or Bubble sort" << endl;
    quick_time();

    return 0;
}

int get_pivot_position(int data[], int low, int high)
{
    int a = data[low]; // first
    int b = data[ (low + high) / 2 ]; //middle
    int c = data[high]; // last
    int middle = (low + high) / 2;

   
    // determine median of three (first, middle, and last elements) elems
       if ( (a < b && b < c) || (c < b && b < a) )
       {
           return middle;
       }

       else if ( (b < a && a < c) || (c < a && a < b) )
       {
           return low;
       }

       else if ( (a < c && c < b) || (b < c && c < a) )
       {
           return high;
       }

       else
       {
           return high;
       }


}

int partition(int data[], int low, int high)
{
    int pivotPosition = get_pivot_position(data, low, high);
 //   int pivotValue = data[pivotPosition];
    int middle = (low + high) / 2;

   /* if (pivotPosition != high)
    {
        if (pivotPosition == low)
        {
            swap(&data[low], &data[high]);
        }

        if (pivotPosition == middle)
        {
            swap(&data[middle], &data[high]);
        }

    }*/
    swap(&data[pivotPosition], &data[high]); 

    int pivotValue = data[high];

    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        // if current elem is smaller than pivotValue, increment the low 
        // and swap i and j
        if (data[j] <= pivotValue)
        {
            i++;
            swap(&data[i], &data[j]);
        }

    }
    swap(&data[i+1], &data[high]);

    return i + 1;


}

void bubble_sort(int data[], int low, int high)
{
    int size = high - low + 1;
    for (int i = 0; i < size; i++)
    {
        for (int j = 1 + i; j < size; j++)
        {
            if (data[i] > data[j])
            {
                swap(&data[i], &data[j]);
            }

        }

    }

}


void quick_sort(int data[], int low, int high)
{
  if (low < high)
  {
     if ( high + 1 <=  5)
     {
         cout << endl << "This array is small. Using Insertion Sort or Bubble Sort instead..." << endl;
       // insertion_sort(data, low, high);
        bubble_sort(data, low, high);
      }

    else
    {
        cout << endl << "This array is large. Using Quick Sort!" << endl;
    
    
        int pivot = partition(data, low, high);
        quick_sort(data, low, pivot - 1);
        quick_sort(data, pivot + 1, high);
     
    }
  }
}


void fill_array_random(int data[], int size, int lbounds, int ubounds)
{
    for (int i = 0; i < size; i++)
    {
        data[i]  = (rand() % (ubounds - lbounds)) + lbounds;
    }

}

void fill_array_inc(int data[], int size)
{
    for (int i = 0; i < size; i++)
    {
        data[i] = i + 1;
    }

}

void fill_array_dec(int data[], int size)
{
    int val = size;
    for (int i = 0; i < size; i++)
    {
        data[i] = val;
        val--;
    }

}

void quick_time()
{
    int *array;
    int arraysize;
    cout << "Enter a positive number for testing: ";
    cin >> arraysize;

    array = new int[arraysize];

    fill_array_random(array, arraysize, 1000, 1000000);
    show_array(array, arraysize);

    int n = arraysize - 1;
    auto start = chrono::steady_clock::now();
    quick_sort(array, 0, n);
    auto end = chrono::steady_clock::now();
    cout << endl;
    cout << "Time to sort (Random) order was ";
    cout << chrono::duration_cast<chrono::milliseconds>(end-start).count() << " milli-second(s)." << endl;

    cout << endl;
    cout << "Post - Sort: " << endl;
    show_array(array, arraysize);

    cout << endl << endl;
    cout << "(Increasing) order: " << endl;
    fill_array_inc(array, arraysize);
    show_array(array, arraysize);

    start = chrono::steady_clock::now();
    quick_sort(array, 0, n);
    end = chrono::steady_clock::now();
    cout << endl;
    cout << "Time to sort (Increasing) order was ";
    cout << chrono::duration_cast<chrono::milliseconds>(end-start).count() << " milli-second(s)." << endl;

    cout << endl;
    cout << "Post - Sort: " << endl;
    show_array(array, arraysize);

    cout << endl << endl;
    cout << "(Decreasing) order: " << endl;
    fill_array_dec(array, arraysize);
    show_array(array, arraysize);

    start = chrono::steady_clock::now();
    quick_sort(array, 0, n);
    end = chrono::steady_clock::now();
    cout << endl;
    cout << "Time to sort (Decreasing) order was ";
    cout << chrono::duration_cast<chrono::milliseconds>(end-start).count() << " milli-second(s)." << endl;

    cout << endl;
    cout << "Post - Sort: " << endl;
    show_array(array, arraysize);

    cout << "       -----End of Hybrid sort!-----" << endl;
}

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void insertion_sort(int data[], int low, int high)
{
    int size = high - low + 1;
    for (int i = low + 1; i < size; i++)
    {
        int key = data[i];
        int j = i;

        while (j > low && data[j - 1] > key)
        {
            data[j] = data[j - 1];
            j--;
        }

        data[j] = key;
    }

}

void show_array(int data[], int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        cout.width(7);
        cout << data[i] << "  ";
        if ( (i+1) % 5 == 0 )
        { cout << endl; }
       
    }

    cout << endl;
}






