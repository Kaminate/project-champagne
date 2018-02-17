#pragma once

#include <d3dx10math.h>
#include "ErrorMessage.h"

// Reference: http://en.wikipedia.org/wiki/HSL_and_HSV

class ColorHSV
{
public:
  ColorHSV();

  D3DXCOLOR GetRGB();

  //Getters
  float GetHue() const;
  float GetSaturation() const;
  float GetValue() const;
  float GetAlpha() const;

  //Setters
  void SetHue(const float newHue);
  void SetSaturation(const float newSaturation);
  void SetValue(const float newValue);
  void SetAlpha(const float newAlpha);

private:
  float hue;           // [0, 360]
  float saturation;    // [0, 1]
  float value;         // [0, 1]
  float alpha;         // [0, 1]
};