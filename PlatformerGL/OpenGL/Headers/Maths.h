#pragma once
#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

#define M_PI       3.14159265358979323846


class Vector2D
{
public:
    union
    {
        struct
        {
            float x;
            float y;
        };
        float xy[2];
    };

    Vector2D() {}
    Vector2D(float a, float b);
    ~Vector2D() {}

    float GetMagnitude() const;
    float dot(const Vector2D vec2);
    void Normalize();


    Vector2D operator+(const Vector2D& vec2);
    Vector2D operator-(const Vector2D& vec2);
    Vector2D operator*(const Vector2D& vec2);
    Vector2D operator*(const float& a);
    Vector2D operator/(const float& a);
};

class Vector3D
{
public:
    union
    {
        struct
        {
            float x;
            float y;
            float z;
        };
        float xyz[3];
    };


    Vector3D() {}
    Vector3D(float a, float b, float c);
    ~Vector3D() {}

    float GetMagnitude() const;
    float Dot(const Vector3D vec3);
    Vector3D CrossProduct(const Vector3D vec3);
    void Normalize();


    Vector3D operator+(const Vector3D& vec3);
    Vector3D operator-(const Vector3D& vec3);
    Vector3D operator*(const Vector3D& vec3);
    Vector3D operator*(const float& a);
    Vector3D operator/(const float& a);
};
Vector3D getSphericalCoords(const float r, const float theta, const float phi);
Vector3D FindVecNormal(Vector3D v0, Vector3D v1, Vector3D v2);


class Vector4D
{
public:
    union
    {
        struct
        {
            float x;
            float y;
            float z;
            float w;
        };
        float xyz[4];
    };

    Vector4D() {}
    Vector4D(float a, float b, float c, float d);
    Vector4D(const Vector3D& vec3, float _w = 1.0f);
    ~Vector4D() {}

    void Homogenize();
    Vector4D CrossProduct(const Vector3D vec4);
    float GetMagnitude() const;
    void Normalize();

    Vector4D operator+(const Vector4D& vec4);
    Vector4D operator*(const Vector4D& vec4);
    Vector4D operator*(const float& a);
};

class Matrix3
{
public:
    float matrixTab3[3][3];

    Matrix3();
    Matrix3(const float a[3][3]);
    ~Matrix3() {}

    Matrix3 operator*(const Matrix3& mat1);
    Vector3D operator*(const Vector3D& vec1);
    Matrix3 GetInvertibleMat3();
    Matrix3 GetTransposeMat3();
    Matrix3 GetAdjugateMat3();
};

class Matrix4
{
public:


    union
    {
        struct
        {
            float matrixTab4[4][4];
        };
        Vector4D Matrix4V[4];
    };

    

    Matrix4();
    Matrix4(const float a[4][4]);
    ~Matrix4() {}

    Vector3D right = { 1, 0 ,0 };
    Vector3D up = { 0, 1, 0 };
    Vector3D direction = { 0, 0, 1 };
    Vector3D position = { 0, 0, 5 };
    Vector3D object = { 0, 0, 0 };


    Matrix4 GetTransposeMat4();

    static Matrix4 CreateTransformMatrix(const Vector3D& rotation, const Vector3D& position, const Vector3D& scale);
    static Matrix4 CreateTranslationMatrix(const Vector3D& translation);
    static Matrix4 CreateScaleMatrix(const Vector3D& scale);
    static Matrix4 CreateXRotationMatrix(float angle);
    static Matrix4 CreateYRotationMatrix(float angle);
    static Matrix4 CreateZRotationMatrix(float angle);
    Matrix4 GetInvertibleMat4();
    Matrix4 GetAdjugateMat4();
    Matrix4 GetProjection(const float& fov, const float& n, const float& f);
    Matrix4 LookAt(Vector3D eye, Vector3D target, Vector3D up);
    Matrix4 GetViewMatrix();

    Matrix4 operator*(const Matrix4& mat1);
    Vector4D operator*(const Vector4D& vec1);
};

inline Matrix3 identity3x3()
{
    Matrix3 mat;

    float mat4[3][3] =
    {
        {1.f, 0.f, 0.f},
        {0.f, 1.f, 0.f},
        {0.f, 0.f, 1.f},
    };

    mat = mat4;
    return mat;
}

inline Matrix4 identity4x4()
{
    Matrix4 mat;

    float mat4[4][4] =
    {
        {1.f, 0.f, 0.f, 0.f},
        {0.f, 1.f, 0.f, 0.f},
        {0.f, 0.f, 1.f, 0.f},
        {0.f, 0.f, 0.f, 1.f},
    };

    mat = mat4;
    return mat;
}

inline float Radian(const float& degree)
{
    return degree * (M_PI / 180);
}


int checkMax2(int a, int b);
int checkMin2(int a, int b);

int checkMax3(int a, int b, int c);
int checkMin3(int a, int b, int c);

float edgeFunction(const Vector3D& a, const Vector3D& b, const Vector3D& c);
float GetDeterminantMat2(const float a, const float b, const float c, const float d);
float GetDeterminantMat3(const Vector3D& a, const Vector3D& b, const Vector3D& c);
float GetDeterminantMat3(const float tab[3][3]);
float GetDeterminantMat4(const Matrix4& a);
float Lerp(float a, float b, float t);

Matrix3 operator*(const Matrix3& a, const Matrix3& b);
Matrix3 operator*(const Matrix3& a, const float b);

Matrix4 operator*(const Matrix4& a, const Matrix4& b);
Matrix4 operator*(const Matrix4& a, const float b);

Vector3D operator*(const float b, const Vector3D& a);

Vector4D operator*(const Vector4D& b, const Matrix4& a);
Vector4D operator*(const Matrix4& a, const Vector4D& b);

class OBB
{
private:
    Matrix4 _umv;
public:
    Vector3D halfSize;
    Vector3D rotation;
    OBB();
    ~OBB() {}
    OBB(Vector3D halfSize,Vector3D rotation);
    Matrix4 umv();
};

class Sphere
{
public:
    float radius;

    Sphere();
    Sphere(float rad);

};

