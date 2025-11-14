#include "App.h"
#include "IPlugin.h"
#include <memory>
#include <stdexcept>
#include <utility>

namespace Core {
App *App::s_Instance = nullptr;

App::App() {
  if (s_Instance) {
    throw std::runtime_error("Application instance already exists!");
  }
  s_Instance = this;
}

App::~App() {
  for (auto &plugin : m_Plugins) {
    plugin->Shutdown();
  }

  while (!m_LayerStack.empty()) {
    PopLayer();
  }

  s_Instance = nullptr;
}

void App::AddPlugin(std::unique_ptr<IPlugin> plugin) {
  if (!plugin)
    return;

  plugin->Build(*this);
  m_Plugins.push_back(std::move(plugin));
}

void App::PushLayer(std::unique_ptr<ILayer> layer) {
  if (!layer)
    return;

  layer->OnAttach();
  m_LayerStack.push_back(std::move(layer));
}

void App::PopLayer() {
  if (m_LayerStack.empty())
    return;

  m_LayerStack.back()->OnDetach();
  m_LayerStack.pop_back();
}

void App::Stop() { m_IsRunning = false; }

void App::Run() {
  m_IsRunning = true;
  while (m_IsRunning) {
    for (auto &layer : m_LayerStack) {
      layer->Update();
    }
    for (auto &layer : m_LayerStack) {
      layer->Render();
    }
  }
}

} // namespace Core
