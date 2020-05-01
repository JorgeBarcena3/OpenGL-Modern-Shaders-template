#include "..\header\PointLight.hpp"

void OpenGLRender3D::PointLight::setUniformVariables(ShaderProgramHelper::Shader_Program& shader)
{
    if (eneabledId != -1)
    {
        shader.set_uniform_value(positionId, position);
        shader.set_uniform_value(eneabledId, eneabled);
        shader.set_uniform_value(ambientColorId, ambientColor);
        shader.set_uniform_value(diffuseColorId, diffuseColor);
        shader.set_uniform_value(specularColorId, specularColor);
    }
    else
        throw std::exception("La luz introducida no es soportada por el shader");
}

void OpenGLRender3D::PointLight::getUniformId(ShaderProgramHelper::Shader_Program& shader, std::string lightId)
{
    eneabledId = shader.get_uniform_id(std::string("pointLights[" + lightId + "].eneabled").c_str());
    positionId = shader.get_uniform_id(std::string("pointLights[" +      lightId + "].position").c_str());
    ambientColorId = shader.get_uniform_id(std::string("pointLights[" +  lightId + "].ambient").c_str());
    diffuseColorId = shader.get_uniform_id(std::string("pointLights[" +  lightId + "].diffuse").c_str());
    specularColorId = shader.get_uniform_id(std::string("pointLights[" + lightId + "].specular").c_str());
}
