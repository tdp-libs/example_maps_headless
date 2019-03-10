#include "example_maps_headless/Globals.h"

#include "tp_maps_headless/Map.h"

#include "tp_maps/layers/Geometry3DLayer.h"
#include "tp_maps/controllers/FlatController.h"

#include "tp_image_utils_freeimage/Globals.h"

#include "tp_image_utils/ColorMap.h"
#include "tp_image_utils/SaveImages.h"

void addSphere(tp_maps::Map* map);

//##################################################################################################
int main()
{
  tp_image_utils_freeimage::init();

  //Construct the headless tp_maps object that will do the drawing.
  tp_maps_headless::Map map(true);
  map.setBackgroundColor({0.0f, 0.0f, 0.0f});

  //Create a shpere model.
  addSphere(&map);

  //Rotate the camera to look down on the sphere at an angle.
  auto controller = new tp_maps::FlatController(&map);
  controller->setViewAngle(60.0f);

  //Render to an image and save it.
  tp_image_utils::ColorMap image(256, 256);
  map.renderToImage(image.width(), image.height(), image.data());
  tp_image_utils::saveImage("output.png", image);

  return 0;
}

//##################################################################################################
void addSphere(tp_maps::Map* map)
{
  tp_maps::Geometry3D geometry;

  //Material to color the sphere with.
  geometry.material.ambient   = {0.1f, 0.4f, 0.2f};
  geometry.material.diffuse   = {0.5f, 1.0f, 0.1f};
  geometry.material.specular  = {0.3f, 0.3f, 0.3f};
  geometry.material.shininess = 32.0f;

  //Create the mesh for the sphere.
  geometry.geometry.triangles = GL_TRIANGLES;
  auto& indexes = geometry.geometry.indexes.emplace_back();
  indexes.type = geometry.geometry.triangles;

  int stride = 6;
  float radius = 10;
  auto addVert = [&](float x, float y, float z)
  {
    geometry.geometry.verts.emplace_back().vert = {x*radius, y*radius, z*radius};
  };

  for(int i=0; i<180; i+=stride)
  {
    float z0=std::cos(glm::radians(float(i)));
    float d0=std::sin(glm::radians(float(i)));
    float z1=std::cos(glm::radians(float(i+stride)));
    float d1=std::sin(glm::radians(float(i+stride)));

    for(int i=0; i<360; i+=stride)
    {
      float x0=std::sin(glm::radians(float(i)));
      float y0=std::cos(glm::radians(float(i)));
      float x1=std::sin(glm::radians(float(i+stride)));
      float y1=std::cos(glm::radians(float(i+stride)));

      addVert(x0*d0, y0*d0, z0); // -4
      addVert(x0*d1, y0*d1, z1); // -3
      addVert(x1*d1, y1*d1, z1); // -2
      addVert(x1*d0, y1*d0, z0); // -1

      indexes.indexes.push_back(int(geometry.geometry.verts.size()-4));
      indexes.indexes.push_back(int(geometry.geometry.verts.size()-3));
      indexes.indexes.push_back(int(geometry.geometry.verts.size()-2));

      indexes.indexes.push_back(int(geometry.geometry.verts.size()-4));
      indexes.indexes.push_back(int(geometry.geometry.verts.size()-2));
      indexes.indexes.push_back(int(geometry.geometry.verts.size()-1));
    }
  }

  //Calculate face normals to make lighting work.
  geometry.geometry.calculateFaceNormals();

  //Add the sphere to the 3D map.
  auto layer = new tp_maps::Geometry3DLayer();
  layer->setGeometry({geometry});
  map->addLayer(layer);
}
