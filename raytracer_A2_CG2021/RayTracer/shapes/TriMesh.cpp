/*
 * TriMesh.cpp
 *
 *
 */
#include "TriMesh.h"


namespace rt{

    TriMesh::TriMesh(Vec3f position, float scale, std::string path, Material *material)
    {
        this->shapeType = "mesh";
        this->position = position;
        this->scale = scale;
        this->material = material;
        this->createMesh(path);
    }

    /**
     * The function for creating the triangle mesh
     * 
     * @param path the path to the Ply model file
    */
    void TriMesh::createMesh(std::string path)
    {   
        try{
            happly::PLYData plyIn(path);

            std::vector<std::array<double,3>> vertices = plyIn.getVertexPositions();
            std::vector<std::vector<size_t>> faces = plyIn.getFaceIndices<size_t>();
            // get the normal x,y,z
            bool hasNormal = plyIn.getElement("vertex").hasProperty("nx") 
                && plyIn.getElement("vertex").hasProperty("ny") 
                && plyIn.getElement("vertex").hasProperty("nz");
            std::vector<double> nx, ny, nz;
            if(hasNormal){
                nx = plyIn.getElement("vertex").getProperty<double>("nx");
                ny = plyIn.getElement("vertex").getProperty<double>("ny");
                nz = plyIn.getElement("vertex").getProperty<double>("nz");
            }

            // get the texture
            bool hasTexture = plyIn.getElement("vertex").hasProperty("s") 
                && plyIn.getElement("vertex").hasProperty("t");
            std::vector<double> s, t;
            if(hasTexture){
                s = plyIn.getElement("vertex").getProperty<double>("s");
                t = plyIn.getElement("vertex").getProperty<double>("t");
            }
            
            for(const auto face : faces){
                // Get the vertices
                Vec3f v0 = Vec3f((float)vertices[face[0]][0], (float)vertices[face[0]][1], (float)vertices[face[0]][2]) * this->scale;
                Vec3f v1 = Vec3f((float)vertices[face[1]][0], (float)vertices[face[1]][1], (float)vertices[face[1]][2]) * this->scale;
                Vec3f v2 = Vec3f((float)vertices[face[2]][0], (float)vertices[face[2]][1], (float)vertices[face[2]][2]) * this->scale;
                
                v0 = v0 + this->position;
                v1 = v1 + this->position;
                v2 = v2 + this->position;

                // Get the normal
                Vec3f n0, n1, n2;
                if(hasNormal){
                    n0 = Vec3f((float)nx[face[0]],(float)ny[face[0]],(float)nz[face[0]]).normalize();
                    n1 = Vec3f((float)nx[face[1]],(float)ny[face[1]],(float)nz[face[1]]).normalize();
                    n2 = Vec3f((float)nx[face[2]],(float)ny[face[2]],(float)nz[face[2]]).normalize();
                }

                // Get the uv
                Vec2f uv0, uv1, uv2;
                if(hasTexture){
                    uv0 = Vec2f((float) s[face[0]], (float) t[face[0]]);
                    uv1 = Vec2f((float) s[face[1]], (float) t[face[1]]);
                    uv2 = Vec2f((float) s[face[2]], (float) t[face[2]]);
                }


                // Add the forth triangle if the faces has four vertices
                if(face.size() == 4){
                    Vec3f v3 = Vec3f((float)vertices[face[3]][0], (float)vertices[face[3]][1], (float)vertices[face[3]][2]) * this->scale;
                    v3 = v3 + this->position;
                    Vec3f n3;
                    if(hasNormal){
                        n3 = Vec3f((float)nx[face[3]],(float)ny[face[3]],(float)nz[face[3]]).normalize();
                    }
                    Vec2f uv3;
                    if(hasTexture){
                        uv3 = Vec2f((float) s[face[3]], (float) t[face[3]]);
                    }

                    // Create the triangle and add to triangles
                    if(hasNormal && hasTexture){
                        this->triangles.push_back(new Triangle(v0, v2, v3, n0, n2, n3, uv0, uv2, uv3, material));
                    }else if(hasNormal){
                        this->triangles.push_back(new Triangle(v0, v2, v3, n0, n2, n3, material));
                    }else if(hasTexture){
                        this->triangles.push_back(new Triangle(v0, v2, v3, uv0, uv2, uv3, material));
                    }else{
                        this->triangles.push_back(new Triangle(v0, v2, v3, material));
                    }
                }

                // Create the triangle and add to triangles
                if(hasNormal && hasTexture){
                    this->triangles.push_back(new Triangle(v0, v1, v2, n0, n1, n2, uv0, uv1, uv2, material));
                }else if(hasNormal){
                    this->triangles.push_back(new Triangle(v0, v1, v2, n0, n1, n2, material));
                }else if(hasTexture){
                    this->triangles.push_back(new Triangle(v0, v1, v2, uv0, uv1, uv2, material));
                }else{
                    this->triangles.push_back(new Triangle(v0, v1, v2, material));
                }
                
            }
            

        }catch(...){
            std::cerr << "Ply file loading failed. \n" << std::endl;
        }
        std::printf("ply loading succeed %d triangles.\n",(int)this->triangles.size());
        // Create the bvh, and the bounding of TriMesh is the bounding of its bvh root
        this->bvh = new BVH(this->triangles);
        this->max = this->bvh->root->box.max;
        this->min = this->bvh->root->box.min;
        this->center = (this->max + this->min) / 2.f;
    }

    /**
	 * Computes whether a ray hit the specific instance of a triangle mesh shape and returns the hit data
	 *
	 * @param ray cast ray to check for intersection with shape
	 *
	 * @return hit struct containing intersection information
	 *
	 */
    Hit TriMesh::intersect(Ray ray)
    {
        // The below is the standard intersection checking method for TriMesh
        // Hit hit;
	    // hit.hasHit = false;
	    // double rayDistance = INFINITY;
	    // for (Shape *shape : this->triangles){
		//     Hit h = shape -> intersect(ray);
		//     if(h.hasHit){
		// 	    float distance = (h.point - ray.origin).length();
		// 	    if(distance <= 1e-3){
		// 		    continue;
		// 	    }
		// 	    if(distance < rayDistance){
		// 		    rayDistance = distance;
		// 		    hit.point = h.point;
		// 		    hit.material = h.material;
		// 		    hit.normal = h.normal;
		// 		    hit.hasHit = true;
		// 		    hit.u = h.u;
		// 		    hit.v = h.v;
		//         }
		//     }
	    // }
	    // return hit;

        // The below is the intersection using BVH for TriMesh
        Hit hit = this->bvh->intersect(ray);
        return hit;
    }

} // namespace rt
