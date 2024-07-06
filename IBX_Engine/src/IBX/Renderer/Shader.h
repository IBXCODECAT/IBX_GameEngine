#pragma once

#include "ibxpch.h"

#include <glm/glm.hpp>

namespace IBX_Engine
{
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual const std::string GetName() const = 0;

		virtual void SetMat4(const std::string& name, const glm::mat4& matrix) = 0;
		virtual void SetFloat3(const std::string& name, const glm::vec3& vector) = 0;
		virtual void SetFloat4(const std::string& name, const glm::vec4& vector) = 0;

		/// <summary>
		/// Create a shader from a file containing shader source code.
		/// </summary>
		/// <param name="filepath">The path to the file to read</param>
		/// <returns>A shader reference</returns>
		static Ref<Shader> Create(const std::string& filepath);

		/// <summary>
		/// Create a shader from source code. This is useful for debugging, testing, and for when you want to create a shader from a string.
		/// It is recommended to use the file version of this function for production.
		/// </summary>
		/// <param name="name">The name of the shader</param>
		/// <param name="vertexSrc">Raw vertex shader code</param>
		/// <param name="fragmentSrc">Raw fragment shader code</param>
		/// <returns>A shader reference</returns>
		static Ref<Shader> Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
	};

	class ShaderLibrary
	{
	public:
		void Add(const Ref<Shader>& shader);
		void Add(const std::string& name, const Ref<Shader>& shader);

		Ref<Shader> Load(const std::string& filepath);
		Ref<Shader> Load(const std::string& name, const std::string& filepath);

		Ref<Shader> Get(const std::string& name);

		inline bool Exists(const std::string& name) const { return m_Shaders.find(name) != m_Shaders.end(); }
	private:
		std::unordered_map<std::string, Ref<Shader>> m_Shaders;
	};
}