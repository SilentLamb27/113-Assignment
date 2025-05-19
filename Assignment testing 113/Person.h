#ifndef PERSON_H
#define PERSON_H

#include <string>
#include "BodyMetric.h"
using namespace std;

class Person {
private:
    string username;
    int age;
    char gender;
    string goal;
    int intensityLevel;
    BodyMetric body;

public:
    // Constructors
    Person();
    Person(string n, int a, char g, double w, double h, string go);

    // Calculation methods
    float calculateBMR() const;
    float calculateTDEE() const;
    float getTargetCalories() const;
    float getMaxWorkoutCalories() const;
    float getMinMealCalories() const;

    // Comparison
    bool hasBetterBMIThan(const Person& other) const {
        return this->body.getBMI() < other.body.getBMI();
    }

    // Display
    void displayUserDetails() const;
    void displayProfile() const;
    void displayBMI() const;
    void displayBMIInfo(int rank) const;

    // Getters
    string getUsername() const;
    int getAge() const;
    char getGender() const;
    string getGoal() const;
    int getIntensityLevel() const;
    float getWeight() const;
    float getHeight() const;

    // Setters
    void setUsername(string name);
    void setAge(int a);
    void setGender(char g);
    void setGoal(string g);
    void setIntensityLevel(int level);
    void setWeight(float w);
    void setHeight(float h);
};

// BMI ranking (non-member)
void createBMIRanking(Person people[], int count);

#endif