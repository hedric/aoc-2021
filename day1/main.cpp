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

  int num_meas = measurements.size();

  std::cout<<"Total measurements: "<<num_meas<<std::endl;
  std::cout<<"Number of increases: "<<incr<<std::endl;

  //Part2: How many increases with the three measurement sliding window?
  int sum_window1 = 0;
  int sum_window2 = 0;
  int win_incr = 0;

  for (auto i=0; i<num_meas; i+=1){

    //Check if the window size index excedes the number of measurements.
    if (i+3 > num_meas || i+2 > num_meas || i+1 > num_meas){
      break;
    }

    sum_window1 += measurements[i];
    sum_window1 += measurements[i+1];
    sum_window1 += measurements[i+2];

    sum_window2 += measurements[i+1];
    sum_window2 += measurements[i+2];
    sum_window2 += measurements[i+3];

    if (sum_window2 > sum_window1){
      win_incr ++;
    }

    sum_window1 = 0;
    sum_window2 = 0;
  }

  std::cout<<"Number of window increases: "<<win_incr<<std::endl;

  input.close();

  return 0;
}
