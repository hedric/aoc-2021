/* Advent of code day 3 */

#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <vector>
#include <bitset>

#define BITS 12

unsigned int calc_gamma(unsigned int bitcount[], unsigned int ctr){
    unsigned int result = 0;
    for(int i=0; i<BITS; i++){
      std::cout<<"bitcount: "<<bitcount[i]<<std::endl;
      if (bitcount[i] > ctr){
        result = (result | (1 << i));
      }
      else{
        result = (result | (0 << i));
      }
    }

    return result;
}
unsigned int calc_epsilon(unsigned int bitcount[], unsigned int ctr){
    unsigned int result = 0;
    for(int i=0; i<BITS; i++){
      std::cout<<"bitcount: "<<bitcount[i]<<std::endl;
      if (bitcount[i] < ctr){
        result = (result | (1 << i));
      }
      else{
        result = (result | (0 << i));
      }
    }

    return result;
}

int main(){

  std::ifstream input("input.txt");

  unsigned int pwr_cons = 0;
  unsigned int gamma_rate = 0;
  unsigned int epsilon_rate = 0;

  unsigned int bitcount[BITS] = {0};

  unsigned int ctr = 0;

  int bin_int;

  /* There is most likely a more efficient way of doing this, 
   * but lets count the number of rows/data points in the file
   * and then just sum all the bits "downwards". If the sum
   * is greater than the number of rows/2 we know that 1 is the most
   * common value for the corresponding bit */

  if (input.is_open()){ 

    std::string line;
    while (std::getline(input, line)){

      bin_int = std::stoi(line,nullptr,2);

      unsigned int bitmask = 1;
      unsigned int result;

      for (int i=0; i<BITS; i++){
        bitmask = (1 << (i));

        result = bitmask & (unsigned int)bin_int;

        if (result > 0){
          bitcount[i] += 1;
        }


      }
      ctr += 1;
    }
  }

  gamma_rate = calc_gamma(bitcount, ctr/2);
  epsilon_rate = calc_epsilon(bitcount, ctr/2);

  std::cout<<"gamma_rate = "<<gamma_rate<<std::endl;
  std::cout<<"gamma_rate = "<<std::bitset<BITS>(gamma_rate)<<std::endl;

  /* I should probably XAND the gamma_rate and avoid doing essentially the same
   * calculation again, and get rid of calc_epsilon... 

   unsigned int max_bits = (1 << BITS) - 1;
   std::cout<<"max_bits= "<<max_bits<<std::endl;
   epsilon_rate =(~(gamma_rate & (max_bits)));
   
  */

  std::cout<<"epsilon_rate = "<<epsilon_rate<<std::endl;
  std::cout<<"epsilon_rate = "<<std::bitset<BITS>(epsilon_rate)<<std::endl;
  
  pwr_cons = gamma_rate * epsilon_rate;

  std::cout<<"Power consumption: "<<pwr_cons<<std::endl;

  input.close();

  return 0;
}
