#ifndef _VECTOR2_H_
#define _VECTOR2_H_

struct Vector2 {
	float x;
	float y;

public:
	Vector2() {
		this->x = 0;
		this->y = 0;
	}

	Vector2(float x, float y) {
		this->x = x;
		this->y = y;
	}

	Vector2 operator+(const Vector2& other) {
		Vector2 v;
		v.x = this->x + other.x;
		v.y = this->y + other.y;
		return v;
	}

	Vector2 operator-(const Vector2& other) {
		Vector2 v;
		v.x = this->x - other.x;
		v.y = this->y - other.y;
		return v;
	}

	Vector2 operator*(float factor) {
		Vector2 v;
		v.x = this->x * factor;
		v.y = this->y * factor;
		return v;
	}

	Vector2 operator/(float factor) {
		Vector2 v;
		v.x = this->x / factor;
		v.y = this->y / factor;
		return v;
	}

	bool operator==(const Vector2& other) {
		return this->x == other.x && this->y == other.y;
	}
};

#endif