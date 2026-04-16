# Apartment Decision-Support System

A C++ interactive decision-support system that evaluates and ranks apartments based on multiple weighted criteria including price, living space, and noise levels.

## Features

- **Interactive Menu**: User-friendly command-line interface
- **Add Apartments Dynamically**: Input apartment details at runtime
- **Multi-criteria Evaluation**: Considers price, space, and noise level
- **Customizable Weights**: Adjust the importance of each criterion
- **Smart Ranking**: Automatically ranks apartments from best to worst
- **View & Manage**: Display all apartments or clear the list

## Prerequisites

- C++17 compatible compiler (g++, clang)
- Make build tool

## Building

```bash
make          # Compile the project
make run      # Run the application
make clean    # Remove build artifacts
```

## Usage

Start the program:
```bash
./build/apartment_evaluator
```

### Menu Options

1. **Add apartment** - Enter a new apartment with ID, price, space, and noise level
2. **View all apartments** - Display all apartments in a formatted table
3. **Rank apartments** - See apartments ranked best to worst with weights used
4. **Customize weights** - Adjust the importance of price, space, and noise
5. **Clear all apartments** - Remove all apartments from the list
6. **Exit** - Close the program

### Example Session

```
=== Welcome to Apartment Evaluation System ===
This system helps you find the best apartment based on your criteria.

=== Apartment Evaluator Menu ===
1. Add apartment
2. View all apartments
3. Rank apartments
4. Customize weights
5. Clear all apartments
6. Exit
Choose an option (1-6): 1

--- Add New Apartment ---
Enter apartment ID: Downtown Studio
Enter monthly price ($): 1800
Enter space (sqft): 650
Enter noise level (0-100): 45
Apartment added successfully!
```

## Scoring Algorithm

The system uses a weighted scoring model:
- **Price** (40% by default): Lower is better
- **Space** (35% by default): Higher is better
- **Noise** (25% by default): Lower is better (0-100 scale)

Weights are automatically normalized when customized, so they always sum to 100%.

## Project Structure

```
.
├── include/          # Header files
│   ├── apartment.h   # Apartment class
│   └── evaluator.h   # Evaluator and scoring logic
├── src/              # Implementation
│   ├── main.cpp      # Interactive menu and program logic
│   ├── apartment.cpp # Apartment class implementation
│   └── evaluator.cpp # Scoring and ranking implementation
├── Makefile          # Build configuration
└── README.md         # This file
```

## Compilation Details

- **C++ Standard**: C++17
- **Compiler Flags**: -Wall -Wextra -Wpedantic (warnings enabled)
- **Output**: `build/apartment_evaluator`

## Future Enhancements

- File I/O (save/load apartment lists)
- Location-based criteria
- Commute time estimation
- Amenities scoring
- Database integration
- GUI interface

## License

Feel free to use and modify this project for your needs.
