# Apartment Decision-Support System

A C++ decision-support system that evaluates and ranks apartments based on multiple weighted criteria including price, space, and noise levels. The system implements a custom scoring algorithm for optimal apartment selection.

## Features

- **Multi-criteria evaluation**: Considers price, living space, and noise levels
- **Customizable weights**: Adjust the importance of each criterion
- **Scoring algorithm**: Normalized weighted scoring for fair comparison
- **Apartment ranking**: Automatically ranks apartments from best to worst

## Building the Project

### Prerequisites
- g++ or clang compiler with C++17 support

### Build Instructions

```bash
# Build the project
make

# Run the application
make run
```

## Project Structure

```
.
├── include/          # Header files
│   ├── apartment.h   # Apartment class definition
│   └── evaluator.h   # Evaluator class definition
├── src/              # Source files
│   ├── main.cpp      # Main application entry point
│   ├── apartment.cpp # Apartment implementation
│   └── evaluator.cpp # Evaluator implementation
├── Makefile          # Build configuration
└── README.md         # Project documentation
```

## Building and Running

```bash
make       # Compile the project
make run   # Run the application
make clean # Clean build artifacts
```
