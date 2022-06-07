#include <Collider.h>
#include <ResourcesManager.h>




SphereCollider::SphereCollider(Vector3D* pos, Sphere sphere)
{
    position = pos;
    this->sphere = sphere;
    if (!wasSphereLoaded)
    {
        ResourcesManager manager;
        manager.CreateResource<Model>("Sphere", "Resources/Obj/sphere.obj");
        sphereModel = manager.GetResource<Model>("Sphere");
        wasSphereLoaded = true;

    }
        colVisualisation = Mesh(sphereModel, Vector3D(0,0,0), *position, Vector3D(sphere.radius-0.5, sphere.radius-0.5, sphere.radius-0.5), "Resources/Textures/wf.png");
  
}

SphereCollider::SphereCollider()
{
    //position = {0,0,0};
    this->sphere = Sphere();
}

OBBCollider::OBBCollider(Vector3D* pos, OBB obb)
{
    position = pos;
    this->obb = obb;

    if (!wasBoxLoaded)
    {
        ResourcesManager manager;
        manager.CreateResource<Model>("Box", "Resources/Obj/cube.obj");
        boxModel = manager.GetResource<Model>("Box");
        wasSphereLoaded = true;
    }
    colVisualisation = Mesh(boxModel, obb.rotation, *position, Vector3D(obb.halfSize.x*2, obb.halfSize.y * 2, obb.halfSize.z * 2), "Resources/Textures/wf.png");
}

OBBCollider::OBBCollider()
{
    //position = {0,0,0};
    this->obb = OBB();
}


void SphereCollider::Update()
{
    colVisualisation.pos = *position;
    if (colVisualisation.scl.x > colVisualisation.scl.y)
    {
        if (colVisualisation.scl.x > colVisualisation.scl.z)
            sphere.radius =0.3+ colVisualisation.scl.x;
        else
            sphere.radius =0.3+ colVisualisation.scl.z;
    }
    else 
    { 
        if (colVisualisation.scl.y > colVisualisation.scl.z)
            sphere.radius =0.3+ colVisualisation.scl.y;
        else
            sphere.radius =0.3+ colVisualisation.scl.z;
    }
}

void OBBCollider::Update()
{
    //*position = colVisualisation.pos;
    obb.halfSize.x = colVisualisation.scl.x / 2;
    obb.halfSize.y = colVisualisation.scl.y / 2;
    obb.halfSize.z = colVisualisation.scl.z / 2;
    obb.rotation = colVisualisation.rot;
}


bool SphereSphereCol(SphereCollider sphere1, SphereCollider sphere2)
{
    Vector3D vecDist = (*sphere1.position - *sphere2.position);
    float distance = sqrt(pow(vecDist.x, 2) + pow(vecDist.y, 2) + pow(vecDist.z, 2));
    float totalRadius = sphere1.sphere.radius + sphere2.sphere.radius;
    return distance < (totalRadius* totalRadius);
}

Vector3D ClosestPointOrientedBox(Vector3D p, OBBCollider b)
{
    Vector3D d = p - *b.position;
    Vector3D q= *b.position;
    Matrix4 umv = b.obb.umv();

    for (int i = 0; i < 3; i++) {

        float dist = d.Dot({ umv.Matrix4V[i].x,umv.Matrix4V[i].y,umv.Matrix4V[i].z });
        if (dist > b.obb.halfSize.xyz[i]) dist = b.obb.halfSize.xyz[i];
        if (dist < (b.obb.halfSize.xyz[i]*-1)) dist = (b.obb.halfSize.xyz[i] * -1);
        q = q+(dist * Vector3D(umv.Matrix4V[i].x,umv.Matrix4V[i].y,umv.Matrix4V[i].z));

    }

    return q;
}

bool SphereOBBCol(SphereCollider sphere, OBBCollider platform)
{
    Vector3D pos = *sphere.position;

    Vector3D closestPoint = ClosestPointOrientedBox(pos, platform);

    Vector3D distance = closestPoint - pos;

    return (distance.Dot(distance) <= (sphere.sphere.radius * sphere.sphere.radius));
}
