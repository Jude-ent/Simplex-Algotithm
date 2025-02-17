#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>

using namespace std;

// Step 1: Define the Simplex class
class Simplex {
private:
    int m, n;  // Number of constraints (m) and number of decision variables (n)
    vector<vector<double>> tableau; // Stores the Simplex tableau (matrix)

public:
    // Constructor to initialize the tableau
    Simplex(int num_variables, int num_constraints) {
        n = num_variables;
        m = num_constraints;
        // Create (m+1) rows and (n+m+1) columns (extra for slack vars & RHS)
        tableau.resize(m + 1, vector<double>(n + m + 1, 0));
    }

    // Step 2: Function to input constraints and objective function
    void input() {
        cout << "Enter the coefficients of the objective function (c1, c2, ..., cn): ";
        for (int i = 0; i < n; i++) {
            cin >> tableau[0][i];  // Objective function coefficients
            tableau[0][i] = -tableau[0][i]; // Convert maximization format
        }

        cout << "Enter the coefficients of the constraint equations:\n";
        for (int i = 1; i <= m; i++) {
            cout << "For constraint " << i << ":\n";
            for (int j = 0; j < n; j++) {
                cin >> tableau[i][j]; // Constraint coefficients
            }
            cout << "Enter the right-hand side (b" << i << "): ";
            cin >> tableau[i][n + m]; // RHS values

            // Add slack variables (Identity matrix form)
            tableau[i][n + i - 1] = 1;
        }
    }

    // Step 3: Function to display the current tableau
    void displayTableau() {
        cout << "\nCurrent Tableau:\n";
        for (int i = 0; i <= m; i++) {
            for (int j = 0; j <= n + m; j++) {
                cout << setw(10) << fixed << setprecision(2) << tableau[i][j] << " ";
            }
            cout << endl;
        }
    }

    // Step 4: Identify the Pivot Column (Entering Variable)
    int getPivotColumn() {
        int pivot_col = -1;
        double min_value = 0;
        for (int j = 0; j < n + m; j++) {
            if (tableau[0][j] < min_value) {
                min_value = tableau[0][j];
                pivot_col = j;
            }
        }
        return pivot_col;
    }

    // Step 5: Identify the Pivot Row (Leaving Variable)
    int getPivotRow(int pivot_col) {
        int pivot_row = -1;
        double min_ratio = numeric_limits<double>::infinity();
        for (int i = 1; i <= m; i++) {
            if (tableau[i][pivot_col] > 0) {
                double ratio = tableau[i][n + m] / tableau[i][pivot_col];
                if (ratio < min_ratio) {
                    min_ratio = ratio;
                    pivot_row = i;
                }
            }
        }
        return pivot_row;
    }

    // Step 6: Perform Pivoting (Row Operations)
    void pivot(int pivot_row, int pivot_col) {
        double pivot_element = tableau[pivot_row][pivot_col];

        // Normalize pivot row
        for (int j = 0; j <= n + m; j++) {
            tableau[pivot_row][j] /= pivot_element;
        }

        // Make other elements in the pivot column zero
        for (int i = 0; i <= m; i++) {
            if (i != pivot_row) {
                double factor = tableau[i][pivot_col];
                for (int j = 0; j <= n + m; j++) {
                    tableau[i][j] -= factor * tableau[pivot_row][j];
                }
            }
        }
    }

    // Step 7: Implement the Simplex Algorithm
    void solve() {
        while (true) {
            displayTableau(); // Show current tableau

            int pivot_col = getPivotColumn(); // Identify pivot column
            if (pivot_col == -1) {
                cout << "Optimal solution found.\n";
                break;
            }

            int pivot_row = getPivotRow(pivot_col); // Identify pivot row
            if (pivot_row == -1) {
                cout << "The problem is unbounded.\n";
                return;
            }

            // Perform pivot operation
            pivot(pivot_row, pivot_col);
        }
    }

    // Step 8: Extract the Optimal Solution
    void getSolution() {
        vector<double> solution(n, 0); // Initialize solution vector

        for (int j = 0; j < n; j++) {
            int basis_row = -1;
            bool is_basic = true;

            for (int i = 1; i <= m; i++) {
                if (tableau[i][j] == 1) {
                    if (basis_row == -1)
                        basis_row = i;
                    else
                        is_basic = false;
                } else if (tableau[i][j] != 0) {
                    is_basic = false;
                }
            }

            if (is_basic && basis_row != -1) {
                solution[j] = tableau[basis_row][n + m]; // Assign RHS value
            }
        }

        // Display final solution
        cout << "\nOptimal Solution:\n";
        for (int i = 0; i < n; i++) {
            cout << "x" << i + 1 << " = " << solution[i] << endl;
        }
        cout << "Maximum Value of Objective Function: " << tableau[0][n + m] << endl;
    }
};

// Step 9: Initialize Tableau and Run the Algorithm
int main() {
    int num_variables, num_constraints;
    cout << "Enter number of variables: ";
    cin >> num_variables;
    cout << "Enter number of constraints: ";
    cin >> num_constraints;

    // Create Simplex object
    Simplex simplex(num_variables, num_constraints);
    simplex.input(); // Take user input
    simplex.solve(); // Run the algorithm
    simplex.getSolution(); // Display results

    return 0;
}
