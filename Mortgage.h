// Mortgage Class Specification

#ifndef MORTGAGE_H
#define MORTGAGE_H

#include <string>
// using namespace std;

/*
    Class: Mortgage

    Programmer's Note:
        - Provides an abstraction for modeling and calculating fixed-rate mortgage data.
        - Encapsulates loan parameters, amortization logic, and output capabilities.
        - Promotes data integrity and computational accuracy.

    Simpler Terms:
        This class helps calculate your monthly home loan payments,
        the total cost of the loan, and can also generate a
        full monthly payment schedule in a text file.
 */
class Mortgage {
private:
    /*
        Private Member Variables

        Programmer's Note:
            - Stores loan details: principal amount, interest rates, and repayment terms.
            - Supports amortization calculations.

        Simpler Terms:
            Info about the loan: how much you borrowed, the interest rate, and how long you’ll take to repay.
     */
    double
        loan_amount,             // Amount borrowed (principal)
        annual_interest_rate,    // Annual interest rate (as a decimal, e.g., 0.05 for 5%)
        monthly_interest_rate;   // Monthly interest rate (annual / 12)

    int
        total_years_to_repay,    // Repayment period in years
        number_of_payments;      // Total payments (years * 12)

public:
    /*
        Constructor & Destructor

        Programmer's Note:
            - Handles the lifecycle of the Mortgage object.
            - Logs creation and destruction for traceability.

        Simpler Terms:
            When you start a loan, the constructor sets it up.
            When you're done, the destructor show's a message that the loan object is cleaned up.
     */
    Mortgage();     // Constructor
    ~Mortgage();    // Destructor

    /*
        Setter Methods for Core Loan Data

        Programmer's Note:
            - Interfaces to set or update loan parameters.
            - Maintains encapsulation and data integrity.

        Simpler Terms:
            Functions to enter or update the loan amount,
            interest rate, and repayment duration in years.
     */
    void setLoanAmount(double amount);          // Sets the loan amount (principal)
    void setAnnualInterestRate(double rate);    // Sets the annual interest rate (percentage)
    void setTotalYearsToRepay(int years);       // Sets the total years to repay the loan

    /*
        Financial Calculation Methods

        Programmer's Note:
            - Computes financial outputs dynamically,
              such as monthly payments and total payback.
            - Marked [[nodiscard]] to warn if the return value is ignored,
              helping prevent accidental misuse of critical financial data.

        Simpler Terms:
            Calculates how much you pay monthly
            and the total repayment amount over the loan term.
            The compiler will warn you if you ignore the results.
    */
    [[nodiscard]] double getMonthlyPayment() const;  // Calculates and returns the monthly mortgage payment
    [[nodiscard]] double getTotalPayback() const;    // Calculates and returns the total amount paid over the loan term


    /*
        Export Detailed Payment Schedule (Extra Credit)

        Programmer's Note:
            - Creates a detailed amortization schedule,
              writing payment breakdowns to a specified text file.

        Simpler Terms:
            Saves a full payment plan to a file,
            showing how each payment splits into interest, principal, and remaining balance.
     */
    void outputPaymentSchedule(const std::string& filename) const;  // Writes detailed amortization schedule to a file

};

#endif // MORTGAGE_H
