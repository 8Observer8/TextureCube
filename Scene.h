#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <QGLWidget>
#include <QKeyEvent>

class Scene : public QGLWidget
{
public:
    Scene( QWidget *parent = 0 );

private:
    void initializeGL();
    void paintGL();
    void resizeGL( int w, int h );
    void keyPressEvent( QKeyEvent *event );

    void initSquare();
    void genTexture();

private:
    // Rotation amounts
    GLfloat xRot;
    GLfloat yRot;
    std::vector<GLfloat> m_vertices;
    std::vector<GLfloat> m_textures;
    std::vector<GLuint> m_indices;
};

#endif // SCENE_H
