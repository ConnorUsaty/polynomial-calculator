#include "Poly.h"
#include <iostream>
#include <chrono>

using namespace std;

int MAX_TESTS = 1000;


string generateRandomPoly() {
    // Generate a random polynomial of the form ax^0+bx^1+cx^2+...
    
    string poly = "";
    int numTerms = rand() % 10 + 1;
    for (int i = 0; i < numTerms; ++i) {
        int coeff = rand() % 100 + 1;
        int exp = i;
        poly += to_string(coeff) + "x^" + to_string(exp);
        if (i != numTerms - 1) {
            poly += "+";
        }
    }
    return poly;
}


int testParser() {
    // Test the parser by generating random polynomials and checking if the parser can parse them

    // Get starting timepoint
    auto start = chrono::high_resolution_clock::now();

    int success = 0;
    vector<string> fails;

    for (int i = 0; i < MAX_TESTS; ++i) {
        string test = generateRandomPoly();
        Poly p = Poly(test);
        string result = p.toString();
        if (result != test) {
            fails.push_back(test);
        } else {
            success++;
        }
    }

    // Get ending timepoint
    auto stop = chrono::high_resolution_clock::now();

    cout << "Parser tests: " << success << "/" << MAX_TESTS << " passed." << endl;
    cout << "Time taken: " << chrono::duration_cast<chrono::milliseconds>(stop - start).count() << " milliseconds" << endl;

    if (fails.size() > 0) {
        cout << "Failed tests: " << endl;
        for (string fail : fails) {
            cout << fail << endl;
        }
    }

    return success;
}

int main() {
    // Calls test suite -> Currently only tests parser
    
    if (testParser() == MAX_TESTS) {
        cout << "Parser passed all tests!" << endl;
    }

    return 0;
}
