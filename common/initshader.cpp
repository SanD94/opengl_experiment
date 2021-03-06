#include "sand.h"
#include <fstream>


namespace Sand {

	static GLchar* ReadShaderSource(const std::string& shaderFile) {

		std::ifstream fin(shaderFile);
		if (!fin.is_open()) { return NULL; }
		fin.seekg(0, fin.end);
		long length = fin.tellg();
		fin.seekg(0, fin.beg);
		
		GLchar* buf = new GLchar[length+1];
		fin.read(buf, length);
		buf[length] = 0;
		fin.close();

		return buf;
	}

	// Create a GLSL program object from vertex and fragment shader files
	GLuint InitShader(const std::string& vShaderFile, const std::string& fShaderFile) {
		struct Shader {
			const std::string filename;
			GLenum type;
			GLchar *source;
		} shaders[2] = {
			{vShaderFile, GL_VERTEX_SHADER, NULL},
			{fShaderFile, GL_FRAGMENT_SHADER, NULL}};

		GLuint program = glCreateProgram();

		for (int i = 0; i < 2; ++i) {
			Shader &s = shaders[i];
			s.source = ReadShaderSource(s.filename);
			if (shaders[i].source == NULL) {
				std::cerr << "Failed to read " << s.filename << std::endl;
				exit(EXIT_FAILURE);
			}

			GLuint shader = glCreateShader(s.type);
			glShaderSource(shader, 1, (const GLchar **)&s.source, NULL);
			glCompileShader(shader);

			GLint compiled;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
			if (!compiled) {
				std::cerr << s.filename << " failed to compile:" << std::endl;
				GLint logSize;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize);
				char *logMsg = new char[logSize];
				glGetShaderInfoLog(shader, logSize, NULL, logMsg);
				glGetShaderInfoLog(shader, logSize, NULL, logMsg);
				std::cerr << logMsg << std::endl;
				delete[] logMsg;

				exit(EXIT_FAILURE);
			}

			delete[] s.source;

			glAttachShader(program, shader);
		}

		/* link  and error check */
		glLinkProgram(program);

		GLint linked;
		glGetProgramiv(program, GL_LINK_STATUS, &linked);
		if (!linked) {
			std::cerr << "Shader program failed to link" << std::endl;
			GLint logSize;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logSize);
			char *logMsg = new char[logSize];
			glGetProgramInfoLog(program, logSize, NULL, logMsg);
			std::cerr << logMsg << std::endl;
			delete[] logMsg;

			exit(EXIT_FAILURE);
		}

		/* use program object */
		glUseProgram(program);

		return program;
	}

}  // namespace Sand
