/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Jorge on February of 2020                                       *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  j.barcenalumbreras@gmail.com                                               *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "BaseModel3D.hpp"
#include <functional>
#include <vector>
#include "Mesh.hpp"

#ifndef MODEL3D_HEADER
#define MODEL3D_HEADER


namespace OpenGLRender3D {


    struct Material
    {

        glm::vec3 Ka;
        glm::vec3 Kd;
        glm::vec3 Ks;

        std::string diffuse_texname;
        int diffuse_tex_id;

        std::string specular_texname;
        int specular_tex_id;

        bool hasTexture()
        {
            return (!specular_texname.empty() || !diffuse_texname.empty());
        }

    };

    /*
    * Clase que va a manejar un modelo 3D
    */
    class Model3D : public BaseModel3D
    {

    private:

        /*
        * La clase Mesh puede acceder a las variables privadas del modelo3D
        */
        friend class Mesh;

        std::vector<Mesh*> meshes;

        std::vector< Material > materials;



    public:

        /*
        * Crea un modelo 3D
        */
        Model3D(Scene& scene, OpenGLRender3D::OPACITYMODEL op, const char* path);

        /*
        * Destructor del modelo 3D
        */
        ~Model3D();     

        // Heredado vía BaseModel3D
        virtual void render() override;



    private:

        /*
        * Carga un obj
        */
        void loadObj(const char* path);

    };

}

#endif