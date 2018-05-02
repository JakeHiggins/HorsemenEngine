#ifndef _VECTOR3_H_
#define _VECTOR3_H_

struct Vector3 {
	float x;
	float y;
	float z;

public:
	Vector3() {
		this->x = 0;
		this->y = 0;
		this->z = 0;
	}

	Vector3(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Vector3 operator+(const Vector3& other) {
		Vector3 v;
		v.x = this->x + other.x;
		v.y = this->y + other.y;
		v.z = this->z + other.z;
		return v;
	}

	Vector3 operator-(const Vector3& other) {
		Vector3 v;
		v.x = this->x - other.x;
		v.y = this->y - other.y;
		v.z = this->z - other.z;
		return v;
	}

	Vector3 operator*(float factor) {
		Vector3 v;
		v.x = this->x * factor;
		v.y = this->y * factor;
		v.z = this->z * factor;
		return v;
	}

	Vector3 operator/(float factor) {
		Vector3 v;
		v.x = this->x / factor;
		v.y = this->y / factor;
		v.z = this->z / factor;
		return v;
	}

	bool operator==(const Vector3& other) {
		return this->x == other.x && this->y == other.y && this->z == other.z;
	}
};

#endif