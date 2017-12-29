#include "shader.h"
#include "util.h"
#include "vertexbuffer.h"

using namespace framework;

GLuint Shader::CompileShader(GLenum shaderType, const char*shaderCode) {
	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &shaderCode, nullptr);
	glCompileShader(shader);
	GLint compileResult = GL_TRUE;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);
	if (compileResult == GL_FALSE) {
		char szLog[1024] = { 0 };
		GLsizei logLen = 0;
		glGetShaderInfoLog(shader, 1024, &logLen, szLog);
		printf("Compile Shader fail error log : %s \nshader code :\n%s\n", szLog, shaderCode);
		glDeleteShader(shader);
		shader = 0;
	}
	return shader;
}
void Shader::CreateProgram(GLuint vsShader, GLuint fsShader) {
	mProgram = glCreateProgram();
	glAttachShader(mProgram, vsShader);
	glAttachShader(mProgram, fsShader);
	glLinkProgram(mProgram);
	glDetachShader(mProgram, vsShader);
	glDetachShader(mProgram, fsShader);
	GLint nResult;
	glGetProgramiv(mProgram, GL_LINK_STATUS, &nResult);
	if (nResult == GL_FALSE){
		char log[1024] = {0};
		GLsizei writed = 0;
		glGetProgramInfoLog(mProgram, 1024, &writed, log);
		printf("create gpu program fail,link error : %s\n", log);
		glDeleteProgram(mProgram);
		mProgram = 0;
	}
}
void Shader::Init(const char*vs, const char*fs) {
	int nFileSize = 0;
	std::shared_ptr<unsigned char> vsCode = LoadFileContent(vs,nFileSize);
	std::shared_ptr<unsigned char> fsCode = LoadFileContent(fs,nFileSize);
	GLuint vsShader = CompileShader(GL_VERTEX_SHADER, (const char*)vsCode.get());
	if (vsShader==0){
		return;
	}
	GLuint fsShader = CompileShader(GL_FRAGMENT_SHADER, (const char*)fsCode.get());
	if (fsShader == 0) {
		return;
	}
	CreateProgram(vsShader, fsShader);
	glDeleteShader(vsShader);
	glDeleteShader(fsShader);
	if ( mProgram != 0 ){
		mModelMatrixLocation = glGetUniformLocation(mProgram, "ModelMatrix");
		mViewMatrixLocation = glGetUniformLocation(mProgram, "ViewMatrix");
		mProjectionMatrixLocation = glGetUniformLocation(mProgram, "ProjectionMatrix");
		mIT_ModelMatrixLocation = glGetUniformLocation(mProgram, "IT_ModelMatrix");
		mPositionLocation = glGetAttribLocation(mProgram, "position");
		mColorLocation = glGetAttribLocation(mProgram, "color");
		mTexcoordLocation = glGetAttribLocation(mProgram, "texcoord");
		mNormalLocation = glGetAttribLocation(mProgram, "normal");
	}
}
void Shader::Bind(float *M, float *V, float *P) {
	glUseProgram(mProgram);
	glUniformMatrix4fv(mModelMatrixLocation, 1, GL_FALSE, M);
	glUniformMatrix4fv(mViewMatrixLocation, 1, GL_FALSE, V);
	glUniformMatrix4fv(mProjectionMatrixLocation, 1, GL_FALSE, P);
	for(auto iter = mUniformVec4s.begin(); iter != mUniformVec4s.end(); ++iter) {
		glUniform4fv(iter->second.mLocation, 1, iter->second.v);
	}
	int iIndex = 0;
	for(auto iter = mUniformTextures.begin(); iter != mUniformTextures.end(); ++iter) {
		glActiveTexture(GL_TEXTURE0 + iIndex);
		glBindTexture(GL_TEXTURE_2D, iter->second.mTexture);
		glUniform1i(iter->second.mLocation, iIndex++);
	}

	glEnableVertexAttribArray(mPositionLocation);
	glVertexAttribPointer(mPositionLocation, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glEnableVertexAttribArray(mColorLocation);
	glVertexAttribPointer(mColorLocation, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 4));
	glEnableVertexAttribArray(mTexcoordLocation);
	glVertexAttribPointer(mTexcoordLocation, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 8));
	glEnableVertexAttribArray(mNormalLocation);
	glVertexAttribPointer(mNormalLocation, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 12));
}
void Shader::SetVec4(const char *name, float x, float y, float z, float w) {
	auto iter = mUniformVec4s.find(name);
	if ( iter == mUniformVec4s.end() ) {
		GLint location = glGetUniformLocation(mProgram, name);
		if (location != -1) {
			UniformVector4f v;
			v.v[0] = x;
			v.v[1] = y;
			v.v[2] = z;
			v.v[3] = w;
			v.mLocation = location;
			mUniformVec4s.insert(std::make_pair(name, v));
		}
	}
	else {
		iter->second.v[0] = x;
		iter->second.v[1] = y;
		iter->second.v[2] = z;
		iter->second.v[3] = w;
	}

}
void Shader::SetTexture(const char *name, const char *imagePath) {
	auto iter = mUniformTextures.find(name);
	if ( iter == mUniformTextures.end() ) {
		GLint location = glGetUniformLocation(mProgram, name);
		if (location != -1) {
			UniformTexture v;
			v.mTexture = CreateTextureFromImage(imagePath);
			v.mLocation = location;
			mUniformTextures.insert(std::make_pair(name, v));
		}
	}
	else {
		iter->second.mTexture = CreateTextureFromImage(imagePath);
	}
}
void Shader::SetTexture(const char *name, GLuint texture) {
	auto iter = mUniformTextures.find(name);
	if ( iter == mUniformTextures.end() ) {
		GLint location = glGetUniformLocation(mProgram, name);
		if (location != -1) {
			UniformTexture v;
			v.mTexture = texture;
			v.mLocation = location;
			mUniformTextures.insert(std::make_pair(name, v));
		}
	}
	else {
		glDeleteTextures(1, &iter->second.mTexture);
		iter->second.mTexture = texture;
	}
}
