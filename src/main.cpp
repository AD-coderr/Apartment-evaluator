#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <limits>
#include "apartment.h"
#include "evaluator.h"

void displayMenu() {
    std::cout << "\n=== Apartment Evaluator Menu ===\n";
    std::cout << "1. Add apartment\n";
    std::cout << "2. View all apartments\n";
    std::cout << "3. Rank apartments\n";
    std::cout << "4. Customize weights\n";
    std::cout << "5. Clear all apartments\n";
    std::cout << "6. Exit\n";
    std::cout << "Choose an option (1-6): ";
}

void displayApartments(const std::vector<Apartment>& apartments) {
    if (apartments.empty()) {
        std::cout << "\nNo apartments added yet.\n";
        return;
    }
    
    std::cout << "\n=== Available Apartments ===\n";
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
}

void rankAndDisplay(std::vector<Apartment> apartments, const Evaluator& evaluator) {
    if (apartments.empty()) {
        std::cout << "\nNo apartments to rank.\n";
        return;
    }
    
    auto ranked = evaluator.rankApartments(apartments);
    
    std::cout << "\n=== Ranked Apartments (Best to Worst) ===\n";
    std::cout << std::string(40, '-') << "\n";
    for (size_t i = 0; i < ranked.size(); ++i) {
        std::cout << i + 1 << ". " << ranked[i].getId() << "\n";
    }
}

int main() {
    std::vector<Apartment> apartments;
    Weights currentWeights(0.4, 0.35, 0.25);
    Evaluator evaluator(currentWeights);
    int choice;
    
    std::cout << "=== Welcome to Apartment Evaluation System ===\n";
    std::cout << "This system helps you find the best apartment based on your criteria.\n";
    
    while (true) {
        displayMenu();
        std::cin >> choice;
        
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        switch (choice) {
            case 1: {
                std::string id;
                double price, space, noise;
                
                std::cout << "\n--- Add New Apartment ---\n";
                std::cout << "Enter apartment ID: ";
                std::getline(std::cin, id);
                
                std::cout << "Enter monthly price ($): ";
                std::cin >> price;
                
                std::cout << "Enter space (sqft): ";
                std::cin >> space;
                
                std::cout << "Enter noise level (0-100): ";
                std::cin >> noise;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                
                apartments.emplace_back(id, price, space, noise);
                std::cout << "Apartment added successfully!\n";
                break;
            }
            
            case 2: {
                displayApartments(apartments);
                break;
            }
            
            case 3: {
                rankAndDisplay(apartments, evaluator);
                
                std::cout << "\nWeights Used:\n";
                std::cout << "  Price:  " << currentWeights.price * 100 << "%\n";
                std::cout << "  Space:  " << currentWeights.space * 100 << "%\n";
                std::cout << "  Noise:  " << currentWeights.noise * 100 << "%\n";
                break;
            }
            
            case 4: {
                double priceW, spaceW, noiseW;
                
                std::cout << "\n--- Set Custom Weights ---\n";
                std::cout << "Enter weight for price (0-1): ";
                std::cin >> priceW;
                
                std::cout << "Enter weight for space (0-1): ";
                std::cin >> spaceW;
                
                std::cout << "Enter weight for noise (0-1): ";
                std::cin >> noiseW;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                
                double total = priceW + spaceW + noiseW;
                if (total > 0) {
                    currentWeights = Weights(priceW / total, spaceW / total, noiseW / total);
                    evaluator.setWeights(currentWeights);
                    std::cout << "Weights updated successfully!\n";
                } else {
                    std::cout << "Error: Weights must sum to a positive value.\n";
                }
                break;
            }
            
            case 5: {
                apartments.clear();
                std::cout << "\nAll apartments cleared.\n";
                break;
            }
            
            case 6: {
                std::cout << "\nThank you for using Apartment Evaluator. Goodbye!\n";
                return 0;
            }
            
            default:
                std::cout << "\nInvalid option. Please choose 1-6.\n";
        }
    }
    
    return 0;
}
