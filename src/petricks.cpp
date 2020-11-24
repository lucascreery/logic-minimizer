#include "petricks.hpp"

p_term::p_term(){}

p_term p_term::operator*(p_term &a){
  p_term out;
  out.ps = ps;
  for(int i = 0; i < a.ps.size(); i++){
    bool exists = false;
    for(int j = 0; j < out.ps.size(); j++){
      if(a.ps[i] == out.ps[j]){
        exists = true;
        break;
      }
    }
    if(!exists){
      out.ps.push_back(a.ps[i]);
    }
  }
  return out;
}

bool p_term::contains(p_term a){
  if(a.ps.size() > ps.size()){
    return false;
  }
  for(int i = 0; i < a.ps.size(); i++){
    bool contains = false;
    for(int j = 0; j < ps.size(); j++){
      if(ps[j] == a.ps[i]){
        contains = true;
      }
    }
    if(!contains){
      return false;
    }
  }
  return true;
}

p_expression::p_expression(){}

p_expression &p_expression::operator*=(p_expression &a){
  vector<p_term> temp = terms;
  terms.clear();
  for(int i = 0; i < temp.size(); i++){
    for(int j = 0; j < a.terms.size(); j++){
      add_p_term(terms, temp[i] * a.terms[j]);
    }
  }
  return *this;
}

p_expression &p_expression::operator+=(p_term &a){
  terms.push_back(a);
  return *this;
}

vector<int> p_expression::get_reduced_terms(){
  float minimum = numeric_limits<float>::infinity();
  vector<int> ps;
  for(int i = 0; i < terms.size(); i++){
    if(terms[i].ps.size() < minimum){
      minimum = terms[i].ps.size();
      ps = terms[i].ps;
    }
  }
  return ps;
}

void add_p_term(vector<p_term> &a, p_term b){
  vector<p_term> temp = a;
  a.clear();
  bool addedB = false;
  for(int i = 0; i < temp.size(); i++){
    if(temp[i].contains(b)){
      a.push_back(b);
      addedB = true;
    }else{
      a.push_back(temp[i]);
    }
  }
  if(!addedB){
    a.push_back(b);
  }
}

vector<int> reduce(bool **prime_table, int primes, int minterms){
  vector<int> out;
  p_expression expression;
  for(int minterm = 0; minterm < minterms; minterm++){
    p_expression column_expression;
    for(int prime = 0; prime < primes; prime++){
      if(prime_table[prime][minterm]){
        p_term t;
        t.ps.push_back(prime);
        column_expression += t;
      }
    }
    if(minterm == 0){
      expression = column_expression;
    }else{
      expression *= column_expression;
    }
  }
  out = expression.get_reduced_terms();
  return out;
}