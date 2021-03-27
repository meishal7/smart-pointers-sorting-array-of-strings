/* main.cpp 
This program takes string from array of strings and puts that string in array of smart pointers in the spot, 
which index was chosen by generating random number. The program generates random number till the empty spot is found
and string is successfully placed in that spot, after that the program looks for the spot for the next string in array.
This program declares the Stone class and uses it in sorting routing. 

Author: Elena Mudrakova
Module: 4
Project: HW-4

Algorithm:
Before main()
#include <iostream>
#include <memory> 
#include <string>
#include <iomanip>
#include <array>
#include <algorithm> 
1. Declare class Stone.
    1.1 Private members: string name, int attemptsNumber, int originalSlot.
    1.2 Public members: default constructor, three argumnets constructor, overloaded operator<< .
In main()
2. Declare array of strings.
3. Declare array of unique_ptr.
4. Declare int totalAttempts.
5. Create for loop for array of strings.
    In loop:
    5.1 Declare int randomN, int attemptsN, bool slotFound = false.
    5.2 While empty slot is not found, generate random number, check if the slot with index == randN in array of pointers is allocated.
    If it's not allocated, allocate memory for newly created objects of Stone class using 3 args constructor and move ownerships
    of that object to unique_ptr in array of ptr witn the index == randN. Switch slotFound to true. Exit while loop and move to the
    next string in array of str.

    If the slot with index == randN is already occupied, do routing in while loop again till the empty slot is found.
6. After for loop print array of unique_ptr in formatted way using setw().
7. Sort array of unique_ptr by string (by letter in our case) using sort() from <algorythm> header.
8. Print newly sorted array of unique_ptr in formatted way using setw().
    

*/
#include <iostream>
#include <memory> // For smart ptr
#include <string>
#include <iomanip>
#include <array>
#include <algorithm> // For using sort()
using namespace std;

class Stone
{
private:
    string stoneName;
    int attemptsN;
    int origSlot;

public:
    Stone()
    {
        stoneName = "";
        attemptsN = 0;
        origSlot = 0;
    }

    Stone(string name, int attN, int origSlot)
    {
        this->stoneName = name;
        this->attemptsN = attN;
        this->origSlot = origSlot;
    }
    
    friend ostream &operator<<(std::ostream &out, const Stone &stone)
    {
        out << setw(10) << left << stone.stoneName << setw(10) << left << stone.attemptsN << setw(10) << left << stone.origSlot;
        return out;
    };
};

int main(){
    // Create array of strings 
    array<string, 10> stones = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J"};
    // Create array of smart pointers
    array<unique_ptr<Stone>, 10> slots;
    int totalAttempts = 0;
    for(int i = 0; i < 10; ++i ){
        bool slotFound = false;
        int randN;
        int attN = 0;
        // While empty slot is not found
        while(!slotFound){
            // Generate rand number
            randN = rand() % 10+0;
            // Track number of attempts to find empty slot
            attN++;
            // Track number of total attempts for all stones
            totalAttempts = totalAttempts + attN;
            // If slot with the index == randNumber is empty
            if(!slots[randN]){
                // Allocate memory for newly created obj
                unique_ptr<Stone> newStone(new Stone(stones[i], attN, randN));
                // Move ownership from created obj to unique_ptr in slots[] array
                slots[randN] = move(newStone);
                // Switch sentinel to true
                slotFound = true;
            }
            
        }
    }
    // Printing slots[] in formatted way
    cout << setw(10) << left << "Slot" << setw(10) << left << "Stone" << setw(10) 
    << left << "Attempts" << setw(10) << left << "Orig slot" << endl;
    cout << "__________________________________________" << endl;
    for(int i = 0; i<10; ++i){
        Stone *p = nullptr;
        p = slots[i].get();
        cout << setw(10) << left << i << *p << endl;
        
    }
    cout << "Total attempts: " << totalAttempts << endl;
    
    // Sort slots[] by letter 
    std::sort(slots.begin(), slots.end());
    
    // Printing slots[] in formatted way
    cout << "\nAfter sorting by stone:\n" << endl;
    cout << setw(10) << left << "Slot" << setw(10) << left << "Stone" << setw(10) 
    << left << "Attempts" << setw(10) << left << "Orig slot" << endl;
    cout << "__________________________________________" << endl;
    for(int i = 0; i<10; ++i){
        Stone *p = nullptr;
        p = slots[i].get();
        cout << setw(10) << left << i << *p << endl;
        
    }
    cout << "Total attempts: " << totalAttempts << endl;


}