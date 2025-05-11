#ifndef PERSON_H
#define PERSON_H
#include <iostream>
#include <cstring>
using namespace std;

// The Person class represents a user with basic personal information and health goals.
class Person {
protected:
    char name[50];            // User's name
    int age;                  // User's age
    char gender;              // 'M' for male, 'F' for female
    char goal[10];            // User's goal: "lose", "maintain", or "gain" weight
    char activityLevel[20];   // User's activity level (e.g., "Sedentary")
public:
    // Default constructor initializes member variables
    Person();
    // Set all personal information and activity level
    void setInfo(const char* n, int a, char g, const char* go, const char* act);
    // Get the user's name
    const char* getName() const;
    // Get the user's gender
    char getGender() const;
    // Get the user's age
    int getAge() const;
    // Get the user's goal
    const char* getGoal() const;
    // Get the user's activity level
    const char* getActivityLevel() const;
    // Display all user information
    void display() const;
};

#endif 