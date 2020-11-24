#include "input.hpp"

logic_function getInputFunction(istream &input){
  string a;
  int num_inputs = 0;
  int num_outputs = 0;
  vector<literal> *outputs;
  string *input_names = NULL, *output_names = NULL;
  input >> a;
  while(a.compare(".e") != 0){
    if(a.compare(".i") == 0){
      input >> a;
      num_inputs = stoi(a);
      int count = pow(2, num_inputs);
      outputs = new vector<literal>[count];
    }else if(a.compare(".o") == 0){
      input >> a;
      num_outputs = stoi(a);
    }else if(a.compare(".ilb") == 0){
      input_names = new string[num_inputs];
      for(int i = 0; i < num_inputs; i++){
        input >> input_names[i];
      }
    }else if(a.compare(".olb") == 0){
      output_names = new string[num_outputs];
      for(int i = 0; i < num_outputs; i++){
        input >> output_names[i];
      }
    }else if(num_inputs == 0 || num_outputs == 0){
      cout << "Incorect file format" << a << '\n';
      return logic_function(0, 0, outputs);
    }else{
      int term = stoi(a, nullptr, 2);
      input >> a;
      if(outputs[term].size() == 0){
        for(int i = 0; i < a.size(); i++){
          switch(a[i]){
            case '1':
            outputs[term].push_back(t);
            break;
            case '0':
            outputs[term].push_back(f);
            break;
            case 'x':
            outputs[term].push_back(x);
            break;
          }
        }
      }else{
        for(int i = 0; i < a.size(); i++){
          switch(a[i]){
            case '1':
            outputs[term][i] = t;
            break;
            case 'x':
            outputs[term][i] = x;
            break;
          }
        }
      }
      //outputs[term] = stoi(a, nullptr, 2);
    }
    input >> a;
  }
  return logic_function(num_inputs, num_outputs, outputs, input_names, output_names);
}