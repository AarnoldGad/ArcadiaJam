#include <Game/Rendering/TestRenderer.hpp>

TestRenderer::TestRenderer()
{
   ResourcesManager::LoadFontFile("assets/fonts/pixel.ttf", 48);
   m_text.setText("foobar");
   m_text.setFont(ResourcesManager::GetFont("assets/fonts/pixel.ttf"));
   m_text.setColor({ 1.f, 1.f, 1.f, 1.f });
   m_text.setPosition({150.f, 150.f});
   
   m_projection = glm::ortho(0.f, 800.f, 0.f, 600.f);
}

void TestRenderer::render()
{
   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   Shader& shader = ResourcesManager::GetShader("text");
   shader.bind();
   shader.setMatrix4("Model", m_text.getTransformsAsMatrix());
   shader.setMatrix4("Projection", m_projection);
   glActiveTexture(GL_TEXTURE0);
   
   m_text.render();
   
   Shader::Bind(0);
   glDisable(GL_BLEND);
}