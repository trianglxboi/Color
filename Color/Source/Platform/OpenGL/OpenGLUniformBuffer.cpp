#include "ColorPCH.h"
#include "OpenGLUniformBuffer.h"

#include <glad/glad.h>

namespace Color
{
	OpenGLUniformBuffer::OpenGLUniformBuffer(size_t size, size_t binding)
	{
		glCreateBuffers(1, &m_RendererID);
		glNamedBufferData(m_RendererID, (GLsizeiptr) size, NULL, GL_DYNAMIC_DRAW);
		glBindBufferBase(GL_UNIFORM_BUFFER, (GLuint) binding, m_RendererID);
	}

	OpenGLUniformBuffer::~OpenGLUniformBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLUniformBuffer::SetData(const void* data, size_t size, size_t offset)
	{
		glNamedBufferSubData(m_RendererID, (GLintptr) offset, (GLsizeiptr) size, data);
	}
}
