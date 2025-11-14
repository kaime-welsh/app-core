#pragma once

#include "ILayer.h"
#include "IPlugin.h"
#include "entt/entity/fwd.hpp"
#include "entt/entt.hpp"
#include <memory>
#include <type_traits>
#include <utility>

namespace Core {
class App {
public:
  static App &Get() { return *s_Instance; }

  App();
  ~App();

  void AddPlugin(std::unique_ptr<IPlugin> plugin);
  template <typename T, typename... Args> void AddPlugin(Args &&...args) {
    static_assert(std::is_base_of<IPlugin, T>::value,
                  "T must derive from IPlugin");
    AddPlugin(std::make_unique<T>(std::forward<Args>(args)...));
  }

  void PushLayer(std::unique_ptr<ILayer> layer);
  template <typename T, typename... Args> void PushLayer(Args &&...args) {
    static_assert(std::is_base_of<ILayer, T>::value,
                  "T must derive from ILayer");
    PushLayer(std::make_unique<T>(std::forward<Args>(args)...));
  }
  void PopLayer();

  entt::registry &GetRegistry() { return m_Registry; }

  void Run();
  void Stop();

private:
  static App *s_Instance;
  entt::registry m_Registry;

  bool m_IsRunning = false;

  std::vector<std::unique_ptr<ILayer>> m_LayerStack;
  std::vector<std::unique_ptr<IPlugin>> m_Plugins;
};
} // namespace Core
