#include "..\header\exampleShapes\Mesh.hpp"
#include "..\header\exampleShapes\Model3D.hpp"
#include "..\header\Camera.hpp"
#include "..\header\Texture2D.hpp"


OpenGLRender3D::Mesh::Mesh(std::vector<GLuint> _indices, Model3D& _model, int _material_index)
{
    indices = _indices;
    model   = &_model;
    material_index = _material_index;
}

void OpenGLRender3D::Mesh::render()
{

    if (model->textures_factory[model->materials[material_index].diffuse_tex_id]->is_ok())
    {
        model->textures_factory[model->materials[material_index].diffuse_tex_id]->bind();

    }

    glm::mat4 camera_matrix = model->scene->getMainCamera()->getProjectionMatrix() * model->scene->getMainCamera()->getTransformation();
    glm::mat4 modelMatrix = model->transform.getModelViewMatrix();

    glUniformMatrix4fv(model->scene->getMainCamera()->getProjectionMatrixId(), 1, GL_FALSE, glm::value_ptr(camera_matrix));
    glUniformMatrix4fv(model->modelMatrixTransformationId, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    // Se selecciona el VAO que contiene los datos del objeto y se dibujan sus elementos:
    glBindVertexArray(model->vao_id);
    glDrawElements(GL_TRIANGLES, indices.size() * sizeof(GLuint), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
