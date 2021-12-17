/* Advent of code day 1 */

#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <vector>
#include <exception>

int main(){

  /*
   * Part1: Calculate horizontal position and depth you would have
   * after following the planned course.
   *
   * What do you get if you multiply your final horizontal position
   * by your final depth?
   */

  std::ifstream input("input.txt");
  std::vector<int> measurements;

  const char delim = ' ';

  int val;
  std::string action;

  int depth = 0;
  int horiz = 0;
  int aim = 0;

  if (input.is_open()){ std::string line;
    while (std::getline(input, line)){

      action = line.substr(0,line.find(delim));
      val = std::stoi(line.substr(line.find(delim)+1));

      if(action == "forward"){
        horiz += val;
        depth = depth + (aim*val);
      }

      if(action == "up"){
        aim -= val;
      }

      if(action == "down"){
        aim += val;
      }
    }
  }

  std::cout<<"Depth: "<<depth<<std::endl;
  std::cout<<"Horizontal: "<<horiz<<std::endl;

  std::cout<<"Horizontal*depth: "<<horiz*depth<<std::endl;

  input.close();

  return 0;
}
