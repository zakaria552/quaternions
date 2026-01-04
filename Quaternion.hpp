#ifndef QUATERNION_HPP
#define QUATERNION_HPP

#include <cmath>

template<typename T>
class Quaternion
{
	float rpart;
public:
	T ipart;
	Quaternion(const T &vec3)
	{
		//static_assert(vec3.x && vec3.y && vec3.z, "Missing x,y or z component");
		rpart = 0;
		ipart = vec3;
	}
	Quaternion(const float &rpart, const T &ipartVec3): rpart(rpart), ipart(ipartVec3)
	{
		//static_assert(ipartVec3.x && ipartVec3.y && ipartVec3.z, "Missing x,y or z component");
	}
	void rotate(T rotAxis, float radians)
	{
		float s = sinf(radians / 2);
		rotAxis.x *= s; rotAxis.y *= s; rotAxis.z *= s;
		Quaternion q = Quaternion(cosf(radians / 2), rotAxis);
		Quaternion qc = q.conjugate();
		Quaternion v = *this;
		Quaternion rq = q*v*qc;

		*this = rq;
	}
	Quaternion conjugate()
	{
		T nipart = ipart;
		nipart.x *= -1;
		nipart.y *= -1;
		nipart.z *= -1;
		return Quaternion(rpart, nipart);
	}
/*
	Quaternion& operator=(const Quaternion &other)
	{
		if (this == &other)
			return;
		rpart = other.rpart;
		ipart = other.ipart;
	}*/
	Quaternion& operator*(const Quaternion &o)
	{
		T ip;
		float rp = (rpart * o.rpart) - (ipart.x * o.ipart.x) - (ipart.y * o.ipart.y) - (ipart.z * o.ipart.z);

		ip.x = (rpart * o.ipart.x) + (ipart.x * o.rpart) + (ipart.y * o.ipart.z) - (ipart.z * o.ipart.y);
		ip.y = (rpart * o.ipart.y) - (ipart.x * o.ipart.z) + (ipart.y * o.rpart) + (ipart.z * o.ipart.x);
		ip.z = (rpart * o.ipart.z) + (ipart.x * o.ipart.y) - (ipart.y * o.ipart.x) + (ipart.z * o.rpart);

		rpart = rp;
		ipart = ip;
		return *this;
	}
};

#endif

