//------------------------------------------------------------------------------
// Fruit.h : declaration and definition file for
//      - base class Fruit
//      - derived classes Orange, Banana
//------------------------------------------------------------------------------
#pragma once

#include <iostream>

// comment this #define to disable debug messages
//#define LC_DEBUG

//------------------------------------------------------------------------------
// using symbols
//------------------------------------------------------------------------------
#ifdef LC_DEBUG
using std::cout;
#endif

using std::ostream;
using std::string;

//------------------------------------------------------------------------------
// constants
//------------------------------------------------------------------------------
constexpr int _FRUIT = 0;
// keep derived class id's alphabetical
constexpr int BANANA = 1;
constexpr int ORANGE = 2;

//------------------------------------------------------------------------------
// Fruit
//------------------------------------------------------------------------------
class Fruit {
    friend ostream& operator<<(ostream& os, const Fruit& f);

private:
    // use static member variable to count instances
    static int s_instanceCount;

    // each instance gets a unique ID
    int instanceID;

    // identify instance type
    int fruitID;

    // fruit data
    int calories;
    string color;

public:
    // constructors
    Fruit(int _fruitID, string _color) {

        // assign unique instance ID and count instances
        instanceID = ++s_instanceCount;

        // identifies type used for instantiation
        fruitID = _fruitID;

        calories = 0;
        color = _color;
    }

    Fruit() : Fruit(_FRUIT, "none") { }

    // getters
    int getInstanceID() const { return instanceID; }
    int getFruitID() const { return fruitID; }
    int getCalories() const { return calories; }
    const string& getColor() const { return color; }

    // access static member variable
    static int getInstanceCount() { return s_instanceCount; }

    // setter
    void setCalories(int _calories) { calories = _calories; }

    //--------------------------------------------------------------------------
    // overload + operator to add calories of two Fruit instances
    // 
    // Fruit f1, f2;
    // in expression f1 + f2, f1 is "this" and f2 is "rhs"
    //--------------------------------------------------------------------------
    int operator+(Fruit& rhs) {
        return this->calories + rhs.calories;
    }

    //--------------------------------------------------------------------------
    // overload < operator to order Fruit instances by derived class ID fruitID
    // 
    // Fruit f1, f2;
    // in expression f1 < f2, f1 is "this" and f2 is "rhs"
    //--------------------------------------------------------------------------
    bool operator<(Fruit& rhs) {
        return this->fruitID < rhs.fruitID;
    }

    //--------------------------------------------------------------------------
    // overload <= operator to order Fruit instances by derived class ID fruitID
    // 
    // Fruit f1, f2;
    // in expression f1 <= f2, f1 is "this" and f2 is "rhs"
    //--------------------------------------------------------------------------
    bool operator<=(Fruit& rhs) {
        return this->fruitID <= rhs.fruitID;
    }

    //--------------------------------------------------------------------------
    // overload > operator to order Fruit instances by derived class ID fruitID
    // 
    // Fruit f1, f2;
    // in expression f1 > f2, f1 is "this" and f2 is "rhs"
    //--------------------------------------------------------------------------
    bool operator>(Fruit& rhs) {
        return this->fruitID > rhs.fruitID;
    }

    //--------------------------------------------------------------------------
    // overload >= operator to order Fruit instances by derived class ID fruitID
    // 
    // Fruit f1, f2;
    // in expression f1 >= f2, f1 is "this" and f2 is "rhs"
    //--------------------------------------------------------------------------
    bool operator>=(Fruit& rhs) {
        return this->fruitID >= rhs.fruitID;
    }

#ifdef LC_DEBUG
    ~Fruit() { cout << "Fruit destructor\n"; }
#endif
};

//------------------------------------------------------------------------------
// Banana
//------------------------------------------------------------------------------
class Banana : public Fruit {
public:
    Banana() : Fruit::Fruit(BANANA, "yellow") { setCalories(90); }

#ifdef LC_DEBUG
    ~Banana() { cout << "Banana destructor\n"; }
#endif
};

//------------------------------------------------------------------------------
// Orange
//------------------------------------------------------------------------------
class Orange : public Fruit {
public:
    Orange() : Fruit::Fruit(ORANGE, "orange") { setCalories(60); }

#ifdef LC_DEBUG
    ~Orange() { cout << "Orange destructor\n"; }
#endif
};

