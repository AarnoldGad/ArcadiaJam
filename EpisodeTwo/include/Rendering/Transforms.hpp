#ifndef TRANSFORMS_HPP
#define TRANSFORMS_HPP

class Transforms
{
public:
   
   explicit Transforms(glm::vec2 pos = glm::vec2(0.f, 0.f), glm::vec2 origin = glm::vec2(0.f, 0.f), glm::vec2 scale = glm::vec2(1.f, 1.f), float rotation = 0.f);
   virtual ~Transforms() = default;
   
   virtual glm::mat4 const& getTransformsAsMatrix() const;
   float const* getTransformsAsArray() const;
   
   void setPosition(glm::vec2 pos);
   void setOrigin(glm::vec2 origin);
   void setScale(glm::vec2 scale);
   void setRotation(float angle);
   
   void move(glm::vec2 offset);
   void scale(glm::vec2 factor);
   void rotate(float angle);
   
   inline glm::vec2 getPosition() const { return m_pos;      }
   inline glm::vec2 getOrigin()   const { return m_origin;   }
   inline glm::vec2 getScale()    const { return m_scale;    }
   inline float     getRotation() const { return m_rotation; }
   
protected:
   
   glm::vec2 m_pos;
   glm::vec2 m_origin;
   glm::vec2 m_scale;
   float m_rotation;
   mutable glm::mat4 m_transforms;
   mutable bool m_needUpdateTransforms;
};

#endif // TRANSFORMS_HPP