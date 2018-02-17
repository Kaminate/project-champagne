#pragma once

#include "fmod.h"
#include "fmod.hpp"
#include "fmod_codec.h"
#include "fmod_dsp.h"
#include "fmod_errors.h"
#include "fmod_memoryinfo.h"
#include "fmod_output.h"
#pragma comment (lib, "fmodex_vc.lib")

class SoundSystem
{
public:
  SoundSystem();

//private: lolnope
  FMOD::System * system;
};