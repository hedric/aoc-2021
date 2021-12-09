/* Advent of code day 1 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main(){

  //Part1: How quickly does depth increase?

  // construct file stream
  std::ifstream input("input.txt");

  int incr = 0;
  int prev = 0;
  int curr = 0;

  std::vector<int> measurements;

  // loop through the file stream
  // cast string entires to integers
  // push integers to vector

  if (input.is_open()){
    std::string line;
    while (std::getline(input, line)){

      curr = std::stoi(line);

      if (curr > prev && prev != 0){
        incr++;
      }
      prev = curr;
      measurements.push_back(curr);

    }
  }

  std::cout<<"Total measurements: "<<measurements.size()<<std::endl;
  std::cout<<"Number of increases: "<<incr<<std::endl;

  input.close();

  return 0;
}
