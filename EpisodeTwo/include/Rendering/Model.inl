template<typename V>
Model<V>::Model(unsigned int mode, size_t vertexCount, unsigned int usage)
 : m_vertexArray(mode, vertexCount, usage), m_needUpdate(true) {}
 
template<typename V>
void Model<V>::setPointCount(size_t count)
{
   m_vertexArray.resize(count);
   m_needUpdate = true;
}