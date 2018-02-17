#include "ErrorMessage.h"

#include "Sound.h"

SoundSystem::SoundSystem()
{
  FMOD_RESULT result;
  result = FMOD::System_Create(&system);

  // Create the main system object.
  if (result != FMOD_OK)
  {
    ErrorMessage("Failed to create the fmod object!");
    std::cout << result << FMOD_ErrorString(result);
    return;
  }

  result = system->init(100, FMOD_INIT_NORMAL, 0);	// Initialize FMOD.
  if (result != FMOD_OK)
  {
    ErrorMessage("Failed to initialize fmod!");
    std::cout << result << FMOD_ErrorString(result);
    return;
  }
}