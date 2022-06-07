#pragma once
#include <Maths.h>
#include <Model.h>
#include <IResources.h>
#include <Mesh.h>

using namespace  LowRenderer;

inline static bool wasSphereLoaded = false;
inline static bool wasBoxLoaded = false;
inline static Model* sphereModel;
inline static Model* boxModel;

class OBBCollider
{
public:
    Vector3D position;
    OBB obb;
    bool showCol = true;
    Mesh colVisualisation;

    OBBCollider();
    ~OBBCollider() {}
    OBBCollider(Vector3D pos, OBB obb);
    void Update();
};

class SphereCollider
{
public:
    Sphere sphere;
    Vector3D position;
    Mesh colVisualisation;

    SphereCollider();
    SphereCollider(Vector3D pos, Sphere sphere);
    void Update();
};

bool SphereSphereCol(SphereCollider sphere1, SphereCollider sphere2);
bool SphereOBBCol(SphereCollider sphere, OBBCollider platform);