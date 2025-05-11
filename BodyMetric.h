#ifndef BODYMETRIC_H
#define BODYMETRIC_H
#include "Person.h"

// The BodyMetric class extends Person to include body measurements and health calculations.
class BodyMetric : public Person {
    float weight; // User's weight in kilograms
    float height; // User's height in meters
    float bmi;    // User's Body Mass Index
public:
    // Default constructor initializes body metrics
    BodyMetric();
    // Set both weight and height, and calculate BMI
    void setMetrics(float w, float h);
    // Update only the weight and recalculate BMI
    void updateWeight(float w);
    // Update only the height and recalculate BMI
    void updateHeight(float h);
    // Calculate BMI based on current weight and height
    void calculateBMI();
    // Get the user's weight
    float getWeight() const;
    // Get the user's height
    float getHeight() const;
    // Get the user's BMI
    float getBMI() const;
    // Calculate Basal Metabolic Rate (BMR) based on user info
    float calculateBMR() const;
    // Calculate Total Daily Energy Expenditure (TDEE) based on BMR and activity level
    float calculateTDEE() const;
    // Get suggested daily calorie intake based on goal
    float getSuggestedCalories() const;
    // Display all body metrics and calculated values
    void displayMetrics() const;
    // Friend function to compare BMI between two BodyMetric objects
    friend bool compareBMI(const BodyMetric& a, const BodyMetric& b);
    // Operator overload to compare BMI between two BodyMetric objects
    bool operator>(const BodyMetric& other) const;
};

// Standalone function to compare BMI between two BodyMetric objects
bool compareBMI(const BodyMetric& a, const BodyMetric& b);

#endif 