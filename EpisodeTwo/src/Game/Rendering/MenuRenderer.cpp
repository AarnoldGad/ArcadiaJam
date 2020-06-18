#include <Game/Rendering/MenuRenderer.hpp>

MenuRenderer::MenuRenderer(Window const& window)
 : m_window(window)
{
   m_background = new Sprite(ResourcesManager::GetTexture("assets/ui/menu_background.png"));
   m_background->setSize(window.getSize());
   
   m_title = new Sprite(ResourcesManager::GetTexture("assets/ui/title.png"));
   m_title->setPosition({ window.getSize().x / 2, 3 * window.getSize().y / 4 });
   m_title->setOrigin({ m_title->getLocalBounds().z / 2.f, m_title->getLocalBounds().w / 2.f });
   
   m_button = new Sprite(ResourcesManager::GetTexture("assets/ui/button.png"));
   
   m_buttonText.setFont(ResourcesManager::GetFont("assets/fonts/pixel.ttf"));
   
   m_projection = glm::ortho(0.f, 800.f, 0.f, 600.f);
}

void MenuRenderer::render()
{
   glEnable(GL_BLEND);
   glDisable(GL_CULL_FACE);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   
   // Sprites
   Shader& spriteShader = ResourcesManager::GetShader("sprite");
   spriteShader.bind();
   spriteShader.setMatrix4("Projection", m_projection);
   spriteShader.setMatrix4("View", glm::mat4(1.f));
   
   m_background->render(spriteShader);
   m_title->render(spriteShader);
   
   // Texts
   Shader& textShader = ResourcesManager::GetShader("text");
   
   textShader.bind();
   textShader.setMatrix4("Projection", m_projection);
   glActiveTexture(GL_TEXTURE0);
   
   
   m_buttonText.setText("Credits");
   m_buttonText.setOrigin({ m_buttonText.getLocalBounds().z / 2.f, m_buttonText.getLocalBounds().w / 2.f});
   m_buttonText.setPosition({ m_window.getSize().x / 2.f, m_window.getSize().y / 6.f * 2.f });
   m_buttonText.render(textShader);
   
   Shader::Bind(0);
}

MenuRenderer::~MenuRenderer()
{
   delete m_background;
   delete m_title;
   delete m_button;
}