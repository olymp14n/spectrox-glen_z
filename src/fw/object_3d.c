#include "object_3d.h"
#include <GL/gl.h>

void fw_object_3d_putFaces(fw_object_3d *object3D) {
    fw_vec3f *v = object3D->v;
    fw_vec3i *f = object3D->f;
    fw_vec4f *c = object3D->c;
    int *cidx = object3D->cidx;
    fw_vec3f *fn = object3D->fn;

    glBegin(GL_TRIANGLES);
    for (int i = 0; i < object3D->numFaces; i++) {
        glColor4f(c[cidx[i]].x, c[cidx[i]].y, c[cidx[i]].z, c[cidx[i]].w);
        glNormal3f(fn[i].x, fn[i].y, fn[i].z);
        glVertex3f(v[f[i].x].x, v[f[i].x].y, v[f[i].x].z);
        glVertex3f(v[f[i].y].x, v[f[i].y].y, v[f[i].y].z);
        glVertex3f(v[f[i].z].x, v[f[i].z].y, v[f[i].z].z);
    }
    glEnd();
}

void fw_object_3d_putFacesArray(fw_object_3d *object3D) {
    glVertexPointer(3,GL_FLOAT,0,object3D->arr.v);
    glNormalPointer(GL_FLOAT,0,object3D->arr.n);
    glColorPointer(4,GL_FLOAT,0,object3D->arr.c);
    glDrawElements(GL_TRIANGLES, object3D->arr.numFaces, GL_UNSIGNED_INT, object3D->arr.f);
}

void fw_object_3d_put(fw_object_3d *object3D) {
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    fw_object_3d_putFaces(object3D);
    glDisable(GL_CULL_FACE);
}

/*
static void fw_object_3d_normalize(fw_vec3f *v) {
    float len = sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
    v->x /= len;
    v->y /= len;
    v->z /= len;
}
*/

static void fw_object_3d_cross(fw_vec3f *a, fw_vec3f *b, fw_vec3f *result) {
    result->x = a->y * b->z - a->z * b->y;
    result->y = a->z * b->x - a->x * b->z;
    result->z = a->x * b->y - a->y * b->x;
}

static void fw_object_3d_calculateNormal(fw_vec3f *a, fw_vec3f *b, fw_vec3f *c, fw_vec3f *result) {
    fw_vec3f v1 = {a->x - c->x, a->y - c->y, a->z - c->z};
    fw_vec3f v2 = {b->x - c->x, b->y - c->y, b->z - c->z};

    fw_object_3d_cross(&v1, &v2, result);
    // Only needed if GL_NORMALIZE is not enabled.
    //fw_object_3d_normalize(result);
}

void fw_object_3d_calculateFaceNormals(fw_object_3d *object3D) {
    fw_vec3f *v = object3D->v;
    fw_vec3i *f = object3D->f;
    fw_vec3f *fn = object3D->fn;

    for (int i=0; i<object3D->numFaces; i++) {
        fw_object_3d_calculateNormal(&v[f[i].x], &v[f[i].y], &v[f[i].z], &fn[i]);
    }
}

void fw_object_3d_initArray(fw_object_3d *object3D) {
    int numFaces = object3D->numFaces * 3;
    int numVerts = object3D->numFaces * 3 * 3;
    int numColors = object3D->numFaces * 3 * 4;

    object3D->arr.numFaces = numFaces;
    object3D->arr.v = calloc(numVerts, sizeof(float));
    object3D->arr.n = calloc(numVerts, sizeof(float));
    object3D->arr.c = calloc(numColors, sizeof(float));
    object3D->arr.f = calloc(numFaces, sizeof(int));

    for (int i=0; i<numFaces; i++) {
        object3D->arr.f[i] = i;
    }

    fw_object_3d_updateArray(object3D);
}

void fw_object_3d_updateArray(fw_object_3d *object3D) {
    int voff = 0;
    int coff = 0;
    int noff = 0;
    for (int i=0; i<object3D->numFaces; i++) {
        object3D->arr.v[voff++] = object3D->v[ object3D->f[i].x ].x;
        object3D->arr.v[voff++] = object3D->v[ object3D->f[i].x ].y;
        object3D->arr.v[voff++] = object3D->v[ object3D->f[i].x ].z;

        object3D->arr.v[voff++] = object3D->v[ object3D->f[i].y ].x;
        object3D->arr.v[voff++] = object3D->v[ object3D->f[i].y ].y;
        object3D->arr.v[voff++] = object3D->v[ object3D->f[i].y ].z;

        object3D->arr.v[voff++] = object3D->v[ object3D->f[i].z ].x;
        object3D->arr.v[voff++] = object3D->v[ object3D->f[i].z ].y;
        object3D->arr.v[voff++] = object3D->v[ object3D->f[i].z ].z;

        // Normals and color per face, i.e. three times the same values for each vertex.
        for (int j=0; j<3; j++) {
            object3D->arr.n[noff++] = object3D->fn[i].x;
            object3D->arr.n[noff++] = object3D->fn[i].y;
            object3D->arr.n[noff++] = object3D->fn[i].z;

            object3D->arr.c[coff++] = object3D->c[ object3D->cidx[i] ].x;
            object3D->arr.c[coff++] = object3D->c[ object3D->cidx[i] ].y;
            object3D->arr.c[coff++] = object3D->c[ object3D->cidx[i] ].z;
            object3D->arr.c[coff++] = object3D->c[ object3D->cidx[i] ].w;
        }
    }
}
