template<typename Arr, typename V, typename... A>
Model<Arr, V>::Model(A&&... arrayArgs)
 : m_vertexArray(std::forward<A>(arrayArgs)...), m_bounds(0.f), m_needUpdate(true), m_needUpdateBounds(true) {}
 
template<typename Arr, typename V>
void Model<Arr, V>::setPointCount(size_t count)
{
   m_vertexArray.resize(pointCount);
   m_needUpdate = true;
}