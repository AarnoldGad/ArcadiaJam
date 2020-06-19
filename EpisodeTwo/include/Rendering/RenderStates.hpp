#ifndef RENDERSTATES_HPP
#define RENDERSTATES_HPP

#include <Rendering/OpenGL/Shader.hpp>

class RenderStates
{
public:
   
   RenderStates(Shader const& shader, glm::mat4 view, glm::mat4 projection);
   virtual ~RenderStates() = default;
   
   void setShader(Shader const& shader);
   void setView(glm::mat4 view);
   void setProjection(glm::mat4 projection);
   
   inline Shader const& getShader() const { return *m_shader; }
   inline glm::mat4 getView() const { return m_view; }
   inline glm::mat4 getProjection() const { return m_projection; }
   
protected:
   
   Shader const* m_shader;
   glm::mat4 m_view;
   glm::mat4 m_projection;
};

#endif // RENDERSTATES_HPP