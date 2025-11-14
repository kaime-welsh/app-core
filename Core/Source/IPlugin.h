#pragma once

namespace Core {
class App;

class IPlugin {
public:
  virtual ~IPlugin() = default;
  virtual void Build(App &app) = 0;
  virtual void Shutdown() {}
};
} // namespace Core
