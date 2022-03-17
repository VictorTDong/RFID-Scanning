/*
Purpose: Show a mac address protocol
Details: Reads from .txt and stores the file into a boolean vector array. The array is then processed in the mac protocol from either the leaf or the root node to display information
Limitations and assumption: Assumes the .txt is properly formatted and file exist in the same directory
Known bugs: None
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <math.h>
#include <algorithm>
using namespace std;

double total = 0;
double success = 0;
int idle = 0;
int collisions = 0;
double rate = 0;

vector<int> itemArray;
vector<bool> leaves;

/*
Function: print
Purpose: To print information about the protocol
Method: Print information from variables
Input: None
Output: void
*/
void print()
{
    rate = (success/total)*100.00;

    cout << " # of items : " << success << endl
         << " Collisions : " << collisions << endl
         << " Idle       : " << idle << endl
         << " Success    : " << success << endl
         << " Total      : " << total << endl
         << " Rate       : " << rate << "%" << endl;
}

/*
Function: searchAtRoot
Purpose: Search starting at the root
Method: Iterates through the virtual levels of the tree to check if an item is successfully found and if there are no collisions
Input:  Int k for the depth of the tree
        Int start for the index of the beginning array
        Int end for the index of the last item of the array
Output: void
*/
void searchAtRoot(int k, int start, int end)
{
    int currDepth = k;
    if(currDepth <= k)
    {
        int isInTree = 0;
        for(int i = start; i < end; i++)
        {
            if(leaves[i] == true)
            {
                isInTree++;
            }
        }
        if(isInTree == 1)
        {
            success += 1;
        }
        else if(isInTree > 1)
        {
            int mid = start + (end - start) / 2;
            collisions += 1;
            searchAtRoot(k - 1, start, mid);
            searchAtRoot(k - 1, mid, end);
        }
        else
        {
            idle += 1;
        }
    }
    total = collisions + success + idle;
}

/*
Function: searchAtLeaf
Purpose: Search at the leaf nodes
Method: Gets information based on the leaf nodes
Input: Int k for the depth of the tree
Output: void
*/
void searchAtLeaf(int k)
{
    total = pow(2,k);
    success = itemArray.size();
    idle = total - success;
    collisions = 0;

    cout << "Searching at leaves..." << endl; 
    print();                                     
}

/*
Function: createLeaf
Purpose: Creates the leafs of the tree
Method: Checks to see if value of the leaf is an item from the user and if it is, true is placed in that leaf index
Input: Int k for the depth of the tree
Output: void
*/
void createLeaf(int k)
{
    int maxSize = pow(2,k);
    for(int i = 0; i < maxSize; i++)
    {
        if(find(itemArray.begin(),itemArray.end(),i) != itemArray.end())
        {
            leaves.push_back(true);
        }
        else
        {
            leaves.push_back(false);
        }
    }
}

/*
Function: readFile
Purpose: Read the file and stores the values
Method: Iterates through the .txt file and stores the information into an array
Input: The file to be looked at
Output: void
*/
void readFile(ifstream &file)
{
    string line;
    int item;

     while(getline(file,line))
     {
        stringstream ss(line);
        ss >> item;
        itemArray.push_back(item);
     }
}

int main(int argc, char const *argv[])
{
    if (argc != 3)
    {
        printf("usage: ./rfid <k> <Filename>\n");
        return 0;
    }

    int k = atoi(argv[1]);
    string filename = argv[2];
    
    ifstream file;
    file.open(filename);
    readFile(file);
    
    createLeaf(k);
    searchAtRoot(k, 0, leaves.size());
    cout << "Searching at root..." << endl; 
    print();
    searchAtLeaf(k);

    return 0;
}
