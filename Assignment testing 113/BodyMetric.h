#ifndef BODYMETRIC_H
#define BODYMETRIC_H

class BodyMetric {
private:
    float weight;
    float height; // in meters

public:
    BodyMetric();
    BodyMetric(float weight, float height);

    float getWeight() const;
    float getHeight() const;
    void setWeight(float w);
    void setHeight(float h);

    float getBMI() const;
    void display() const;
};

#endif