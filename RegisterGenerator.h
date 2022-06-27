
#ifndef HW5_REGISTERGENERATOR_H
#define HW5_REGISTERGENERATOR_H

#include <string>

 /*This class generates a new register name, of the format: "tx" where x is a number. if the numbers are exceeding int_max
  * then we append more t's to the beginning, e.g: "tt6"*/
 class RegisterGenerator
{
     std::string _current_reg_prefix = "%t";
     int _current_reg_number = 0;
    RegisterGenerator() = default;
    std::string getRegisterInternal();

 public:
    RegisterGenerator(const RegisterGenerator&) = delete;
    RegisterGenerator& operator=(const RegisterGenerator&) = delete;
    static RegisterGenerator& Get();
    static std::string getRegister();
    static std::string getRawRegister(std::string& str);
};

#endif //HW5_REGISTERGENERATOR_H
