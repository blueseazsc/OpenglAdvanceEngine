#include "vertexbuffer.h"
#include "util.h"

using namespace framework;

VertexBuffer::VertexBuffer() {
	mVBO = -1;
	mVertexes = nullptr;
	mVertexCount = 0;
}
VertexBuffer::~VertexBuffer() {
	if ( mVertexes )
		delete[] mVertexes;
}
void VertexBuffer::SetSize(int vertexCount) {
	mVertexCount = vertexCount;
	mVertexes = new Vertex[mVertexCount];
	memset(mVertexes, 0, sizeof(Vertex) * mVertexCount);

	mVBO = CreateBufferObject(GL_ARRAY_BUFFER, sizeof(Vertex) * mVertexCount, GL_STATIC_DRAW, nullptr);
}
void VertexBuffer::Bind() {
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * mVertexCount, mVertexes);
}
void VertexBuffer::Unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void VertexBuffer::SetPosition(int index, float x, float y, float z, float w /* = 1.0f */) {
	mVertexes[index].position[0] = x;
	mVertexes[index].position[1] = -y;
	mVertexes[index].position[2] = z;
	mVertexes[index].position[3] = w;
}
void VertexBuffer::SetColor(int index, float r, float g, float b, float a /* = 1.0f */ ) {
	mVertexes[index].color[0] = r;
	mVertexes[index].color[1] = g;
	mVertexes[index].color[2] = b;
	mVertexes[index].color[3] = a;
}
void VertexBuffer::SetTexcoord(int index, float x, float y) {
	mVertexes[index].texcoord[0] = x;
	mVertexes[index].texcoord[1] = y;
}
void VertexBuffer::SetNormal(int index, float x, float y, float z) {
	mVertexes[index].normal[0] = x;
	mVertexes[index].normal[1] = y;
	mVertexes[index].normal[2] = z;
	mVertexes[index].normal[3] = 1.0;
}
Vertex& VertexBuffer::Get(int index) {
	return mVertexes[index];
}
