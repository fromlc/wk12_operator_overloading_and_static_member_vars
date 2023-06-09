//------------------------------------------------------------------------------
// fruit_vector.cpp 
//
// Demos vector that
//	- uses vector of pointers to base class Fruit instances
//	- vector can store pointers to derived class and base class instances
//	- member variable fruitID identifies instance type: _FRUIT, ORANGE, BANANA
//------------------------------------------------------------------------------
#include "Fruit.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

//------------------------------------------------------------------------------
// using symbols
//------------------------------------------------------------------------------
using std::cout;
using std::string;
using std::vector;

//------------------------------------------------------------------------------
// local function prototypes
//------------------------------------------------------------------------------
vector<Fruit*>* getFruitVector();
void sortFruits(vector<Fruit*>* pV, bool ascending = true);
void displayFruits(vector<Fruit*>*);
void countCalories();
void deleteFruits(vector<Fruit*>*&);

//------------------------------------------------------------------------------
// entry point
//------------------------------------------------------------------------------
int main() {

    vector<Fruit*>* pVFruits = getFruitVector();

    // demo std::sort() with function pointer param=vSortDown
    // works
    sortFruits(pVFruits, false);
    displayFruits(pVFruits);

    // demo std::sort() with Fruit class operator < overload
    //#TODO doesn't work
    sortFruits(pVFruits, true);
    displayFruits(pVFruits);

    // demo operator + overload
    countCalories();

    deleteFruits(pVFruits);

    // very inefficient but convenient way to keep app window open
    system("pause");

    return 0;
}

//------------------------------------------------------------------------------
// - instantiate classes derived from Fruit
// - store instance pointers in new vector<Fruit>
// - return pointer to new vector<Fruit>
//------------------------------------------------------------------------------
vector<Fruit*>* getFruitVector() {

    // tell C++ we'll store pointers to base class instances
    vector<Fruit*>* pV = new vector<Fruit*>;

    // we can store base class pointers too
    pV->push_back(new Fruit);

    // store pointers to derived class instances instead
    // there are different ways to do this...
    Orange* pOrange = new Orange;
    pV->push_back(pOrange);
    pV->push_back(new Orange);
    pV->push_back(new Banana);

    // we can store base class pointers too
    pV->push_back(new Fruit);

    // use static member function to report instance count
    cout << "Created " << Fruit::getInstanceCount()
        << " Fruit instances\n\n";

    return pV;
}

//------------------------------------------------------------------------------
// called by std::sort()
//------------------------------------------------------------------------------
static bool vSortDown(const Fruit* pLhs, const Fruit* pRhs) {
    return pLhs->getFruitID() > pRhs->getFruitID();
}

//------------------------------------------------------------------------------
// std::sort() vector by element fruitID
//------------------------------------------------------------------------------
void sortFruits(vector<Fruit*>* pV, bool ascending) {

    if (ascending) {
        cout << "sorting derived class ID in ascending order\n";
        cout << "#TODO doesn't work! What does this sort instead?\n";
        std::sort(pV->begin(), pV->end());
    }
    else {
        cout << "sorting derived class ID in descending order\n";
        std::sort(pV->begin(), pV->end(), vSortDown);
    }
}

//------------------------------------------------------------------------------
// display vector elements
//------------------------------------------------------------------------------
void displayFruits(vector<Fruit*>* pV) {

    // traverse vector of pointers with range-based for loop
    for (auto p : *pV) {

        // determine which type this instance was instantiated with
        int fruitID = p->getFruitID();

        cout << "Derived class ID " << p->getFruitID() << ": ";

        if (fruitID == ORANGE) {
            cout << "Oranges are ";
        }
        else if (fruitID == BANANA) {
            cout << "Bananas are ";
        }
        else if (fruitID == _FRUIT) {
            cout << "Fruits have ";
        }

        cout << p->getColor() << '\n';

        // getColor() returns a const reference to prevent mutating private color
        //string test = p->getColor();
        //&test = "blue";	// won't compile
    }
    cout << '\n';
}

//------------------------------------------------------------------------------
// - delete vector elements
// - delete vector and set passed reference pointer to nullptr
//------------------------------------------------------------------------------
void deleteFruits(vector<Fruit*>*& pV) {

    // traverse vector of pointers with iterator this time
    for (auto it = pV->begin(); it != pV->end(); ++it) {
        delete (*it);
    }

    delete pV;
    pV = nullptr;
}

//------------------------------------------------------------------------------
// demo operator + overload for Fruit instances
//------------------------------------------------------------------------------
void countCalories() {
    Banana b;
    Orange o;
    Fruit f;

    //cout << "Calories for Banana: " << b.getCalories() << '\n';
    //cout << "Calories for Orange: " << o.getCalories() << '\n';
    //cout << "Calories for Fruit: " << f.getCalories() << '\n';

    // replace above cout's with operator overload function for <<
    cout << b << '\n';
    cout << o << '\n';
    cout << f << '\n';

    int totalCalories = b + o;

    cout << "Total calories for Banana + Orange: "
        << totalCalories << "\n\n";
}
