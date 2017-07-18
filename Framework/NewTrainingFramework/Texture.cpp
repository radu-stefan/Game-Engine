#pragma once
#include "stdafx.h"
#include "Texture.h"
#include "Resource.h"

int Texture::Load()
{
	GLenum type;
	int w, h;
	int bpp, rgb;
	char *pArr = LoadTGA(tr->path.c_str(), &w, &h, &bpp);

	if (bpp == 32) 
		rgb = GL_RGBA;
	else if(bpp == 24)
		rgb = GL_RGB;

	switch (tr->type) {
	case TextureResource::_2d:
		type = GL_TEXTURE_2D;
		break;
	case TextureResource::cube:
		type = GL_TEXTURE_CUBE_MAP;
		break;
	}

	glGenTextures(1, &texId);
	glBindTexture(type, texId);

	glTexParameteri(type, GL_TEXTURE_MIN_FILTER, tr->min_filter);
	glTexParameteri(type, GL_TEXTURE_MAG_FILTER, tr->mag_filter);

	glTexParameteri(type, GL_TEXTURE_WRAP_S, tr->wrap_s);
	glTexParameteri(type, GL_TEXTURE_WRAP_T, tr->wrap_t);

	switch (tr->type) {
	case TextureResource::_2d:
		glTexImage2D(type, 0, rgb, w, h, 0, rgb, GL_UNSIGNED_BYTE, pArr);
		break;
	case TextureResource::cube:
	
		char* buffer = new char[(w/4)*(h/3)*bpp/8];
		int offsetW = (w / 4)*(bpp / 8);
		int k = 0;
		for (int i = 1 * (h / 3); i < 2 * (h / 3); i++) {
			int offsetH = i * (w*bpp / 8);
			for (int j = offsetH + 2*offsetW; j < offsetH + 3* offsetW; j++) {
				buffer[k] = pArr[j];
				k++;
			}
		}
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, rgb, w / 4, h / 3, 0, rgb, GL_UNSIGNED_BYTE, buffer);
		k = 0;

		for (int i = 1 * (h / 3); i < 2 * (h / 3); i++) {
			int offsetH = i * (w*bpp / 8);
			for (int j = offsetH + 0 * offsetW; j < offsetH + 1 * offsetW; j++) {
				buffer[k] = pArr[j];
				k++;
			}
		}
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, rgb, w / 4, h / 3, 0, rgb, GL_UNSIGNED_BYTE, buffer);
		k = 0;
		for (int i = 0 * (h / 3); i < 1 * (h / 3); i++) {
			int offsetH = i * (w*bpp / 8);
			for (int j = offsetH + 1 * offsetW; j < offsetH + 2 * offsetW; j++) {
				buffer[k] = pArr[j];
				k++;
			}
		}
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, rgb, w / 4, h / 3, 0, rgb, GL_UNSIGNED_BYTE, buffer);
		k = 0;
		for (int i = 2 * (h / 3); i < 3 * (h / 3); i++) {
			int offsetH = i * (w*bpp / 8);
			for (int j = offsetH + 1 * offsetW; j < offsetH + 2 * offsetW; j++) {
				buffer[k] = pArr[j];
				k++;
			}
		}
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, rgb, w / 4, h / 3, 0, rgb, GL_UNSIGNED_BYTE, buffer);
		k = 0;
		for (int i = 1 * (h / 3); i < 2 * (h / 3); i++) {
			int offsetH = i * (w*bpp / 8);
			for (int j = offsetH + 1 * offsetW; j < offsetH + 2 * offsetW; j++) {
				buffer[k] = pArr[j];
				k++;
			}
		}
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, rgb, w / 4, h / 3, 0, rgb, GL_UNSIGNED_BYTE, buffer);
		k = 0;

		for (int i = 1 * (h / 3) ; i < 2 * (h / 3); i++) {
			int offsetH = i * (w*bpp / 8);
			for (int j = offsetH + 3 * offsetW; j < offsetH + 4 * offsetW; j++) {
				buffer[k] = pArr[j];
				k++;
			}
		}
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, rgb, w / 4, h / 3, 0, rgb, GL_UNSIGNED_BYTE, buffer);
		
		delete buffer;
		break;
	}

	glBindTexture(type, 0);
	free(pArr);
	return 1;
}

Texture::Texture()
{
}


Texture::~Texture()
{
}
