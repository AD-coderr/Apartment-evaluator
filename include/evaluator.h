#pragma once

#include <vector>
#include "apartment.h"

struct Weights {
    double price;
    double space;
    double noise;
    
    Weights(double p = 0.4, double s = 0.35, double n = 0.25)
        : price(p), space(s), noise(n) {}
};

class Evaluator {
public:
    Evaluator(const Weights& weights = Weights());
    
    double scoreApartment(const Apartment& apt) const;
    std::vector<Apartment> rankApartments(std::vector<Apartment> apartments);
    
    void setWeights(const Weights& weights);
    Weights getWeights() const;
    
private:
    Weights weights;
};
