#ifndef _LOADERS_H_
#define _LOADERS_H_

#include <vector>

#include <glm/glm.hpp>

using namespace std;
using namespace glm;

struct Vertex {
	vec3 position;
	vec2 uv;
	vec3 normal;

	bool operator<(const Vertex other) const {
		return memcmp((void*)this, (void*)&other, sizeof(Vertex)) > 0;
	}
};

bool SimilarIndex(Vertex& vert, map<Vertex, unsigned short>& vertexMap, unsigned short& result) {
	map<Vertex, unsigned short>::iterator it = vertexMap.find(vert);
	if (it == vertexMap.end()) {
		return false;
	}
	else {
		result = it->second;
		return true;
	}
}

void IndexVBO(
	vector<vec3>& in_vertices,
	vector<vec2>& in_uvs,
	vector<vec3>& in_normals,
	vector<vec3>& in_tangents,
	vector<vec3>& in_bitangents,

	vector<unsigned short>& out_indices,
	vector<vec3>& out_vertices,
	vector<vec2>& out_uvs,
	vector<vec3>& out_normals,
	vector<vec3>& out_tangents,
	vector<vec3>& out_bitangents
) {
	map<Vertex, unsigned short> vertexMap;

	for (unsigned int i = 0; i < in_vertices.size(); i++) {
		Vertex vert = { in_vertices[i], in_uvs[i], in_normals[i] };

		unsigned short index;
		bool found = SimilarIndex(vert, vertexMap, index);

		// similar index is in indices, use it instead
		if (found) {
			out_indices.push_back(index);

			// Average the tangents and bitangents
			out_tangents[index] += in_tangents[i];
			out_bitangents[index] += in_bitangents[i];
		}
		else {
			out_vertices.push_back(in_vertices[i]);
			out_uvs.push_back(in_uvs[i]);
			out_normals.push_back(in_normals[i]);
			out_tangents.push_back(in_tangents[i]);
			out_bitangents.push_back(in_bitangents[i]);

			unsigned short nIndex = (unsigned short)out_vertices.size() - 1;
			out_indices.push_back(nIndex);
			vertexMap[vert] = nIndex;
		}
	}
}

static bool LoadObj(const char* path, vector<vec3>& out_vertices, vector<vec2>& out_uvs, vector<vec3>& out_normals) {
	vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	vector<vec3> vertices;
	vector<vec2> uvs;
	vector<vec3> normals;

	FILE* file = fopen(path, "r");
	if (!file) { printf("ModelLoadError [%s]: Model could not be loaded.\n", path); return false; }

	while (1) {
		char lineHeader[128];

		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF) break;

		if (strcmp(lineHeader, "v") == 0) {
			vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
				&vertexIndex[0], &uvIndex[0], &normalIndex[0],
				&vertexIndex[1], &uvIndex[1], &normalIndex[1],
				&vertexIndex[2], &uvIndex[2], &normalIndex[2]);

			if (matches != 9) { printf("ModelLoadError [%s]: File can't be read by parser, ensure export as triangles\n", path); return false; }

			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
	}

	for (unsigned int i = 0; i < vertexIndices.size(); i++) {
		unsigned int vertexIndex = vertexIndices[i];
		vec3 vertex = vertices[vertexIndex - 1];
		out_vertices.push_back(vertex);
	}

	for (unsigned int i = 0; i < uvIndices.size(); i++) {
		unsigned int uvIndex = uvIndices[i];
		vec2 uv = uvs[uvIndex - 1];
		out_uvs.push_back(uv);
	}

	for (unsigned int i = 0; i < normalIndices.size(); i++) {
		unsigned int normalIndex = normalIndices[i];
		vec3 normal = normals[normalIndex - 1];
		out_normals.push_back(normal);
	}


	return true;
}

static void ComputeTangedBasis(
	vector<vec3>& vertices,
	vector<vec2>& uvs,
	vector<vec3>& normals,

	vector<vec3>& out_tangents,
	vector<vec3>& out_bitangents
) {
	for (unsigned int i = 0; i < vertices.size(); i += 3) {
		vec3& v0 = vertices[i + 0];
		vec3& v1 = vertices[i + 1];
		vec3& v2 = vertices[i + 2];
		
		vec2& uv0 = uvs[i + 0];
		vec2& uv1 = uvs[i + 1];
		vec2& uv2 = uvs[i + 2];
		
		vec3 deltaPos1 = v1 - v0;
		vec3 deltaPos2 = v2 - v0;

		vec2 deltaUV1 = uv1 - uv0;
		vec2 deltaUV2 = uv2 - uv0;
		
		float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
		vec3 tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * r;
		vec3 bitangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x) * r;

		out_tangents.push_back(tangent);
		out_tangents.push_back(tangent);
		out_tangents.push_back(tangent);

		out_bitangents.push_back(bitangent);
		out_bitangents.push_back(bitangent);
		out_bitangents.push_back(bitangent);
	}
}

#endif