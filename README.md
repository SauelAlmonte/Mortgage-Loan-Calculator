# Mortgage Loan Calculator

A C++ program that calculates fixed-rate mortgage payments and generates a detailed amortization schedule.

---

### Author
**Sauel Almonte**  
[LinkedIn Profile](https://www.linkedin.com/in/sauel-almonte)

---

## Features
- Calculates monthly mortgage payments based on loan amount, interest rate, and term.
- Computes total amount to be paid over the life of the loan.
- Optionally outputs a detailed payment schedule to a text file showing:
    - Payment number
    - Payment amount
    - Interest portion
    - Principal portion
    - Remaining loan balance
- Clean modular design:
    - **Mortgage.h** — Class declaration and function prototypes
    - **Mortgage.cpp** — Class implementation and calculations
    - **main.cpp** — User interface and program flow

---

## Project Structure

```
/mortgage-loan-calculator
├── Banner.cpp      # Implementation of banner display functions
├── Banner.h        # Banner display function declarations
├── CMakeLists.txt  # Build configuration for CMake
├── main.cpp        # Program entry point and user interaction
├── Mortgage.cpp    # Implementation of Mortgage class methods
├── Mortgage.h      # Mortgage class declaration and prototypes
├── mortgage.txt    # Sample or output amortization schedule (optional)
├── .gitignore      # Git ignore rules
└── README.md       # Project documentation
```

---

## Build & Run Instructions

### Prerequisites
- A C++ compiler (e.g., g++, clang++, or MSVC)
- C++17 standard or later
- IDE or editor:
    - JetBrains CLion
    - Visual Studio Code (VSCode)
    - Visual Studio (Windows)
    - Or terminal/command prompt

---

### Option 1: Compile & Run via Terminal
```
g++ -std=c++17 -o mortgage_calculator Banner.cpp Mortgage.cpp main.cpp
./mortgage_calculator
```
---

### Option 2: Using JetBrains CLion
1. Open CLion.
2. Select **Open** and navigate to the project directory.
3. CLion will configure CMake automatically.
4. Click **Build** or press `Shift + F9` to compile.
5. Press **Run** or `Shift + F10` to execute the program.

---

### Option 3: Using Visual Studio Code
1. Install the **C/C++ Extension Pack**.
2. Open the project folder in VSCode.
3. Compile via terminal:
```
g++ -std=c++17 -o mortgage_calculator Banner.cpp Mortgage.cpp main.cpp
./mortgage_calculator
```

---

### Option 4: Using Visual Studio (Windows)
1. Create a **New Console App Project**.
2. Add **Mortgage.h**, **Mortgage.cpp**, and **main.cpp** to the project.
3. Set the project to use the **C++17 standard** in Project Properties.
4. Build and run the solution.

---

## Usage

1. Run the program after building it.
2. Enter the loan amount, annual interest rate (percentage), and loan term (years) when prompted.
3. The program will calculate and display the monthly payment and total payback amount.
4. Optionally, you can generate a detailed payment schedule saved to a text file, showing monthly breakdowns of principal, interest, and remaining balance.
5. Choose to process another loan or exit the program.

---

### Example Output
```
============================================================
                 Mortgage Payment Schedule
============================================================

Loan Amount:              $250000.00
Annual Interest Rate:     4.75%
Years to repay:           30
Monthly Payment:          $1304.12
Total Pay Back:           $469482.60

Pmt#    Payment Amount    Interest    Principal    Remaining Balance
   1           1304.12       989.58       314.54           249685.46
   2           1304.12       988.34       315.78           249369.68

```

---

## License
This project is licensed under the [MIT License](LICENSE).  
This project is for academic and personal educational use only.
© 2025 Sauel Almonte. All rights reserved.
Do not redistribute or use commercially without explicit permission.

#### Disclaimer
This project is provided "as is" without any warranties or guarantees.  
The author is not responsible for any issues or damages resulting from its use.  
Use at your own discretion.

---
