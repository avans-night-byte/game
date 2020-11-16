#pragma once

class MainMenu
{
public:
  MainMenu();
  ~MainMenu();
  static void init(EngineRenderingAPI *renderAPI, EngineWindowAPI *engineWindowAPI, AudioAPI *audioApi);
  static void render(EngineRenderingAPI *renderAPI, EngineWindowAPI *engineWindowAPI, Input i);
};