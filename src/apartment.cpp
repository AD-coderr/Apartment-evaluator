#include "apartment.h"

Apartment::Apartment(const std::string& id, double price, double space, double noise)
    : id(id), price(price), space(space), noise(noise) {}

std::string Apartment::getId() const {
    return id;
}

double Apartment::getPrice() const {
    return price;
}

double Apartment::getSpace() const {
    return space;
}

double Apartment::getNoise() const {
    return noise;
}
