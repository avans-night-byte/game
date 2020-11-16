#pragma once

class MainMenu
{
public:
  MainMenu();
  ~MainMenu();
  static void init(EngineRenderingAPI *renderAPI, EngineWindowAPI *engineWindowAPI);
  static void render(EngineRenderingAPI *renderAPI, EngineWindowAPI *engineWindowAPI, Input i);
};