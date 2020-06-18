template<typename V>
VertexArray<V>::VertexArray(GLenum mode, size_t vertexCount, GLenum usage)
 : m_vao(0), m_vbo(0), m_mode(mode), m_usage(usage), m_vertices(vertexCount), m_sizeChanged(true)
{
   if (!std::is_base_of<Vertex, V>::value)
   {
      NeptuneProject::GetLogger().logError("Not deriving from Vertex");
      exit(-1);
   }
   
   glGenVertexArrays(1, &m_vao);
   glGenBuffers(1, &m_vbo);
}

template<typename V>
void VertexArray<V>::draw()
{
   glBindVertexArray(m_vao);
   glDrawArrays(m_mode, 0, static_cast<GLsizei>(getVertexCount()));
   glBindVertexArray(0);
}

template<typename V>
void VertexArray<V>::update()
{
   glBindVertexArray(m_vao);
   glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
   
   if (m_sizeChanged)
      glBufferData(GL_ARRAY_BUFFER, m_vertices[0].getByteSize() * getVertexCount(), 0, m_usage);
   m_sizeChanged = false;
   
   size_t dataOffset = 0;
   AttribInfo attrib;
   for (size_t l = 0; l < m_vertices[0].getLocationCount(); ++l)
   {
      attrib = m_vertices[0].getAttribInfo(l);
      // Emplace attributes data into the buffer
      for (size_t v = 0; v < getVertexCount(); ++v)
         glBufferSubData(GL_ARRAY_BUFFER, v * m_vertices[v].getByteSize() + dataOffset, attrib.byteSize, m_vertices[v].getAttrib(l));
      
      // Enable and set attribute pointer
      glEnableVertexAttribArray((GLuint) l);
      glVertexAttribPointer((GLuint) l, attrib.size, attrib.dataType, attrib.normalized, m_vertices[0].getByteSize(), (void*) dataOffset);
                                        
      // Increase offset of consecutive attributes
      dataOffset += m_vertices[0].getAttribInfo(l).byteSize;
   }
   
   glBindVertexArray(0);
   glBindBuffer(GL_ARRAY_BUFFER, 0);
}

template<typename V>
V& VertexArray<V>::operator[](size_t index)
{
   return at(index);
}

template<typename V>
V const& VertexArray<V>::operator[](size_t index) const
{
   return at(index);
}

template<typename V>
V& VertexArray<V>::at(size_t index)
{
   if (index >= getVertexCount())
   {
      NeptuneProject::GetLogger().logDebug("Vertex Array Out of Bound ", index);
      exit(-1); // TODO Error handling
   }
   
   return m_vertices[index];
}

template<typename V>
void VertexArray<V>::resize(size_t size)
{
   if (size != getVertexCount())
   {
      m_vertices.resize(size);
      m_sizeChanged = true;
   }
}

template<typename V>
void VertexArray<V>::append(V const& vertex)
{
   m_vertices.push_back(vertex);
   m_sizeChanged = true;
}

template<typename V>
void VertexArray<V>::reset()
{
   m_vertices = std::vector<V>(getVertexCount());
}

template<typename V>
VertexArray<V>::~VertexArray()
{
   glDeleteVertexArrays(1, &m_vao);
   glDeleteBuffers(1, &m_vbo);
}