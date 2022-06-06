#include <Maths.h>


//===== Vector2D =====

// --> Builder
Vector2D::Vector2D(float a, float b)
{
    this->x = a;
    this->y = b;
}

// --> Fonction
float Vector2D::GetMagnitude() const
{
    return (float)sqrt(pow(this->x, 2) + pow(this->y, 2));
}

float Vector2D::dot(const Vector2D vec3)
{
    return ((x * vec3.x) + (y * vec3.y));
}

void Vector2D::Normalize()
{
    float norme = this->GetMagnitude();
    x = x / norme;
    y = y / norme;
}

// --> Operator
Vector2D Vector2D::operator+(const Vector2D& vec3)
{
    Vector2D vec;
    vec.x = vec3.x + x;
    vec.y = vec3.y + y;
    return vec;
}

Vector2D Vector2D::operator-(const Vector2D& vec3)
{
    Vector2D vec;
    vec.x = x - vec3.x;
    vec.y = y - vec3.y;
    return vec;
}

Vector2D Vector2D::operator*(const Vector2D& vec3)
{
    Vector2D vec;
    vec.x = x * vec3.x;
    vec.y = y * vec3.y;
    return vec;
}

Vector2D Vector2D::operator*(const float& a)
{
    Vector2D vec;
    vec.x = x * a;
    vec.y = y * a;
    return vec;
}

Vector2D Vector2D::operator/(const float& a)
{
    Vector2D vec;
    vec.x = x / a;
    vec.y = y / a;
    return vec;
}

//===== Vector3D =====

// --> Builder
Vector3D::Vector3D(float a, float b, float c)
{
    this->x = a;
    this->y = b;
    this->z = c;
}

// --> Fonction
float Vector3D::GetMagnitude() const
{
    return (float)sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2));
}

float Vector3D::Dot(const Vector3D vec3)
{
    return ((x * vec3.x) + (y * vec3.y) + (z * vec3.z));
}

Vector3D Vector3D::CrossProduct(const Vector3D vec3)
{
    Vector3D vec;
    vec.x = (vec3.z * y - vec3.y * z);
    vec.y = (vec3.x * z - vec3.z * x);
    vec.z = (vec3.y * x - vec3.x * y);
    return vec;
}

void Vector3D::Normalize()
{
    float norme = this->GetMagnitude();
    x = x / norme;
    y = y / norme;
    z = z / norme;
}

// --> Operator
Vector3D Vector3D::operator+(const Vector3D& vec3)
{
    Vector3D vec;
    vec.x = vec3.x + x;
    vec.y = vec3.y + y;
    vec.z = vec3.z + z;
    return vec;
}

Vector3D Vector3D::operator-(const Vector3D& vec3)
{
    Vector3D vec;
    vec.x = x - vec3.x;
    vec.y = y - vec3.y;
    vec.z = z - vec3.z;
    return vec;
}

Vector3D Vector3D::operator*(const Vector3D& vec3)
{
    Vector3D vec;
    vec.x = x * vec3.x;
    vec.y = y * vec3.y;
    vec.z = z * vec3.z;
    return vec;
}

Vector3D Vector3D::operator*(const float& a)
{
    Vector3D vec;
    vec.x = x * a;
    vec.y = y * a;
    vec.z = z * a;
    return vec;
}

Vector3D Vector3D::operator/(const float& a)
{
    Vector3D vec;
    vec.x = x / a;
    vec.y = y / a;
    vec.z = z / a;
    return vec;
}

// Function that takes the coordinates of a sphere
Vector3D getSphericalCoords(const float r, const float theta, const float phi)
{
    return
    {
        r * sin(theta) * cos(phi),
        r * cos(theta),
        r * sin(theta) * sin(phi)
    };
};

// Function that returns the normal vector of a plane
Vector3D FindVecNormal(Vector3D v0, Vector3D v1, Vector3D v2)
{
    Vector3D v0v1 = v1 - v0;
    Vector3D v0v2 = v2 - v0;

    return v0v1.CrossProduct(v0v2);
}


//===== Vector4D =====

// --> Builder
Vector4D::Vector4D(float a, float b, float c, float d)
{
    this->x = a;
    this->y = b;
    this->z = c;
    this->w = d;
}

Vector4D::Vector4D(const Vector3D& vec3, float _w)
{
    this->x = vec3.x;
    this->y = vec3.y;
    this->z = vec3.z;
    this->w = _w;
}

// --> Fonction
void Vector4D::Homogenize()
{
    if (w != 0)
    {
        x /= w;
        y /= w;
        z /= w;
    }
}

Vector4D Vector4D::CrossProduct(const Vector3D vec4)
{
    Vector4D vec;
    vec.x = (vec4.z * y - vec4.y * z);
    vec.y = (vec4.x * z - vec4.z * x);
    vec.z = (vec4.y * x - vec4.x * y);
    return vec;
}

float Vector4D::GetMagnitude() const
{
    Vector4D temp{ {x, y, z}, w };
    return (float)sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2));
}

void Vector4D::Normalize()
{
    float norme = this->GetMagnitude();
    x /= norme;
    y /= norme;
    z /= norme;
}

// --> Operator
Vector4D Vector4D::operator+(const Vector4D& vec4)
{
    Vector4D vec;
    vec.x = vec4.x + x;
    vec.y = vec4.y + y;
    vec.z = vec4.z + z;
    vec.w = vec4.w + w;
    return vec;
}

Vector4D Vector4D::operator*(const Vector4D& vec4)
{
    Vector4D vec;
    vec.x = vec4.x * x;
    vec.y = vec4.y * y;
    vec.z = vec4.z * z;
    vec.w = vec4.w * w;
    return vec;
}

Vector4D Vector4D::operator*(const float& a)
{
    Vector4D vec;
    vec.x = x * a;
    vec.y = y * a;
    vec.z = z * a;
    vec.w = w * a;
    return vec;
}

//===== Matrix3 =====

// --> Builder
Matrix3::Matrix3()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            matrixTab3[i][j] = 0.f;
        }
    }
}

Matrix3 Matrix3::GetTransposeMat3()
{
    Matrix3 matrix = Matrix3();
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            matrix.matrixTab3[i][j] = this->matrixTab3[j][i];
        }
    }
    return matrix;
}

Matrix3 Matrix3::GetAdjugateMat3()
{
    Matrix3 matrix = Matrix3();

    matrix.matrixTab3[0][0] = GetDeterminantMat2(this->matrixTab3[1][1], this->matrixTab3[1][2], this->matrixTab3[2][1], this->matrixTab3[2][2]);
    matrix.matrixTab3[0][1] = GetDeterminantMat2(this->matrixTab3[1][0], this->matrixTab3[1][2], this->matrixTab3[2][0], this->matrixTab3[2][2]);
    matrix.matrixTab3[0][2] = GetDeterminantMat2(this->matrixTab3[1][0], this->matrixTab3[1][1], this->matrixTab3[2][0], this->matrixTab3[2][1]);

    matrix.matrixTab3[1][0] = GetDeterminantMat2(this->matrixTab3[0][1], this->matrixTab3[0][2], this->matrixTab3[2][1], this->matrixTab3[2][2]);
    matrix.matrixTab3[1][1] = GetDeterminantMat2(this->matrixTab3[0][0], this->matrixTab3[0][2], this->matrixTab3[2][0], this->matrixTab3[2][2]);
    matrix.matrixTab3[1][2] = GetDeterminantMat2(this->matrixTab3[0][0], this->matrixTab3[0][1], this->matrixTab3[2][0], this->matrixTab3[2][1]);

    matrix.matrixTab3[2][0] = GetDeterminantMat2(this->matrixTab3[0][1], this->matrixTab3[0][2], this->matrixTab3[1][1], this->matrixTab3[1][2]);
    matrix.matrixTab3[2][1] = GetDeterminantMat2(this->matrixTab3[0][0], this->matrixTab3[0][2], this->matrixTab3[1][0], this->matrixTab3[1][2]);
    matrix.matrixTab3[2][2] = GetDeterminantMat2(this->matrixTab3[0][0], this->matrixTab3[0][1], this->matrixTab3[1][0], this->matrixTab3[1][1]);

    return matrix;
}

Matrix3::Matrix3(const float a[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            matrixTab3[i][j] = a[i][j];
        }
    }
}

Matrix3 Matrix3::GetInvertibleMat3()
{
    return (this->GetAdjugateMat3().GetTransposeMat3() * (1 / GetDeterminantMat3(this->matrixTab3)));
}


// --> Operator
Matrix3 Matrix3::operator*(const Matrix3& mat1)
{
    Matrix3 mat;
    mat.matrixTab3[0][0] = matrixTab3[0][0] * mat1.matrixTab3[0][0] + matrixTab3[0][1] * mat1.matrixTab3[1][0] + matrixTab3[0][2] * mat1.matrixTab3[2][0];
    mat.matrixTab3[1][0] = matrixTab3[1][0] * mat1.matrixTab3[0][0] + matrixTab3[1][1] * mat1.matrixTab3[1][0] + matrixTab3[1][2] * mat1.matrixTab3[2][0];
    mat.matrixTab3[2][0] = matrixTab3[2][0] * mat1.matrixTab3[0][0] + matrixTab3[2][1] * mat1.matrixTab3[1][0] + matrixTab3[2][2] * mat1.matrixTab3[2][0];

    mat.matrixTab3[0][1] = matrixTab3[0][0] * mat1.matrixTab3[0][1] + matrixTab3[0][1] * mat1.matrixTab3[1][1] + matrixTab3[0][2] * mat1.matrixTab3[2][1];
    mat.matrixTab3[1][1] = matrixTab3[1][0] * mat1.matrixTab3[0][1] + matrixTab3[1][1] * mat1.matrixTab3[1][1] + matrixTab3[1][2] * mat1.matrixTab3[2][1];
    mat.matrixTab3[2][1] = matrixTab3[2][0] * mat1.matrixTab3[0][1] + matrixTab3[2][1] * mat1.matrixTab3[1][1] + matrixTab3[2][2] * mat1.matrixTab3[2][1];

    mat.matrixTab3[0][2] = matrixTab3[0][0] * mat1.matrixTab3[0][2] + matrixTab3[0][1] * mat1.matrixTab3[1][2] + matrixTab3[0][2] * mat1.matrixTab3[2][2];
    mat.matrixTab3[1][2] = matrixTab3[1][0] * mat1.matrixTab3[0][2] + matrixTab3[1][1] * mat1.matrixTab3[1][2] + matrixTab3[1][2] * mat1.matrixTab3[2][2];
    mat.matrixTab3[2][2] = matrixTab3[2][0] * mat1.matrixTab3[0][2] + matrixTab3[2][1] * mat1.matrixTab3[1][2] + matrixTab3[2][2] * mat1.matrixTab3[2][2];
    return mat;
}

Vector3D Matrix3::operator*(const Vector3D& vec1)
{
    Vector3D vec;
    vec.x = vec1.x * matrixTab3[0][0] + vec1.y * matrixTab3[0][1] + vec1.z * matrixTab3[0][2];
    vec.y = vec1.x * matrixTab3[1][0] + vec1.y * matrixTab3[1][1] + vec1.z * matrixTab3[1][2];
    vec.z = vec1.x * matrixTab3[2][0] + vec1.y * matrixTab3[2][1] + vec1.z * matrixTab3[2][2];
    return vec;
}


//===== Matrix4 =====

// --> Builder
Matrix4::Matrix4()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            matrixTab4[i][j] = 0.f;
        }
    }
}

Matrix4::Matrix4(const float a[4][4])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            matrixTab4[i][j] = a[i][j];
        }
    }
}

Matrix4 Matrix4::GetTransposeMat4()
{
    Matrix4 matrix = Matrix4();
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            matrix.matrixTab4[i][j] = this->matrixTab4[j][i];
        }
    }
    return matrix;
}

// --> Fonction
Matrix4 Matrix4::CreateTransformMatrix(const Vector3D& rotation, const Vector3D& position, const Vector3D& scale)
{
    return  CreateTranslationMatrix(position) * CreateYRotationMatrix(rotation.y) * CreateXRotationMatrix(rotation.x) * CreateZRotationMatrix(rotation.z) * CreateScaleMatrix(scale);
}

Matrix4 Matrix4::CreateTranslationMatrix(const Vector3D& translation)
{
    float tab[4][4] =
    {
        {1, 0, 0, translation.x},
        {0, 1, 0, translation.y},
        {0, 0, 1, translation.z},
        {0, 0, 0, 1}
    };
    Matrix4 temp = tab;
    return temp;
}

Matrix4 Matrix4::CreateScaleMatrix(const Vector3D& scale)
{
    float tab[4][4] =
    {
        {scale.x, 0, 0, 0},
        {0, scale.y, 0, 0},
        {0, 0, scale.z, 0},
        {0, 0, 0, 1}
    };
    Matrix4 temp = tab;
    return temp;
}

Matrix4 Matrix4::CreateXRotationMatrix(float angle)
{
    float tab[4][4] =
    {
        {1, 0, 0, 0},
        {0, cosf(angle), -sinf(angle), 0},
        {0, sinf(angle), cosf(angle), 0},
        {0, 0, 0, 1},
    };
    Matrix4 temp = tab;
    return temp;
}

Matrix4 Matrix4::CreateYRotationMatrix(float angle)
{
    float tab[4][4] =
    {
        {cosf(angle), 0, sinf(angle), 0},
        {0, 1, 0, 0},
        {-sinf(angle), 0, cosf(angle), 0},
        {0, 0, 0, 1}
    };

    Matrix4 temp = tab;
    return temp;
}

Matrix4 Matrix4::CreateZRotationMatrix(float angle)
{
    float tab[4][4] =
    {
        {cosf(angle), -sinf(angle), 0, 0},
        {sinf(angle), cosf(angle), 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1},
    };
    Matrix4 temp = tab;
    return tab;
}

Matrix4 Matrix4::GetAdjugateMat4()
{
    Matrix4 matrix = Matrix4();

    matrix.matrixTab4[0][0] = GetDeterminantMat3({ this->matrixTab4[1][1], this->matrixTab4[1][2], this->matrixTab4[1][3] }, { this->matrixTab4[2][1], this->matrixTab4[2][2], this->matrixTab4[2][3] }, { this->matrixTab4[3][1], this->matrixTab4[3][2], this->matrixTab4[3][3] });
    matrix.matrixTab4[0][1] = GetDeterminantMat3({ this->matrixTab4[1][0], this->matrixTab4[1][2], this->matrixTab4[1][3] }, { this->matrixTab4[2][0], this->matrixTab4[2][2], this->matrixTab4[2][3] }, { this->matrixTab4[3][0], this->matrixTab4[3][2], this->matrixTab4[3][3] });
    matrix.matrixTab4[0][2] = GetDeterminantMat3({ this->matrixTab4[1][0], this->matrixTab4[1][1], this->matrixTab4[1][3] }, { this->matrixTab4[2][0], this->matrixTab4[2][1], this->matrixTab4[2][3] }, { this->matrixTab4[3][0], this->matrixTab4[3][1], this->matrixTab4[3][3] });
    matrix.matrixTab4[0][3] = GetDeterminantMat3({ this->matrixTab4[1][0], this->matrixTab4[1][1], this->matrixTab4[1][2] }, { this->matrixTab4[2][0], this->matrixTab4[2][1], this->matrixTab4[2][2] }, { this->matrixTab4[3][0], this->matrixTab4[3][1], this->matrixTab4[3][2] });

    matrix.matrixTab4[1][0] = GetDeterminantMat3({ this->matrixTab4[0][1], this->matrixTab4[0][2], this->matrixTab4[0][3] }, { this->matrixTab4[2][1], this->matrixTab4[2][2], this->matrixTab4[2][3] }, { this->matrixTab4[3][1], this->matrixTab4[3][2], this->matrixTab4[3][3] });
    matrix.matrixTab4[1][1] = GetDeterminantMat3({ this->matrixTab4[0][0], this->matrixTab4[0][2], this->matrixTab4[0][3] }, { this->matrixTab4[2][0], this->matrixTab4[2][2], this->matrixTab4[2][3] }, { this->matrixTab4[3][0], this->matrixTab4[3][2], this->matrixTab4[3][3] });
    matrix.matrixTab4[1][2] = GetDeterminantMat3({ this->matrixTab4[0][0], this->matrixTab4[0][1], this->matrixTab4[0][3] }, { this->matrixTab4[2][0], this->matrixTab4[2][1], this->matrixTab4[2][3] }, { this->matrixTab4[3][0], this->matrixTab4[3][1], this->matrixTab4[3][3] });
    matrix.matrixTab4[1][3] = GetDeterminantMat3({ this->matrixTab4[0][0], this->matrixTab4[0][1], this->matrixTab4[0][2] }, { this->matrixTab4[2][0], this->matrixTab4[2][1], this->matrixTab4[2][2] }, { this->matrixTab4[3][0], this->matrixTab4[3][1], this->matrixTab4[3][2] });

    matrix.matrixTab4[2][0] = GetDeterminantMat3({ this->matrixTab4[0][1], this->matrixTab4[0][2], this->matrixTab4[0][3] }, { this->matrixTab4[1][1], this->matrixTab4[1][2], this->matrixTab4[1][3] }, { this->matrixTab4[3][1], this->matrixTab4[3][2], this->matrixTab4[3][3] });
    matrix.matrixTab4[2][1] = GetDeterminantMat3({ this->matrixTab4[0][0], this->matrixTab4[0][2], this->matrixTab4[0][3] }, { this->matrixTab4[1][0], this->matrixTab4[1][2], this->matrixTab4[1][3] }, { this->matrixTab4[3][0], this->matrixTab4[3][2], this->matrixTab4[3][3] });
    matrix.matrixTab4[2][2] = GetDeterminantMat3({ this->matrixTab4[0][0], this->matrixTab4[0][1], this->matrixTab4[0][3] }, { this->matrixTab4[1][0], this->matrixTab4[1][1], this->matrixTab4[1][3] }, { this->matrixTab4[3][0], this->matrixTab4[3][1], this->matrixTab4[3][3] });
    matrix.matrixTab4[2][3] = GetDeterminantMat3({ this->matrixTab4[0][0], this->matrixTab4[0][1], this->matrixTab4[0][2] }, { this->matrixTab4[1][0], this->matrixTab4[1][1], this->matrixTab4[1][2] }, { this->matrixTab4[3][0], this->matrixTab4[3][1], this->matrixTab4[3][2] });

    matrix.matrixTab4[3][0] = GetDeterminantMat3({ this->matrixTab4[0][1], this->matrixTab4[0][2], this->matrixTab4[0][3] }, { this->matrixTab4[1][1], this->matrixTab4[1][2], this->matrixTab4[1][3] }, { this->matrixTab4[2][1], this->matrixTab4[2][2], this->matrixTab4[2][3] });
    matrix.matrixTab4[3][1] = GetDeterminantMat3({ this->matrixTab4[0][0], this->matrixTab4[0][2], this->matrixTab4[0][3] }, { this->matrixTab4[1][0], this->matrixTab4[1][2], this->matrixTab4[1][3] }, { this->matrixTab4[2][0], this->matrixTab4[2][2], this->matrixTab4[2][3] });
    matrix.matrixTab4[3][2] = GetDeterminantMat3({ this->matrixTab4[0][0], this->matrixTab4[0][1], this->matrixTab4[0][3] }, { this->matrixTab4[1][0], this->matrixTab4[1][1], this->matrixTab4[1][3] }, { this->matrixTab4[2][0], this->matrixTab4[2][1], this->matrixTab4[2][3] });
    matrix.matrixTab4[3][3] = GetDeterminantMat3({ this->matrixTab4[0][0], this->matrixTab4[0][1], this->matrixTab4[0][2] }, { this->matrixTab4[1][0], this->matrixTab4[1][1], this->matrixTab4[1][2] }, { this->matrixTab4[2][0], this->matrixTab4[2][1], this->matrixTab4[2][2] });

    return matrix;
}

Matrix4 Matrix4::GetInvertibleMat4()
{
    return (this->GetAdjugateMat4().GetTransposeMat4() * (1 / GetDeterminantMat4(*this)));
}

Matrix4 Matrix4::GetProjection(const float& fov, const float& n, const float& f)
{
    float s = 1 / tanf((fov / 2) * (M_PI / 180));
    float c = f / (f - n);

    float projectionMatrix[4][4] = {
        {s, 0.f, 0.f, 0.f},
        {0.f, s, 0.f, 0.f},
        {0.f, 0.f, -c, -(c * n)},
        {0.f, 0.f, -1.f, 0.f},
    };
    return projectionMatrix;
}


// --> Operator
Matrix4 Matrix4::operator*(const Matrix4& mat1)
{
    Matrix4 mat;
    mat.matrixTab4[0][0] = matrixTab4[0][0] * mat1.matrixTab4[0][0] + matrixTab4[0][1] * mat1.matrixTab4[1][0] + matrixTab4[0][2] * mat1.matrixTab4[2][0] + matrixTab4[0][3] * mat1.matrixTab4[3][0];
    mat.matrixTab4[1][0] = matrixTab4[1][0] * mat1.matrixTab4[0][0] + matrixTab4[1][1] * mat1.matrixTab4[1][0] + matrixTab4[1][2] * mat1.matrixTab4[2][0] + matrixTab4[1][3] * mat1.matrixTab4[3][0];
    mat.matrixTab4[2][0] = matrixTab4[2][0] * mat1.matrixTab4[0][0] + matrixTab4[2][1] * mat1.matrixTab4[1][0] + matrixTab4[2][2] * mat1.matrixTab4[2][0] + matrixTab4[2][3] * mat1.matrixTab4[3][0];
    mat.matrixTab4[3][0] = matrixTab4[3][0] * mat1.matrixTab4[0][0] + matrixTab4[3][1] * mat1.matrixTab4[1][0] + matrixTab4[3][2] * mat1.matrixTab4[2][0] + matrixTab4[3][3] * mat1.matrixTab4[3][0];

    mat.matrixTab4[0][1] = matrixTab4[0][0] * mat1.matrixTab4[0][1] + matrixTab4[0][1] * mat1.matrixTab4[1][1] + matrixTab4[0][2] * mat1.matrixTab4[2][1] + matrixTab4[0][3] * mat1.matrixTab4[3][1];
    mat.matrixTab4[1][1] = matrixTab4[1][0] * mat1.matrixTab4[0][1] + matrixTab4[1][1] * mat1.matrixTab4[1][1] + matrixTab4[1][2] * mat1.matrixTab4[2][1] + matrixTab4[1][3] * mat1.matrixTab4[3][1];
    mat.matrixTab4[2][1] = matrixTab4[2][0] * mat1.matrixTab4[0][1] + matrixTab4[2][1] * mat1.matrixTab4[1][1] + matrixTab4[2][2] * mat1.matrixTab4[2][1] + matrixTab4[2][3] * mat1.matrixTab4[3][1];
    mat.matrixTab4[3][1] = matrixTab4[3][0] * mat1.matrixTab4[0][1] + matrixTab4[3][1] * mat1.matrixTab4[1][1] + matrixTab4[3][2] * mat1.matrixTab4[2][1] + matrixTab4[3][3] * mat1.matrixTab4[3][1];

    mat.matrixTab4[0][2] = matrixTab4[0][0] * mat1.matrixTab4[0][2] + matrixTab4[0][1] * mat1.matrixTab4[1][2] + matrixTab4[0][2] * mat1.matrixTab4[2][2] + matrixTab4[0][3] * mat1.matrixTab4[3][2];
    mat.matrixTab4[1][2] = matrixTab4[1][0] * mat1.matrixTab4[0][2] + matrixTab4[1][1] * mat1.matrixTab4[1][2] + matrixTab4[1][2] * mat1.matrixTab4[2][2] + matrixTab4[1][3] * mat1.matrixTab4[3][2];
    mat.matrixTab4[2][2] = matrixTab4[2][0] * mat1.matrixTab4[0][2] + matrixTab4[2][1] * mat1.matrixTab4[1][2] + matrixTab4[2][2] * mat1.matrixTab4[2][2] + matrixTab4[2][3] * mat1.matrixTab4[3][2];
    mat.matrixTab4[3][2] = matrixTab4[3][0] * mat1.matrixTab4[0][2] + matrixTab4[3][1] * mat1.matrixTab4[1][2] + matrixTab4[3][2] * mat1.matrixTab4[2][2] + matrixTab4[3][3] * mat1.matrixTab4[3][2];

    mat.matrixTab4[0][3] = matrixTab4[0][0] * mat1.matrixTab4[0][3] + matrixTab4[0][1] * mat1.matrixTab4[1][3] + matrixTab4[0][2] * mat1.matrixTab4[2][3] + matrixTab4[0][3] * mat1.matrixTab4[3][3];
    mat.matrixTab4[1][3] = matrixTab4[1][0] * mat1.matrixTab4[0][3] + matrixTab4[1][1] * mat1.matrixTab4[1][3] + matrixTab4[1][2] * mat1.matrixTab4[2][3] + matrixTab4[1][3] * mat1.matrixTab4[3][3];
    mat.matrixTab4[2][3] = matrixTab4[2][0] * mat1.matrixTab4[0][3] + matrixTab4[2][1] * mat1.matrixTab4[1][3] + matrixTab4[2][2] * mat1.matrixTab4[2][3] + matrixTab4[2][3] * mat1.matrixTab4[3][3];
    mat.matrixTab4[3][3] = matrixTab4[3][0] * mat1.matrixTab4[0][3] + matrixTab4[3][1] * mat1.matrixTab4[1][3] + matrixTab4[3][2] * mat1.matrixTab4[2][3] + matrixTab4[3][3] * mat1.matrixTab4[3][3];
    return mat;
}

Vector4D Matrix4::operator*(const Vector4D& vec1)
{
    Vector4D vec;
    vec.x = vec1.x * matrixTab4[0][0] + vec1.y * matrixTab4[0][1] + vec1.z * matrixTab4[0][2] + vec1.w * matrixTab4[0][3];
    vec.y = vec1.x * matrixTab4[1][0] + vec1.y * matrixTab4[1][1] + vec1.z * matrixTab4[1][2] + vec1.w * matrixTab4[1][3];
    vec.z = vec1.x * matrixTab4[2][0] + vec1.y * matrixTab4[2][1] + vec1.z * matrixTab4[2][2] + vec1.w * matrixTab4[2][3];
    vec.w = vec1.x * matrixTab4[3][0] + vec1.y * matrixTab4[3][1] + vec1.z * matrixTab4[3][2] + vec1.w * matrixTab4[3][3];
    return vec;
}

Matrix4 operator*(const Matrix4& a, const Matrix4& b)
{
    Matrix4 c = Matrix4();

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                c.matrixTab4[i][j] += a.matrixTab4[i][k] * b.matrixTab4[k][j];
            }
        }
    }

    return c;
}


Matrix4 operator*(const Matrix4& a, const float b)
{
    Matrix4 c = Matrix4();

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            c.matrixTab4[i][j] = a.matrixTab4[i][j] * b;
        }
    }

    return c;
}

Matrix3 operator*(const Matrix3& a, const Matrix3& b)
{
    Matrix3 c = Matrix3();

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                c.matrixTab3[i][j] += a.matrixTab3[i][k] * b.matrixTab3[k][j];
            }
        }
    }

    return c;
}

Matrix3 operator*(const Matrix3& a, const float b)
{
    Matrix3 c = Matrix3();

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            c.matrixTab3[i][j] = a.matrixTab3[i][j] * b;
        }
    }

    return c;
}


Vector4D operator*(const Matrix4& a, const Vector4D& b)
{
    Vector4D c = Vector4D();

    c.x = a.matrixTab4[0][0] * b.x + a.matrixTab4[0][1] * b.y + a.matrixTab4[0][2] * b.z + a.matrixTab4[0][3] * b.w;
    c.y = a.matrixTab4[1][0] * b.x + a.matrixTab4[1][1] * b.y + a.matrixTab4[1][2] * b.z + a.matrixTab4[1][3] * b.w;
    c.z = a.matrixTab4[2][0] * b.x + a.matrixTab4[2][1] * b.y + a.matrixTab4[2][2] * b.z + a.matrixTab4[2][3] * b.w;
    c.w = a.matrixTab4[3][0] * b.x + a.matrixTab4[3][1] * b.y + a.matrixTab4[3][2] * b.z + a.matrixTab4[3][3] * b.w;

    return c;
}

Vector4D operator*(const Vector4D& b, const Matrix4& a)
{
    Vector4D c = Vector4D();

    c.x = a.matrixTab4[0][0] * b.x + a.matrixTab4[0][1] * b.y + a.matrixTab4[0][2] * b.z + a.matrixTab4[0][3] * b.w;
    c.y = a.matrixTab4[1][0] * b.x + a.matrixTab4[1][1] * b.y + a.matrixTab4[1][2] * b.z + a.matrixTab4[1][3] * b.w;
    c.z = a.matrixTab4[2][0] * b.x + a.matrixTab4[2][1] * b.y + a.matrixTab4[2][2] * b.z + a.matrixTab4[2][3] * b.w;
    c.w = a.matrixTab4[3][0] * b.x + a.matrixTab4[3][1] * b.y + a.matrixTab4[3][2] * b.z + a.matrixTab4[3][3] * b.w;

    return c;
}

Matrix4 Matrix4::LookAt(Vector3D eye, Vector3D target, Vector3D up)
{
    Vector3D zaxis = target - eye;
    target.Normalize();
    Vector3D xaxis = zaxis.CrossProduct(up);
    xaxis.Normalize();
    Vector3D yaxis = xaxis.CrossProduct(zaxis);

    zaxis * -1;

    float viewMatrix[4][4] = {
        {xaxis.x, xaxis.y, xaxis.z, -xaxis.Dot(eye)},
        {yaxis.x, yaxis.y, yaxis.z, -yaxis.Dot(eye)},
        {zaxis.x, zaxis.y, zaxis.z, -zaxis.Dot(eye)},
        {0, 0, 0, 1}
    };

    return viewMatrix;
}

// -- > More Fonction 
// find the maximum between 2 points
int checkMax2(int a, int b)
{
    return (a < b) ? b : a;
}

// Find the minimum between 2 points
int checkMin2(int a, int b)
{
    return (a < b) ? a : b;
}

// find the maximum between 3 points
int checkMax3(int a, int b, int c)
{
    int d;
    d = a < b ? b : a;
    return (d < c) ? c : d;
}

// Find the minimum between 3 points
int checkMin3(int a, int b, int c)
{
    int d;
    d = a > b ? b : a;
    return (d > c) ? c : d;
}

// Function to find the barycenter
float edgeFunction(const Vector3D& a, const Vector3D& b, const Vector3D& c)
{
    return (c.x - a.x) * (b.y - a.y) - (c.y - a.y) * (b.x - a.x);
}

float GetDeterminantMat2(const float a, const float b, const float c, const float d)
{
    return (a * d - b * c);
}

float GetDeterminantMat3(const Vector3D& a, const Vector3D& b, const Vector3D& c)
{
    return (
        a.x * GetDeterminantMat2(b.y, b.z, c.y, c.z)
        - a.y * GetDeterminantMat2(b.x, b.z, c.x, c.z)
        + a.z * GetDeterminantMat2(b.x, b.y, c.x, c.y)
        );
}

float GetDeterminantMat3(const float tab[3][3])
{
    return (
        tab[0][0] * GetDeterminantMat2(tab[1][1], tab[1][2], tab[2][1], tab[2][2])
        - tab[0][1] * GetDeterminantMat2(tab[1][0], tab[1][2], tab[2][0], tab[2][2])
        + tab[0][2] * GetDeterminantMat2(tab[1][0], tab[1][1], tab[2][0], tab[2][1])
        );
}

float GetDeterminantMat4(const Matrix4& a)
{
    return(
        a.matrixTab4[0][0] * GetDeterminantMat3({ a.matrixTab4[1][1], a.matrixTab4[1][2], a.matrixTab4[1][3] }, { a.matrixTab4[2][1], a.matrixTab4[2][2], a.matrixTab4[2][3] }, { a.matrixTab4[3][1], a.matrixTab4[3][2], a.matrixTab4[3][3] })
        - a.matrixTab4[0][1] * GetDeterminantMat3({ a.matrixTab4[1][0], a.matrixTab4[1][2], a.matrixTab4[1][3] }, { a.matrixTab4[2][0], a.matrixTab4[2][2], a.matrixTab4[2][3] }, { a.matrixTab4[3][0], a.matrixTab4[3][2], a.matrixTab4[3][3] })
        + a.matrixTab4[0][2] * GetDeterminantMat3({ a.matrixTab4[1][0], a.matrixTab4[1][1], a.matrixTab4[1][3] }, { a.matrixTab4[2][0], a.matrixTab4[2][1], a.matrixTab4[2][3] }, { a.matrixTab4[3][0], a.matrixTab4[3][1], a.matrixTab4[3][3] })
        - a.matrixTab4[0][3] * GetDeterminantMat3({ a.matrixTab4[1][0], a.matrixTab4[1][1], a.matrixTab4[1][2] }, { a.matrixTab4[2][0], a.matrixTab4[2][1], a.matrixTab4[2][2] }, { a.matrixTab4[3][0], a.matrixTab4[3][1], a.matrixTab4[3][2] })
        );
}

float Lerp(float a, float b, float t)
{
    return a + t * (b - a);
}

Vector3D operator*(const float b, const Vector3D& a)
{
    Vector3D c(
        a.x * b,
        a.y * b,
        a.z * b
    );
    return c;
}

Sphere::Sphere()
{
    radius = 0;
}

Sphere::Sphere(float rad)
{
    radius = rad;
}

OBB::OBB()
{
    umv = nullptr;
}

OBB::OBB(Matrix4 t_umv)
{
    umv = t_umv;
}