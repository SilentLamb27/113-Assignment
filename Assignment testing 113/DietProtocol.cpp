#include "DietProtocol.h"
#include <iostream>
using namespace std;

// Base class implementation
DietProtocol::DietProtocol() : mealType(""), mealName(""), calories(0) {}
DietProtocol::DietProtocol(string type, string name, int cal) :
    mealType(type), mealName(name), calories(cal) {}

string DietProtocol::getMealType() const { return mealType; }
string DietProtocol::getMealName() const { return mealName; }
int DietProtocol::getCalories() const { return calories; }

void DietProtocol::setMealType(string type) { mealType = type; }
void DietProtocol::setMealName(string name) { mealName = name; }
void DietProtocol::setCalories(int cal) { calories = cal; }

void DietProtocol::displayMeal() const {
    cout << mealType << ": " << mealName << " (" << calories << " cal)\n";
}

// Derived class: Breakfast
Breakfast::Breakfast() : DietProtocol("Breakfast", "", 0) {}
Breakfast::Breakfast(string name, int cal) : DietProtocol("Breakfast", name, cal) {}
void Breakfast::displayMeal() const {
    cout << "Breakfast: " << mealName << " (" << calories << " cal)\n";
}

// Derived class: Lunch
Lunch::Lunch() : DietProtocol("Lunch", "", 0) {}
Lunch::Lunch(string name, int cal) : DietProtocol("Lunch", name, cal) {}
void Lunch::displayMeal() const {
    cout << "Lunch: " << mealName << " (" << calories << " cal)\n";
}

// Derived class: Dinner
Dinner::Dinner() : DietProtocol("Dinner", "", 0) {}
Dinner::Dinner(string name, int cal) : DietProtocol("Dinner", name, cal) {}
void Dinner::displayMeal() const {
    cout << "Dinner: " << mealName << " (" << calories << " cal)\n";
}

// Derived class: Snack
Snack::Snack() : DietProtocol("Snack", "", 0) {}
Snack::Snack(string name, int cal) : DietProtocol("Snack", name, cal) {}
void Snack::displayMeal() const {
    cout << "Snack: " << mealName << " (" << calories << " cal)\n";
}
