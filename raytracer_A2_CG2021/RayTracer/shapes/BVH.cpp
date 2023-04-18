/*
 * BVH.cpp
 *
 *
 */
#include "BVH.h"
#include "Plane.h"
#include "Triangle.h"
#include "Sphere.h"
#include <fstream>

namespace rt{

    BVHNode* BVH::BuildBVHTree(std::vector<Shape *> shapes)
    {
        BVHNode* node = new BVHNode;
        node->shape = nullptr;
        node->hasShape = false;
        node->isEmpty = false;
        node->left = nullptr;
        node->right = nullptr;
        if(shapes.size() == 0){
            node->isEmpty = true;
            return node;
        }
        if(shapes.size() == 1){
            Shape* shape = shapes[0];
            node->shape = shape;
            node->box.min = shape->min;
            node->box.max = shape->max;
            node->hasShape = true;
            return node;
        }

        // Split the shapes into two parts
        std::vector<Shape *> left;
        std::vector<Shape *> right;
        // Skip the complex spliting if only two shapes
        if(shapes.size() == 2){
            left.push_back(shapes.at(0));
            right.push_back(shapes.at(1));
        }else{ 
            // Find the left most shape and right most shape;
            Shape* left_most = shapes.at(0);
            Shape* right_most = shapes.at(0);

            // Try splitting by x
            for(auto it = shapes.begin(); it != shapes.end(); ++it){
                Shape* currShape = *it;
                if(currShape->getCenter().x < left_most->getCenter().x){
                    left_most = currShape;
                }
                if(currShape->getCenter().x > right_most->getCenter().x){
                    right_most = currShape;
                }
            }
            
            // Split again by y if all shapes have same x
            if(left_most->getCenter().x == right_most->getCenter().x){
                for(auto it = shapes.begin(); it != shapes.end(); ++it){
                    Shape* currShape = *it;
                    if(currShape->getCenter().y < left_most->getCenter().y){
                        left_most = currShape;
                    }
                    if(currShape->getCenter().y > right_most->getCenter().y){
                        right_most = currShape;
                    }
                }
            }

            // If all shapes has same x and y, split again by z
            if(left_most->getCenter().y == right_most->getCenter().y){
                for(auto it = shapes.begin(); it != shapes.end(); ++it){
                    Shape* currShape = *it;
                    if(currShape->getCenter().z < left_most->getCenter().z){
                        left_most = currShape;
                    }
                    if(currShape->getCenter().z > right_most->getCenter().z){
                        right_most = currShape;
                    }
                }
            }

            // In the worst case that two shapes have the same center, let right be next
            if(left_most->getCenter() == right_most->getCenter()){
                right_most = shapes.at(1);
            }

            left.push_back(left_most);
            right.push_back(right_most);
            int l = shapes.size() / 2;
            //Now split the shapes by the distance of their centers
            for(auto it = shapes.begin(); it != shapes.end(); ++it){
                Shape* currShape = *it;
                if(currShape == left_most){
                    continue;
                }
                if(currShape == right_most){
                    continue;
                }
                if(left.size() >= l){
                    right.push_back(currShape);
                    continue;
                }
                if(right.size() >= l){
                    left.push_back(currShape);
                    continue;
                }

                float center_to_left = (currShape->getCenter() - left_most->getCenter()).length();
                float center_to_right = (currShape->getCenter() - right_most->getCenter()).length();
                if(center_to_left < center_to_right){
                    left.push_back(currShape);
                }else{
                    right.push_back(currShape);
                } 
            }
        }
        
        BVHNode* leftNode = BVH::BuildBVHTree(left);
        BVHNode* rightNode = BVH::BuildBVHTree(right);
        node->left = leftNode;
        node->right = rightNode;
        // std::printf("BVH tree finished building.\n");
        if(leftNode->isEmpty == true && rightNode->isEmpty == true){
            return node;
        }
        else if(leftNode->isEmpty == true){
            node->box.max = rightNode->box.max;
            node->box.min = rightNode->box.min;
            return node;
        }
        else if(rightNode->isEmpty == true){
            node->box.max = leftNode->box.max;
            node->box.min = leftNode->box.min;
            return node;
        }else{
            float max_x = std::max(leftNode->box.max.x, rightNode->box.max.x);
            float max_y = std::max(leftNode->box.max.y, rightNode->box.max.y);
            float max_z = std::max(leftNode->box.max.z, rightNode->box.max.z);

            float min_x = std::min(leftNode->box.min.x, rightNode->box.min.x);
            float min_y = std::min(leftNode->box.min.y, rightNode->box.min.y);
            float min_z = std::min(leftNode->box.min.z, rightNode->box.min.z);

            node->box.max = Vec3f{max_x, max_y, max_z};
            node->box.min = Vec3f{min_x, min_y, min_z};    
            return node;        
        }
        
    }

    Hit BVH::getIntersect(Ray ray, BVHNode* node)
    {
        BVHNode* current = node;
        Hit hit;
        hit.hasHit = false;
        if(node){
        }else{
            return hit;
        }
        if(node == nullptr){
            return hit;
        }       
        if(node->isEmpty){
            return hit;
        }

        if(!checkBounding(ray, node->box)){
            return hit;
        }
        // Return the hit if bottom leaf node
        if(node->hasShape){
            Shape* shape = node->shape;
            Hit shapeHit = shape->intersect(ray);
            if(!shapeHit.hasHit){
                return hit;
            }else{
                return shapeHit;
            }
        }

        BVHNode* leftNode;
        BVHNode* rightNode;
        Hit left;
        Hit right;
        if(node->left && node->right){
            leftNode = current->left;
            rightNode = current->right;
            left = BVH::getIntersect(ray, leftNode);
            right = BVH::getIntersect(ray, rightNode);
        }else if(node->left){       
            leftNode = node->left;
            left = BVH::getIntersect(ray,leftNode);
            if(!left.hasHit){
                return hit;
            }
            float dis_left = (left.point - ray.origin).length();
            if(dis_left <= 1e-3) return hit;
            return left;
        }else if(node->right){
            rightNode = node->right;
            right = BVH::getIntersect(ray,rightNode);
            if(!right.hasHit){
                return hit;
            }
            float dis_right = (right.point - ray.origin).length();
            if(dis_right <= 1e-3) return hit;
            return right;
        }else{
            return hit;
        }
        

        if(!left.hasHit && !right.hasHit){
            return hit;
        }else if(!left.hasHit){
            float dis_right = (right.point - ray.origin).length();
            if(dis_right <= 1e-3) return hit;
            return right;
        }else if(!right.hasHit){
            float dis_left = (left.point - ray.origin).length();
            if(dis_left <= 1e-3) return hit;
            return left;
        }else{
            float dis_left = (left.point - ray.origin).length();
            float dis_right = (right.point - ray.origin).length();

            // prevent reflection ray hitting the origin object
            if(dis_left <= 1e-3 && dis_right <=1e-3){
                return hit;
            }else if(dis_left <= 1e-3){
                return right;
            }else if(dis_right <= 1e-3){
                return left;
            } 

            // return the closer hit point
            if(dis_left < dis_right){
                return left;
            }else{
                return right;
            }
        }

    }

    bool BVH::checkBounding(Ray ray, BoundingBox box)
    {   
        Vec3f t_min = (box.min - ray.origin) * ray.inv_dir;
        Vec3f t_max = (box.max - ray.origin) * ray.inv_dir;
        float t_enter_x = (ray.inv_dir.x >= 0) ? t_min.x : t_max.x;
        float t_enter_y = (ray.inv_dir.y >= 0) ? t_min.y : t_max.y;
        float t_enter_z = (ray.inv_dir.z >= 0) ? t_min.z : t_max.z;
        float t_exit_x = (ray.inv_dir.x >= 0) ? t_max.x : t_min.x;
        float t_exit_y = (ray.inv_dir.y >= 0) ? t_max.y : t_min.y;
        float t_exit_z = (ray.inv_dir.z >= 0) ? t_max.z : t_min.z;

        float t_enter = std::max(std::max(t_enter_x, t_enter_y),t_enter_z);
        float t_exit = std::min(std::min(t_exit_x, t_exit_y),t_exit_z);
        return t_enter <= t_exit;
    }

} // namespace rt
