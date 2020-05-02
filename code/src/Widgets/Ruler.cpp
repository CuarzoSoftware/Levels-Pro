#include "Ruler.h"
#include <QOpenGLContext>


Ruler::Ruler()
{

}

void Ruler::initializeGL()
{
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    initShaders();
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, quad);
    glEnableVertexAttribArray(0);
    initialized = true;
    setBackgroundColor(backgroundColor);
}

void Ruler::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void Ruler::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void Ruler::setBackgroundColor(const QColor &color)
{
    backgroundColor = color;
    if(initialized)
        glUniform3f(backgroundColorUniform,backgroundColor.redF(),backgroundColor.greenF(),backgroundColor.blueF());
}

void Ruler::initShaders()
{
    // Creates shader program
    program = new QOpenGLShaderProgram();

    // Compile vertex shader
    if (!program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":res/shaders/ruler/vshader.glsl"))
        close();

    // Compile fragment shader
    if (!program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":res/shaders/ruler/fshader.glsl"))
        close();

    // Link shader pipeline
    if (!program->link())
        close();

    // Bind shader pipeline for use
    if (!program->bind())
        close();

    backgroundColorUniform = glGetUniformLocation(program->programId(),"backgroundColor");

}
