#include "stdafx.h"
#include "Model.h"

using namespace std;

Model::Model()
{
}

Model::~Model()
{
}

int Model::Load()
{
	ifstream in;
	in.open(mr->path);

	if (!in.good()) {
		cout << "Unable to load file: " << mr->path << endl;
		return -1;
	}

	string str;
	regex e("[^[:digit:]\\.-]");
	stringstream ss;
	Vertex vertex;
	int n;

	in >> str >> n;
	getline(in, str);

	for (int i = 0; i < n; i++) {
		in >> str;
		getline(in, str);
		ss.str(regex_replace(str, e, " "));
		ss >> vertex.pos.x >> vertex.pos.y >> vertex.pos.z;
		ss >> vertex.norm.x >> vertex.norm.y >> vertex.norm.z;
		ss >> vertex.binorm.x >> vertex.binorm.y >> vertex.binorm.z;
		ss >> vertex.tgt.x >> vertex.tgt.y >> vertex.tgt.z;
		ss >> vertex.uv.x >> vertex.uv.y;

		mVertex.push_back(Vertex(vertex));
		ss.clear();
	}

	in >> str >> n;
	n = n / 3;
	getline(in, str);

	unsigned int i1, i2, i3;
	for (int i = 0; i < n; i++) {
		in >> str;
		getline(in, str);

		ss.str(regex_replace(str, e, " "));
		ss >> i1 >> i2 >> i3;
		ss.clear();

		mIndices.push_back(i1);
		mIndices.push_back(i2);
		mIndices.push_back(i3);

		mLinesIndices.push_back(i1);
		mLinesIndices.push_back(i2);

		mLinesIndices.push_back(i2);
		mLinesIndices.push_back(i3);

		mLinesIndices.push_back(i1);
		mLinesIndices.push_back(i3);
	}
	nrIndici = mIndices.size();
	nrIndiciWired = mLinesIndices.size();

	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, mVertex.size() * sizeof(Vertex), mVertex.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &iboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, nrIndici * sizeof(unsigned short), mIndices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glGenBuffers(1, &wiredIboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, wiredIboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, nrIndiciWired * sizeof(unsigned short), mLinesIndices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	in.close();
	return 1;
}
