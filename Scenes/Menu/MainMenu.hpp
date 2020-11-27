#pragma once

#include "memory"

class MainMenu
{
public:
  static void init(EngineRenderingAPI *renderAPI, EngineWindowAPI *engineWindowAPI, AudioAPI *audioApi);
  static void render(EngineRenderingAPI *renderAPI, EngineWindowAPI *engineWindowAPI, Input i);
};