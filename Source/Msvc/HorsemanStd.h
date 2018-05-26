#pragma once

// General includes
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory>

#include <algorithm>
#include <string>
#include <list>
#include <vector>
#include <queue>
#include <map>

using std::shared_ptr;
using std::weak_ptr;

using std::vector;
using std::map;
using std::string;

// OpenGL Includes
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <GL/GL.h>

using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat4;
using glm::quat;

// Include rapidxml
#include <rapidxml/rapidxml.hpp>

// Internal includes
#include "Core/interfaces.h"
#include "Utils/config.h"
#include "Utils/templates.h"

// Config object
extern HorsemanConfig config;

// Useful #defines
#define CONCAT_NX(A, B) A ## B
#define CONCAT(A, B) CONCAT_NX(A, B)

#define STRINGIZE_NX(A) #A
#define STRINGIZE(A) STRINGIZE_NX(A)

#define M_PI		3.14159265358979323846
#define DEG2RAD		M_PI / 180
#define RAD2DEG		180 / M_PI

#if !defined(SAFE_DELETE)
#define SAFE_DELETE(x) if(x) delete x; x=NULL;
#endif

#if !defined(SAFE_DELETE_ARRAY)
#define SAFE_DELETE_ARRAY(x) if (x) delete [] x; x=NULL; 
#endif

#if !defined(SAFE_RELEASE)
#define SAFE_RELEASE(x) if(x) x->Release(); x=NULL;
#endif

#define PROPERTY(t,n)  __declspec( property (put = property__set_##n, get = property__get_##n)) t n; \
	typedef t property__tmp_type_##n
#define READONLY_PROPERTY(t,n) __declspec( property (get = property__get_##n) ) t n;\
	typedef t property__tmp_type_##n
#define WRITEONLY_PROPERTY(t,n) __declspec( property (put = property__set_##n) ) t n;\
	typedef t property__tmp_type_##n

#define GET(n) property__tmp_type_##n property__get_##n()
#define SET(n) void property__set_##n(const property__tmp_type_##n& value)