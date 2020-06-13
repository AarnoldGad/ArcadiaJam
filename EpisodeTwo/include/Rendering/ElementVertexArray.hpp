#ifndef ELEMENTVERTEXARRAY_HPP
#define ELEMENTVERTEXARRAY_HPP

#include <Rendering/VertexArray.hpp>

template<typename V>
class ElementVertexArray : public VertexArray<V>
{
public:
   
   ElementVertexArray(unsigned int mode, size_t vertexCount, unsigned int usage, unsigned int const* indices, size_t indexCount);
   virtual ~ElementVertexArray();
   
   virtual void draw();
   virtual void update();
   
   void setElementArrayBuffer(unsigned int const* indices, size_t count);
   
protected:
   
   unsigned int m_ebo;
   size_t m_indexCount;
};

#endif // ELEMENTVERTEXARRAY_HPP