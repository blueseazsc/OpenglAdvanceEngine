#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include "header.h"

namespace framework {

struct Vertex {
	float position[4];
	float color[4];
	float texcoord[2];
	float normal[4];
};

class VertexBuffer {
public:
	VertexBuffer();
	~VertexBuffer();
	void SetSize(int vertexCount);
	void Bind();
	void Unbind();
	void SetPosition(int index, float x, float y, float z, float w = 1.0f);
	void SetColor(int index, float r, float g, float b, float a = 1.0f);
	void SetTexcoord(int index, float x, float y);
	void SetNormal(int index, float x, float y, float z);
	Vertex& Get(int index);
	int GetVertexCount() const { return mVertexCount; }
protected:
	GLuint mVBO;
	Vertex *mVertexes;
	int mVertexCount;
};
}
#endif
