#pragma once

class MainMenu
{
public:
  static void init(EngineRenderingAPI *renderAPI, EngineWindowAPI *engineWindowAPI, AudioAPI *audioApi);
  static void render(EngineRenderingAPI *renderAPI, EngineWindowAPI *engineWindowAPI, Input i);
  static void clicked(int x, int y);
};