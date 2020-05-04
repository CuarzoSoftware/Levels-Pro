#ifndef OPENGLRULER_H
#define OPENGLRULER_H

#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>

class OpenGLRuler : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit OpenGLRuler();
    void setBackgroundColor(const QColor &color);
    void setBarSize(GLfloat barSizePixels);
    void setBeatsPerBar(GLfloat beats);
    void setXScroll(GLfloat pos);


protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    bool initialized = false;
    GLfloat barSize = 200.0f;
    GLfloat beatsPerBar = 4.0f;
    GLfloat xScroll = 0.0f;
    QColor backgroundColor = QColor("#333333");
    QOpenGLShaderProgram *program;
    QOpenGLFunctions *f;
    GLint backgroundColorUniform,barSizeUniform,beatsUniform,xScrollUniform;
    GLfloat quad[8] =
    {
        -1.0f, -1.0f,
        -1.0f,  1.0f,
         1.0f,  1.0f,
         1.0f, -1.0f
    };
    void initShaders();

};

#endif // RULER_H
