#ifndef _VECTOR4_H_
#define _VECTOR4_H_

struct Vector4 {
	float x;
	float y;
	float z;
	float w;

public:
	Vector4() {
		this->x = 0;
		this->y = 0;
		this->z = 0;
		this->w = 0;
	}

	Vector4(float x, float y, float z, float w) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	Vector4 operator+(const Vector4& other) {
		Vector4 v;
		v.x = this->x + other.x;
		v.y = this->y + other.y;
		v.z = this->z + other.z;
		v.w = this->w + other.w;
		return v;
	}

	Vector4 operator-(const Vector4& other) {
		Vector4 v;
		v.x = this->x - other.x;
		v.y = this->y - other.y;
		v.z = this->z - other.z;
		v.w = this->w - other.w;
		return v;
	}

	Vector4 operator*(float factor) {
		Vector4 v;
		v.x = this->x * factor;
		v.y = this->y * factor;
		v.z = this->z * factor;
		v.w = this->w * factor;
		return v;
	}

	Vector4 operator/(float factor) {
		Vector4 v;
		v.x = this->x / factor;
		v.y = this->y / factor;
		v.z = this->z / factor;
		v.w = this->w / factor;
		return v;
	}

	bool operator==(const Vector4& other) {
		return this->x == other.x && this->y == other.y && this->z == other.z && this->w == other.w;
	}
};

#endif