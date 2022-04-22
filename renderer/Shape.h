#pragma once
#include <vector>
#include <string>
#include "Vector3D.h"
#include "Ray.h"
#include "Shader.h"
#include "HitStructure.h"
#include "AABoundingBox.h"

namespace renderer {

class Shape
{
public:
  Shape();

  /**
   * @brief Determines whether the given ray intersects with this shape and modifies the given hit
   *        structure if it does
   * @param r The Ray object
   * @param tmin The minimum tvalue that is considered a hit
   * @param tmax The maximum tvalue that is considered a hit
   * @param hit A HitStructure that will be filled in the event of a hit
   * @return True if it intersects, otherwise false
  */
  virtual bool closestHit(const Ray &r, const float tmin, float &tmax, HitStructure &hit, int depth) = 0;

  /**
   * @brief Determines whether the given ray intersects with this shape
   * @param r The Ray object
   * @param tmin The minimum tvalue that is considered a hit
   * @param tmax The maximum tvalue that is considered a hit
   * @return True if it intersects, otherwise false
  */
  virtual bool hit(const Ray &r, float tmin, float tmax, int depth) = 0;

  /**
   * @brief Setter for the shader pointer
   * @param The shader pointer
  */
  virtual void setShader(Shader *s);

  /**
   * @brief Setter for the name
   * @param The name
  */
  virtual void setName(std::string s);

  /**
   * @brief Setter for the bounding box
   * @param b The bounding box
  */
  virtual void setBoundingBox(AABoundingBox &b);

  /**
   * @brief Sets the minimum and maximum reflection depths at which the shape is visible
   * @param min The minimum
   * @param max The maximum
  */
  virtual void setVisibleDepthBounds(int min, int max);

  /**
   * @brief Sets the minimum and maximum reflection depths at which the shape casts a shadow
   * @param min The minimum
   * @param max The maximum
  */
  virtual void setShadowDepthBounds(int min, int max);

  /**
   * @brief Getter for the shader pointer
   * @return The shader pointer
  */
  virtual Shader *getShader() const;

  /**
   * @brief Getter for the name
   * @return name
  */
  virtual const std::string &getName() const;

  /**
   * @brief Getter for the bounding box
   * @return The bounding box
  */
  virtual AABoundingBox &getBoundingBox();

  /**
   * @brief Getter for the center
   * @return The center
  */
  virtual Vector3D getCenter() const;

protected:
  Shader *shaderPtr;
  std::string name;
  AABoundingBox bound;
  Vector3D center;
};
}// namespace renderer