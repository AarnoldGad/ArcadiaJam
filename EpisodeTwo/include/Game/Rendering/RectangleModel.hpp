#ifndef RECTANGLEMODEL_HPP
#define RECTANGLEMODEL_HPP

#include <Rendering/Common/Model2D.hpp>

class RectangleModel : public Model2D
{
public:
   
   RectangleModel(glm::vec2 size, glm::vec4 color = glm::vec4(1.f));
   virtual ~RectangleModel() = default;
   
   void setSize(glm::vec2 size);
   
   inline glm::vec2 getSize() const { return m_size; }
   
private:

   void updatePositions() override;
   
   glm::vec2 m_size;
};

#endif // RECTANGLEMODEL_HPP