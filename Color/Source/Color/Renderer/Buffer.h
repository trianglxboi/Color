#pragma once

#include "Core/Base.h"

namespace Color
{
	enum class ShaderDataType
	{
		None = 0,
		Float, Float2, Float3, Float4,
		Mat3, Mat4,
		Int, Int2, Int3, Int4,
		Bool
	};

	size_t SizeOfShaderDataType(ShaderDataType type);

	struct BufferElement
	{
		std::string Name;
		ShaderDataType Type = ShaderDataType::None;
		size_t Size = 0, Offset = 0;
		bool Normalized = false;

		BufferElement() = default;
		BufferElement(ShaderDataType type, std::string_view name, bool normalized = false)
			: Name(name), Type(type), Size(SizeOfShaderDataType(type)), Offset(0), Normalized(normalized) {}

		uint8_t GetComponentCount() const
		{
			switch (Type)
			{
			case ShaderDataType::Float:  return 1;
			case ShaderDataType::Float2: return 2;
			case ShaderDataType::Float3: return 3;
			case ShaderDataType::Float4: return 4;
			case ShaderDataType::Mat3:   return 3;
			case ShaderDataType::Mat4:   return 4;
			case ShaderDataType::Int:    return 1;
			case ShaderDataType::Int2:   return 2;
			case ShaderDataType::Int3:   return 3;
			case ShaderDataType::Int4:   return 4;
			case ShaderDataType::Bool:   return 1;
			}

			unreachable();
			return 0;
		}
	};

	class BufferLayout
	{
	public:
		BufferLayout() = default;
		BufferLayout(std::initializer_list<BufferElement> elements)
			: m_Elements(elements)
		{
			RecalculateStrideAndElementOffsets();
		}

		void RecalculateStrideAndElementOffsets()
		{
			size_t offset = 0;

			for (BufferElement& element : m_Elements)
			{
				element.Offset = offset;
				offset += element.Size;
				// m_Stride += element.Size;
			}

			m_Stride = offset;
		}

		const std::vector<BufferElement>& GetElements() const { return m_Elements; }
		size_t GetStride() const { return m_Stride; }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator cbegin() const { return m_Elements.cbegin(); }
		std::vector<BufferElement>::const_iterator cend() const { return m_Elements.cend(); }

		std::vector<BufferElement>::reverse_iterator rbegin() { return m_Elements.rbegin(); }
		std::vector<BufferElement>::reverse_iterator rend() { return m_Elements.rend(); }
		std::vector<BufferElement>::const_reverse_iterator rbegin() const { return m_Elements.rbegin(); }
		std::vector<BufferElement>::const_reverse_iterator rend() const { return m_Elements.rend(); }
		std::vector<BufferElement>::const_reverse_iterator crbegin() const { return m_Elements.crbegin(); }
		std::vector<BufferElement>::const_reverse_iterator crend() const { return m_Elements.crend(); }
	private:
		std::vector<BufferElement> m_Elements;
		size_t m_Stride = 0;
	};

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual	void SetLayout(const BufferLayout& layout) = 0;
		virtual	void SetData(const void* data, size_t size) = 0;

		virtual const BufferLayout& GetLayout() const = 0;

		static Ref<VertexBuffer> Create(const float* vertices, size_t size);
		static Ref<VertexBuffer> Create(size_t size);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual size_t GetCount() const = 0;

		static Ref<IndexBuffer> Create(const uint32_t* indices, size_t count);
	};
}
