#include "Engine.hpp"

//FUNCTIONS
/*Loads the textures into memory*/
void Engine::loadTextures() {
    int width, height;
    bool hasAlpha;

    //load the logo
    loadImage((char*) "data/logo.png", width, height, hasAlpha, &logoImg);
    glGenTextures(1, &logoTex);
    glBindTexture(GL_TEXTURE_2D, logoTex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, logoImg);

    logoWidth = width;
    logoHeight = height;

    //load the title
    loadImage((char*) "data/title.png", width, height, hasAlpha, &titleImg);
    glGenTextures(1, &titleTex);
    glBindTexture(GL_TEXTURE_2D, titleTex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, titleImg);

    //load buttons
    loadImage((char*) "data/refresh.png", width, height, hasAlpha, &refreshImg);
    glGenTextures(1, &refreshTex);
    glBindTexture(GL_TEXTURE_2D, refreshTex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, refreshImg);

    loadImage((char*) "data/standard.png", width, height, hasAlpha, &stdImg);
    glGenTextures(1, &stdTex);
    glBindTexture(GL_TEXTURE_2D, stdTex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, stdImg);

    loadImage((char*) "data/blackhole.png", width, height, hasAlpha, &blackImg);
    glGenTextures(1, &blackTex);
    glBindTexture(GL_TEXTURE_2D, blackTex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, blackImg);

    loadImage((char*) "data/swish.png", width, height, hasAlpha, &swishImg);
    glGenTextures(1, &swishTex);
    glBindTexture(GL_TEXTURE_2D, swishTex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, swishImg);

    loadImage((char*) "data/butterfly.png", width, height, hasAlpha, &butterImg);
    glGenTextures(1, &butterTex);
    glBindTexture(GL_TEXTURE_2D, butterTex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, butterImg);

    loadImage((char*) "data/reform.png", width, height, hasAlpha, &reformImg);
    glGenTextures(1, &reformTex);
    glBindTexture(GL_TEXTURE_2D, reformTex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, reformImg);

    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    free(logoImg);
    free(titleImg);
    free(refreshImg);
    free(stdImg);
    free(blackImg);
    free(swishImg);
    free(butterImg);
    free(reformImg);
}


/*Loads a png image*/
bool Engine::loadImage(char *name, int &outWidth, int &outHeight, bool &outHasAlpha, GLubyte **outData) {
    png_structp pngPtr;
    png_infop infoPtr;
    unsigned int sigRead = 0;
    int colorType, interlaceType;
    FILE *file;

    if ((file = fopen(name, "rb")) == NULL) return false;

    pngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (pngPtr == NULL) {
        fclose(file);
        return false;
    }

    infoPtr = png_create_info_struct(pngPtr);
    if (infoPtr == NULL) {
        fclose(file);
        png_destroy_read_struct(&pngPtr, png_infopp_NULL, png_infopp_NULL);
        return false;
    }

    if (setjmp(png_jmpbuf(pngPtr))) {
        png_destroy_read_struct(&pngPtr, &infoPtr, png_infopp_NULL);
        fclose(file);
        return false;
    }

    png_init_io(pngPtr, file);
    png_set_sig_bytes(pngPtr, sigRead);

    png_read_png(pngPtr, infoPtr, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND, png_voidp_NULL);

    outWidth = infoPtr->width;
    outHeight = infoPtr->height;

    switch (infoPtr->color_type) {
        case PNG_COLOR_TYPE_RGBA:
            outHasAlpha = true;
            break;
        case PNG_COLOR_TYPE_RGB:
            outHasAlpha = false;
            break;
        default:
            cout << "Color type " << infoPtr->color_type << " not supported" << endl;
            png_destroy_read_struct(&pngPtr, &infoPtr, NULL);
            fclose(file);
            return false;
    }

    unsigned int rowBytes = png_get_rowbytes(pngPtr, infoPtr);
    *outData = (unsigned char*) malloc(rowBytes*outHeight);
    png_bytepp rowPointers = png_get_rows(pngPtr, infoPtr);

    for (int i = 0; i < outHeight; i++)
        memcpy(*outData+(rowBytes*(outHeight-1-i)), rowPointers[i], rowBytes);

    png_destroy_read_struct(&pngPtr, &infoPtr, png_infopp_NULL);
    fclose(file);

    return true;
}