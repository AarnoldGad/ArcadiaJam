#include <Rendering/OpenGL/Shader.hpp>
#include <Application.hpp>
#include <Util/FileHelper.hpp>
#include <Core/Logger.hpp>

Shader::Shader()
 : m_program(0) {}

bool Shader::loadFromFile(std::string const& vertex, std::string const& fragment, std::string const& geometry)
{
   std::string vertexCode = FileHelper::ToString(vertex);
   std::string fragmentCode = FileHelper::ToString(fragment);
   std::string geometryCode = FileHelper::ToString(geometry);
   return loadFromSource(vertexCode.c_str(), fragmentCode.c_str(), !geometry.empty() ? geometryCode.c_str() : nullptr);
}

bool Shader::loadFromSource(char const* vertex, char const* fragment, char const* geometry)
{
   if (m_program)
   {
      glDeleteProgram(m_program);
      m_program = 0;
   }
   
   m_program = glCreateProgram();
   
   unsigned int vertexID = addShader(GL_VERTEX_SHADER, vertex);
   unsigned int fragmentID = addShader(GL_FRAGMENT_SHADER, fragment);
   unsigned int geometryID = addShader(GL_GEOMETRY_SHADER, geometry);
   
   glLinkProgram(m_program);
   
   glDeleteShader(vertexID);
   glDeleteShader(fragmentID);
   glDeleteShader(geometryID);
   
   return checkLinkStatus(m_program);
}

unsigned int Shader::addShader(unsigned int type, char const* source)
{
   unsigned int shader = glCreateShader(type);
   
   if (shader && source)
   {
      glShaderSource(shader, 1, &source, nullptr);
      glCompileShader(shader);
      
      if (checkCompileStatus(shader))
         glAttachShader(m_program, shader);
      
      return shader;
   }
   
   return 0;
}

bool Shader::checkCompileStatus(unsigned int shader) const
{
   int success;
   char log[512];
   
   int type;
   glGetShaderiv(shader, GL_SHADER_TYPE, &type);
   
   glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
   if (!success)
   {
      glGetShaderInfoLog(shader, 512, nullptr, log);
      Application::GetLogger().logError(type == GL_VERTEX_SHADER ? "vertex" : (type == GL_FRAGMENT_SHADER ? "fragment" : "geometry"),
                                        " shader compilation error : ", log);
      return false;
   }
   return true;
}

bool Shader::checkLinkStatus(unsigned int program) const
{
   int success;
   char log[512];
   
   glGetProgramiv(program, GL_LINK_STATUS, &success);
   if (!success)
   {
      glGetProgramInfoLog(program, 512, nullptr, log);
      Application::GetLogger().logError("Shader linking error : ", log);
      return false;
   }
   
   Application::GetLogger().logDebug("Program ", program, " link successful");
   return true;
}

int Shader::getUniformLocation(std::string const& name) const
{
   int location;
   
   try
   {
      location = m_uniforms.at(name);
   }
   catch (std::out_of_range const& e)
   {
      location = glGetUniformLocation(m_program, name.c_str());
      
      if (location == -1 || location == GL_INVALID_VALUE)
         Application::GetLogger().logError("Unable to retrieve uniform location for value ", name, " in shader ", m_program);
      else
         m_uniforms.emplace(name, location);
   }
   
   return location;
}

void Shader::setBoolean(std::string const& name, bool value) const
{
   return setInteger(name, static_cast<int>(value));
}

void Shader::setInteger(std::string const& name, int value) const
{
   glUniform1i(getUniformLocation(name), value);
}

void Shader::setFloat(std::string const& name, float value) const
{
   glUniform1f(getUniformLocation(name), value);
}

void Shader::setVector2(std::string const& name, glm::vec2 value) const
{
   glUniform2f(getUniformLocation(name), value.x, value.y);
}

void Shader::setVector3(std::string const& name, glm::vec3 value) const
{
   glUniform3f(getUniformLocation(name), value.x, value.y, value.z);
}

void Shader::setVector4(std::string const& name, glm::vec4 value) const
{
   glUniform4f(getUniformLocation(name), value.x, value.y, value.z, value.w);
}

void Shader::setMatrix4(std::string const& name, glm::mat4 value, bool transpose) const
{
   glUniformMatrix4fv(getUniformLocation(name), 1, transpose ? GL_TRUE : GL_FALSE, glm::value_ptr(value));
}

void Shader::bind() const
{
   Shader::Bind(m_program);
}

void Shader::Bind(unsigned int program)
{
   glUseProgram(program);
}

Shader::~Shader()
{
   if (m_program)
      glDeleteProgram(m_program);
}