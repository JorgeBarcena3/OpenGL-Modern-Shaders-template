#include "../header/Light.hpp"

void OpenGLRender3D::Light::setUpdateFunction(std::function<void(Light*, float time)> UpdateFunction)
{
    updateFunction = UpdateFunction;
}
