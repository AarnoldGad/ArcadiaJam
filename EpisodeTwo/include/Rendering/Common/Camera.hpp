#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/gtc/type_ptr.hpp>
#include <Rendering/Common/Transforms.hpp>

class Camera : public Transforms
{
public:
   
   explicit Camera(glm::vec2 pos, glm::vec4 viewport = glm::vec4(0.f, 0.f, 1.f, 1.f), float rotation = 0.f);
   
   glm::mat4 const& getTransformsAsMatrix() const override;
   
   void setViewport(glm::vec4 viewport);
   
   inline glm::vec4 getViewport() const { return m_viewport; }
   
private:
   
   glm::vec4 m_viewport;
};

#endif // CAMERA_HPP