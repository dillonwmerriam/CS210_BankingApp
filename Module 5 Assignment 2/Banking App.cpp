/*
 * Bank App IT 210.cpp
 *
 *  Date: 10/21/2023
 *  Author: Dillon Merriam
 *
 * Given the user input values of initial investment, the amount of a recurring monthly deposit,
 * the interest rate, and to plan on investing on however many years - this program will calculate
 * the projections for yearly end-balances as well as the total yearly interest accrued.
 * 
 * Essentially the way this program works is the main() function calls the printDataInput() function
 * which prompts a user for 4 pieces of data (initial investment, monthly deposit amount, interest rate,
   and # of years) that are stored into variables which are then sent to be calculated and then those
   calculations are sent into print functions that properly format the data and make it look aesthetically 
   pleasing.
 */

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

//function to create proper amount of whitespace between "Balance" and "Interest" results
//no whitespace function is required between "Year" and "Balance" since it will be a fixed amount
void printWhiteSpaces(int yearEndBalance, int interestEarned) {
    
    //log10(num)+1 = # of digits it contains (not including the 2 decimals, so add those 4)
    //add 2 decimal points and 2 dollar signs and this = numChars.
    int numChars = floor(log10(yearEndBalance)) + floor(log10(interestEarned)) + 9;
    int numSpaces;
    string whiteSpaces;
    
    for (numSpaces = 0; numSpaces < 31 - numChars; numSpaces++) {
        whiteSpaces += " ";
    }
    
    cout << whiteSpaces;
}

//prints formatted lines of calculated data to the console
void printDetails(int year, double yearEndBalance, double interestEarned) {
    cout << "  " << year << "                 " << "$" << fixed << setprecision(2) << yearEndBalance;
    printWhiteSpaces(yearEndBalance, interestEarned);
    cout << "$" << interestEarned << endl;
    cout << endl;
}

//function to create proper amount of whitespace between "Balance" and "Interest" results
//no whitespace function is required between "Year" and "Balance" since it will be a fixed amount
void calculateBalanceWithoutMonthlyDeposit(double initialInvestment, double interestRate, int numberOfYears) {

    double balance = initialInvestment;
    double monthlyInterest = (interestRate / 100) / 12;
    double interestEarned;

    //iterate over each of the 12 months to find the accumulative yearly interestEarned
    //at the same time, keep track of the growth in balance, and what the final balance is which = yearEndBalance
    for (int i = 1; i <= numberOfYears; i++) {
        interestEarned = 0;

        for (int j = 0; j < 12; j++) {
            interestEarned += balance * monthlyInterest;
            balance += balance * monthlyInterest;
        }

        // after calculating yearEndBalance and interestEarned, print a line of data with the function "printDetails"
        double yearEndBalance = balance;
        int year = i;
        printDetails(year, yearEndBalance, interestEarned);
    }
}

double calculateBalanceWithMonthlyDeposit(double initialInvestment, double monthlyDeposit, double interestRate, int numberOfYears) {

    //balance will grow from initialInvestment until it reaches the end and becomes yearEndBalance
    double balance = initialInvestment;
    double monthlyInterest = (interestRate / 100) / 12;
    double interestEarned = 0;

    //if numberOfYears = 0, yearEndBalance = initialInvestment
    if (numberOfYears > 0) {
        for (int year = 1; year <= numberOfYears; year++) {
            interestEarned = 0;
            for (int month = 1; month <= 12; month++) {
                //if it is the first month, interestEarned = balance times the interest rate
                //balance = balance + interestEarned
                if (year == 1 && month == 0) {
                    interestEarned += balance * monthlyInterest;
                    balance += interestEarned;
                }
                else {
                    interestEarned += (balance + monthlyDeposit) * monthlyInterest;
                    double balanceWithDeposit = balance + monthlyDeposit;
                    balance = balance + monthlyDeposit + ((balance + monthlyDeposit) * monthlyInterest);
                }
            }
            double yearEndBalance = balance;
            //pass crucial data of year, balance, and interest to the print function
            printDetails(year, yearEndBalance, interestEarned);
        }
        balance += monthlyDeposit;
    }
    return balance;
}

void printComputedResults(double initialInvestment, double monthlyDeposit, double interestRate, int numberOfYears) {

    //printed this header that looks symmetrical, taking time to count the spaces
    //Afterwards, send data to calculate functions, which send them to print functions

    cout << "================================================================" << endl;
    cout << "   Balance and Interest Without Additional Monthly Deposits    " << endl;
    cout << "================================================================" << endl;
    cout << endl;
    cout << "  Year         Year End Balance        Year End Earned Interest    " << endl;
    cout << endl;
    cout << "----------------------------------------------------------------" << endl;
    cout << endl;
    calculateBalanceWithoutMonthlyDeposit(initialInvestment, interestRate, numberOfYears);
    cout << "================================================================" << endl;
    cout << "   Balance and Interest With Additional Monthly Deposits    " << endl;
    cout << "================================================================" << endl;
    cout << endl;
    cout << "  Year         Year End Balance        Year End Earned Interest    " << endl;
    cout << endl;
    cout << "----------------------------------------------------------------" << endl;
    cout << endl;
    calculateBalanceWithMonthlyDeposit(initialInvestment, monthlyDeposit, interestRate, numberOfYears);

}

void printDataInput() {

    //declare variables that will be initialized with user input values
    double initialInvestment;
    double monthlyDeposit;
    double interestRate;
    double numberOfYears;
    int anyKey;

    //Header
    cout << "*********************************" << endl;
    cout << endl;
    cout << "********** " << "Data Input " << "***********" << endl;
    cout << endl;
    //Data Prompt. I put spaces in there to better center the text
    cout << "  Initial Investment: " << endl;
    cout << "         ";
    cin >> initialInvestment;
    cout << "  Monthly Deposit: " << endl;
    cout << "         ";
    cin >> monthlyDeposit;
    cout << "  Annual Interest: " << endl;
    cout << "         ";
    cin >> interestRate;
    cout << "  Number of Years" << endl;
    cout << "         ";
    cin >> numberOfYears;
    cout << endl;
    cout << "    Press any key and hit" << endl;
    cout << "      enter to continue " << endl;
    cout << endl;
    cin >> anyKey;

    //send user data to the print function
    printComputedResults(initialInvestment, monthlyDeposit, interestRate, numberOfYears);
}


int main() {
    printDataInput();

    return 0;
}