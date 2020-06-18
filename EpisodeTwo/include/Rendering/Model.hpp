#ifndef MODEL_HPP
#define MODEL_HPP

#include <Rendering/Renderable.hpp>
#include <Rendering/Transforms.hpp>
#include <Rendering/VertexArray.hpp>

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

#include <Rendering/Model.inl>

#endif // MODEL_HPP