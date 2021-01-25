#include "jMath.h"
namespace JDX
{
	Vector2::Vector2()
	{
		x = y = 0.0f;
	}
	Vector2::Vector2(float fx, float fy)
	{
		x = fx;
		y = fy;
	}
	Vector2::Vector2(const Vector2& v)
	{
		x = v.x;
		y = v.y;
	}
	Vector2 Vector2::operator + (Vector2 const& v)
	{
		return Vector2(x + v.x, y + v.y);
	}
	Vector2 Vector2::operator - (Vector2 const& v)
	{
		return Vector2(x - v.x, y - v.y);
	}
	Vector2 Vector2::operator * (float const& fScala)
	{
		return Vector2(x * fScala, y * fScala);
	}
	Vector2 Vector2::operator + (float const& fScala)
	{
		return Vector2(x + fScala, y + fScala);
	}
	Vector2 Vector2::operator / (float const& fScala)
	{
		return Vector2(x / fScala, y / fScala);
	}
	bool    Vector2::operator == (Vector2 const &v)
	{
		if (fabs(x - v.x) < J_EPSILON)
		{
			if (fabs(y - v.y) < J_EPSILON)
			{
				return true;
			}
		}
		return false;
	}

	Vector3::Vector3()
	{
		x = y = z = 0.0f;
	}
	Vector3::Vector3(float fx, float fy, float fz)
	{
		x = fx;
		y = fy;
		z = fz;
	}
	Vector3::Vector3(const Vector3& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
	}
	Vector3 Vector3::operator + (Vector3 const& v)
	{
		return Vector3(x + v.x, y + v.y, z + v.z);
	}
	Vector3 Vector3::operator - (Vector3 const& v)
	{
		return Vector3(x - v.x, y - v.y, z - v.z);
	}
	Vector3 Vector3::operator * (float const& fScala)
	{
		return Vector3(x * fScala, y * fScala, z *fScala);
	}
	Vector3 Vector3::operator + (float const& fScala)
	{
		return Vector3(x + fScala, y + fScala, z + fScala);
	}
	Vector3 Vector3::operator / (float const& fScala)
	{
		return Vector3(x / fScala, y / fScala, z / fScala);
	}
	bool    Vector3::operator == (Vector3 const &v)
	{
		if (fabs(x - v.x) < J_EPSILON)
		{
			if (fabs(y - v.y) < J_EPSILON)
			{
				if (fabs(z - v.z) < J_EPSILON)
				{
					return true;
				}
			}
		}
		return false;
	}
	float  Vector3::operator | (Vector3 const &v)
	{
		return x * v.x + y * v.y + z * v.z;
	}
	Vector3  Vector3::operator ^ (Vector3 const &v)
	{
		return Vector3(y*v.z - z * v.y,
			z*v.x - x * v.z,
			x*v.y - y * v.x);
	}
	float   Vector3::Length()
	{
		return sqrt(x*x + y * y + z * z);
	}
	Vector3 Vector3::Normalize()
	{
		float fInvLength = 1.0f / Length();
		return Vector3(x*fInvLength, y*fInvLength, z*fInvLength);
	}
	Vector3 Vector3::operator * (Matrix& mat)
	{
		Vector3 ret;
		ret.x = x * mat._11 + y * mat._21 + z * mat._31 + mat._41;
		ret.y = x * mat._12 + y * mat._22 + z * mat._32 + mat._42;
		ret.z = x * mat._13 + y * mat._23 + z * mat._33 + mat._43;
		return ret;
	}

	Vector4::Vector4()
	{
		x = y = z = w = 0.0f;
	}
	Vector4::Vector4(float fx, float fy, float fz, float fw)
	{
		x = fx;
		y = fy;
		z = fz;
		w = fw;
	}
	Vector4::Vector4(const Vector4& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		w = v.w;
	}
	Vector4 Vector4::operator + (Vector4 const& v)
	{
		return Vector4(x + v.x, y + v.y, z + v.z, w + v.w);
	}
	Vector4 Vector4::operator - (Vector4 const& v)
	{
		return Vector4(x - v.x, y - v.y, z - v.z, w - v.w);
	}
	Vector4 Vector4::operator * (float const& fScala)
	{
		return Vector4(x * fScala, y * fScala, z *fScala, w* fScala);
	}
	Vector4 Vector4::operator + (float const& fScala)
	{
		return Vector4(x + fScala, y + fScala, z + fScala, w + fScala);
	}
	Vector4 Vector4::operator / (float const& fScala)
	{
		return Vector4(x / fScala, y / fScala, z / fScala, w / fScala);
	}
	bool    Vector4::operator == (Vector4 const &v)
	{
		if (fabs(x - v.x) < J_EPSILON)
		{
			if (fabs(y - v.y) < J_EPSILON)
			{
				if (fabs(z - v.z) < J_EPSILON)
				{
					if (fabs(w - v.w) < J_EPSILON)
					{
						return true;
					}
				}
			}
		}
		return false;
	}

	Matrix Matrix::Transpose()
	{
		Matrix self;
		self._11 = _11; self._12 = _21; self._13 = _31; self._14 = _41;
		self._21 = _12; self._22 = _22; self._23 = _32; self._24 = _42;
		self._31 = _13; self._32 = _23; self._33 = _33; self._34 = _43;
		self._41 = _14; self._42 = _24; self._43 = _34; self._44 = _44;
		return self;
	}

	void Matrix::Identity()
	{
		_11 = _12 = _13 = _14 = 0.0f;
		_21 = _22 = _23 = _24 = 0.0f;
		_31 = _32 = _33 = _34 = 0.0f;
		_41 = _42 = _43 = _44 = 0.0f;
		_11 = _22 = _33 = _44 = 1.0f;
	}
	Matrix::Matrix()
	{
		Identity();
	}
	Matrix::Matrix(const Matrix& mat)
	{
		for (int row = 0; row < 4; row++)
		{
			for (int col = 0; col < 4; col++)
			{
				m[row][col] = mat.m[row][col];
			}
		}
	}

	void Matrix::Translation(float x, float y, float z)
	{
		Identity();
		_41 = x;
		_42 = y;
		_43 = z;
	}
	void Matrix::Translation(Vector3 v)
	{
		Translation(v.x, v.y, v.z);
	}
	void Matrix::Scale(float x, float y, float z)
	{
		Identity();
		_11 = x;
		_22 = y;
		_33 = z;
	}
	void Matrix::Scale(Vector3 v)
	{
		Scale(v.x, v.y, v.z);
	}
	void Matrix::RotateX(float fRadian)
	{
		float fCos = cos(fRadian);
		float fSin = sin(fRadian);
		Identity();
		_22 = fCos; _23 = fSin;
		_32 = -fSin; _33 = fCos;
	}
	void Matrix::RotateY(float fRadian)
	{
		float fCos = cos(fRadian);
		float fSin = sin(fRadian);
		Identity();
		_11 = fCos; _13 = -fSin;
		_31 = fSin; _33 = fCos;
	}
	void Matrix::RotateZ(float fRadian)
	{
		float fCos = cos(fRadian);
		float fSin = sin(fRadian);
		Identity();
		_11 = fCos; _12 = fSin;
		_21 = -fSin; _22 = fCos;
	}
	Matrix Matrix::operator *(Matrix const &mat)
	{
		Matrix ret;
		for (int row = 0; row < 4; row++)
		{
			for (int col = 0; col < 4; col++)
			{
				ret.m[col][row] =
					m[col][0] * mat.m[0][row] +
					m[col][1] * mat.m[1][row] +
					m[col][2] * mat.m[2][row] +
					m[col][3] * mat.m[3][row];
			}
		}
		return ret;
	}

	Matrix Matrix::CreateViewLookAt(Vector3& pos,
		Vector3& target,
		Vector3& up)
	{
		Matrix mat;
		Vector3 vLook = (target - pos).Normalize();
		Vector3 vRight = (up ^ vLook).Normalize();
		Vector3 vUp = (vLook ^ vRight).Normalize();


		mat._11 = vRight.x; mat._12 = vUp.x; mat._13 = vLook.x;
		mat._21 = vRight.y; mat._22 = vUp.y; mat._23 = vLook.y;
		mat._31 = vRight.z; mat._32 = vUp.z; mat._33 = vLook.z;
		mat._41 = -(pos | vRight);
		mat._42 = -(pos | vUp);
		mat._43 = -(pos | vLook);
		return mat;
	}

	Matrix Matrix::CreateObjectLookAt(Vector3& pos,
		Vector3& target,
		Vector3& up)
	{
		Vector3 vLook = (target - pos).Normalize();
		float fDot = up | vLook;
		Vector3 vUp = (up - (vLook*fDot)).Normalize();
		Vector3 vRight = (vUp ^ vLook).Normalize();

		_11 = vRight.x; _12 = vRight.y; _13 = vRight.z;
		_21 = vUp.x; _22 = vUp.y; _23 = vUp.z;
		_31 = vLook.x; _32 = vLook.y; _33 = vLook.z;
		_41 = pos.x;
		_42 = pos.y;
		_43 = pos.z;
		return *this;
	}

	Matrix Matrix::CreatePerspectiveFovLH(
		float fNear,
		float fFar,
		float fFovY,
		float fAspect)
	{
		Matrix mat;
		ZeroMemory(&mat, sizeof(Matrix));
		float h, w, q;
		h = 1.0f / tan(fFovY*0.5f);
		w = h / fAspect;
		q = fFar / (fFar - fNear);
		mat._11 = w;
		mat._22 = h;
		mat._33 = q;
		mat._43 = -q * fNear;
		mat._34 = 1;
		return mat;
	}
	JMath::JMath()
	{
	}


	JMath::~JMath()
	{
	}
}
