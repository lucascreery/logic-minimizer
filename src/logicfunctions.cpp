#include "logicfunctions.hpp"

term::term(int order, vector<literal> b) : order(order), bits(b), isPrime(true){
}

int term::oneCount(){
  int c = 0;
  for(int i = 0; i < order; i++){
    if(bits[i] == t) c++;
  }
  return c;
}

ostream& operator<<(ostream &os, const term&a){
  for(int i = 0; i < a.order; i++){
    switch(a.bits[i]){
      case t:
      os << '1';
      break;
      case f:
      os << '0';
      break;
      case x:
      os << '-';
      break;
    }
  }
  os << ' ' << a.output;
  return os;
}

bool term::contains(term &a){
  if((output & a.output) != a.output){
    return false;
  }
  for(int i = 0; i < a.bits.size(); i++){
    if(bits[i] != a.bits[i]){
      if(bits[i] != x){
        return false;
      }
    }
  }
  return true;
}

minterms::minterms(int order) : order(order){
  int size = pow(2, order);
  bits = new vector<literal>[size];
  for(int i = 0; i < pow(2, order); i++){
    for(int j = 0; j < order; j++){
      literal a = ((i>>j) % 2 == 1) ? t : f;
      bits[i].insert(bits[i].begin(), a);
    }
  }
}

term minterms::operator[](int a){
  return term(order, bits[a]);
}

term operator&(term &a, term &b){
  vector<literal> new_bits;
  for(int i = 0; i < a.order; i++){
    literal xliteral;
    if(a.bits[i] == b.bits[i]){
      xliteral = a.bits[i];
    }else{
      xliteral = x;
    }
    new_bits.push_back(xliteral);
  }
  term new_term(a.order, new_bits);
  new_term.output = a.output & b.output;
  return new_term;
}

int operator&=(term &a, term &b){
  int count = 0;
  for(int i = 0; i < a.order; i++){
    if(a.bits[i] != b.bits[i]) count++;
  }
  return count;
}

logic_function::logic_function(int order, int outputs, vector<literal> *truth_values,
                                string *i_names, string *o_names) 
                                : order(order), outputs(outputs), input_names(i_names), output_names(o_names) {
  minterms a(order);
  int count = 0;
  for(int i = 0; i < pow(2, order); i++){
    if(truth_values[i].size() != 0){
      for(int j = 0; j < outputs; j++){
        switch(truth_values[i][j]){
          case t:
          terms.push_back(a[i]);
          terms[terms.size() - 1].output = pow(2, outputs - j - 1);
          terms[terms.size() - 1].necessary = true;
          count ++;
          break;
          case x:
          terms.push_back(a[i]);
          terms[terms.size() - 1].output = pow(2, outputs - j - 1);
          terms[terms.size() - 1].necessary = false;
          count ++;
          break;
        }
      }
    }
  }
}

bool logic_function::isZero()  {
  if(order == 0){
    return true;
  }
  return false;
}

void logic_function::getPrimes(){
  vector<term> *truth_val_set;
  int *max_matches = new int[terms.size()];
  vector<term> lastterms;
  vector<term> implicants;
  int o = order;
  for(int i = 0; i < terms.size(); i++){
    for(int j = 0; j < implicants.size(); j++){
      if((terms[i] &= implicants[j]) == 0 && (terms[i].output & implicants[j].output) == 0){
        term temp = implicants[j];
        temp.isPrime = true;
        temp.output = terms[i].output | implicants[j].output;
        implicants.push_back(temp);
      }
    }
    implicants.push_back(terms[i]);
  }
  while(implicants.size() > 0){
    lastterms = implicants;
    implicants.clear();
    truth_val_set = new vector<term>[o+1];
    // Sort all of the terms into sets based on how many ones the term has
    for(int i = 0; i < lastterms.size(); i++){
      lastterms[i].isPrime = true;
      truth_val_set[lastterms[i].oneCount()].push_back(lastterms[i]);
    }
    // compare terms to terms of next adjacent set and check if they differ by one term
    // if so, add the combination term to new_terms
    for(int i = 0; i < o; i++){
      // i is the current set
      for(int j = 0; j < truth_val_set[i].size(); j++){
        //j is the current term in the ith set
        for(int k = 0; k < truth_val_set[i+1].size(); k++){
          // k is the term to compare to in the (i+1)th set
          if((truth_val_set[i][j] &= truth_val_set[i+1][k]) == 1 
                && (truth_val_set[i][j].output & truth_val_set[i+1][k].output) != 0){
            bool exists = false;
            term temp = truth_val_set[i][j] & truth_val_set[i+1][k];
            temp.isPrime = true;
            for(int n = 0; n < implicants.size(); n++){
              if((temp &= implicants[n]) == 0){
                exists = true;
              }
            }
            if(!exists){
              implicants.push_back(temp);
              truth_val_set[i][j].isPrime = false;
              truth_val_set[i+1][k].isPrime = false;
            }
          }
        }
      }
    }
    for(int i = 0; i < o + 1; i++){
      for(int j = 0; j < truth_val_set[i].size(); j++){
        if(truth_val_set[i][j].isPrime){
          for(int n = 0; n < implicants.size(); n++){
            if((truth_val_set[i][j] &= implicants[n]) == 1 && truth_val_set[i][j].output == implicants[n].output){
              truth_val_set[i][j].isPrime = false;
            }
          }
        }
        if(truth_val_set[i][j].isPrime){
          primes.push_back(truth_val_set[i][j]);
        }
      }
    }
    o--;
  }
}

void logic_function::petricksMethod(){
  if(primes.size() == 0){
    return;
  }
  int min_count = 0;
  for(int i = 0; i < terms.size(); i++){
    if(terms[i].necessary) min_count++;
  }
  bool **prime_implicants = new bool*[primes.size()];
  for(int i = 0; i < primes.size(); i++){
    prime_implicants[i] = new bool[min_count];
    int min_number = 0;
    for(int j = 0; j < terms.size(); j++){
      if(terms[j].necessary){
        prime_implicants[i][min_number] = primes[i].contains(terms[j]);
        min_number ++;
      }
    }
  }
  reduced_primes = reduce(prime_implicants, primes.size(), min_count);
}

ostream& operator<<(ostream &os, const logic_function &a){
  for(int function = 0; function < a.outputs; function++){
    if(a.output_names == NULL){
      os << "f" << function << " = ";
    }else{
      os << a.output_names[function] << " = ";
    }
    int first = true;
    for(int term = 0; term < a.reduced_primes.size(); term++){
      if((a.primes[a.reduced_primes[term]].output & (int)pow(2, a.outputs - 1 - function)) == (int)pow(2, a.outputs - 1 - function)){
        if(!first){
          os << " + ";
        }else{
          first = false;
        }
        for(int element = 0; element < a.order; element++){
          if(a.input_names == NULL){
            switch(a.primes[a.reduced_primes[term]].bits[element]){
              case t:
              os << "(I" << element + 1 << ")";
              break;
              case f:
              os << "(I" << element + 1 << ")'";
              break;
            }
          }else{
            switch(a.primes[a.reduced_primes[term]].bits[element]){
              case t:
              os << "(" << a.input_names[element] << ")";
              break;
              case f:
              os << "(" << a.input_names[element] << ")'";
              break;
            }
          }
        }
      }
    }
    os << "\n\n";
  }
  return os;
}