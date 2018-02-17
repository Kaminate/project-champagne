#include "ColorHSV.h"

// Reference: http://en.wikipedia.org/wiki/HSL_and_HSV

// Helper function for ColorHSV:GetRGB
void SolveRpGpBp(float & Rp, float & Gp, float & Bp, const float C, const float X, const unsigned int Hi);

// Helper function for setters (these should probably  be found in a math library somewhere)
bool IsWithinBounds(const int min, const int max, const int value);
bool IsWithinBounds(const float min, const float max, const float value);

ColorHSV::ColorHSV():
  hue(0),           // [0, 360]
  saturation(1.0f), // [0, 1]
  value(1.0f),      // [0, 1]
  alpha(1.0f)       // [0, 1]
{
}

D3DXCOLOR ColorHSV::GetRGB()
{
  if (saturation == 0.0f)
  {
    return D3DXCOLOR(saturation, saturation, saturation, 1.0f);
  }

  float C;         // chroma [0, 1]
  float Hp;        // Hue as a float from [0, 1]
  unsigned int Hi; // Integral part of Hue [0, 6]
  float Hf;        // Remaining float part [0, 1]
  float X;         // intermediate value [0, 1] (?)

  float Rp;        // Red prime   [0, 1]
  float Gp;        // Green prime [0, 1]
  float Bp;        // Blue prime  [0, 1]

  float R;         // Red   [0, 1]
  float G;         // Green [0, 1]
  float B;         // Blue  [0, 1]

  // Solve for chroma
  C = value * saturation;

  // Solve for hue prime
  Hp = hue / 60.0f;
  Hi = (int) Hp;
  Hf = Hp - (float)Hi;

  // Solve for intermediate value X

  X = C * (1 - fabs( (Hi % 2) - 1.0f + Hf) );

  SolveRpGpBp(Rp, Gp, Bp, C, X, Hi);

  // Add value m to Rp, Gp, Bp to match the value
  float m = value - C;
  R = Rp + m;
  G = Gp + m;
  B = Bp + m;

  return D3DXCOLOR(R, G, B, alpha);
}

// Getters
float ColorHSV::GetHue() const
{
  return hue;
}

float ColorHSV::GetSaturation() const
{
  return saturation;
}

float ColorHSV::GetValue() const
{
  return value;
}

float ColorHSV::GetAlpha() const
{
  return alpha;
}

// Setters
void ColorHSV::SetHue(const float newHue)
{
  const float HUE_MIN = 0.0f;
  const float HUE_MAX = 360.0f;

  if(IsWithinBounds(HUE_MIN, HUE_MAX, newHue))
  {
    hue = newHue;
  }
  else
  {
    ErrorMessage("Hue out of bounds!");
  }
}

void ColorHSV::SetSaturation(const float newSaturation)
{
  const float SATURATION_MIN = 0;
  const float SATURATION_MAX = 1;
  if(IsWithinBounds(SATURATION_MIN, SATURATION_MAX, newSaturation))
  {
    saturation = newSaturation;
  }
  else
  {
    ErrorMessage("Saturation out of bounds!");
  }
}

void ColorHSV::SetValue(const float newValue)
{
  const float VALUE_MIN = 0;
  const float VALUE_MAX = 1;
  if(IsWithinBounds(VALUE_MIN, VALUE_MAX, newValue))
  {
    value = newValue;
  }
  else
  {
    ErrorMessage("Value out of bounds!");
  }
}

void ColorHSV::SetAlpha(const float newAlpha)
{
  const float ALPHA_MIN = 0;
  const float ALPHA_MAX = 1;
  if(IsWithinBounds(ALPHA_MIN, ALPHA_MAX, newAlpha))
  {
    alpha = newAlpha;
  }
  else
  {
    ErrorMessage("Alpha out of bounds!");
  }
}

// Helpers
void SolveRpGpBp(float & Rp, float & Gp, float & Bp, const float C, const float X, const unsigned int Hi)
{
  switch (Hi)
  {
  case 0:
    Rp = C;
    Gp = X;
    Bp = 0.0f;
    break;

  case 1:
    Rp = X;
    Gp = C;
    Bp = 0.0f;
    break;

  case 2:
    Rp = 0.0f;
    Gp = C;
    Bp = X;
    break;

  case 3:
    Rp = 0.0f;
    Gp = X;
    Bp = C;
    break;

  case 4:
    Rp = X;
    Gp = 0.0f;
    Bp = C;
    break;

  case 5:
    Rp = C;
    Gp = 0.0f;
    Bp = X;
    break;
  //default:
  //  break;
  }
}

bool IsWithinBounds(const int min, const int max, const int value)
{
  return (value >= min && value <= max);
}

bool IsWithinBounds(const float min, const float max, const float value)
{
  return (value >= min && value <= max);
}