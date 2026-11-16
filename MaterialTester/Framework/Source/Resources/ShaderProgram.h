#pragma once

namespace fw
{
	class ShaderProgram
	{
	public:
		ShaderProgram();
		ShaderProgram(const char* vertFilename, const char* fragFilename);
		virtual ~ShaderProgram();

		GLuint getProgram() { return m_program; }
		bool isValid() { return m_program != 0; }
		const char* getLastErrorMessage() { return m_lastErrorMessage; }

	protected:
		void cleanup();

		void compileShader(GLuint& shaderHandle, const char* shaderString);
		bool init(const char* vertFilename, const char* fragFilename);
		bool reload();

	protected:
		char* m_vertShaderString = nullptr;
		char* m_fragShaderString = nullptr;

		GLuint m_vertShader = 0;
		GLuint m_fragShader = 0;
		GLuint m_program = 0;

		char* m_lastErrorMessage = nullptr;
	};
} // namespace fw
