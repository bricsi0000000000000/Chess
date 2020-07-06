#include <iostream>
#include <string>

#include "InputManager.h"

InputManager* InputManager::instance = 0;

int main()
{
  InputManager* input_manager = input_manager->Instance();
  input_manager->Menu();

  return 0;
}
