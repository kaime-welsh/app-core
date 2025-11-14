#pragma once

#include "IPlugin.h"
#include <raylib.h>

namespace Plugins {
class RaylibPlugin : public Core::IPlugin {
private:
  int m_width;
  int m_height;
  const char *m_title;
  ConfigFlags m_flags;

public:
  RaylibPlugin(int width, int height, const char *title, ConfigFlags flags)
      : m_width(width), m_height(height), m_title(title), m_flags(flags) {}

  void Build(Core::App &app) override;
  void Shutdown() override;
};
} // namespace Plugins
