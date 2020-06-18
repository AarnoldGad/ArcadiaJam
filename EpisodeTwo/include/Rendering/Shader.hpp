#ifndef SHADER_HPP
#define SHADER_HPP

#include <glad/glad.h>

class Shader
{
public:
   
   Shader();
   ~Shader();
   
   bool loadFromFile(std::string const& vertex, std::string const& fragment, std::string const& geometry = std::string());
   bool loadFromSource(char const* vertex, char const* fragment, char const* geometry = nullptr);
   
   int getUniformLocation(std::string const& name);
   
   void setBoolean(std::string const& name, bool value);
   void setInteger(std::string const& name, int value);
   void setFloat(std::string const& name, float value);
   void setVector2(std::string const& name, glm::vec2 value);
   void setVector3(std::string const& name, glm::vec3 value);
   void setVector4(std::string const& name, glm::vec4 value);
   void setMatrix4(std::string const& name, glm::mat4 value, bool transpose = false);
   
   inline unsigned int getHandle() const { return m_program; }
   
   void bind() const;
   static void Bind(unsigned int program);
   
private:
   
   bool checkCompileStatus(unsigned int shader) const;
   bool checkLinkStatus(unsigned int program) const;
   
   unsigned int addShader(unsigned int type, char const* source);
   
   unsigned int m_program;
   std::map<std::string, int> m_uniforms;
};

#endif // SHADER_HPP