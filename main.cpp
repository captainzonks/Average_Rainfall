/////////////////////
// Matthew Barham
// 2022-04-30
///////////////////////////////////////////////////////////////////
// Average Rainfall
//
// Takes input of average monthly rainfall and actual monthly rainfall
// then produces a pretty table, or graph, of the rainfall difference from the average.
//
///////////////////////////////////////////////////////////////////

#include <iostream>
#include <iomanip>

namespace Rainfall {

    const std::string months[]{"January",
                               "February",
                               "March",
                               "April",
                               "May",
                               "June",
                               "July",
                               "August",
                               "September",
                               "October",
                               "November",
                               "December"};
    const int total_months{12}; // length of the months array

    double average_monthly_rainfall[12]{};
    double actual_monthly_rainfall[12]{};
    int current_month{};

    /**
     *  Retrieves the average rainfall per month from the user
     */
    void get_monthly_average_rainfall() {
        for (size_t i{}; i < total_months; ++i) {
            std::cout << "Enter the average rainfall in inches in " << months[i] << ": ";
            std::cin >> average_monthly_rainfall[i];
        }
    }

    /**
     * Retrieves the actual monthly rainfall from the user, beginning w/ the current month
     */
    void get_actual_monthly_average_rainfall() {
        while (current_month < 1 || current_month > 12) {
            std::cout << "Enter a number for the current month (i.e. 1 for January, 2 for February: ";
            std::cin >> current_month;
            std::cout << std::endl;

            // do not proceed if input is outside of array bounds
            if (current_month < 1 || current_month > 12) {
                std::cout << "The month index you entered is invalid." << std::endl;
            }
        }

        // subtract 1 for array indexing
        current_month -= 1;
        // setup a mutable index
        int i{current_month};

        do {
            --i;
            // did we just do January? if so, go to December
            if (i < 0) {
                i = total_months - 1;
            }

            std::cout << "Enter the real rainfall last " << months[i] << ": ";
            std::cin >> actual_monthly_rainfall[i];
        } while (i != current_month);
    }

    /**
     * Prints a pretty table of actual rainfall differences from the monthly average
     */
    void print_table() {
        // top header border
        std::cout << "\n";
        for (size_t i{}; i < 50; ++i) {
            std::cout << "=";
        }
        std::cout << "\n";

        // header titles
        std::cout << std::setw(10) << std::left << "Month" <<
                  std::setw(1) << std::left << " || " <<
                  std::setw(5) << std::left << "Last Rainfall" <<
                  std::setw(1) << std::left << " || " <<
                  std::setw(1) << std::left << "Average Diff. " << std::endl;

        // bottom header border
        for (size_t i{}; i < 50; ++i) {
            std::cout << "=";
        }
        std::cout << "\n";

        // setup mutable index
        int index{current_month};
        do {
            --index;
            // did we do January? if so, go to December
            if (index < 0) {
                index = total_months - 1;
            }

            // bunch of pretty formatting calls in here to make the table look decent
            std::cout << std::endl;
            std::cout << std::setw(10) << std::left <<
                      months[index] << " || " <<
                      std::setw(13) << std::left <<
                      actual_monthly_rainfall[index] << " || " <<
                      std::setw(1) << std::left <<
                      std::showpos << actual_monthly_rainfall[index] - average_monthly_rainfall[index] <<
                      std::noshowpos;
        } while (index != current_month);

        std::cout << std::endl;

        // footer
        for (size_t i{}; i < 50; ++i) {
            std::cout << "=";
        }
        std::cout << "\n";
    }

    /**
     * Helper function to print asterisks (taken from Chapter 7.2 Display 7.8)
     * @param n Number of asterisks to print
     */
    void print_asterisks(int n) {
        for (size_t i{}; i <= n; ++i) {
            std::cout << "*";
        }
    }

    /**
     * Prints a bar of asterisks for actual and average rainfall per month (taken from Chapter 7.2 Display 7.8)
     */
    void print_graph() {
        std::cout << "\nRainfall Actual vs Average" << std::endl;
        for (size_t i{}; i < total_months; ++i) {
            std::cout << std::setw(4) << "||" << months[i] << std::endl;
            std::cout << "Actual: ";
            print_asterisks(static_cast<int>(actual_monthly_rainfall[i]));
            std::cout << "\nAverage: ";
            print_asterisks(static_cast<int>(average_monthly_rainfall[i]));
            std::cout << std::endl;
        }
    }

}

int main() {
    Rainfall::get_monthly_average_rainfall();
    Rainfall::get_actual_monthly_average_rainfall();

    int input{-1};
    while (input != 0) {
        std::cout << "Would you like to see the table (1) or graph (2) or quit (0)? ";
        std::cin >> input;

        switch (input) {
            case 1:
                Rainfall::print_table();
                break;
            case 2:
                Rainfall::print_graph();
                break;
            case 0:
                std::cout << "Quitting.\n";
                break;
            default:
                std::cout << "Invalid request.\n";
        }
    }
    return 0;
}
