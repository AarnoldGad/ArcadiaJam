template<typename V>
ElementVertexArray<V>::ElementVertexArray(unsigned int mode, size_t vertexCount, unsigned int usage, unsigned int const* indices, size_t indexCount)
 : VertexArray(mode, vertexCount, usage), m_ebo(0), m_indexCount(indexCount)
{
   glGenBuffers(1, &m_ebo);
   
   glBindVertexArray(m_vao);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
   
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);
   
   glBindVertexArray(0);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

template<typename V>
void ElementVertexArray<V>::draw()
{
   glBindVertexArray(m_vao);
   glDrawElements(m_mode, static_cast<int>(m_indexCount), GL_UNSIGNED_INT, 0);
   glBindVertexArray(0);
}

template<typename V>
void ElementVertexArray<V>::update()
{
   glBindVertexArray(m_vao);
   glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
   
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
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}