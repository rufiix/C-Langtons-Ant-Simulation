# Langton's Ant Simulation in C

## Overview

This project is a C-based simulation of Langton's Ant, a two-dimensional universal Turing machine with a very simple set of rules. The ant moves on a grid of black and white cells, following a deterministic algorithm that leads to complex emergent behavior. Initially, the ant's movement appears chaotic, but after about 10,000 steps, it famously builds a recurring "highway" pattern.

This implementation allows users to configure the simulation's parameters, such as board dimensions, number of iterations, and the ant's starting conditions. The program outputs the state of the board to text files for each of the final 1000 iterations.

---

## Features

* **Configurable Simulation**: Set board size, iteration count, initial ant direction, and the percentage of initially black cells via command-line arguments.
* **Dynamic Board Generation**: The grid is dynamically allocated based on user-defined dimensions.
* **Step-by-Step Simulation**: The core logic processes the ant's movement and board state changes for each iteration.
* **State Output**: The program saves the last 1000 states of the simulation board as individual text files in the `out/` directory.
* **Modular Codebase**: The source code is logically divided into modules for the ant, the board, and the main application logic, as described in the project report.

---

## How to Compile and Run

### Prerequisites

* A C compiler (e.g., `gcc`)
* `make` utility

### Compilation

To compile the project, run the `make` command from the root directory. This will compile the source files from `src/` and place the executable `mrowka` into the `bin/` directory.

```bash
make all
