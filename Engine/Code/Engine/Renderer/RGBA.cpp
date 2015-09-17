#include "Engine/Renderer/RGBA.hpp"


const RGBA RGBA::WHITE(1.f, 1.f, 1.f, 1.f);


RGBA::RGBA() : red(0.0f), blue(0.0f), green(0.0f), alpha(1.0f)
{
}

RGBA::RGBA(float Red, float Green, float Blue) : red(Red), blue(Blue), green(Green), alpha(1.0f)
{

}

RGBA::RGBA(float Red, float Green, float Blue, float Alpha) : red(Red), blue(Blue), green(Green), alpha(Alpha)
{

}

RGBA::~RGBA()
{
}