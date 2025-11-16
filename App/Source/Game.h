#pragma once

#include "ILayer.h"

class GameLayer : public Core::ILayer {
public:
  void OnAttach() override;

  void OnDetach() override;

  void Update() override;
  void Render() override;
};
