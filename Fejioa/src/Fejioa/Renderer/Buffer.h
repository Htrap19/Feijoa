#pragma once

namespace Fejioa
{
	enum class ShaderDataType
	{
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	static unsigned int ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
		case Fejioa::ShaderDataType::Float:  return 4;
		case Fejioa::ShaderDataType::Float2: return 4 * 2;
		case Fejioa::ShaderDataType::Float3: return 4 * 3;
		case Fejioa::ShaderDataType::Float4: return 4 * 4;
		case Fejioa::ShaderDataType::Mat3:   return 4 * 3 * 3;
		case Fejioa::ShaderDataType::Mat4:	 return 4 * 4 * 4;
		case Fejioa::ShaderDataType::Int:    return 4;
		case Fejioa::ShaderDataType::Int2:   return 4 * 2;
		case Fejioa::ShaderDataType::Int3:   return 4 * 3;
		case Fejioa::ShaderDataType::Int4:   return 4 * 4;
		case Fejioa::ShaderDataType::Bool:   return 1;

		default:
			break;
		}

		FJ_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	struct BufferElement
	{
		std::string Name;
		ShaderDataType Type;
		unsigned int Size;
		unsigned int Offset;
		bool Normalized;

		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
			: Type(type), Name(name), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
		{
		}

		unsigned int GetComponentCount() const
		{
			switch (Type)
			{
			case Fejioa::ShaderDataType::Float:  return 1;
			case Fejioa::ShaderDataType::Float2: return 2;
			case Fejioa::ShaderDataType::Float3: return 3;
			case Fejioa::ShaderDataType::Float4: return 4;
			case Fejioa::ShaderDataType::Mat3:   return 3 * 3;
			case Fejioa::ShaderDataType::Mat4:   return 4 * 4;
			case Fejioa::ShaderDataType::Int:    return 1;
			case Fejioa::ShaderDataType::Int2:   return 2;
			case Fejioa::ShaderDataType::Int3:   return 3;
			case Fejioa::ShaderDataType::Int4:   return 4;
			case Fejioa::ShaderDataType::Bool:   return 1;

			default:
				break;
			}

			FJ_CORE_ASSERT(false, "Unkown ShaderDataType!");
			return 0;
		}
	};

	class BufferLayout
	{
	public:
		BufferLayout() = default;

		BufferLayout(const std::initializer_list<BufferElement>& elements)
			: m_Elements(elements)
		{
			CalculateOffsetsAndStride();
		}

		inline unsigned int GetStride() const { return m_Stride; }
		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

	private:
		void CalculateOffsetsAndStride()
		{
			unsigned int offset = 0;
			m_Stride = 0;

			for (auto& element : m_Elements)
			{
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
		}

	private:
		std::vector<BufferElement> m_Elements;
		unsigned int m_Stride;
	};

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual const BufferLayout& GetLayout() const = 0;

		static Ref<VertexBuffer> Create(float* vertices, unsigned int size);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual inline unsigned int GetCount() const = 0;

		static Ref<IndexBuffer> Create(unsigned int* indices, unsigned int count);
	};
}