# Apartment Decision-Support System

A C++ interactive decision-support system that evaluates and ranks apartments based on multiple weighted criteria including price, living space, and noise levels.

## Features

- **Interactive Menu**: User-friendly command-line interface
- **Add Apartments Dynamically**: Input apartment details at runtime
- **Multi-criteria Evaluation**: Considers price, space, and noise level
- **Adjustable Preferences**: Customize the importance of each criterion with persistent weight profiles
- **File Input**: Load apartment data from CSV files
- **Web Interface**: Access the system through a web browser
- **Smart Ranking**: Automatically ranks apartments from best to worst
- **View & Manage**: Display all apartments or clear the list

## Prerequisites

- C++17 compatible compiler (g++, clang)
- Make build tool

## Building

```bash
make          # Compile both CLI and web versions
make run      # Run the CLI version
make web      # Run the web version
make clean    # Remove build artifacts
```

## Usage

### Command Line Version

Start the program:
```bash
./build/apartment_evaluator
```

### Menu Options

1. **Add apartment** - Enter a new apartment with ID, price, space, and noise level
2. **View all apartments** - Display all apartments in a formatted table
3. **Rank apartments** - See apartments ranked best to worst with weights used
4. **Customize weights** - Adjust the importance of price, space, and noise
5. **Load apartments from file** - Import apartment data from a CSV file (format: ID,Price,Space,Noise)
6. **Save weights profile** - Save current weights to a file for later use
7. **Load weights profile** - Load previously saved weights from a file
8. **Clear all apartments** - Remove all apartments from the list
9. **Exit** - Close the program

### Web Version

Start the web server:
```bash
./build/apartment_web
```

Then open your browser and navigate to `http://localhost:8080`

The web interface provides:
- Form to add new apartments
- Weight customization
- File upload for apartment data
- Real-time apartment list
- Ranking functionality

### File Format

For loading apartments from file, use CSV format with the following columns:
```
ID,Price,Space,Noise
```

Example `apartments.csv`:
```
Downtown Studio,1800,650,45
Suburban House,1200,1100,25
City Loft,2200,800,60
```
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
