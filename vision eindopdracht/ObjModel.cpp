#include "ObjModel.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

#define STB_IMAGE_IMPLEMENTATION
#define STB_PERLIN_IMPLEMENTATION

#include "stb_image.h"
#include "stb_perlin.h"

#ifdef __APPLE__

#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>

#else
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

//TODO: Remove me before the final release
#define DRAW_BOUNDING_BOX false


std::string replace(std::string str, std::string toReplace, std::string replacement) {
    size_t index = 0;
    while (true) {
        index = str.find(toReplace, index);
        if (index == std::string::npos)
            break;
        str.replace(index, toReplace.length(), replacement);
        ++index;
    }
    return str;
}

std::vector<std::string> split(std::string str, std::string sep) {
    std::vector<std::string> ret;
    size_t index;
    while (true) {
        index = str.find(sep);
        if (index == std::string::npos)
            break;
        ret.push_back(str.substr(0, index));
        str = str.substr(index + 1);
    }
    ret.push_back(str);
    return ret;
}

inline std::string toLower(std::string data) {
    std::transform(data.begin(), data.end(), data.begin(), ::tolower);
    return data;
}


ObjModel::ObjModel(std::string fileName) {
    xpos = ypos = zpos = xrot = yrot = zrot = 0;
//Fix for the OSX project, because our paht starts from shiro-bougyo instead of Project
#ifdef __APPLE__
    fileName = "Project/" + fileName;
#endif

    std::string dirName = fileName;
    if (dirName.rfind("/") != std::string::npos)
        dirName = dirName.substr(0, dirName.rfind("/"));
    if (dirName.rfind("\\") != std::string::npos)
        dirName = dirName.substr(0, dirName.rfind("\\"));
    if (fileName == dirName)
        dirName = "";


    std::ifstream pFile(fileName.c_str());

    if (!pFile.is_open()) {
        std::cout << "Could not open file " << fileName << std::endl;
        return;
    }


    ObjGroup *currentGroup = new ObjGroup();
    currentGroup->materialIndex = -1;


    while (!pFile.eof()) {
        std::string line;
        std::getline(pFile, line);

        line = replace(line, "\t", " ");
        while (line.find("  ") != std::string::npos)
            line = replace(line, "  ", " ");
        if (line == "")
            continue;
        if (line[0] == ' ')
            line = line.substr(1);
        if (line == "")
            continue;
        if (line[line.length() - 1] == ' ')
            line = line.substr(0, line.length() - 1);
        if (line == "")
            continue;
        if (line[0] == '#')
            continue;

        std::vector<std::string> params = split(line, " ");
        params[0] = toLower(params[0]);

        if (params[0] == "v")
            vertices.push_back(new Vec3f((float) atof(params[1].c_str()), (float) atof(params[2].c_str()),
                                         (float) atof(params[3].c_str())));
        else if (params[0] == "vn")
            normals.push_back(new Vec3f((float) atof(params[1].c_str()), (float) atof(params[2].c_str()),
                                        (float) atof(params[3].c_str())));
        else if (params[0] == "vt")
            texcoords.push_back(new Vec2f((float) atof(params[1].c_str()), (float) atof(params[2].c_str())));
        else if (params[0] == "f") {
            for (size_t ii = 4; ii <= params.size(); ii++) {
                Face face;

                for (size_t i = ii - 3; i < ii; i++)    //magische forlus om van quads triangles te maken ;)
                {
                    Vertex vertex;
                    std::vector<std::string> indices = split(params[i == (ii - 3) ? 1 : i], "/");
                    if (indices.size() >= 1)    //er is een positie
                        vertex.position = atoi(indices[0].c_str()) - 1;
                    if (indices.size() == 2)        //alleen texture
                        vertex.texcoord = atoi(indices[1].c_str()) - 1;
                    if (indices.size() == 3)        //v/t/n of v//n
                    {
                        if (indices[1] != "")
                            vertex.texcoord = atoi(indices[1].c_str()) - 1;
                        vertex.normal = atoi(indices[2].c_str()) - 1;
                    }
                    face.vertices.push_back(vertex);
                }
                currentGroup->faces.push_back(face);
            }
        }
        else if (params[0] == "s") {//smoothing
        }
        else if (params[0] == "mtllib") {
            loadMaterialFile(dirName + "/" + params[1], dirName);
        }
        else if (params[0] == "usemtl") {
            if (currentGroup->faces.size() != 0)
                groups.push_back(currentGroup);
            currentGroup = new ObjGroup();
            currentGroup->materialIndex = -1;

            for (size_t i = 0; i < materials.size(); i++) {
                MaterialInfo *info = materials[i];
                if (info->name == params[1]) {
                    currentGroup->materialIndex = i;
                    break;
                }
            }
            if (currentGroup->materialIndex == -1)
                std::cout << "Could not find material name " << params[1] << std::endl;
        }
    }
    groups.push_back(currentGroup);
    CalcMinVertex();
    CalcMaxVertex();
    InitBoundingSpheres();
    CalcBoundingSpheres();
}

void ObjModel::CalcMinVertex() {
    float smallestx, smallesty, smallestz;
    smallestx = smallesty = smallestz = 0;

    //find smallest x
    smallestx = 100000; //using 100 as a base value, this has to be a big number.
    for (auto &vertice : vertices) {
        if (vertice->x < smallestx) {
            smallestx = vertice->x;
        }
    }

    //find smallest y
    smallesty = 100000;
    for (auto &vertice : vertices) {
        if (vertice->y < smallesty) {
            smallesty = vertice->y;
        }
    }

    smallestz = 100000;
    for (auto &vertice : vertices) {
        if (vertice->z < smallestz) {
            smallestz = vertice->z;
        }
    }
    printf("What I've found:\n %f %f %f\n", smallestx, smallesty, smallestz);

    //Transform it into a vertex.
    vertices_min = new Vec3f(smallestx, smallesty, smallestz);

}

void ObjModel::CalcMaxVertex() {
    float maxx, maxy, maxz;
    maxx = maxy = maxz = 0;

    //find smallest x
    maxx = -100000; //using -100 as a base value, this has to be a big number.
    for (auto &vertice : vertices) {
        if (vertice->x > maxx) {
            maxx = vertice->x;
        }
    }

    //find smallest y
    maxy = -100000;
    for (auto &vertice : vertices) {
        if (vertice->y > maxy) {
            maxy = vertice->y;
        }
    }

    maxz = -1000000;
    for (auto &vertice : vertices) {
        if (vertice->z > maxz) {
            maxz = vertice->z;
        }
    }

    printf("What I've found:\n %f %f %f\n", maxx, maxy, maxz);
    vertices_max = new Vec3f(maxx, maxy, maxz);
}

ObjModel::~ObjModel(void) {
}


void ObjModel::draw() {
    //This affects the entire model
    //glColor
    glPushMatrix();

    glTranslatef(xpos, ypos, zpos);

    glRotatef(xrot, 1, 0, 0);
    glRotatef(yrot, 0, 1, 0);
    glRotatef(zrot, 0, 0, 1);

//	glTranslatef(xpos, ypos, zpos);



    for (auto &g : groups) {
        if (materials[g->materialIndex]->hasTexture) {
            glEnable(GL_TEXTURE_2D);
            materials[g->materialIndex]->texture->bind();
        }

        glBegin(GL_TRIANGLES);
        for (auto &f : g->faces) {
            for (auto &v : f.vertices) {
                glNormal3f(normals[v.normal]->x, normals[v.normal]->y, normals[v.normal]->z);
                glTexCoord2f(texcoords[v.texcoord]->x, texcoords[v.texcoord]->y);
                glVertex3f(vertices[v.position]->x, vertices[v.position]->y, vertices[v.position]->z);
            }
        }
        glEnd();
    }

    if (DRAW_BOUNDING_BOX) {
//        glLineWidth(5);
//
//        glBegin(GL_LINE_LOOP);
//        glVertex3f(vertices_max->x, vertices_max->y, vertices_min->z);
//        glVertex3f(vertices_min->x, vertices_max->y, vertices_min->z);
//        glVertex3f(vertices_min->x, vertices_min->y, vertices_min->z);
//        glVertex3f(vertices_max->x, vertices_min->y, vertices_min->z);
//        glEnd();
//
//        glBegin(GL_LINE_LOOP);
//        glVertex3f(vertices_max->x, vertices_min->y, vertices_max->z);
//        glVertex3f(vertices_max->x, vertices_max->y, vertices_max->z);
//        glVertex3f(vertices_min->x, vertices_max->y, vertices_max->z);
//        glVertex3f(vertices_min->x, vertices_min->y, vertices_max->z);
//        glEnd();
//
//        glBegin(GL_LINE_LOOP);
//        glVertex3f(vertices_max->x, vertices_max->y, vertices_min->z);
//        glVertex3f(vertices_max->x, vertices_max->y, vertices_max->z);
//        glVertex3f(vertices_min->x, vertices_max->y, vertices_max->z);
//        glVertex3f(vertices_min->x, vertices_max->y, vertices_min->z);
//        glEnd();
//
//        glBegin(GL_LINE_LOOP);
//        glVertex3f(vertices_max->x, vertices_min->y, vertices_max->z);
//        glVertex3f(vertices_min->x, vertices_min->y, vertices_max->z);
//        glVertex3f(vertices_min->x, vertices_min->y, vertices_min->z);
//        glVertex3f(vertices_max->x, vertices_min->y, vertices_min->z);
//        glEnd();

        for(auto &e : boundingSpheres) {
            if (e->collides) {
                glPushMatrix();
                glColor3ub(0, 255, 255);
                glTranslatef(e->x, e->y, e->z);
                glutWireSphere(e->radius, 20, 20); //Radius, polycount, polycount
                glPopMatrix();
            }
        }
        glColor3f(1,1,1);

    }
    glPopMatrix();
}

void ObjModel::loadMaterialFile(std::string fileName, std::string dirName) {
    std::ifstream pFile(fileName.c_str());
    if (!pFile.is_open()) {
        std::cout << "Could not open file " << fileName << std::endl;
        return;
    }

    MaterialInfo *currentMaterial = NULL;

    while (!pFile.eof()) {
        std::string line;
        std::getline(pFile, line);

        line = replace(line, "\t", " ");
        while (line.find("  ") != std::string::npos)
            line = replace(line, "  ", " ");
        if (line == "")
            continue;
        if (line[0] == ' ')
            line = line.substr(1);
        if (line == "")
            continue;
        if (line[line.length() - 1] == ' ')
            line = line.substr(0, line.length() - 1);
        if (line == "")
            continue;
        if (line[0] == '#')
            continue;

        std::vector<std::string> params = split(line, " ");
        params[0] = toLower(params[0]);
        if (params[0] == "newmtl") {
            if (currentMaterial != NULL) {
                materials.push_back(currentMaterial);
            }
            currentMaterial = new MaterialInfo();
            currentMaterial->name = params[1];
        }
        else if (params[0] == "map_kd") {
            currentMaterial->hasTexture = true;
            currentMaterial->texture = new Texture(dirName + "/" + params[1]);
            std::cout << "Made material named " << params[1] << std::endl;
        }
        else
            std::cout << "Didn't parse " << params[0] << " in material file" << std::endl;
    }
    if (currentMaterial != NULL)
        materials.push_back(currentMaterial);

}

bool ObjModel::CollidesWith(ObjModel *obj2) {
    this->CalcBoundingSpheres();
    obj2->CalcBoundingSpheres();

    bool retval = false;

    for (auto &sphere1 : this->boundingSpheres) {
        for (auto &sphere2 : obj2->boundingSpheres) {
            if (sphere1 != sphere2 && sphere1->intersect(sphere2)){
                retval = true;
                return retval;
            }
        }
    }

    return retval;
}

void ObjModel::update() {
    yrot += 0.5;
    if (xpos > 5) {
        xpos = -5;
    }
}

void ObjModel::InitBoundingSpheres() {
    //Calculate bounding spheres here, to be overriden by specific classes.
    //Here we make just 1 bounding sphere.
    //Hence, the sphere has to be in the middle of the model, using either width, height or depth for the radius, whichever is the biggest.

    //Calculate width
    float width = vertices_max->x - vertices_min->x;
    float height = vertices_max->y - vertices_min->y;
    float depth = vertices_max->z - vertices_min->z;

    //X, Y and Z of sphere is the middle of the model

    float x, y, z ;
    x = y = z = 0;

    x = width / 2 + vertices_min->x;
    y = height / 2+vertices_min->y;
    z = depth / 2+vertices_min->z;

    printf("Width = %f\n",width);
    printf("Height = %f\n",height);
    printf("Depth = %f\n",depth);

    if( width>=height && width>=depth ){
        //Use width
        printf("Using width\n");
        boundingSpheres.push_back(new Sphere(x, y, z, width/2));
    }

    if( height>=width && height>=depth ) {
        //Use height
        printf("Using height\n");
        boundingSpheres.push_back(new Sphere(x, y, z, height/2));
    }

    if( depth>=width && depth>=height ) {
        //Use depth
        printf("Using depth\n");
        boundingSpheres.push_back(new Sphere(x, y, z, depth/2));
    }

    printf("Called base\n");


}

void ObjModel::CalcBoundingSpheres() {
    for (auto &sphere : boundingSpheres) {
        sphere->xpos = sphere->x + this->xpos;
        sphere->ypos = sphere->y + this->ypos;
        sphere->zpos = sphere->z + this->zpos;
    }
}


ObjModel::MaterialInfo::MaterialInfo() {
    Texture *texture;
    hasTexture = false;
}


Vec3f::Vec3f(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Vec3f::Vec3f() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Vec3f::Vec3f(Vec3f &other) {
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
}

float &Vec3f::operator[](int index) {
    return v[index];
}


Vec2f::Vec2f(float x, float y) {
    this->x = x;
    this->y = y;
}

Vec2f::Vec2f() {
    this->x = 0;
    this->y = 0;
}

Vec2f::Vec2f(Vec2f &other) {
    this->x = other.x;
    this->y = other.y;
}

float &Vec2f::operator[](int index) {
    return v[index];
}

ObjModel::Texture::Texture(const std::string &fileName) {
    int width, height, bpp;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *imgData = stbi_load(fileName.c_str(), &width, &height, &bpp, 4);

    glGenTextures(1, &index);
    glBindTexture(GL_TEXTURE_2D, index);

    glTexImage2D(GL_TEXTURE_2D,
                 0,        //level
                 GL_RGBA,        //internal format
                 width,        //width
                 height,        //height
                 0,        //border
                 GL_RGBA,        //data format
                 GL_UNSIGNED_BYTE,    //data type
                 imgData);        //data
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    stbi_image_free(imgData);
}

void ObjModel::Texture::bind() {
    glBindTexture(GL_TEXTURE_2D, index);
}

bool ObjModel::Sphere::intersect(ObjModel::Sphere *other) {

    if(collides){
        float distance = sqrtf((this->xpos - other->xpos) * (this->xpos - other->xpos) +
                               (this->ypos - other->ypos) * (this->ypos - other->ypos) +
                               (this->zpos - other->zpos) * (this->zpos - other->zpos));
        return distance < (other->radius + other->radius);
    }

    return false;

}

bool ObjModel::Sphere::intersect(float x, float y, float z) {
    if(collides){
        float distance = sqrtf((x - this->xpos) * (x - this->xpos) +
                               (y - this->ypos) * (y - this->ypos) +
                               (z - this->zpos) * (z - this->zpos));
        return distance < this->radius;
    }
    return false;
}

ObjModel::Sphere::Sphere(float x, float y, float z, float radius):x(x), y(y), z(z), radius(radius) {
    //Initialize a sphere
}

ObjModel::Sphere* ObjModel::Sphere::setCollision(bool value) {
    collides = value;
    return this;
}







