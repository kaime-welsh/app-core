#include "RaylibPlugin.h"

namespace Plugins {
void RaylibPlugin::Build(Core::App &app) {
  SetConfigFlags(m_flags);
  InitWindow(m_width, m_height, m_title);
  SetTraceLogLevel(LOG_DEBUG);
}
void RaylibPlugin::Shutdown() { CloseWindow(); }
} // namespace Plugins
