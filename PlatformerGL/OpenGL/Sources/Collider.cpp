#include <Collider.h>
#include <ResourcesManager.h>




SphereCollider::SphereCollider(Vector3D pos, Sphere sphere)
{
    position = pos;
    this->sphere = sphere;
    if (!wasSphereLoaded)
    {
        ResourcesManager manager;
        manager.CreateResource<Model>("Sphere", "Resources/Obj/sphere.obj");
        Model* sphere = manager.GetResource<Model>("Sphere");
        sphereModel = sphere;
        wasSphereLoaded = true;

    }
        colVisualisation = Mesh(sphereModel, Vector3D(0,0,0), position, Vector3D(sphere.radius, sphere.radius, sphere.radius), "Resources/Textures/wf.png");
  
}

SphereCollider::SphereCollider()
{
    position = {0,0,0};
    this->sphere = Sphere();

}

OBBCollider::OBBCollider(Vector3D pos, OBB obb)
{
    position = pos;
    this->obb = obb;
}

OBBCollider::OBBCollider()
{
    position = {0,0,0};
    this->obb = OBB();
}


bool SphereSphereCol(SphereCollider sphere1, SphereCollider sphere2)
{
    Vector3D vecDist = (sphere1.position - sphere2.position);
    float distance = sqrt(pow(vecDist.x, 2) + pow(vecDist.y, 2));
    float totalRadius = sphere1.sphere.radius + sphere2.sphere.radius;

    return distance < (totalRadius* totalRadius);
}

bool SphereOBBCol(SphereCollider sphere, OBBCollider platform)
{
    Vector3D pos = sphere.position;
    pos = Vector3D(
        pos.Dot(pos * Vector3D(platform.obb.umv.matrixTab4[0][0], platform.obb.umv.matrixTab4[0][1], platform.obb.umv.matrixTab4[0][2])),
        pos.Dot(pos * Vector3D(platform.obb.umv.matrixTab4[1][0], platform.obb.umv.matrixTab4[1][1], platform.obb.umv.matrixTab4[1][2])),
        pos.Dot(pos * Vector3D(platform.obb.umv.matrixTab4[2][0], platform.obb.umv.matrixTab4[2][1], platform.obb.umv.matrixTab4[2][2]))
    );

    float distance = 0;

    for (int i = 0; i < 3; ++i)
    {
        if (pos.xyz[i] < -(platform.obb.halfSize.xyz[i]))
        {
            float borderDistance = -(platform.obb.halfSize.xyz[i]) - pos.xyz[i];
            distance += borderDistance * borderDistance;
        }
        else if (pos.xyz[i] > platform.obb.halfSize.xyz[i])
        {
            float borderDistance = pos.xyz[i] - platform.obb.halfSize.xyz[i];
            distance += borderDistance * borderDistance;
        }
    }
    return (distance <= (sphere.sphere.radius * sphere.sphere.radius));
}
