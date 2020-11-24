#include <iostream>
#include <fstream>
#include <string>
#include "input.hpp"
#include "logicfunctions.hpp"

using namespace std;

int main(int argc, char **argv)
{
  if (argc < 2)
  {
    cout << "Propper use: qm.exe [filename]\n";
    return 0;
  }
  ifstream input;
  input.open(argv[1]);
  if(!input.is_open()){
    cout << "Error opening file\n";
    return 0;
  }
  logic_function function1 = getInputFunction(input);
  if(function1.isZero()){
    cout << "Failed to initilaize function\n";
    return 0;
  }
  function1.getPrimes();
  function1.petricksMethod();
  cout << function1;
  return 0;
}