#include "engine_precompiled/engine_precompiled.hpp"
#include "rendering/opengl/texture_opengl.hpp"

#include <glad/glad.h>
#include <stb/stb_image.h>

namespace Engine {

	OpenGlTexture2D::OpenGlTexture2D(const std::string& path)
	: mPath(path) {
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		mWidth = width;
		mHeight = height;

		GLenum internalFormat = 0, dataFormat = 0;
		if(channels == 4) {
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		} else if(channels == 3) {
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}

		glCreateTextures(GL_TEXTURE_2D, 1, &mRendererId);
		glTextureStorage2D(mRendererId, 1, internalFormat, mWidth, mHeight);

		glTextureParameteri(mRendererId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(mRendererId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureSubImage2D(mRendererId, 0, 0, 0, mWidth, mHeight, dataFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	OpenGlTexture2D::~OpenGlTexture2D() {
		glDeleteTextures(1, &mRendererId);
	}

	void OpenGlTexture2D::Bind(uint32_t slot) {
		glBindTextureUnit(slot, mRendererId);
	}

}