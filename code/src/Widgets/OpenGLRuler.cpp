#include "OpenGLRuler.h"
#include <QOpenGLContext>

/*!
    \class OpenGLRuler
    \brief The OpenGLRuler class...

    \inheaderfile Widgets/OpenGLRuler.h
    \ingroup Widgets
    \inmodule Widgets

    \inherits QOpenGLWidget
*/

OpenGLRuler::OpenGLRuler()
{

}

void OpenGLRuler::initializeGL()
{
    f = QOpenGLContext::currentContext()->functions();
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    initShaders();
    f->glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, quad);
    f->glEnableVertexAttribArray(0);
    initialized = true;
    setBackgroundColor(backgroundColor);
    setBeatsPerBar(beatsPerBar);
    setBarSize(barSize);
}

void OpenGLRuler::resizeGL(int w, int h)
{
    Q_UNUSED(w);
    Q_UNUSED(h);
}

void OpenGLRuler::paintGL()
{
    makeCurrent();
    f->glClear(GL_COLOR_BUFFER_BIT);
    f->glUniform1f(beatsUniform,beatsPerBar);
    f->glUniform3f(backgroundColorUniform,backgroundColor.redF(),backgroundColor.greenF(),backgroundColor.blueF());
    f->glUniform1f(barSizeUniform,barSize);
    f->glUniform1f(xScrollUniform,xScroll);
    f->glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    doneCurrent();
}

void OpenGLRuler::setBackgroundColor(const QColor &color)
{
    backgroundColor = color;
    if(initialized)
        update();

}

void OpenGLRuler::setBarSize(GLfloat barSizePixels)
{
    barSize = barSizePixels;
    if(initialized)
        update();

}

void OpenGLRuler::setBeatsPerBar(GLfloat beats)
{
    beatsPerBar = beats;
    if(initialized)
        update();
}

void OpenGLRuler::setXScroll(GLfloat pos)
{
    xScroll = pos;
    if(initialized)
        update();
}



void OpenGLRuler::initShaders()
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

    backgroundColorUniform = f->glGetUniformLocation(program->programId(),"backgroundColor");
    barSizeUniform = f->glGetUniformLocation(program->programId(),"barSize");
    beatsUniform = f->glGetUniformLocation(program->programId(),"beats");
    xScrollUniform = f->glGetUniformLocation(program->programId(),"xScroll");

}
