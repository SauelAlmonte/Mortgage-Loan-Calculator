// Mortgage Class Implementation

#include "Mortgage.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <vector>

using namespace std;

/*
    Constructor

    Programmer's Note:
        - Initializes member variables to default values by assignment.
        - Logs the creation of the Mortgage object for traceability.

    Simpler Terms:
        When a Mortgage object is created, this sets all loan details to zero
        and shows a message that the mortgage calculation is starting.
 */
Mortgage::Mortgage() {
    loan_amount = 0.0;
    annual_interest_rate = 0.0;
    monthly_interest_rate = 0.0;
    total_years_to_repay = 0;
    number_of_payments = 0;

    cout << "\nINFO: executing constructor for Mortgage class." << endl;
}

/*
    Destructor

    Programmer's Note:
        - Handles the cleanup when the Mortgage object is destroyed.
        - Outputs the loan amount for context during destruction.

    Simpler Terms:
        When the Mortgage object is finished, this shows a message
        that includes the loan amount to confirm cleanup.
 */
Mortgage::~Mortgage() {
    cout << "INFO: Executing DESTRUCTOR for Mortgage class (loan amount = "
         << fixed << setprecision(2) << loan_amount << ")." << endl;
}

/*
    Set Loan Amount

    Programmer's Note:
        - Stores the principal loan amount.

    Simpler Terms:
        Saves how much money you want to borrow.
 */
void Mortgage::setLoanAmount(double amount) {
    loan_amount = amount;
}

/*
    Set Annual Interest Rate

    Programmer's Note:
        - Stores the annual interest rate.
        - Calculates the equivalent monthly interest rate.

    Simpler Terms:
        Sets the yearly interest rate and figures out the monthly rate.
 */
void Mortgage::setAnnualInterestRate(double rate) {
    annual_interest_rate = rate / 100.0;
    monthly_interest_rate = annual_interest_rate / 12.0;
}

/*
    Set Total Years to Repay

    Programmer's Note:
        - Stores the repayment term in years.
        - Calculates the total number of monthly payments.

    Simpler Terms:
        Saves how many years you’ll take to pay off the loan,
        and figures out how many monthly payments that means.
 */
void Mortgage::setTotalYearsToRepay(int years) {
    total_years_to_repay = years;
    number_of_payments = total_years_to_repay * 12;
}

/*
    Get Monthly Payment

    Programmer's Note:
        - Computes the monthly mortgage payment using the standard amortization formula.
        - Returns zero if interest rate or number of payments is invalid.

    Simpler Terms:
        Calculates how much you have to pay every month on your loan.
 */
double Mortgage::getMonthlyPayment() const {
    if (monthly_interest_rate == 0 || number_of_payments == 0) {
        return 0.0;
    }

    double power_factor = pow(1 + monthly_interest_rate, number_of_payments);
    double monthly_payment = (loan_amount * monthly_interest_rate * power_factor) / (power_factor - 1);
    return monthly_payment;
}

/*
    Get Total Payback

    Programmer's Note:
        - Calculates the total amount paid back over the life of the loan.

    Simpler Terms:
        Calculates the total amount of money you’ll pay by the time the loan is fully paid off.
 */
double Mortgage::getTotalPayback() const {
    return getMonthlyPayment() * number_of_payments;
}

/*
    Output Payment Schedule (Extra Credit)

    Programmer's Note:
        - Writes a formatted, column-aligned amortization schedule to a specified text file.
        - Includes payment number, monthly payment, interest, principal, and remaining balance.
        - Prevents the remaining balance from dropping below zero due to rounding.

    Simpler Terms:
        Saves a monthly payment plan to a file that shows:
        - How much of each payment goes toward interest.
        - How much reduces the original loan.
        - How much is still left to pay after each month.
 */
void Mortgage::outputPaymentSchedule(const string& filename) const {
    // Creates and open the output file stream with the specified filename
    ofstream outFile(filename);

    // Checks if the file failed to open
    if (!outFile) {
        // Displays an error message to standard error output
        cerr << "ERROR: Could not open file " << filename << " for writing." << endl;
        // Exit the function early since writing to the file is not possible
        return;
    }

    const string bannerMessage = " Mortgage Payment Schedule ";
    constexpr int bannerWidth = 60;  // Adjust width as needed

    outFile << setfill('=') << setw(bannerWidth) << "=" << setfill(' ')<< "\n"
        << setw(static_cast<int>((bannerWidth + bannerMessage.length()) / 2))
        << bannerMessage << endl;
    outFile << setfill('=') << setw(bannerWidth) << "=" << endl << endl;

    // Reset fill for normal output
    outFile << setfill(' ');

    double balance = loan_amount;
    double monthly_payment = getMonthlyPayment();

    outFile << fixed << showpoint << setprecision(2);

    outFile << "Loan Amount:"
            << setw(15) << "$" << loan_amount << "\n"
            << "Annual Interest Rate:"
            << right << setw(9) << (annual_interest_rate * 100) << "%" << "\n"
            << "Years to repay:"
            << setw(13) << total_years_to_repay << "\n"
            << "Monthly Payment:"
            << setw(11) << "$" << monthly_payment << "\n"
            << "Total Pay Back:"
            << setw(12) << "$" << getTotalPayback() << endl << endl;

    constexpr int padding = 4;  // Space between columns
    vector<string> headers = { "Pmt#", "Payment Amount", "Interest", "Principal", "Remaining Balance" };

    vector<int> columnWidths(headers.size());
    for (unsigned int i = 0; i < headers.size(); ++i) {
        columnWidths[i] = static_cast<int>(headers[i].length());
    }

    for (int pmt_number = 1; pmt_number <= number_of_payments; ++pmt_number) {
        double interest = monthly_interest_rate * balance;
        double principal = monthly_payment - interest;
        balance -= principal;
        if (balance < 0.0) balance = 0.0;

        // Check and update width per column
        if (static_cast<int>(to_string(pmt_number).length()) > columnWidths[0]) {
            columnWidths[0] = static_cast<int>(to_string(pmt_number).length());
        }

        if (static_cast<int>(to_string(monthly_payment).length()) > columnWidths[1]) {
            columnWidths[1] = static_cast<int>(to_string(monthly_payment).length());
        }

        if (static_cast<int>(to_string(interest).length()) > columnWidths[2]) {
            columnWidths[2] = static_cast<int>(to_string(interest).length());
        }

        if (static_cast<int>(to_string(principal).length()) > columnWidths[3]) {
            columnWidths[3] = static_cast<int>(to_string(principal).length());
        }

        if (static_cast<int>(to_string(balance).length()) > columnWidths[4]) {
            columnWidths[4] = static_cast<int>(to_string(balance).length());
        }
    }

    outFile << left;
    for (const auto& header : headers) {
        outFile << setw(static_cast<int>(header.length()) + padding) << header;
    }
    outFile << endl;

    outFile << right;

    // Reset balance before outputting
    balance = loan_amount;

    for (int pmt_number = 1; pmt_number <= number_of_payments; ++pmt_number) {
        double interest = monthly_interest_rate * balance;
        double principal = monthly_payment - interest;
        balance -= principal;
        if (balance < 0.0) balance = 0.0;

        outFile
            << setw(static_cast<int>(headers[0].length())) << pmt_number << string(padding, ' ')
            << setw(static_cast<int>(headers[1].length())) << monthly_payment << string(padding, ' ')
            << setw(static_cast<int>(headers[2].length())) << interest << string(padding, ' ')
            << setw(static_cast<int>(headers[3].length())) << principal << string(padding, ' ')
            << setw(static_cast<int>(headers[4].length())) << balance
            << endl;

    }

    outFile.close();

}
