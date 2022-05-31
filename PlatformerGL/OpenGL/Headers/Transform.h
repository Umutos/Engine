#pragma once

#include <Maths.h>
#include <vector>
#include <Model.h>

using namespace Resources;
class Transform
{
public:
    //Local space information
    Vector3D pos = { 0.0f, 0.0f, 0.0f };
    Vector3D rot = { 0.0f, 0.0f, 0.0f };
    Vector3D scale = { 1.0f, 1.0f, 1.0f };
};