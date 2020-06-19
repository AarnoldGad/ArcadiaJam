#include <Rendering/Common/Renderer2D.hpp>

Renderer2D::Renderer2D(Shader const& shader, glm::mat4 view, glm::mat4 projection)
 : Renderer(shader, view, projection) {}

void Renderer2D::pushObject(Renderable& object, float weight)
{
   auto result = m_objects.try_emplace(weight, std::vector<Renderable*>());
   result.first->second.push_back(&object);
}

void Renderer2D::render()
{
   glEnable(GL_BLEND);
   glDisable(GL_CULL_FACE);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   
   getShader().bind();
   getShader().setMatrix4("View", getView());
   getShader().setMatrix4("Projection", getProjection());
   glActiveTexture(GL_TEXTURE0);
   
   for (auto it : m_objects)
      for (auto it2 : it.second)
         it2->render(*this);
   
   m_objects.clear();
   Shader::Bind(0);
}