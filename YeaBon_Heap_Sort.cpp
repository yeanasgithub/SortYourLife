// Lab 15 Yeana Bond
// Heap sort

#include <iostream>

using namespace std;

void show_array(int data[], int count);

bool is_max_heap(int data[], int count);

void heapify(int data[], int count);



int main()
{
    int array[1000];
    int choice = 0;
    int count = 0;
   

    do
    {
        cout << endl << "Enter -1 to quit. Otherwise,";
        cout << " enter an interger: ";
        cin >> choice;
        
        if ( choice != -1 )
        {
            array[++count - 1] = choice;
           
            show_array(array, count);
        }

    
    } while (choice != -1);

    
    if (choice == -1 && count > 1)
    {

        heapify(array, count);
        cout << endl <<  "Verifying..." << endl;

        if (is_max_heap(array, count))
        {
            cout << "The array is a verified max heap!" << endl;
           // show_array(array, count);
        }
        
        else
        {
            cout << "The array is not verified max heap." << endl;
        }
    } 
    
    else
    {
        cout << "Verification is not necessary." << endl;
    }

    show_array(array, count);
    cout << endl;

    return 0;
}


bool is_max_heap(int data[], int count)
{
    int parent = 0, left = 1, right = 2;
    bool is_max = true;

    while (left < count)
    {
        if ( !(data[left] <= data[parent]) )
        {
            is_max = false;
        }

        if ( right < count )
        {
            if ( !(data[right] <= data[parent]) )
            {
                is_max = false;
            }

        }

        parent++;
        left = (parent * 2) + 1;
        right = (parent * 2) + 2;

    }

    return is_max;

}

void heapify(int data[], int count)
{
    int parent = 0;
    int left = 1;
    int right = 2;
    int temp;
    int max;

    while (left < count)
    {
        max = parent;

        if ( data[left] > data[parent] )
        {
            max = left;
        }

        if ( data[right] > data[parent] && right < count )
        {
            max = right;
        }

        if ( data[max] != data[parent] )
        {
            temp = data[parent];
            data[parent] = data[max];
            data[max] = temp;
        }

        parent++;
        left = (parent * 2) + 1;
        right = (parent * 2) + 2;

    }

    if ( !(is_max_heap(data, count)) )
    {
        heapify(data, count);
    }    
            
}

void show_array(int data[], int count)
{
    for (int i = 0; i < count; i++)
    {
        if( i % 10 == 0)
        {
            cout << endl;
        }
        cout << data[i] << " ";
    }

}

    


