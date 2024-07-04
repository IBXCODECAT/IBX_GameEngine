#pragma once

namespace IBX_Engine
{
	/// <summary>
	/// Abstract representation of a texture.
	/// </summary>
	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		
		virtual void Bind(uint32_t slot = 0) const = 0;
	};
	
	/// <summary>
	/// Abstract representation of a 2D texture.
	/// Requires an implementation from a specific graphics API.
	/// </summary>
	class Texture2D : public Texture
	{
	public:
		static Ref<Texture2D> Create(const std::string& path);
	};
}