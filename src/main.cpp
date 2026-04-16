#include <iostream>
#include <vector>
#include <iomanip>
#include "apartment.h"
#include "evaluator.h"

int main() {
    // Create sample apartments
    std::vector<Apartment> apartments = {
        Apartment("apt1", 1500.0, 800.0, 45.0),
        Apartment("apt2", 1200.0, 650.0, 60.0),
        Apartment("apt3", 1800.0, 1000.0, 30.0),
        Apartment("apt4", 1400.0, 750.0, 50.0)
    };
    
    // Create evaluator with default weights (40% price, 35% space, 25% noise)
    Evaluator evaluator;
    
    std::cout << "=== Apartment Evaluation System ===\n\n";
    
    std::cout << "Available Apartments:\n";
    std::cout << std::string(70, '-') << "\n";
    std::cout << std::left << std::setw(10) << "ID"
              << std::setw(15) << "Price ($)"
              << std::setw(15) << "Space (sqft)"
              << std::setw(15) << "Noise (0-100)\n";
    std::cout << std::string(70, '-') << "\n";
    
    for (const auto& apt : apartments) {
        std::cout << std::left << std::setw(10) << apt.getId()
                  << std::fixed << std::setprecision(2)
                  << std::setw(15) << apt.getPrice()
                  << std::setw(15) << apt.getSpace()
                  << std::setw(15) << apt.getNoise() << "\n";
    }
    
    // Rank apartments
    auto ranked = evaluator.rankApartments(apartments);
    
    std::cout << "\n=== Ranked Apartments (Best to Worst) ===\n";
    std::cout << std::string(40, '-') << "\n";
    for (size_t i = 0; i < ranked.size(); ++i) {
        std::cout << i + 1 << ". " << ranked[i].getId() << "\n";
    }
    
    std::cout << "\nWeights Used:\n";
    Weights w = evaluator.getWeights();
    std::cout << "  Price:  " << w.price * 100 << "%\n";
    std::cout << "  Space:  " << w.space * 100 << "%\n";
    std::cout << "  Noise:  " << w.noise * 100 << "%\n";
    
    return 0;
}
