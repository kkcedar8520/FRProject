#pragma once
#include <windows.h>
#include <math.h>
#define J_EPSILON  (0.001f)
namespace JDX
{
	class Matrix;

	struct float2
	{
		union
		{
			struct { float x, y; };
			float v[2];
		};
	};
	struct float3
	{
		union
		{
			struct { float x, y, z; };
			float v[3];
		};
	};
	struct float4
	{
		union
		{
			struct { float x, y, z, w; };
			float v[4];
		};
	};
	struct float4x4
	{
		union {
			struct {
				float _11, _12, _13, _14;
				float _21, _22, _23, _24;
				float _31, _32, _33, _34;
				float _41, _42, _43, _44;
			};
			float m[4][4];
		};
	};
	class Vector2 : public float2
	{
	public:
		Vector2();
		Vector2(float fx, float fy);
		Vector2(const Vector2& v);
		~Vector2() {};
	public:
		Vector2 operator + (Vector2 const& v);
		Vector2 operator - (Vector2 const& v);
		Vector2 operator * (float const& fScala);
		Vector2 operator + (float const& fScala);
		Vector2 operator / (float const& fScala);
		bool    operator == (Vector2 const &v);
	};
	class Vector3 : public float3
	{
	public:
		Vector3();
		Vector3(float fx, float fy, float fz);
		Vector3(const Vector3& v);
		~Vector3() {};
	public:
		Vector3 operator + (Vector3 const& v);
		Vector3 operator - (Vector3 const& v);
		Vector3 operator * (float const& fScala);
		Vector3 operator + (float const& fScala);
		Vector3 operator / (float const& fScala);
		bool    operator == (Vector3 const &v);
		float operator | (Vector3 const &v);
		Vector3 operator ^ (Vector3 const &v);

		Vector3 operator * (Matrix& mat);
	public:
		float   Length();
		Vector3 Normalize();
	};
	class Vector4 : public float4
	{
	public:
		Vector4();
		Vector4(float fx, float fy, float fz, float fw);
		Vector4(const Vector4& v);
		~Vector4() {};
	public:
		Vector4 operator + (Vector4 const& v);
		Vector4 operator - (Vector4 const& v);
		Vector4 operator * (float const& fScala);
		Vector4 operator + (float const& fScala);
		Vector4 operator / (float const& fScala);
		bool    operator == (Vector4 const &v);
	};
	class Matrix : public float4x4
	{
	public:
		void Identity();
		Matrix();
		Matrix(const Matrix& mat);
		~Matrix() {}
	public:
		Matrix operator *(Matrix const &mat);
		void Translation(float x, float y, float z);
		void Translation(Vector3 v);
		void Scale(float x, float y, float z);
		void Scale(Vector3 v);
		void RotateX(float fRadian);
		void RotateY(float fRadian);
		void RotateZ(float fRadian);
		Matrix Transpose();
		static Matrix CreateViewLookAt(Vector3& pos,
			Vector3& target,
			Vector3& up);
		Matrix CreateObjectLookAt(Vector3& pos,
			Vector3& target,
			Vector3& up);

		static Matrix CreatePerspectiveFovLH(
			float fnear,
			float fFar,
			float fFovY,
			float fAspect);

	};
	class JMath
	{
	public:
		JMath();
		virtual ~JMath();
	};
}
using namespace JDX;

