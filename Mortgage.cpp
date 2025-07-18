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
    // Initialize all loan-related member variables to default values
    loan_amount = 0.0;               // Initial loan amount set to 0
    annual_interest_rate = 0.0;      // Annual interest rate set to 0%
    monthly_interest_rate = 0.0;     // Monthly interest rate set to 0%
    total_years_to_repay = 0;        // Total repayment duration in years set to 0
    number_of_payments = 0;          // Total number of payments set to 0

    // Output a message indicating the constructor execution for tracing/debugging
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
    // Display a message indicating the destructor is running, showing the current loan amount
    cout << "INFO: Executing DESTRUCTOR for Mortgage class (loan amount = "
         << fixed << setprecision(2) // Format loan amount to two decimal places
         << loan_amount << ")." << endl; // Output loan amount and close message
}

/*
    Set Loan Amount

    Programmer's Note:
        - Stores the principal loan amount.

    Simpler Terms:
        Saves how much money you want to borrow.
 */
void Mortgage::setLoanAmount(double amount) {
    loan_amount = amount; // Store the provided loan amount into the member variable
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
    annual_interest_rate = rate / 100.0;     // Convert percentage to decimal (e.g., 5% -> 0.05)
    monthly_interest_rate = annual_interest_rate / 12.0;  // Calculate monthly rate
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
    total_years_to_repay = years;             // Store the repayment period in years
    number_of_payments = total_years_to_repay * 12;  // Calculate total monthly payments
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
    // Safeguard: Return 0 if either the interest rate or number of payments is zero (invalid scenario)
    if (monthly_interest_rate == 0 || number_of_payments == 0) {
        return 0.0;
    }

    // Compute (1 + monthly_interest_rate) raised to the number_of_payments
    double power_factor = pow(1 + monthly_interest_rate, number_of_payments);

    // Apply the amortization formula for fixed-rate mortgages
    double monthly_payment = (loan_amount * monthly_interest_rate * power_factor) / (power_factor - 1);

    return monthly_payment;  // Return the computed monthly payment
}

/*
    Get Total Payback

    Programmer's Note:
        - Calculates the total amount paid back over the life of the loan.

    Simpler Terms:
        Calculates the total amount of money you’ll pay by the time the loan is fully paid off.
 */
double Mortgage::getTotalPayback() const {
    return getMonthlyPayment() * number_of_payments;  // Total payback = monthly payment * total number of payments
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
    // Creates and opens the output file stream with the specified filename
    ofstream outFile(filename);

    // Checks if the file failed to open
    if (!outFile) {
        // Display an error message to standard error output
        cerr << "ERROR: Could not open file " << filename << " for writing." << endl;
        // Exit the function early since writing to the file is not possible
        return;
    }

    // Define the banner message to label the payment schedule section
    const string bannerMessage = " Mortgage Payment Schedule ";

    // Define the total width of the banner for visual formatting
    constexpr int bannerWidth = 60;  // Adjust width as needed

    // Output the top border of the banner using '=' characters
    outFile << setfill('=') << setw(bannerWidth) << "=" << setfill(' ') << "\n"

    // Center the banner message within the defined banner width
            << setw(static_cast<int>((bannerWidth + bannerMessage.length()) / 2))
            << bannerMessage << endl;

    // Output the bottom border of the banner using '=' characters
    outFile << setfill('=') << setw(bannerWidth) << "=" << endl << endl;

    // Reset fill character back to space for normal output formatting
    outFile << setfill(' ');

    // Initialize the loan balance with the original loan amount
    double balance = loan_amount;

    // Retrieve the calculated monthly payment amount
    const double monthly_payment = getMonthlyPayment();

    // Format all subsequent numeric output with fixed-point notation, always show the decimal point,
    // and limit to two decimal places for currency representation
    outFile << fixed << showpoint << setprecision(2);

    // Output the loan details summary, formatted for readability
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

    // Defines the number of spaces to insert between columns for alignment
    constexpr int padding = 4;  // Space between columns

    // Define the header labels for the payment schedule table
    const vector<string> headers = { "Pmt#", "Payment Amount", "Interest", "Principal", "Remaining Balance" };

    // Initialize a vector to store the width of each column, starting with the length of each header
    vector<int> columnWidths(headers.size());
    for (unsigned int i = 0; i < headers.size(); ++i) {
        columnWidths[i] = static_cast<int>(headers[i].length());
    }

    // Iterate through each payment number to determine the maximum width required for each column
    for (int pmt_number = 1; pmt_number <= number_of_payments; ++pmt_number) {
        double interest = monthly_interest_rate * balance;
        double principal = monthly_payment - interest;
        balance -= principal;
        if (balance < 0.0) balance = 0.0;  // Prevent balance from going negative due to rounding

        // Update column width if the length of the current payment number is greater than the existing width
        if (static_cast<int>(to_string(pmt_number).length()) > columnWidths[0]) {
            columnWidths[0] = static_cast<int>(to_string(pmt_number).length());
        }

        // Update column width if the length of the monthly payment value is greater than the existing width
        if (static_cast<int>(to_string(monthly_payment).length()) > columnWidths[1]) {
            columnWidths[1] = static_cast<int>(to_string(monthly_payment).length());
        }

        // Update column width if the length of the interest value is greater than the existing width
        if (static_cast<int>(to_string(interest).length()) > columnWidths[2]) {
            columnWidths[2] = static_cast<int>(to_string(interest).length());
        }

        // Update column width if the length of the principal value is greater than the existing width
        if (static_cast<int>(to_string(principal).length()) > columnWidths[3]) {
            columnWidths[3] = static_cast<int>(to_string(principal).length());
        }

        // Update column width if the length of the remaining balance is greater than the existing width
        if (static_cast<int>(to_string(balance).length()) > columnWidths[4]) {
            columnWidths[4] = static_cast<int>(to_string(balance).length());
        }
    }

    // Set text alignment to left for printing the table headers
    outFile << left;

    // Output each header label with spacing defined by the header's length plus padding
    for (const auto& header : headers) {
        outFile << setw(static_cast<int>(header.length()) + padding) << header;
    }

    // Move to the next line after printing all headers
    outFile << endl;


    // Reset the balance to the original loan amount before generating the payment schedule output
    balance = loan_amount;

    // Iterate over each payment number to calculate and display the amortization details
    for (int pmt_number = 1; pmt_number <= number_of_payments; ++pmt_number) {
        // Calculate the interest portion of the current payment
        double interest = monthly_interest_rate * balance;

        // Calculate the principal portion by subtracting interest from the monthly payment
        double principal = monthly_payment - interest;

        // Update the remaining balance after applying the principal
        balance -= principal;
        if (balance < 0.0) balance = 0.0;  // Prevent negative balance due to rounding errors

        // Output each column value aligned to the right, with spacing based on the header length
        outFile << right
            << setw(static_cast<int>(headers[0].length())) << pmt_number << string(padding, ' ')
            << setw(static_cast<int>(headers[1].length())) << monthly_payment << string(padding, ' ')
            << setw(static_cast<int>(headers[2].length())) << interest << string(padding, ' ')
            << setw(static_cast<int>(headers[3].length())) << principal << string(padding, ' ')
            << setw(static_cast<int>(headers[4].length())) << balance
            << endl;
    }

    // Close the output file after writing the complete payment schedule
    outFile.close();

}
