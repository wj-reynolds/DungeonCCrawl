#include "io/fileio.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "global.h"
#include "logger/logger.h"

char* readShaderFile(const char* source)
{
    FILE *fp = fopen(source, "rb");
    if (!fp) {
        logERROR("Failed to find or open shader file: %s\n", source);
        return nullptr;
    }

    fseek(fp, 0, SEEK_END);
    const long size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char *buffer = malloc(size + 1);
    if (buffer == nullptr) {
        logERROR("Failed to allocate memory for shader file buffer: %s\n", source);
        fclose(fp);
        free(buffer);
        return nullptr;
    }

    fread(buffer, sizeof(char), size, fp);
    buffer[size]= '\0';

    fclose(fp);
    return buffer;
}

static char* readOptionsFile(const char* source)
{
    FILE *fp = fopen(source, "rb");
    if (!fp) {
        logERROR("Failed to find or open options file: %s\n", source);
        return nullptr;
    }

    fseek(fp, 0, SEEK_END);
    const long size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char *buffer = malloc(size + 1);
    if (buffer == nullptr) {
        logERROR("Failed to allocate memory for options file buffer: %s\n", source);
        fclose(fp);
        free(buffer);
        return nullptr;
    }

    fread(buffer, sizeof(char), size, fp);
    buffer[size]= '\0';

    fclose(fp);
    return buffer;
}

void parseOptions(const char* source)
{
    const char* fileContents = readOptionsFile(source);

    char* buffer = nullptr;
    KeyAction mode = NONE;

    for (int _ = 0; fileContents[_] != '\0'; _++) {
        for (int i = 0; fileContents[i] != '='; i++) {
            buffer = malloc(sizeof(char) * (i + 1));
            buffer[i] = fileContents[i];
            if (strcmp(buffer, "up") > 0) {
                printf("%s\n", buffer);
                mode = UP;
            }
            free(buffer);
        }
    }
}