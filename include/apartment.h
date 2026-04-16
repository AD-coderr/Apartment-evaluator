#pragma once

#include <string>

class Apartment {
public:
    Apartment(const std::string& id, double price, double space, double noise);
    
    std::string getId() const;
    double getPrice() const;
    double getSpace() const;
    double getNoise() const;
    
private:
    std::string id;
    double price;   // Monthly rent
    double space;   // Square feet
    double noise;   // Noise level (0-100)
};
