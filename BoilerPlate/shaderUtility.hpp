#include <fstream>
#include <GL/glew.h>
#include <iostream>
#include <string>
#include <sstream>
#include <utility>
#include <vector>
#include <Windows.h>



#pragma once
#ifndef SHADER_H
#define SHADER_H

namespace engine{
	namespace utilities {
		struct shaderUtility
		{
			// FUNCTIONS
			shaderUtility();
			shaderUtility(std::vector <std::pair <std::string, GLenum>>);
			GLuint create_handle(std::pair <std::string, GLenum>);
			std::string  read_code_from_file(std::pair <std::string, GLenum>);
			void compile_shader(GLuint, std::string, std::string);
			void link_program();
			void clean_up();
			GLuint execute();
			int display_error_message(std::string, std::string, std::string, std::string);
			GLuint get_uniform_id(GLuint, const GLchar*);

			// MEMBERS
			std::vector <std::pair <std::string, GLenum>> shaderList;
			std::vector <GLuint> shaderHandlerList;

			GLint Result = GL_FALSE;
			int InfoLogLength;
			GLuint ProgramID;
		};
	}
}
#endif // !SHADER_H


