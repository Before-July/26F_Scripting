#include "Core/CoreHeaders.h"
#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace fw
{
	Texture::Texture()
	{
		unsigned char pixels[16]
		{
			255,0,0,255,    0,255,0,255,
			0,0,255,255,    255,255,255,255,
		};

		create( pixels, 2, 2 );
	}

	Texture::Texture(std::string filename)
	{
		int x,y,n;
		stbi_set_flip_vertically_on_load( true );
		unsigned char* data = stbi_load( filename.c_str(), &x, &y, &n, 4 );
		create( data, x, y );
		stbi_image_free( data );
	}

	Texture::~Texture()
	{
	}

	void Texture::create(unsigned char* pixels, int width, int height)
	{
		glGenTextures( 1, &m_texture );

		glActiveTexture( GL_TEXTURE0 );
		glBindTexture( GL_TEXTURE_2D, m_texture );
		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels );

		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

		glBindTexture( GL_TEXTURE_2D, 0 );
	}
}
