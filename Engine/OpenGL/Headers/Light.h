#pragma once
#include <Maths.h>

namespace LowRenderer
{
	class Light
	{
	public:
		Vector3D ambientColor;
		Vector3D diffuseColor;
		Vector3D specularColor;
	};

	class PointLight : public Light
	{
	public:
		Vector3D position;

		float constant;
		float linear;
		float quadratic;

		PointLight(const Vector3D& pos, const Vector3D& color, float cons, float lin, float quad)
		{
			position = pos;
			ambientColor = 0.1f * color ;
			diffuseColor = 0.5f * color;
			specularColor = 1.f * color;
			constant = cons;
			linear = lin;
			quadratic = quad;
		}

		PointLight(const Vector3D& pos, const Vector3D& amb, const Vector3D& diff, const Vector3D& spec, float cons, float lin, float quad)
		{
			position = pos;
			ambientColor = amb;
			diffuseColor = diff;
			specularColor = spec;
			constant = cons;
			linear = lin;
			quadratic = quad;
		}
	};

	class DirectionnalLight : public Light
	{
	public:
		Vector3D direction;

		DirectionnalLight(const Vector3D& dir, const Vector3D& color)
		{
			direction = dir;
			ambientColor = 0.1f * color;
			diffuseColor = 0.5f * color;
			specularColor = 1.f * color;
		}

		DirectionnalLight(const Vector3D& dir, const Vector3D& amb, const Vector3D& diff, const Vector3D& spec)
		{
			direction = dir;
			ambientColor = amb;
			diffuseColor = diff;
			specularColor = spec;
		}
	};

	class SpotLight : public Light
	{
	public:
		Vector3D position;
		Vector3D direction;

		float constant;
		float linear;
		float quadratic;

		float angle;  //only between M_PI / 3.1 and 0

		SpotLight(const Vector3D& dir, const Vector3D& pos, const Vector3D& color, float cons, float lin, float quad, float ang)
		{
			direction = dir;
			position = pos;
			ambientColor = 0.1f * color;
			diffuseColor = 0.5f * color;
			specularColor = 1.f * color;
			constant = cons;
			linear = lin;
			quadratic = quad;
			angle = ang;
		}

		SpotLight(const Vector3D& dir, const Vector3D& pos, const Vector3D& amb, const Vector3D& diff, const Vector3D& spec, float cons, float lin, float quad, float ang)
		{
			direction = dir;
			position = pos;
			ambientColor = amb;
			diffuseColor = diff;
			specularColor = spec;
			constant = cons;
			linear = lin;
			quadratic = quad;
			angle = ang;
		}
	};
}