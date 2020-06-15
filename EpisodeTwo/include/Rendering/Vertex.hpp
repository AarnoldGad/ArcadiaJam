#ifndef VERTEX_HPP
#define VERTEX_HPP

typedef struct 
{
   GLsizei size = 0;
   GLsizei byteSize = 0;
   GLenum dataType;
   GLboolean normalized = GL_FALSE;
} AttribInfo;

class Vertex
{
public:
   
   Vertex() = default;
   virtual ~Vertex() = default;
   
   virtual size_t getLocationCount() const = 0;
   virtual size_t getByteSize() const = 0;
   virtual AttribInfo getAttribInfo(size_t location) const = 0;
   virtual void const* getAttrib(size_t location) const = 0;
};

#endif // VERTEX_HPP