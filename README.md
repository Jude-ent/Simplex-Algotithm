Simplex Algorithm Implementation in C++
1. System Specifications
Operating System
Windows, macOS, or Linux
Required Software and Libraries
A C++ compiler (e.g., GCC, Clang, or MSVC)
CMake (optional, for build automation)
Standard Template Library (STL)
Hardware Requirements
Minimum 2GB RAM
Processor: Intel i3 or equivalent
Disk Space: At least 100MB free space
2. How the User Can Use It
Input Requirements
The program expects the user to enter:
Number of decision variables
Number of constraints
Coefficients for the objective function
Coefficients for the constraints
Right-hand side values for constraints
Expected Output
The program will return the optimal solution or indicate if the problem is unbounded or infeasible.
3. How the Code Works
Main Components
final.cpp: Implements the Simplex Algorithm
Simplex class:
Handles tableau initialization
Manages pivot selection and row operations
Executes the Simplex method
Extracts the optimal solution
Algorithm Overview
Initializes the simplex tableau.
Iteratively selects pivot elements.
Performs row operations to optimize the solution.
Terminates when the optimal solution is found.
Key Data Structures
vector<vector<double>> tableau: Stores the simplex tableau.
vector<int> basicVariables: Keeps track of basic variables.
4. README File
Program Description
This program implements the Simplex Algorithm to solve linear programming problems.

Example Code and Output
Example C++ Code (Simplex Algorithm)
#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>
using namespace std;

int main() {
    cout << "Simplex Algorithm Implementation" << endl;
    return 0;
}
Expected Output
Simplex Algorithm Implementation
Compilation and Execution
g++ final.cpp -o simplex
./simplex
Example Input and Expected Output
Example Question
Solve the following linear programming problem using the Simplex Algorithm:

Maximize Z = 3x1 + 5x2
Subject to:
  x1 + 2x2 ≤ 4
  2x1 + x2 ≤ 5
  x1, x2 ≥ 0
Example Input
Enter number of variables: 2
Enter number of constraints: 2
Enter the coefficients of the objective function: 3 5
Enter the coefficients of the constraints:
For constraint 1: 1 2
Enter the right-hand side: 4
For constraint 2: 2 1
Enter the right-hand side: 5
Expected Output
Optimal Solution:
x1 = 1
x2 = 1.5
Maximum Value of Objective Function: 10.5
The full implementation is available in final.cpp.
