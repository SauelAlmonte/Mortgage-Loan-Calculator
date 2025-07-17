// Mortgage Class Implementation

#include "Mortgage.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>

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

    cout << "INFO: Executing constructor for Mortgage class." << endl;
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
    annual_interest_rate = rate;
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
        - Writes a detailed amortization schedule to a specified text file.
        - Includes payment number, monthly payment, interest, principal, and remaining balance.
        - Ensures balance doesn't drop below zero due to rounding.

    Simpler Terms:
        Saves a payment plan to a text file that shows what part of each monthly payment
        goes to interest, what reduces the loan, and how much is left to pay.
 */
void Mortgage::outputPaymentSchedule(const string& filename) const {
    ofstream outFile(filename);

    if (!outFile) {
        cerr << "ERROR: Could not open file " << filename << " for writing." << endl;
        return;
    }

    double balance = loan_amount;
    double monthly_payment = getMonthlyPayment();

    outFile << fixed << setprecision(2);
    outFile << "Loan Amount: $" << loan_amount << endl;
    outFile << "Annual Interest Rate: " << annual_interest_rate << endl;
    outFile << "Years to repay: " << total_years_to_repay << endl;
    outFile << "Monthly Payment: $" << monthly_payment << endl;
    outFile << "Total Pay Back: $" << getTotalPayback() << endl << endl;

    outFile << "Pmt#\tPayment Amount\tInterest\tPrincipal\tRemaining Balance" << endl;

    for (int pmt_number = 1; pmt_number <= number_of_payments; ++pmt_number) {
        double interest = monthly_interest_rate * balance;
        double principal = monthly_payment - interest;
        balance -= principal;

        if (balance < 0.0) balance = 0.0; // safeguard against negative due to floating point

        outFile << pmt_number << "\t"
                << monthly_payment << "\t\t"
                << interest << "\t\t"
                << principal << "\t\t"
                << balance << endl;
    }

    outFile.close();
}
