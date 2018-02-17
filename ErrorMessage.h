#pragma once

#include <iostream>

/*!
  @brief This function is used to show an error to the console
  @param line use __LINE__
  @param function ues __FUNCTION__
  @param errorInfo say related info about what may have caused the error
*/

#define ErrorMessage(message) \
  ConsoleErrorMessage(__LINE__, __FUNCTION__, __FILE__, message ); \
  __debugbreak()

void ConsoleErrorMessage(int line, std::string fn, std::string file, std::string errorInfo);