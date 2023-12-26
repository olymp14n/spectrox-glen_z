#ifndef FW_OBJECT_3D_H
#define FW_OBJECT_3D_H

#include "types.h"

typedef struct {
    int numFaces; // Number of faces.
    int *f; // Every face has points to 3 unique vertices.
    float *v; // Vertices, each made of 3 coordinates.
    float *n; // Vertex normals, each made of 3 coordinates.
    float *c; // Vertex colors, each made of 4 values.
} fw_object_3d_array;

typedef struct {
    fw_vec3f *v;
    int numVertices;
    fw_vec3i *f;
    int numFaces;
    fw_vec4f *c;
    int *cidx;
    fw_vec3f *fn;
    fw_object_3d_array arr;
} fw_object_3d;


void fw_object_3d_putFaces(fw_object_3d *object3D);
void fw_object_3d_putFacesArray(fw_object_3d *object3D);
void fw_object_3d_put(fw_object_3d *object3D);
void fw_object_3d_calculateFaceNormals(fw_object_3d *object3D);

void fw_object_3d_initArray(fw_object_3d *object3D);
void fw_object_3d_updateArray(fw_object_3d *object3D);


#endif
