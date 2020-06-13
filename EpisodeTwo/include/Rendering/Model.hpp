#ifndef MODEL_HPP
#define MODEL_HPP

#include <Rendering/Transforms.hpp>

template<typename Arr, typename V>
class Model : public Transforms
{
public:

   template<typename... A>
   Model(A&&... arrayArgs);
   virtual ~Model();
   
   virtual void render() = 0;
   
   void setPointCount(size_t count);
   inline size_t getPointCount() const { return m_vertexArray.getVertexCount(); }
   
protected:

   virtual void update() = 0;
   
   Arr<V> m_vertexArray;
   
   bool m_needUpdate;
};

#endif // MODEL_HPP