#ifndef TESTMODEL_HPP
#define TESTMODEL_HPP

#include <Rendering/Model.hpp>
#include <Rendering/Vertex2D.hpp>

class TestModel : public Model<Vertex2D>
{
public:
   
   TestModel() : Model(GL_TRIANGLE_STRIP, 4, GL_STATIC_DRAW)
   
   void render() override
   {
      if (m_needUpdate)
      {
         update();
         m_vertexArray.update();
      }
      
      m_vertexArray.draw();
   }
   
private:
   
   void update() override
   {
      m_vertexArray
      
      m_needUpdate = false;
   }
};

#endif // TESTMODEL_HPP