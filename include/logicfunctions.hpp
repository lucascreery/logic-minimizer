#ifndef LOGICFUNCTIONS_HPP
#define LOGICFUNCTIONS_HPP
#include <vector>
#include <math.h>
#include <iostream>
#include <string>
#include "petricks.hpp"

using namespace std;

enum literal {
  t = true,
  f = false,
  x = 2
};

class term {
  public:
  vector<literal> bits;
  int output;
  bool isPrime;
  bool necessary;
  //default constructor
  term(); 

  // consturcts term with (order) variables and bits (b)
  term(int order, vector<literal> b);   

  // Combines two terms; returns a term
  friend term operator&(term &, term &);  

  // Returns then number of literals in a term that are different
  friend int operator&=(term &, term &); 

  // Return the number of ones that a term has
  int oneCount(); 

  // Return true if the the term contains the term a
  bool contains(term &a);

  friend ostream& operator<<(ostream &os, const term&a);
  private:
  int order;
};

class minterms {
  public:
  // Constructs an array of all minterms for some order of function
  minterms(int order);  

  // Returns the (a)th minterm as a term
  term operator[](int a); 

  private:
  int order;
  vector<literal> *bits;
};

class logic_function{
  public:
  // Defualt constructor; 
  // Terms are initialized with minterms that are equal to (value)
  // Truth values are stored in the truth value vector
  logic_function(int order, int outputs, vector<literal> *truth_values, 
                  string *i_names = NULL, string *o_names = NULL); 

  // Uses terms to find all prime implicants
  // Prime implicants are stored in primes 
  void getPrimes();

  // Checks if a function was initiated with zero terms
  bool isZero();

  // Determine the inium sum of products from primes
  void petricksMethod();

  friend ostream& operator<<(ostream&, const logic_function&);
  private:
  string *input_names, *output_names;
  int order;
  int outputs;
  vector<term> terms;
  vector<term> primes;
  vector<int> reduced_primes;
};

#endif