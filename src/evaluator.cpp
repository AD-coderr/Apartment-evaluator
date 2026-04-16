#include "evaluator.h"
#include <algorithm>

Evaluator::Evaluator(const Weights& weights) : weights(weights) {}

double Evaluator::scoreApartment(const Apartment& apt) const {
    double priceScore = apt.getPrice() * weights.price;
    double spaceScore = (1000.0 - apt.getSpace()) * weights.space;
    double noiseScore = apt.getNoise() * weights.noise;
    
    return priceScore + spaceScore + noiseScore;
}

std::vector<Apartment> Evaluator::rankApartments(std::vector<Apartment> apartments) const {
    std::sort(apartments.begin(), apartments.end(),
        [this](const Apartment& a, const Apartment& b) {
            return scoreApartment(a) < scoreApartment(b);
        });
    return apartments;
}

void Evaluator::setWeights(const Weights& weights) {
    this->weights = weights;
}

Weights Evaluator::getWeights() const {
    return weights;
}
