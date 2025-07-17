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
            - Encapsulated data members representing principal amount,
              interest rates, and repayment terms for amortization computations.

        Simpler Terms:
            These are the main loan details: how much you borrowed,
            the interest rate, and how long you’ll take to pay it back.
     */
    double
        loan_amount,             // Principal borrowed
        annual_interest_rate,    // Annual interest rate as a decimal (e.g., 0.05 for 5%)
        monthly_interest_rate;   // Monthly interest rate (annual / 12)
    int
        total_years_to_repay,    // Total number of years to pay off the loan
        number_of_payments;      // Total number of payments (years * 12)

public:
    /*
        Constructor & Destructor

        Programmer's Note:
            - Manages the lifecycle of the Mortgage object.
            - Logs instantiation and destruction to trace object management.

        Simpler Terms:
            When you start working on a loan, the constructor sets everything up.
            When you're done, the destructor runs and shows a message that the loan process has finished.
     */
    Mortgage();     // Constructor
    ~Mortgage();    // Destructor

    /*
        Setter Methods for Core Loan Data

        Programmer's Note:
            - Provides controlled interfaces to set or update loan parameters.
            - Ensures encapsulation and data integrity.

        Simpler Terms:
            These functions let you enter or update the loan amount,
            interest rate, and how many years you’ll take to pay it off.
     */
    void setLoanAmount(double amount);
    void setAnnualInterestRate(double rate);
    void setTotalYearsToRepay(int years);

    /*
        Financial Calculation Methods

        Programmer's Note:
            - Accessor methods that dynamically compute financial outputs
              like monthly payments and total repayment amounts.

        Simpler Terms:
            These functions calculate your monthly loan payment
            and the total amount you’ll pay back to the bank.
     */
    double getMonthlyPayment() const;
    double getTotalPayback() const;

    /*
        Export Detailed Payment Schedule (Extra Credit)

        Programmer's Note:
            - Generates a comprehensive amortization schedule
              and writes it to the specified text file.
            - Details each payment's interest, principal reduction,
              and remaining balance.

        Simpler Terms:
            This function saves a detailed payment plan to a text file,
            showing each month's payment breakdown: how much goes to interest,
            how much reduces the loan, and how much you still owe.
     */
    void outputPaymentSchedule(const std::string& filename) const;
};

#endif // MORTGAGE_H
