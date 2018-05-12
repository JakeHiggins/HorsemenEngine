#include "HorsemanStd.h"
#include "Texture.h"

#include <SOIL/SOIL.h>

Texture::Texture() {
}


Texture::~Texture() {
}

void Texture::LoadTexture(const char* path) {
	string p(path);
	size_t pos = p.rfind('.');
	string extension;

	if (pos != string::npos) {
		extension = p.substr(pos);
	}
	else {
		printf("[Texture Load ERROR (%s)]: File has no extension.\n", path);
		return;
	}

	if (extension == ".png" || extension == ".PNG") {
		LoadPNG(path);
	}
	else if (extension == ".bmp" || extension == ".BMP") {
		LoadBMP(path);
	}
	else if (extension == ".dds" || extension == ".DDS") {
		LoadDDS(path);
	}
	else {
		printf("[Texture Load ERROR (%s)]: %s not supported yet, check back later.\n", path, extension.c_str());
	}
}

void Texture::LoadBMP(const char * path) {
	printf("Loading texture %s\n", path);
	unsigned char header[54];
	unsigned int dataPos;
	unsigned int width, height;
	unsigned int imageSize;
	unsigned char* data;

	FILE* file = fopen(path, "rb");
	if (!file) { printf("[Texture Load ERROR (%s)] Image could not be loaded.\n", path); return; }

	if (fread(header, 1, 54, file) != 54) {
		printf("[Texture Load ERROR (%s)] Not a BMP file.\n", path);
		fclose(file);
		return;
	}

	if (header[0] != 'B' || header[1] != 'M') {
		printf("[Texture Load ERROR (%s)] Not a BMP file.\n", path);
		fclose(file);
		return;
	}

	// Ensure 24bpp
	if (*(int*)&(header[0x1E]) != 0) { printf("Not a correct BMP file\n");    fclose(file); return; }
	if (*(int*)&(header[0x1C]) != 24) { printf("Not a correct BMP file\n");    fclose(file); return; }

	dataPos		= *(int*)&(header[0x0A]);
	imageSize	= *(int*)&(header[0x22]);
	width		= *(int*)&(header[0x12]);
	height		= *(int*)&(header[0x16]);

	if (imageSize == 0) imageSize = width * height * 3;
	if (dataPos == 0) dataPos = 54;

	data = new unsigned char[imageSize];
	fread(data, 1, imageSize, file);
	fclose(file);

	// Create texture parameter for opengl
	GLuint textureID;
	glGenTextures(1, &textureID);

	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);

	m_Image = textureID;
}

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

void Texture::LoadDDS(const char * path) {
	unsigned char header[124];

	FILE* file;
	fopen_s(&file, path, "rb");
	if (!file) { printf("[Texture Load ERROR (%s)] Image could not be loaded.\n", path); return; }

	// Verify file type
	char filecode[4];
	fread(filecode, 1, 4, file);
	if (strncmp(filecode, "DDS ", 4) != 0) {
		printf("[Texture Load ERROR (%s)] Not a BMP file.\n", path);
		fclose(file);
		return;
	}

	// Load header data
	fread(&header, 124, 1, file);

	unsigned int height			= *(unsigned int*)&(header[8]);
	unsigned int width			= *(unsigned int*)&(header[12]);
	unsigned int linearSize		= *(unsigned int*)&(header[16]);
	unsigned int mipMapCount	= *(unsigned int*)&(header[24]);
	unsigned int fourCC			= *(unsigned int*)&(header[80]);

	// Load actual data
	unsigned char* buffer;
	unsigned int bufsize;

	bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
	buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char));
	fread(buffer, 1, bufsize, file);

	fclose(file);

	// Parse DXT1, DXT3, and DXT5 formats
	unsigned int components = (fourCC == FOURCC_DXT1) ? 3 : 4;
	unsigned int format;

	switch (fourCC) {
	case FOURCC_DXT1:
		format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
		break;
	case FOURCC_DXT3:
		format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
		break;
	case FOURCC_DXT5:
		format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
		break;
	default:
		free(buffer);
		printf("[Texture Load ERROR (%s)] unrecognized DDS format: %s\n", path, std::to_string(fourCC).c_str());
		return;
	}

	// Create Texture
	GLuint textureID;
	glGenTextures(1, &textureID);

	glBindTexture(GL_TEXTURE_2D, textureID);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, (mipMapCount == 1) ? 0 : mipMapCount - 1);

	if (mipMapCount > 1) {
		printf("[Texture Load INFO (%s)] Texture contains mipmaps.\n", path);
	}
	else {
		printf("[Texture Load INFO (%s)] No mipmaps found.\n", path);
	}

	// Fill mipmaps
	unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
	unsigned int offset = 0;

	// Load mipmaps
	for (unsigned int level = 0; level < mipMapCount && (width || height); ++level) {
		unsigned int size = ((width + 3) / 4) * ((height + 3) / 4) * blockSize;

		glCompressedTexImage2D(
			GL_TEXTURE_2D,		// Target
			level,				// level of mipmap
			format,				// format of texture
			width,				// width of texture
			height,				// height of texture
			0,					// border size
			size,				// size of block
			buffer + offset		// actual data of texture
		);

		offset += size;
		width /= 2;
		height /= 2;

		if (width < 1) width = 1;
		if (height < 1) height = 1;
	}

	free(buffer);

	m_Image = textureID;
}

void Texture::LoadPNG(const char* path) {
	GLuint textureID = SOIL_load_OGL_texture(
		path,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	if (textureID == 0) {
		printf("[Texture Load ERROR (%s)] Image could not be loaded.\n", path);
		return;
	}

	m_Image = textureID;
}

void Texture::Cleanup() {
	glDeleteTextures(1, &m_Image);
}
