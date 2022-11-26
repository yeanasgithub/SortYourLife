
// Yeana Bond
// Strange Sort

#include <iostream>
#include <cmath>
#include <string>

using namespace std;

// declare function pointers 

// this function pointer can point to a function that performs comparisons
// the function can be named anything as long as it
//   - returns a bool
//   - has 2 integer parameters
typedef bool (*comparer)(int, int);

// this function pointer can point to a function that sorts an array, using a comparison function
// passed in the third parameter 
// the function can be named anything as long as it
//   - is a void 
//   - it has three parameters: an array, an integer, and a pointer to a comparer function
typedef void (*sorter)(int *, int, comparer);

int const SIZE = 20;
int UNSORTED[SIZE] = { 15, 1, 3, 25, 8, 11, 9, 34, 17, 12, 7, 18, 2, 14, 19, 50, 23, 26, 16, 10 };

class QuadSort 
{
    public:
        int data[SIZE];

        // sort is being declared as a pointer to a function of type "sorter"
        sorter sort;

        QuadSort() 
        {
            // currently, the sorter function doesn't point to anything
            sort = NULL;
        }

        friend void show_data(QuadSort & qs);
};

void show_data(QuadSort & qs)
{
    for (int i = 0; i < SIZE; i++)
    {
        cout << qs.data[i] << " ";
    }
    cout << endl;
}

// prototypes for comparer functions
bool increasing(int, int);
bool decreasing(int, int);
// a strange comparison algorithm 
bool strange(int, int);

// prototypes for sorter functions
void selection_sort(int *, int, comparer);
void insertion_sort(int *, int, comparer);
void bubble_sort(int *, int, comparer);

void copy_array(int *, int *, int);

int main()
{
    QuadSort quad;

    // copy the unsorted data into our temp array
    copy_array(UNSORTED, quad.data, SIZE);

    // now call the selection sorter ------------------------------
    // and sort by increasing
    // the sorting algorithm is assigned to the .sort property
    // the sort() function is passed the name of the increasing() function
    // passing in the increasing function in the 3rd parameter uses that
    // function for sorting in increasing order
    quad.sort = selection_sort;
    quad.sort(quad.data, SIZE, increasing);

    // display data
    cout << "\nSorted using Selection (increasing): " << endl;
    show_data(quad);

    // now call the insertion sorter ------------------------------
    // uncomment the line below if you want to use unsorted data
    // for your insertion sort. If you don't, your data will already
    // have been sorted by selection above
    // copy_array(UNSORTED, quad.data, SIZE);
    quad.sort = insertion_sort;
    quad.sort(quad.data, SIZE, decreasing);

    // display data
    cout << "\nSorted using Insertion (decreasing): " << endl;
    show_data(quad);

    // now call the bubble sorter --------------------------------
    quad.sort = bubble_sort;
    quad.sort(quad.data, SIZE, increasing);

    // display data
    cout << "\nSorted using Bubble (increasing): " << endl;
    show_data(quad);

    // TODO: now call the bubble sorter, using the "strange" order
    quad.sort = bubble_sort;
    // - assign the bubble_sort as the sorting algorithm
   
    // - call the sort() using the strange comparer

    quad.sort(quad.data, SIZE, strange);

    // display data
    cout << "\nSorted using Bubble (in strange order): " << endl;
    show_data(quad);

    return 0;
}

void copy_array(int *src, int *dest, int size)
{
    for (int i = 0; i < size; i++)
    {
        *(dest + i) = *(src + i);
    }
}

void selection_sort(int * array, int size, comparer fncompare)
{
  //  cout << "\nSorting using Selection Sort - NOT IMPLEMENTED YET\n";

    // TODO: Write a selection sort to sort 'array'
    // implement the selection sort algorithm
    // be sure to use the fncompare() function to do any
    // comparisons to determine sort order (see bubble_sort example)
    int sorted;
    int index;
    for ( int i = 0; i < size; i++ )
    {
        sorted = array[i];
        index = i; 
        for ( int j = i; j < size; j++ ) // fncompare(smaller, bigger) = true
        {
            if (fncompare(array[j], sorted) && fncompare(array[j], array[i]))
            {
                sorted = array[j]; // if array[j] is smaller than sorted array[i]
                index = j;         // swap array[i] with array[j]
            }
        }
        array[index] = array[i]; // index = j
        array[i] = sorted; // i = index of sorted array going left to right
    }

}

void insertion_sort(int * array, int size, comparer fncompare)
{
    

   // cout << "\nSorting using Insertion Sort - NOT IMPLEMENTED YET\n";

    // TODO: Write an insertion sort to sort 'array'
    // implement the insertion sort algorithm
    // be sure to use the fncompare() function to do any
    // comparisons to determine sort order (see bubble_sort example)
    for ( int i = 1; i < size; i++ )
    {
        int unsorted = array[i];
        int j = i - 1; // Here, j is the index of sorted array 
        
        while ( j >= 0 && fncompare(unsorted, array[j]) ) // Once, unsorted is bigger than sorted
        {
            array[j + 1] = array[j];
            j--; // compare from right to left (direction)
        }

        array[j + 1] = unsorted; // sorted index + 1 is the spot for unsorted element

    }

}

void bubble_sort(int * array, int size, comparer fncompare)
{
    // implement the bubble sort algorithm
    int temp;
    int i = 0;
    bool swapped = true;
    while (i < size-1 && swapped)
    {
        swapped = false;
        for (int j = 0; j < size-1; j++)
        {
            // fncompare is a parameter of type comparer
            // it will return a boolean value that says
            // its parameters are sorted
            // the comparer function determines the sort order
            if (fncompare(array[j+1], array[j]))
            {
                temp = array[j+1];
                array[j+1] = array[j];
                array[j] =  temp;

                // set flags to continue swapping
                swapped = true;
                i = 0;
            }
        }
        i++;
    }
}

bool strange(int lhs, int rhs)
{
    // TODO: Implement the 'strange' comparison
    // here's the description for the 'strange' sort
    // take lhs, and get the 1st digit of the number
    // for example, if it's 900, the 1st digit is 9
    //
    // also take the 1st digit of rhs
    // for example, if it's 600, the 1st digit is 6
    // now, map 9 (lhs) to its english word => 'nine'
    //      map 6 (rhs) to its english word => 'six'
    // take the 1st character of 'nine' => 'n'
    // take the 1st character of 'six'  => 's'
    // 
    // now do an alphabetized sort on the 1st character
    // of lhs versus the 1st character of rhs
    // in this example, 'n' IS less than 's'
    // which would mean that for this strange comparison
    // 900 is less than 600
    //
    // set the return value based on this strange sort
    //
  /*  This method did not work!!!
   *  string lefts = to_string(lhs);

    string rights = to_string(rhs);
    cout << "1. to string " +  lefts + " " + rights << endl;
    char leftF = lefts.at(0);
    //cout << leftF << " " << rightF << endl;
    char rightF = rights.at(0);
    cout << "2. first character left and right " << leftF << " " << rightF << endl;
    bool done  = false;
    int left = abs(int(leftF));
    int right = abs(int(rightF));
    cout << "3. transforming to integer ->" << left << " " << right << endl;
   */
    int temp;
    char leftF, rightF;
    bool swapped = false;

    int left = abs(lhs);
    int right = abs(rhs);

    if (left >= 0)
    {
        while ( left >= 10 ) 
        {
            left = left / 10; // to get the first digit of any number equal to or greater than 10
        }
 
         
        switch (left)
        {
            case 0:
                leftF = 'z';
                break;
            case 1:
                leftF = 'o';
                break;
            case 2:
            case 3:
                leftF = 't';
                break;
            case 4:
            case 5:
                leftF = 'f';
                break;
            case 6:
            case 7:
                leftF = 's';
                break;
            case 8:
                leftF = 'e';
                break;
            case 9:
                leftF = 'n';
                break;
            default:
                cout << "Strange sort failed!" << endl;
                break; 

        }
    }

    if ( right >= 0)
    {
        while ( right >= 10 )
        {
            right = right / 10;
        }

        switch (right)
        {
            case 0:
                rightF = 'z';
                break;
            case 1:
                rightF = 'o';
                break;
            case 2:
            case 3:
                rightF = 't';
                break;
            case 4:
            case 5:
                rightF = 'f';
                break;
            case 6:
            case 7:
                rightF = 's';
                break;
            case 8:
                rightF = 'e';
                break;
            case 9:
                rightF = 'n';
                break;
            default:
                cout << "Strange sort failed!" << endl;
                break;

        }
    }

    if ( rightF > leftF ) // provided that strange order puts a smaller value on the left and a bigger value on the right according to strange sort rule
                         // e < f < n < o < s < t < z
                         // 8 < 50 < 9 < 1 < ....< 7 < 2 < 3 < ... 
    {
        cout << rightF + " " + leftF << endl;
         
         temp = lhs;
         lhs = rhs;
         rhs = temp;
         swapped = true;
        cout << "swapped!!!!!" << endl;        

    }
     
    return swapped;


}

bool increasing(int lhs, int rhs)
{
    return lhs < rhs;
}

bool decreasing(int lhs, int rhs)
{
    return lhs > rhs;
}


