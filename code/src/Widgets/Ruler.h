#ifndef RULER_H
#define RULER_H

#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>

class Ruler : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit Ruler();
    void setBackgroundColor(const QColor &color);

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    bool initialized = false;
    QColor backgroundColor = QColor("#333333");
    QOpenGLShaderProgram *program;
    GLint backgroundColorUniform;
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
