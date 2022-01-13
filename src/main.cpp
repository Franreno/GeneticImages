#include <iostream>
#include <GL/glut.h>
#include <stdlib.h>
#include <vector>

#include "Ag.hpp"

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600

dataType img;
dataType imgproc;

float PIXEL_SIZE_RELATIVE_TO_OPENGL = 0;
int imgWidth = 0;
int imgHeight = 0;

void readCabecalho(FILE *f, long fileSize)
{
    string helper = "";

    char c = 0;

    // Pular os tres primeiros bytes
    fseek(f, 3, SEEK_CUR);

    fread(&c, sizeof(unsigned char), 1, f);
    // Verificar se o caractere lido foi #
    if (c == '#')
    {
        // Pular o comentario do cabecalho
        while (c != '\n')
            fread(&c, sizeof(unsigned char), 1, f);
    }
    else
    {
        helper += c;
    }

    // Ler a primeira dimensao da imagem
    while (c != ' ')
    {
        fread(&c, sizeof(unsigned char), 1, f);
        helper += c;
    }

    imgWidth = atoi(helper.c_str());
    helper = "";

    // Ler a segunda dimensao da imagem
    while (c != '\n')
    {
        fread(&c, sizeof(unsigned char), 1, f);
        helper += c;
    }

    imgHeight = atoi(helper.c_str());

    // Calculo do pixel
    PIXEL_SIZE_RELATIVE_TO_OPENGL = 1 / (imgWidth * 0.5);

    c = 0;
    // Read last line from header
    while (c != '\n')
    {
        fread(&c, sizeof(unsigned char), 1, f);
    }
}

void draw()
{
    glClear(GL_COLOR_BUFFER_BIT);

    float column = 1;
    float row = -1;
    int columnsCounter = 0;
    for (auto byte : imgproc)
    {
        float byteColor = (float)byte / 255.0;
        glColor3f(byteColor, byteColor, byteColor);

        glBegin(GL_POLYGON);

        glVertex2d(row, column);
        glVertex2d(row + PIXEL_SIZE_RELATIVE_TO_OPENGL, column);
        glVertex2d(row + PIXEL_SIZE_RELATIVE_TO_OPENGL, column - PIXEL_SIZE_RELATIVE_TO_OPENGL);
        glVertex2d(row, column - PIXEL_SIZE_RELATIVE_TO_OPENGL);

        row += PIXEL_SIZE_RELATIVE_TO_OPENGL;
        columnsCounter++;
        if (columnsCounter == imgWidth)
        {
            columnsCounter = 0;
            row = -1;
            column -= PIXEL_SIZE_RELATIVE_TO_OPENGL;
        }

        glEnd();
    }

    glutSwapBuffers();
}

void timer(int)
{
    glutPostRedisplay();

    //update();

    glutTimerFunc(1000 / 15, timer, 0);
}

int main(int argc, char **argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    int winId = glutCreateWindow("Imagem");
    glClearColor(1.0, 1.0, 1.0, 1.0);

    FILE *fd = fopen("images/heart.pgm", "rb");
    if (fd == NULL)
    {
        std::cout << "Erro ao abrir imagem\n";
    }

    fseek(fd, 0, SEEK_END);
    long fileSize = ftell(fd);
    fseek(fd, 0, SEEK_SET);

    readCabecalho(fd, fileSize);

    unsigned char byte;

    while (ftell(fd) != fileSize)
    {
        fread(&byte, sizeof(unsigned char), 1, fd);
        img.push_back(byte);
    }
    fclose(fd);

    Ag ag(img);
    ag.initialize();

    do{
        glClearColor(1.0, 1.0, 1.0, 1.0);
        ag.evaluatePop();
        ag.tournament();
        //ag.elitism();
        
        ag.print();

        imgproc = ag.getBest();

        draw();
        glutPostRedisplay();
    } while (ag.getGeneration() != LIMIT_GEN);

    glutMainLoop();

    glutDestroyWindow(winId);
    return 0;
}