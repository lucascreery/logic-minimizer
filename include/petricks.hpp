#ifndef PETRICKS_HPP
#define PETRICKS_HPP
#include <vector>
#include <iostream>
#include <limits>

using namespace std;

class p_term {
  public:
  // Contains the prime numbers in the term
  vector<int> ps;
  p_term();

  // Mulitplies one term of primes to another
  p_term operator*(p_term&);

  // Returns true if all of the expressions in the provided term are also in this term
  bool contains(p_term);
  private:
};

class p_expression {
  public:
  p_expression();

  // Returns an expression of the expression times a second expression
  p_expression &operator*=(p_expression&);

  // Returns an expression of the expression plus a second expression
  p_expression &operator+=(p_term&);

  // Returns a vector of type int where each int denotes which prime is necessary in the minimum expression
  vector<int> get_reduced_terms();
  private:
  vector<p_term> terms;
};

// Adds a term to the an existing vector of terms
void add_p_term(vector<p_term>&, p_term);

// Reduces a prime implication table and returns a vector of ints that denote which primes are necessary
vector<int> reduce(bool **prime_table, int primes, int minterms);

#endif