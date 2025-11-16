#include "App.h"
#include "Game.h"
#include "RaylibPlugin.h"
#include "raylib.h"

int main() {
  Core::App app;
  app.AddPlugin<Plugins::RaylibPlugin>(800, 600, "HYDRO-STATIC",
                                       FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT |
                                           FLAG_WINDOW_MAXIMIZED);
  app.PushLayer<GameLayer>();
  app.Run();
}
