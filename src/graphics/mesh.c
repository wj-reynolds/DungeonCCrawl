#include "graphics/mesh.h"

#include <glad/gl.h>

Mesh generateMesh(const float* vertexArray, const int32_t vertexCount, const int32_t dimensions)
{
    Mesh mesh = { 0 };
    glGenVertexArrays(1, &mesh.vao);
    glBindVertexArray(mesh.vao);

    glGenBuffers(1, &mesh.positionVbo);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.positionVbo);
    glBufferData(GL_ARRAY_BUFFER,  vertexCount * dimensions * (long long) sizeof(float), vertexArray, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, dimensions, GL_FLOAT, GL_FALSE, 0, nullptr);
    glDisableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    mesh.vertexCount = vertexCount;

    return mesh;
}

Mesh generateMeshI(const float* vertexArray, const int32_t vertexCount, const int32_t dimensions, const uint32_t* elementArray, const uint32_t elementCount)
{
    Mesh mesh = generateMesh(vertexArray, vertexCount, dimensions);

    glBindVertexArray(mesh.vao);

    glGenBuffers(1, &mesh.ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,  elementCount * (long long) sizeof(uint32_t), elementArray, GL_STATIC_DRAW);

    glBindVertexArray(0);

    mesh.elementCount = elementCount;

    return mesh;
}

void bindMesh(const Mesh mesh)
{
    glBindVertexArray(mesh.vao);
    glEnableVertexAttribArray(0);
}

void unbindMesh()
{
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
}

void cleanUpMesh(const Mesh* mesh)
{
    glDeleteBuffers(1, &mesh->positionVbo);
    if (mesh->ebo != 0) {
        glDeleteBuffers(1, &mesh->ebo);
    }
    glDeleteVertexArrays(1, &mesh->vao);
}