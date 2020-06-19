#ifndef MODEL_HPP
#define MODEL_HPP

#include <Rendering/Abstract/Renderable.hpp>
#include <Rendering/Common/Transforms.hpp>
#include <Rendering/OpenGL/VertexArray.hpp>

template<typename V>
class Model : public Transforms, public Renderable
{
public:

   Model(unsigned int mode, size_t vertexCount, unsigned usage);
   virtual ~Model() = default;
   
   void setPointCount(size_t count);
   inline size_t getPointCount() const { return m_vertexArray.getVertexCount(); }
   
protected:

   virtual void update() = 0;
   
   VertexArray<V> m_vertexArray;
   bool m_needUpdate;
};

#include <Rendering/Abstract/Model.inl>

#endif // MODEL_HPP