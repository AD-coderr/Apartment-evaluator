#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <limits>
#include <fstream>
#include <sstream>
#include <filesystem>
#include "apartment.h"
#include "evaluator.h"

void displayMenu() {
    std::cout << "\n=== Apartment Evaluator Menu ===\n";
    std::cout << "1. Add apartment\n";
    std::cout << "2. View all apartments\n";
    std::cout << "3. Rank apartments\n";
    std::cout << "4. Customize weights\n";
    std::cout << "5. Load apartments from file\n";
    std::cout << "6. Save weights profile\n";
    std::cout << "7. Load weights profile\n";
    std::cout << "8. Clear all apartments\n";
    std::cout << "9. Exit\n";
    std::cout << "Choose an option (1-9): ";
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

bool loadApartmentsFromFile(std::vector<Apartment>& apartments, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error: Could not open file " << filename << "\n";
        return false;
    }
    
    std::string line;
    int loaded = 0;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        
        std::stringstream ss(line);
        std::string id, priceStr, spaceStr, noiseStr;
        
        if (std::getline(ss, id, ',') &&
            std::getline(ss, priceStr, ',') &&
            std::getline(ss, spaceStr, ',') &&
            std::getline(ss, noiseStr, ',')) {
            
            try {
                double price = std::stod(priceStr);
                double space = std::stod(spaceStr);
                double noise = std::stod(noiseStr);
                
                apartments.emplace_back(id, price, space, noise);
                loaded++;
            } catch (const std::exception&) {
                std::cout << "Warning: Skipping invalid line: " << line << "\n";
            }
        } else {
            std::cout << "Warning: Skipping malformed line: " << line << "\n";
        }
    }
    
    std::cout << "Loaded " << loaded << " apartments from " << filename << "\n";
    return loaded > 0;
}

bool saveWeightsProfile(const Weights& weights, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error: Could not create file " << filename << "\n";
        return false;
    }
    
    file << weights.price << "," << weights.space << "," << weights.noise << "\n";
    std::cout << "Weights profile saved to " << filename << "\n";
    return true;
}

bool loadWeightsProfile(Weights& weights, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error: Could not open file " << filename << "\n";
        return false;
    }
    
    std::string line;
    if (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string priceStr, spaceStr, noiseStr;
        
        if (std::getline(ss, priceStr, ',') &&
            std::getline(ss, spaceStr, ',') &&
            std::getline(ss, noiseStr, ',')) {
            
            try {
                double price = std::stod(priceStr);
                double space = std::stod(spaceStr);
                double noise = std::stod(noiseStr);
                
                double total = price + space + noise;
                if (total > 0) {
                    weights = Weights(price / total, space / total, noise / total);
                    std::cout << "Weights profile loaded from " << filename << "\n";
                    return true;
                }
            } catch (const std::exception&) {
                // fall through to error
            }
        }
    }
    
    std::cout << "Error: Invalid weights profile file\n";
    return false;
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
                std::string filename;
                std::cout << "\n--- Load Apartments from File ---\n";
                std::cout << "Enter filename (CSV format: ID,Price,Space,Noise): ";
                std::getline(std::cin, filename);
                
                if (loadApartmentsFromFile(apartments, filename)) {
                    std::cout << "Apartments loaded successfully!\n";
                }
                break;
            }
            
            case 6: {
                std::string filename;
                std::cout << "\n--- Save Weights Profile ---\n";
                std::cout << "Enter filename to save weights: ";
                std::getline(std::cin, filename);
                
                saveWeightsProfile(currentWeights, filename);
                break;
            }
            
            case 7: {
                std::string filename;
                std::cout << "\n--- Load Weights Profile ---\n";
                std::cout << "Enter filename to load weights: ";
                std::getline(std::cin, filename);
                
                if (loadWeightsProfile(currentWeights, filename)) {
                    evaluator.setWeights(currentWeights);
                    std::cout << "Weights loaded and applied!\n";
                }
                break;
            }
            
            case 8: {
                apartments.clear();
                std::cout << "\nAll apartments cleared.\n";
                break;
            }
            
            case 9: {
                std::cout << "\nThank you for using Apartment Evaluator. Goodbye!\n";
                return 0;
            }
            
            default:
                std::cout << "\nInvalid option. Please choose 1-9.\n";
        }
    }
    
    return 0;
}
