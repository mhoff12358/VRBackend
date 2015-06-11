#include "Quaternion.h"

Quaternion::Quaternion() {
	x = 0;
	y = 0;
	z = 0;
	w = 1;
}

Quaternion::Quaternion(std::array<float, 4> val) {
	x = val[0];
	y = val[1];
	z = val[2];
	w = val[3];
}

Quaternion::Quaternion(float xval, float yval, float zval, float wval) :
	x(xval), y(yval), z(zval), w(wval) {

}

std::array<float, 4> Quaternion::GetArray() const {
	return { { x, y, z, w } };
}

float Quaternion::dot(const Quaternion& other) const {
	return x*other.x + y*other.y + z*other.z + w*other.w;
}

Quaternion Quaternion::operator*(const Quaternion& other) const {
	return Quaternion(
		w*other.x + x*other.w + y*other.z - z*other.y,
		w*other.y - x*other.z + y*other.w + z*other.x,
		w*other.z + x*other.y - y*other.x + z*other.w,
		w*other.w - x*other.x - y*other.y - z*other.z);
}

Quaternion Quaternion::operator*(const float other) const {
	return Quaternion(x*other, y*other, z*other, w*other);
}

Quaternion Quaternion::ToPower(const float& other) const {
	// To avoid a divide by zero scenario, if theta is 0 (meaning w is 1) then
	// the end result is just the same quaternion
	if (w == 1.0f) {
		return Quaternion(0, 0, 0, 1);
	}
	float theta = acos(w) * 2.0f;
	float imaginary_scale = sin(theta*other / 2.0f) / sin(theta / 2.0f);

	return Quaternion(imaginary_scale*x, imaginary_scale*y, imaginary_scale*z, cos(theta*other/2.0f));
}

Quaternion Quaternion::RotationAboutAxis(AxisID axis, float angle_in_radians) {
	switch (axis) {
	case AID_X:
		return Quaternion(sin(angle_in_radians / 2.0f), 0, 0, cos(angle_in_radians / 2));
	case AID_Y:
		return Quaternion(0, sin(angle_in_radians / 2.0f), 0, cos(angle_in_radians / 2));
	case AID_Z:
		return Quaternion(0, 0, sin(angle_in_radians / 2.0f), cos(angle_in_radians / 2));
	}
}

Quaternion Quaternion::Slerp(const Quaternion& q0, const Quaternion& q1, float weight) {
	if (q0.dot(q1) >= 0) {
		return q0*((q0.ToPower(-1)*q1).ToPower(weight));
	} else {
		return q0*((q0.ToPower(-1)*(q1*-1)).ToPower(weight));
	}
}

Quaternion Quaternion::RotationBetweenVectors(const std::array<float, 3>& start_vec, const std::array<float, 3>& end_vec) {
	// This assumes that the two vectors are normalized
	std::array<float, 3> halfway_vec;
	float halfway_vec_mag = 0.0f;
	for (int i = 0; i < 3; i++) {
		halfway_vec[i] = (start_vec[i] + end_vec[i]) / 2.0f;
		halfway_vec_mag += pow(halfway_vec[i], 2);
	}
	halfway_vec_mag = pow(halfway_vec_mag, 0.5);
	for (int i = 0; i < 3; i++) {
		halfway_vec[i] /= halfway_vec_mag;
	}
	// The first 3 values are the cross product, and the last value is the dot product
	std::array<float, 4> result_vec;
	result_vec[3] = 0.0f;
	for (int i = 0; i < 3; i++) {
		result_vec[3] += start_vec[i] * halfway_vec[i];
	}
	result_vec[0] = halfway_vec[1] * start_vec[2] - halfway_vec[2] * start_vec[1];
	result_vec[1] = -halfway_vec[0] * start_vec[2] + halfway_vec[2] * start_vec[0];
	result_vec[2] = halfway_vec[0] * start_vec[1] - halfway_vec[1] * start_vec[0];
	return Quaternion(result_vec);
}