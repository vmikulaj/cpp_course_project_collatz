// ----------------------------
// projects/collatz/Collatz.c++
// Copyright (C) 2016
// ----------------------------

// --------
// includes
// --------

#include <iostream> // istream, ostream
#include <string>   // string
#include <utility>  // pair

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <algorithm>


using namespace std;

// ------------
// collatz_read
// ------------

/**
* read two ints from r into i an j
* @param r an istream
* @param i an int
* @param j an int
* @return true if the read is successful, otherwise false
*/
bool collatz_read(istream& r, int& i, int& j);

// ------------
// collatz_eval
// ------------

/**
* @param i the beginning of the range, inclusive
* @param j the end       of the range, inclusive
* @return the max cycle length of the range [i, j)
*/
int collatz_eval(int i, int j);

// -------------
// collatz_print
// -------------

/**
* print three ints to w
* @param w an ostream
* @param i the beginning of the range, inclusive
* @param j the end       of the range, inclusive
* @param v the max cycle length
*/
void collatz_print(ostream& w, int i, int j, int v);

// -------------
// collatz_solve
// -------------

/**
* @param r an istream
* @param w an ostream
*/
void collatz_solve(istream& r, ostream& w);



// ------------
// collatz_read
// ------------

bool collatz_read(istream& r, int& i, int& j) {
    if (!(r >> i))
        return false;
    r >> j;
    return true;
}

int nextValue(int n) {
    if (n % 2 == 0)
        return (n / 2);       // if n is even
    else
        return (3 * n + 1);   // if n is odd
}

int cycleLength(int n) {
    // our base case
    // 1 has a cycle length of 1
    if (n == 1)
        return 1;

    // the cycle length of the current number is 1 greater
    // than the cycle length of the next number
    int length = 1 + cycleLength(nextValue(n));

    return length;
}

int collatz_eval(int i, int j) {
    int current_number;
    int max = 0;

    if (i > j)
        swap(i, j);

    for (current_number = i; current_number <= j; current_number++)
    {
        int current_length = cycleLength(current_number);
        if (current_length > max)
            max = current_length;
    }
    return max;
}

// -------------
// collatz_print
// -------------

void collatz_print(ostream& w, int i, int j, int v) {
    w << i << " " << j << " " << v << endl;
}

// -------------
// collatz_solve
// -------------

void collatz_solve(istream& r, ostream& w) {
    int i;
    int j;
    while (collatz_read(r, i, j)) {
        const int v = collatz_eval(i, j);
        collatz_print(w, i, j, v);
    }
}

// ----
// main
// ----

int main() {
    using namespace std;
    collatz_solve(cin, cout);
    return 0;
}

/*
% g++-4.8 -pedantic -std=c++11 -Wall -fprofile-arcs -ftest-coverage Collatz.c++ RunCollatz.c++ -o RunCollatz
% ./RunCollatz < RunCollatz.in > RunCollatz.tmp
% diff RunCollatz.tmp RunCollatz.out
*/

