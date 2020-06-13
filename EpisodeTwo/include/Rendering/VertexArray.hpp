#ifndef VERTEXARRAY_HPP
#define VERTEXARRAY_HPP

#include <NeptuneProject.hpp>
#include <Rendering/Vertex.hpp>

template<typename V>
class VertexArray
{
public:
   
   VertexArray(GLenum mode, size_t vertexCount, GLenum usage);
   virtual ~VertexArray();
   
   virtual void draw();
   virtual void update();
   
   V& operator[](size_t index);
   V const& operator[](size_t index) const;
   
   inline size_t getVertexCount() const { return m_vertices.size(); }
   V& at(size_t index);
   void resize(size_t size);
   void append(V const& vertex);
   void reset();
   
private:
   
   unsigned int m_vao;
   unsigned int m_vbo;
   GLenum m_mode;
   GLenum m_usage;
   std::vector<V> m_vertices;
   bool m_sizeChanged;
};

#include <Rendering/VertexArray.inl>

#endif // VERTEXARRAY_HPP