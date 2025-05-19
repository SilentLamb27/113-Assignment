#include <iostream>
#include <iomanip>
#include "Person.h"
using namespace std;

// Constructors
Person::Person() {
    username = "";
    age = 0;
    gender = ' ';
    goal = "";
    intensityLevel = 1;
}

Person::Person(string n, int a, char g, double w, double h, string go) {
    username = n;
    age = a;
    gender = g;
    goal = go;
    intensityLevel = 1;
    body.setWeight(w);
    body.setHeight(h);
}

// Setters
void Person::setUsername(string n) { username = n; }
void Person::setAge(int a) { age = a; }
void Person::setGender(char g) { gender = g; }
void Person::setGoal(string g) { goal = g; }
void Person::setIntensityLevel(int level) { intensityLevel = level; }
void Person::setWeight(float w) { body.setWeight(w); }
void Person::setHeight(float h) { body.setHeight(h); }

// Getters
string Person::getUsername() const { return username; }
int Person::getAge() const { return age; }
char Person::getGender() const { return gender; }
string Person::getGoal() const { return goal; }
int Person::getIntensityLevel() const { return intensityLevel; }
float Person::getWeight() const { return body.getWeight(); }
float Person::getHeight() const { return body.getHeight(); }

// Calculations
float Person::calculateBMR() const {
    float height_cm = body.getHeight() * 100;
    if (gender == 'M' || gender == 'm')
        return 10 * body.getWeight() + 6.25 * height_cm - 5 * age + 5;
    else
        return 10 * body.getWeight() + 6.25 * height_cm - 5 * age - 161;
}

float Person::calculateTDEE() const {
    float factor;
    switch (intensityLevel) {
        case 1: factor = 1.2; break;
        case 2: factor = 1.375; break;
        case 3: factor = 1.55; break;
        case 4: factor = 1.725; break;
        case 5: factor = 1.9; break;
        default: factor = 1.55; break;
    }
    return calculateBMR() * factor;
}

float Person::getTargetCalories() const {
    if (goal == "Lose weight") return calculateTDEE() - 500;
    if (goal == "Gain weight") return calculateTDEE() + 500;
    return calculateTDEE();
}

float Person::getMaxWorkoutCalories() const {
    return calculateTDEE() * 0.4f;
}

float Person::getMinMealCalories() const {
    return calculateTDEE() * 0.2f;
}

// Displays
void Person::displayUserDetails() const {
    cout << "Username: " << username << endl;
    cout << "Age: " << age << endl;
    cout << "Gender: " << gender << endl;
    cout << "Weight: " << body.getWeight() << " kg" << endl;
    cout << "Height: " << body.getHeight() << " m" << endl;
    cout << "Goal: " << goal << endl;
    cout << "------------------------------" << endl;
}

void Person::displayProfile() const {
    cout << "\n===========================================\n";
    cout << "||           User Profile Summary         ||\n";
    cout << "===========================================\n";
    cout << "| Username   : " << username << "\n";
    cout << "| Age        : " << age << "\n";
    cout << "| Gender     : " << gender << "\n";
    cout << "| Weight     : " << body.getWeight() << " kg\n";
    cout << "| Height     : " << body.getHeight() << " m\n";
    cout << "| Goal       : " << goal << "\n";
    string activityDesc[] = {"Invalid", "Sedentary", "Lightly Active", "Moderately Active", "Very Active", "Super Active"};
    cout << "| Intensity  : " << activityDesc[intensityLevel] << " (" << intensityLevel << ")\n";
    cout << "|-----------------------------------------|\n";
    cout << "| BMR        : " << calculateBMR() << " kcal\n";
    cout << "| TDEE       : " << calculateTDEE() << " kcal\n";
    cout << "===========================================\n";
}

void Person::displayBMI() const {
    body.display();
}

void Person::displayBMIInfo(int rank) const {
    float bmi = body.getBMI();
    string status;

    if (bmi < 18.5)       status = "Underweight";
    else if (bmi < 25.0)  status = "Normal";
    else if (bmi < 30.0)  status = "Overweight";
    else                  status = "Obese";

    cout << "| " << setw(4) << left << rank << " | "
         << setw(10) << left << username << " | "
         << setw(7) << left << fixed << setprecision(1) << bmi << " | "
         << setw(15) << left << status << " |\n";
}

// Non-member leaderboard function
void createBMIRanking(Person people[], int count) {
    // Sort by BMI ascending
    for (int i = 0; i < count - 1; ++i) {
        for (int j = 0; j < count - i - 1; ++j) {
            if (!people[j].hasBetterBMIThan(people[j + 1])) {
                Person temp = people[j];
                people[j] = people[j + 1];
                people[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < count; ++i) {
        people[i].displayBMIInfo(i + 1);
    }
}