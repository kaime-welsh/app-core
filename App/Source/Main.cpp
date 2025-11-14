#include "App.h"
#include "RaylibPlugin.h"
#include "raylib.h"

struct PlayerTag {};
struct Transform2D {
  float x = 0.0f;
  float y = 0.0f;
};

class GameLayer : public Core::ILayer {
public:
  void OnAttach() override {
    TraceLog(LOG_DEBUG, "GameLayer Attached!");

    auto &registry = Core::App::Get().GetRegistry();

    entt::entity player = registry.create();
    registry.emplace<PlayerTag>(player);
    registry.emplace<Transform2D>(player, 400.0f, 300.0f);
  }

  void OnDetach() override { TraceLog(LOG_DEBUG, "GameLayer Detached!"); }

  void Update() override {
    if (WindowShouldClose()) {
      Core::App::Get().Stop();
      return;
    }

    auto &registry = Core::App::Get().GetRegistry();
    auto view = registry.view<PlayerTag, Transform2D>();

    float dt = GetFrameTime();
    float speed = 300.0f;

    for (auto [tag, transform] : view.each()) {
      if (IsKeyDown(KEY_W))
        transform.y -= speed * dt;
      if (IsKeyDown(KEY_S))
        transform.y += speed * dt;
      if (IsKeyDown(KEY_A))
        transform.x -= speed * dt;
      if (IsKeyDown(KEY_D))
        transform.x += speed * dt;
    }
  }

  void Render() override {
    BeginDrawing();
    ClearBackground(BLACK);

    auto &registry = Core::App::Get().GetRegistry();
    auto view = registry.view<const PlayerTag, const Transform2D>();

    for (auto [tag, transform] : view.each()) {
      DrawCircle((int)transform.x, (int)transform.y, 20.0f, GREEN);
    }

    DrawText("Use WASD to Move", 10, 10, 20, WHITE);
    EndDrawing();
  }
};

int main() {
  Core::App app;
  app.AddPlugin<Plugins::RaylibPlugin>(800, 600, "Hello!",
                                       FLAG_WINDOW_RESIZABLE);
  app.PushLayer<GameLayer>();
  app.Run();
}
