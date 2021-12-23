/* Advent of code day 3 */

#include <algorithm>
#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <vector>
#include <bitset>
#include <bits/stdc++.h>

using namespace std;

#define BITS 12

unsigned int calc_gamma(unsigned int bitcount[], unsigned int ctr){
    unsigned int result = 0;
    for(int i=0; i<BITS; i++){
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
      if (bitcount[i] < ctr){
        result = (result | (1 << i));
      }
      else{
        result = (result | (0 << i));
      }
    }

    return result;
}

/* This function calculates an accumulative sum of the ones in each bit position
 * which is later used to determine whether ones or zeroes are the most common
 * value in current bit position 
 */
void sum_ones(vector<unsigned int> nums, unsigned int bitsum[BITS]){
  unsigned int bitmask = 1;
  unsigned int result;

  for(unsigned int i: nums){
    for (int j=BITS-1; j>=0; j--){
      bitmask = (1 << (j));
      result = bitmask & i;
      if (result > 0){
        bitsum[j] += 1;
      }
    }
  }
}

unsigned int filter_numbers(vector<unsigned int> numbers, bool most_common){

  int i=0; // bit iterator
  int j=0; // number iterator

  unsigned int bitmask = 1;
  unsigned int result;

  vector<unsigned int> tmp;

  unsigned int size = numbers.size();

  static unsigned int bitsum[BITS];

  sum_ones(numbers,bitsum);

  do{

    bitmask = (1 << (BITS-1-i));

    while((unsigned int)j < size){

      result = bitmask & numbers[j];
      
      if(most_common){
        if(bitsum[BITS-i-1] >= (size - bitsum[BITS-i-1])){
          if (result >= 1){
            tmp.push_back(numbers[j]);
          }
        }
        else
        {
          if (result < 1){
            tmp.push_back(numbers[j]);
          }
        }
      }
      else
      {
        if((size - bitsum[BITS-i-1]) <= bitsum[BITS-i-1]){
          if (result < 1){
            tmp.push_back(numbers[j]);
          }
        }
        else{
          if (result >= 1){
            tmp.push_back(numbers[j]);
          }
        }
      }

      j+=1;
    }

    size = tmp.size();
    numbers = tmp;

    // Set all entries to 0
    memset(bitsum,0,sizeof(bitsum));
    
    sum_ones(tmp,bitsum);

    j=0;  //set number iterator to 0
    i+=1; //increment bit
    tmp.resize(0);

  } while (size >= 1 && i<BITS);

  return numbers[0];
}

int main(){

  // Part 1

  ifstream input("input.txt");

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

  vector<unsigned int> numbers;

  if (input.is_open()){

    string line;
    while (getline(input, line)){

      bin_int = stoi(line,nullptr,2);
      numbers.push_back((unsigned int)bin_int);

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

  cout<<"gamma_rate = "<<gamma_rate<<endl;
  cout<<"gamma_rate binary = "<<bitset<BITS>(gamma_rate)<<endl;

  cout<<"epsilon_rate = "<<epsilon_rate<<endl;
  cout<<"epsilon_rate binary = "<<bitset<BITS>(epsilon_rate)<<endl;

  pwr_cons = gamma_rate * epsilon_rate;

  cout<<"Power consumption: "<<pwr_cons<<endl;

  input.close();

  // Part 2

  unsigned int o2_gen_rating = 0;
  unsigned int co2_scrub_rating = 0;
  unsigned int life_supp_rating = 0;

  cout<<"o2_gen_rating: "<<endl;
  o2_gen_rating = filter_numbers(numbers, true);
  cout<<"co2_scrub_rating: "<<endl;
  co2_scrub_rating = filter_numbers(numbers, false);

  life_supp_rating = o2_gen_rating*co2_scrub_rating;

  cout<<"o2 generator rating = "<<o2_gen_rating<<endl;
  cout<<"co2 scrubber rating = "<<co2_scrub_rating<<endl;
  cout<<"life support rating = "<<life_supp_rating<<endl;

  return 0;
}
