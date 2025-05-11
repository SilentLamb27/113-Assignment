#include "Person.h"

// Default constructor: Initializes all member variables to default values
Person::Person() {
    name[0] = '\0';           // Initialize name as empty string
    age = 0;                  // Initialize age to 0
    gender = 'M';             // Default gender to 'M'
    goal[0] = '\0';          // Initialize goal as empty string
    activityLevel[0] = '\0'; // Initialize activity level as empty string
}

// Sets all personal information and activity level for the user
void Person::setInfo(const char* n, int a, char g, const char* go, const char* act) {
    strcpy(name, n);          // Set name
    age = a;                  // Set age
    gender = g;               // Set gender
    strcpy(goal, go);         // Set goal
    strcpy(activityLevel, act); // Set activity level
}

// Returns the user's name
const char* Person::getName() const { return name; }
// Returns the user's gender
char Person::getGender() const { return gender; }
// Returns the user's age
int Person::getAge() const { return age; }
// Returns the user's goal
const char* Person::getGoal() const { return goal; }
// Returns the user's activity level
const char* Person::getActivityLevel() const { return activityLevel; }

// Displays all user information in a formatted way
void Person::display() const {
    cout << "Name: " << name << ", Age: " << age << ", Gender: " << gender
         << ", Goal: " << goal << ", Activity Level: " << activityLevel << endl;
} 