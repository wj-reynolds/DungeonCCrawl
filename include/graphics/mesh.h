#pragma once
#include <stdint.h>

typedef struct Mesh_T {
    float* vertexArray;
    uint32_t vertexCount;
    uint32_t elementCount;
    uint32_t dimensions;
    uint32_t vao;
    uint32_t ebo;
    uint32_t positionVbo;
} Mesh;

Mesh generateMesh(const float* vertexArray, int32_t vertexCount, int32_t dimensions);
Mesh generateMeshI(const float* vertexArray, int32_t vertexCount, int32_t dimensions, const uint32_t* elementArray, uint32_t elementCount);
void bindMesh(Mesh mesh);
void unbindMesh();
void cleanUpMesh(const Mesh* mesh);