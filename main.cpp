/*
    Author      : Sauel Almonte
    Date        : July 17th, 2025
    Due Date    : July 22nd, 2025
    Course      : CSC 237
    Lab         : 13a – Mortgage
    Program     : Mortgage Loan Calculator

    Description:
        This program calculates the monthly payment and total repayment amount
        for a fixed-rate mortgage loan based on user-provided input such as
        loan amount, annual interest rate, and number of years to repay.

        The user can optionally generate a detailed payment schedule
        saved to a text file, which outlines the interest, principal,
        and remaining balance for each monthly payment.

        The program demonstrates class encapsulation, member functions,
        constructors/destructors, and file output operations.
*/

#include "Banner.h"
#include "Mortgage.h"
#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
using namespace std;

/*
    Function: main

    Programmer's Note:
        - Drives the Mortgage class functionality through user interaction.
        - Repeatedly prompts for loan details, calculates results, and offers
          the option to process additional loans.
        - Handles input clearing to prevent input stream issues.

    Simpler Terms:
        This is the main program that asks the user for loan info,
        shows the monthly payment and total payback,
        and asks if the user wants to process another loan.
 */
int main() {
    char choice = 'y'; // User input to control whether to continue looping

    displayBanner("Mortgage Loan Calculator"); // Display program banner

    while (tolower(choice) == 'y') {
        Mortgage loan;  // Create a new Mortgage object on each iteration

        double amount, rate;
        int years;

        cout << "\nEnter the amount of the loan: ";
        cin >> amount;
        loan.setLoanAmount(amount); // Set the loan amount for this Mortgage object

        cout << "Enter the annual interest rate as a percentage (e.g., 4.75 for 4.75%): ";
        cin >> rate;
        loan.setAnnualInterestRate(rate); // Set the annual interest rate

        cout << "Enter the length of the loan in years: ";
        cin >> years;
        loan.setTotalYearsToRepay(years); // Set total years for loan repayment

        cout << fixed << showpoint << setprecision(2); // Format monetary values with 2 decimals

        // Display the loan details and calculated payments
        cout << "\nLoan Amount:"
             << setw(15) << "$" << amount << "\n"
             << "Annual Interest Rate:"
             << right << setw(9) << rate << "%" << "\n"
             << "Years to repay:"
             << setw(13) << years << "\n"
             << "Monthly Payment:"
             << setw(11) << "$" << loan.getMonthlyPayment() << "\n"
             << "Total Pay Back:"
             << setw(12) << "$" << loan.getTotalPayback() << endl;

        // Prompt to generate detailed payment schedule file
        char generateSchedule;
        cout << "\nDo you want to generate the full payment schedule to a file? (y/n): ";
        cin >> generateSchedule;

        if (tolower(generateSchedule) == 'y') {
            string filename;
            cout << "Enter the output file name (e.g., schedule.txt): ";
            cin >> filename;
            loan.outputPaymentSchedule(filename); // Generate and save schedule
            cout << "Payment schedule saved to " << filename << endl;
        }

        cout << "\nDo you wish to process another loan? (y/n): ";
        cin >> choice;

        // Clear input buffer to handle any leftover characters, ensuring clean input for next iteration
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "\nProgram terminated. Thank you for using the Mortgage Calculator." << endl;
    return 0;
}
