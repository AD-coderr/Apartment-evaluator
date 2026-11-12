# Apartment Evaluator

![C++17](https://img.shields.io/badge/C%2B%2B-17-00599C?logo=cplusplus&logoColor=white)
![Build](https://img.shields.io/badge/build-make-informational)

A C++ **decision-support tool** that ranks apartments using a weighted multi-criteria score of price, living space and noise level.
It has an interactive command-line app and a small web interface built on [cpp-httplib](https://github.com/yhirose/cpp-httplib).

```
=== Ranked Apartments (Best to Worst) ===
----------------------------------------
1. Suburban House
2. Quiet Apartment
3. Downtown Studio
4. City Loft
5. Luxury Penthouse

Weights Used:
  Price:  40%
  Space:  35%
  Noise:  25%
```

## Features

- **Weighted scoring**: price (lower is better), space (higher is better), noise (lower is better)
- **Adjustable weights**: customize what matters to you; weights are normalized to 100%
- **Weight profiles**: save and load your preferences to and from a file
- **CSV import**: load a list of apartments in one go
- **Interactive CLI**: add, view, rank and clear apartments from a menu
- **Web interface**: add apartments, tweak weights and see rankings in the browser

## Build & run

Requires a C++17 compiler (g++ or clang) and `make`.

```bash
make          # build both the CLI and the web server into build/
make run      # start the CLI
make web      # start the web server on http://localhost:8080
make clean    # remove build output
```

## How the score works

Each apartment gets a weighted **cost score**, and the lowest score ranks first:

```
score = price × w_price + (1000 − space) × w_space + noise × w_noise
```

| Criterion | Default weight | Better when |
|-----------|---------------:|-------------|
| Price     | 40% | lower  |
| Space     | 35% | higher (sq ft, measured against 1000) |
| Noise     | 25% | lower (0–100 scale) |

## CLI menu

1. Add apartment
2. View all apartments
3. Rank apartments
4. Customize weights
5. Load apartments from file
6. Save weights profile
7. Load weights profile
8. Clear all apartments
9. Exit

### CSV format

```
ID,Price,Space,Noise
Downtown Studio,1800,650,45
Suburban House,1200,1100,25
City Loft,2200,800,60
```

A sample file is included as [`apartments.csv`](apartments.csv), and [`weights_profile.txt`](weights_profile.txt) is an example saved weight profile.

## Project structure

```
.
├── include/
│   ├── apartment.h      # Apartment model
│   └── evaluator.h      # Scoring and ranking
├── src/
│   ├── main.cpp         # Interactive CLI
│   ├── apartment.cpp
│   ├── evaluator.cpp
│   └── web_server.cpp   # Web interface (cpp-httplib)
├── external/httplib.h   # Single-header HTTP library
├── apartments.csv       # Sample data
└── Makefile
```

## Roadmap

- [ ] CSV upload in the web interface (currently CLI only)
- [ ] Location and commute-time criteria
- [ ] Amenities scoring
- [ ] Normalize criteria to a common scale (raw price currently outweighs noise)
- [ ] Unit tests
