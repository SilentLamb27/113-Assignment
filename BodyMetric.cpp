#include "BodyMetric.h"
#include <iostream>
#include <cstring>
using namespace std;

// Default constructor: Initializes weight, height, and BMI to zero
BodyMetric::BodyMetric() : weight(0), height(0), bmi(0) {}

// Sets both weight and height, then recalculates BMI
void BodyMetric::setMetrics(float w, float h) {
    weight = w;
    height = h;
    calculateBMI();
}

// Updates only the weight and recalculates BMI
void BodyMetric::updateWeight(float w) {
    weight = w;
    calculateBMI();
}

// Updates only the height and recalculates BMI
void BodyMetric::updateHeight(float h) {
    height = h;
    calculateBMI();
}

// Calculates BMI using the formula: weight (kg) / (height (m) * height (m))
void BodyMetric::calculateBMI() {
    bmi = weight / (height * height);
}

// Returns the user's weight in kilograms
float BodyMetric::getWeight() const { return weight; }
// Returns the user's height in meters
float BodyMetric::getHeight() const { return height; }
// Returns the user's BMI
float BodyMetric::getBMI() const { return bmi; }

// Calculates Basal Metabolic Rate (BMR) using the Mifflin-St Jeor Equation
float BodyMetric::calculateBMR() const {
    if (gender == 'M' || gender == 'm')
        return (10 * weight) + (6.25 * height * 100) - (5 * age) + 5; // For males
    else
        return (10 * weight) + (6.25 * height * 100) - (5 * age) - 161; // For females
}

// Calculates Total Daily Energy Expenditure (TDEE) based on BMR and activity level
float BodyMetric::calculateTDEE() const {
    float bmr = calculateBMR();
    if (strcmp(activityLevel, "Sedentary") == 0) return bmr * 1.2f;
    if (strcmp(activityLevel, "LightlyActive") == 0) return bmr * 1.375f;
    if (strcmp(activityLevel, "ModeratelyActive") == 0) return bmr * 1.55f;
    if (strcmp(activityLevel, "VeryActive") == 0) return bmr * 1.725f;
    if (strcmp(activityLevel, "SuperActive") == 0) return bmr * 1.9f;
    return bmr * 1.2f; // Default to Sedentary if not matched
}

// Returns suggested daily calorie intake based on user's goal
float BodyMetric::getSuggestedCalories() const {
    float tdee = calculateTDEE();
    if (strcmp(goal, "lose") == 0) return tdee - 500;   // For weight loss
    if (strcmp(goal, "gain") == 0) return tdee + 500;   // For weight gain
    return tdee; // For maintenance
}

// Displays all body metrics and calculated values for the user
void BodyMetric::displayMetrics() const {
    display();
    cout << "Weight: " << weight << " kg, Height: " << height << " m, BMI: " << bmi << endl;
    cout << "BMR: " << calculateBMR() << ", TDEE: " << calculateTDEE()
         << ", Suggested Calories: " << getSuggestedCalories() << endl;
}

// Operator overload: Returns true if this user's BMI is greater than the other's
bool BodyMetric::operator>(const BodyMetric& other) const {
    return bmi > other.bmi;
}

// Friend/standalone function: Returns true if the first user's BMI is greater than the second's
bool compareBMI(const BodyMetric& a, const BodyMetric& b) {
    return a.bmi > b.bmi;
} 