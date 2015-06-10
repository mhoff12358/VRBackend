#pragma once

#include <array>

enum AxisID {
	AID_X = 0x1,
	AID_Y = 0x2,
	AID_Z = 0x4,
	AID_XY = AID_X | AID_Y,
	AID_XZ = AID_X | AID_Z,
	AID_YZ = AID_Y | AID_Z,
	AID_XYZ = AID_X | AID_Y | AID_Z,
};

class Quaternion {
public:
	Quaternion();
	Quaternion(std::array<float, 4> val);
	Quaternion(float xval, float yval, float zval, float wval);
	std::array<float, 4> GetArray() const;

	float dot(const Quaternion& other) const;

	Quaternion operator*(const Quaternion& other) const;
	Quaternion operator*(const float other) const;
	Quaternion ToPower(const float& other) const;

	float x, y, z, w;

	static Quaternion Slerp(const Quaternion& q0, const Quaternion& q1, float weight);
	static Quaternion RotationBetweenVectors(const std::array<float, 3>& start_vec, const std::array<float, 3>& end_vec);
};
