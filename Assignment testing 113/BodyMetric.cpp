#include "BodyMetric.h"
#include <iostream>
using namespace std;

BodyMetric::BodyMetric() : weight(0), height(0) {}

BodyMetric::BodyMetric(float w, float h) : weight(w), height(h) {}

float BodyMetric::getWeight() const {
    return weight;
}

float BodyMetric::getHeight() const {
    return height;
}

void BodyMetric::setWeight(float w) {
    if (w > 0)
        weight = w;
    else
        weight = 0; // or handle invalid input differently
}

void BodyMetric::setHeight(float h) {
    if (h > 0)
        height = h;
    else
        height = 0; // or handle invalid input differently
}

float BodyMetric::getBMI() const {
    if (height == 0) return 0;
    return weight / (height * height);
}

void BodyMetric::display() const {
    cout << "\n========================\n";
    cout << "||     User's BMI      ||\n";
    cout << "========================\n";
    cout << "| " "Weight: " << weight << " kg        |\n";
    cout << "| " "Height: " << height << " m        |\n";
    cout << "| " "BMI: " << getBMI() << "         |\n";
    cout << "========================\n";

    float bmi = getBMI();
    if (bmi == 0)
        cout << " (Invalid height or weight)";
    else if (bmi < 18.5)
        cout << " (Underweight)";
    else if (bmi < 25)
        cout << " (Normal weight)";
    else if (bmi < 30)
        cout << " (Overweight)";
    else
        cout << " (Obese)";

    cout << "\n";
}
