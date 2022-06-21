
#ifndef HW5_REGISTERGENERATOR_H
#define HW5_REGISTERGENERATOR_H

#include <string>

 /*This class generates a new register name, of the format: "tx" where x is a number. if the numbers are excceeding int_max
  * then we append more t's to the beginning, e.g: "tt6"*/
 class RegisterGenerator
{
     std::string _current_reg_prefix;
     int _current_reg_number;

 public:
    RegisterGenerator();
    std::string getRegister();
};

#endif //HW5_REGISTERGENERATOR_H
