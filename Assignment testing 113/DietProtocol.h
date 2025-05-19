#ifndef DIETPROTOCOL_H
#define DIETPROTOCOL_H

#include <string>
using namespace std;

// Base class
class DietProtocol {
protected:
    string mealType;
    string mealName;
    int calories;

public:
    DietProtocol();
    DietProtocol(string mealType, string mealName, int calories);

    string getMealType() const;
    string getMealName() const;
    int getCalories() const;

    void setMealType(string type);
    void setMealName(string name);
    void setCalories(int cal);

    void displayMeal() const; // base version
};

class Breakfast : public DietProtocol {
public:
    Breakfast();
    Breakfast(string name, int cal);
    void displayMeal() const;
};

class Lunch : public DietProtocol {
public:
    Lunch();
    Lunch(string name, int cal);
    void displayMeal() const;
};

class Dinner : public DietProtocol {
public:
    Dinner();
    Dinner(string name, int cal);
    void displayMeal() const;
};

class Snack : public DietProtocol {
public:
    Snack();
    Snack(string name, int cal);
    void displayMeal() const;
};

#endif
