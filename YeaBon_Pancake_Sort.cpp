// Lab 16 Yeana Bond
// I created functions of pancake sort, flip_pancake, and maxIndex! 
// I ended up using insertion sort ---- sort(string items[], int size);
// when I almost gave up on debugging on my pancake sort.

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int find_item_linear(string items[], string item, int size); // return the index of item if it is found in items
                                                             // if not found, return -1;
                                                             
void pancake_sort(string items[], int size); // sort items in increasing order, use any algo you like
void flip_pancake(string items[], int index);
int maxIndex(string items[], int size);
void sort(string items[], int size); // just in case you did not like the fact that I used a recursive sorting method!! 

int find_items_binary(string items[], string item, int size); // binary search - will return the index of item
                                                              // no recursive
                                                              
int find_matches(string items[], string pattern, int size, string matches[]); 
// search items looking for strings that contain pattern
// returns a count of the number of matching strings
// Use matches[] array to store the matching strings

int main()
{
    string text[25] = { "winter", "radius", "arthritis", "sponge", "rotation", "brandy",
        "radium", "crank", "ginger", "ankle", "cooler", "cranium", "potato", "receipt", 
        "keratin", "stool", "termite", "dynamite", "singing", "banker", "thrifty", "longer",
        "tattoo", "rations", "being"};
    
    
    
    int size = sizeof(text) / sizeof(text[0]);
    pancake_sort(text, size); // needed for binary search to work
   // sort(text, size);
    
    for ( int i = 0; i < 25; i++ )
    {
        cout << text[i] << " ";
        if ( (i + 1) % 5 == 0 )
        {
            cout << endl;
        }

    }

    int selected = 0;

    do
    {
        cout << endl;

        cout << "1 - Search for a word using linear" << endl;
        cout << "2 - Search for a word using binary" << endl;
        cout << "3 - Search for a partial string" << endl;
        cout << "0 - To Quit!" << endl;
        cout << "Select: ";
        cin >> selected;

      //  int size = sizeof(text) / sizeof(text[0]);
   
        int index;
        string item = "";
        if (selected == 1 )
        {
            cout << "Enter a word: ";
            cin >> item;
            index = find_item_linear(text, item, size);
            if (index == -1)
            {
                cout << "Such a word does not exist." << endl;
            }

            else
            {
                cout << "Found it!" << endl;
                cout << item << " is located at the index " << index << endl;
            }

        }

        if (selected == 2)
        {
            cout << "Enter a word: ";
            cin >> item;
            index = find_items_binary(text, item, size);
            if (index == -1)
            {
                cout << "Such a word does not exist." << endl;
            }

            else
            {
                cout << "Found it!" << endl;
                cout << item << " is located at the index " << index << endl;
            }
        }

        if (selected == 3)
        {
            cout << "Enter a partial string: ";
            cin >> item;

            string matches[25];
            index = find_matches(text, item, size, matches); // find_matches returns number of counts of matching cases
            if (index >= 1)
            {   
            
                for (int i = 0; i < index; i++)
                {
                    cout << matches[i] << "  ";
                
                }
                cout << endl;
                cout << "----Found above " << index << " matche(s)----" << endl;

            }   

            else
            {
                cout << "No matchting partial strings!" << endl;
            }

        }

    } while ( selected != 0 );

    cout << "Good bye!" << endl;
   
    return 0;
}

void sort(string items[], int size) // insertion sort is used
{
    
    for ( int i = 1; i < size; i++)
    {
        string key = items[i];
        int j = i - 1;
        while (  j >= 0 && items[j] > key)
        
        {
            items[j + 1]  = items[j];
            j--;
        }

        items[j + 1] = key;

    }

}


void pancake_sort(string items[], int size) // sort items in increasing order, use any algo you like
{
    for (int s = size; s > 1; s--)
    {
        int index = maxIndex(items, s); // DO NOT PUT size!!! it is (items, s) --- it took hours to find this one little mistake! Whoa.
        if (index != s - 1)
        {
            flip_pancake(items, index); // flipping order from the index 0 to max index
            
            flip_pancake(items, s - 1); // flipping order again from index 0 to the last index to put the max element to the last position in the array
            
        }

    }

}

void flip_pancake(string items[], int index)
{
    string temp = "";
    int start = 0;
    while (start <= index)
    {
        temp = items[start];
        items[start] = items[index];
        items[index] = temp;
        index--;
        start++;

    }

}


int maxIndex(string items[], int size)
{
   /* int max, i;
    for (max = 0, i = 0; i < size; ++i)
    {
        if (items[i] > items[max])
        {
            max = i;
        }
   
    }*/  
    // more verbose way to find the max index 
        int max  =  0;
        for (int j = max + 1; j < size ; j++) 
        {
            
            if (items[j] > items[max])
            {
                max = j;
            }
            
            else
            {
                max = max;
            }
         

        }
   
        return max;

}



int find_items_binary(string items[], string item, int size)
{
    int left = 0;
    int right = size - 1;
  
    int found = -1;
    

    while ( left <= right && found == -1 ) // once left > right, no need to enter while anymore
    {
        
        int middle = ((right - left) / 2) + left;
        if (items[middle] == item)
        {
            found = middle;
        }

        else if (items[middle] < item) // if item is greater than the middle, new left index is middle + 1
        {
            left = middle + 1;
           
        }
    
        else // if item is smaller than the middle, new right is middle - 1
        {
            right = middle - 1;
           
        } 

   // alternative way with for loop for binary search     
   /* int num_of_execution = log2 (size) + 1; //to ensure to round up to obtain the number of loops  16 < 25 < 32
    cout << num_of_execution << endl;

    for ( int i = 0; i < num_of_execution; i++ ) --- for loop could be used when able to expect the max number of loop executed
    { 
        int middle = ((right - left) / 2) + left;
        if (items[middle] == item)
        {
            found = middle;
        }

        if (items[middle] < item)
        {
            left = middle + 1;
        }

        if (items[middle] > item)
        {
            right = middle -1;
        } */

        // once the relationship between number of elements in an array and the number of loops(checks) is figured out mathematically,
        // below if block is not needed:

      /*  if ( i == 5 && found == -1 )
        {
            found = -1;
        } */


    }

    return found;

}



int find_item_linear(string items[], string item, int size) // return the index of item if it is found in items
{
    int found = -1;
    for (int i = 0; i < size; i++)
    {
        if (item == items[i])
        {
            found = i;
        }

    }

    return found;
   
}

int find_matches(string items[], string item, int size, string matches[])
{
    int count = 0;
    for (int i = 0; i < size; i++)
    {
        std::size_t found = items[i].find(item);
        if (found != std::string::npos)
        {
            matches[count] = items[i];
            count = count + 1;   // actual count is index of matches[] + 1
        }
        
    }

    return count;

}




