#pragma once

#include "Colour.h"

struct TracedMaterial
{
    enum MaterialType { Metal };

    MaterialType type;
    Colour albedo;
    Colour emission;
    float roughness;
};