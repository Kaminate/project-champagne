#include "ErrorMessage.h"
#include <string>

/*!
  @brief This function is used to show an error to the console
  @param line use __LINE__
  @param function ues __FUNCTION__
  @param errorInfo say related info about what may have caused the error
*/
void ConsoleErrorMessage( int line, std::string fn, std::string file, std::string errorInfo)
{
  std::cout << std::endl;
  std::cout << "Error on line: "   << line << std::endl;
  std::cout << "Inside function: " << fn   << std::endl;
  std::cout << "In file: "         << file << std::endl;
  std::cout << errorInfo << std::endl;
};