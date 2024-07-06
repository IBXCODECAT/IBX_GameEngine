#include "ibxpch.h"
#include "OpenGLShader.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace IBX_Engine
{
	static GLenum ShaderTypeFromString(const std::string& type)
	{
		if (type == "vertex")
			return GL_VERTEX_SHADER;
		if (type == "fragment" || type == "pixel")
			return GL_FRAGMENT_SHADER;

		IBX_CORE_ASSERT(false, "Unknown shader type!");
		return 0;
	}

	OpenGLShader::OpenGLShader(const std::string& filepath)
	{
		std::string shaderSrc = ReadFile(filepath);
		auto shaderSources = PreProcess(shaderSrc);

		Compile(shaderSources);

		// Extract the name of the shader from the filepath
		// Example: assets/shaders/Texture.glsl -> Texture
		size_t lastSlash = filepath.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		size_t lastDot = filepath.rfind('.');
		size_t count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
		m_Name = filepath.substr(lastSlash, count);
	}

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
		: m_Name(name)
	{
		std::unordered_map<GLenum, std::string> sources;
		sources[GL_VERTEX_SHADER] = vertexSrc;
		sources[GL_FRAGMENT_SHADER] = fragmentSrc;
		Compile(sources);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	std::string OpenGLShader::ReadFile(const std::string& filepath)
	{
		std::string result;
		std::ifstream in(filepath, std::ios::in | std::ios::binary);

		if (in)
		{
			// Seek to the end
			in.seekg(0, std::ios::end);

			// Resize the result string to the size of the file's contents
			result.resize(in.tellg());

			// Seek to the beginning
			in.seekg(0, std::ios::beg);

			// Read the file's contents into the result string starting from the beginning and ending at the end
			in.read(&result[0], result.size());

			// Close the file
			in.close();

			IBX_CORE_TRACE("Read shader '{0}'", filepath);
		}
		else
		{
			IBX_CORE_ERROR("Could not open file '{0}'", filepath);
		}

		return result;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& source)
	{
		std::unordered_map<GLenum, std::string> shaderSources;

		// Token to indicate the start of a shader type declaration
		const char* typeToken = "#type";

		// Calculate the length of the token
		size_t typeTokenLength = strlen(typeToken);

		// Locate the start of the shader type declaration line
		size_t pos = source.find(typeToken, 0);

		while (pos != std::string::npos)
		{
			size_t eol = source.find_first_of("\r\n", pos); // End of shader type declaration line
			IBX_CORE_ASSERT(eol != std::string::npos, "Syntax error");
			size_t begin = pos + typeTokenLength + 1; // Start of shader type name (after "#type " keyword)
			std::string type = source.substr(begin, eol - begin);
			IBX_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type specification");

			size_t nextLinePos = source.find_first_not_of("\r\n", eol); // Start of shader code after the shader type declaration line
			IBX_CORE_ASSERT(nextLinePos != std::string::npos, "Syntax error");
			pos = source.find(typeToken, nextLinePos); // Start of next shader type declaration line

			shaderSources[ShaderTypeFromString(type)] = (pos == std::string::npos) ? source.substr(nextLinePos) : source.substr(nextLinePos, pos - nextLinePos);
		}

		IBX_CORE_TRACE("Preprocessed {0} shaders.", shaderSources.size());
		return shaderSources;
	}

	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources)
	{
		// Create an empty program handle
		GLuint program = glCreateProgram();

		IBX_CORE_ASSERT(shaderSources.size() <= 2, "Shader compilation failed! IBX Engine only supports 2 shaders per program for now.");
		std::array<GLenum, 2> glShaderIDs;

		// Incrementing index for the shader ID array
		int glShaderIDIndex = 0;

		// For each shader source pair (file)
		for (auto& kv : shaderSources)
		{
			// Extract the shader type and source code
			GLenum shaderType = kv.first;
			const std::string& source = kv.second;

			// Create a shader of the specified type
			GLuint shader = glCreateShader(shaderType);

			// Send the shader source code to GL
			const GLchar* sourceCStr = source.c_str();
			glShaderSource(shader, 1, &sourceCStr, 0);

			// Compile the shader
			glCompileShader(shader);

			// Check for compile time errors (did it fail to compile?)
			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				// If it failed, then get the length of the info log
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				// The maxLength includes the NULL character
				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				// We don't need the shader anymore because it failed to compile
				// So why should we keep it around?
				glDeleteShader(shader);

				// Print the info log
				IBX_CORE_ERROR("{0}", infoLog.data());
				IBX_CORE_ASSERT(false, "Shader Compilation Failure");
				break;
			}
		
			// If the shader compiled successfully, attach it to the program
			glAttachShader(program, shader);

			// Store the shader ID in the array
			glShaderIDs[glShaderIDIndex++] = shader;
			
		}
		
		m_RendererID = program;

		IBX_CORE_TRACE("Compiling {0} shaders from source.", shaderSources.size());

		// Link our program
		glLinkProgram(program);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);
			
			// Delete shaders after an unsuccessful link - we don't need them anymore
			for (auto& id : glShaderIDs) glDeleteShader(id);

			IBX_CORE_ERROR("{0}", infoLog.data());
			IBX_CORE_ASSERT(false, "Shader Linking Failure");
			return;
		}

		IBX_CORE_TRACE("Linked shader program {0}.", m_RendererID);
		IBX_CORE_TRACE("Shader compilation successful.");

		//Always detach shaders after a successful link - don't leak shaders
		for (auto& id : glShaderIDs) glDeleteShader(id);

		IBX_CORE_TRACE("Cleaned up shader objects.");
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::SetInt(const std::string& name, int value)
	{
		UploadUniformInt(name, value);
	}

	void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& matrix)
	{
		UploadUniformMat4(name, matrix);
	}

	void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& vector)
	{
		UploadUniformFloat3(name, vector);
	}

	void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4& vector)
	{
		UploadUniformFloat4(name, vector);
	}


	void OpenGLShader::UploadUniformInt(const std::string& name, int value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::UploadUniformFloat(const std::string& name, float value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1f(location, value);
	}

	void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& vector)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2f(location, vector.x, vector.y);
	}

	void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& vector)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3f(location, vector.x, vector.y, vector.z);
	}

	void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& vector)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4f(location, vector.x, vector.y, vector.z, vector.w);
	}

	void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}
}