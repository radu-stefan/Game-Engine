#pragma once
#include "stdafx.h"
#include "Vertex.h"
#include "Resource.h"
#include <vector>
#include "../Utilities/utilities.h"

class Model
{
public:
	ModelResource* mr;

	GLuint iboId, wiredIboId, vboId;
	int nrIndici, nrIndiciWired;

	std::vector<Vertex> mVertex;
	std::vector<unsigned short> mIndices;
	std::vector<unsigned short> mLinesIndices;

	Model();
	~Model();
	int Load();

};

