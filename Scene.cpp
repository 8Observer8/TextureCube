
#include <math.h>
#include <QDebug>
#include "Scene.h"

// Define a constant for the value of PI
#define GL_PI 3.1415f

Scene::Scene( QWidget *parent ) :
    QGLWidget( parent ),
    xRot( 0.0f ),
    yRot( 0.0f )
{
    this->setFocusPolicy( Qt::StrongFocus );
}

void Scene::initializeGL()
{
    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

    // Black background
    glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );

    // Set drawing color to green
    glColor3f( 0.0f, 1.0f, 0.0f );

    initSquare();

    // Enable the vertex array
    glEnableClientState( GL_VERTEX_ARRAY );

    // Tell OpenGL where the vertices are
    glVertexPointer( 3, GL_FLOAT, 0, &m_vertices[0] );
    glTexCoordPointer( 2, GL_FLOAT, 0, &m_textures[0] );

    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);

    glEnable(GL_TEXTURE_2D);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    genTexture();
}

void Scene::paintGL()
{
    // Clear the window with current clearing color
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    // Save matrix state and do the rotation
    glPushMatrix();
    glRotatef( xRot, 1.0f, 0.0f, 0.0f );
    glRotatef( yRot, 0.0f, 1.0f, 0.0f );

    //Draw the triangles, we pass in the number of indices, the data type of
    //the index array (GL_UNSIGNED_INT) and then the pointer to the start of
    //the array
    glDrawElements( GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT,
                    m_indices.data() );

    // Restore transformations
    glPopMatrix();
}

void Scene::resizeGL( int w, int h )
{
    // Prevent a divide by zero
    if( h == 0 ) {
        h = 1;
    }

    // Set Viewport to window dimensions
    glViewport( 0, 0, w, h );

    // Reset projection matrix stack
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    GLfloat nRange = 100.0f;

    // Establish clipping volume (left, right, bottom, top, near, far)
    if ( w <= h ) {
        glOrtho ( -nRange, nRange, -nRange*h/w, nRange*h/w,
                  -nRange, nRange );
    } else {
        glOrtho ( -nRange*w/h, nRange*w/h, -nRange, nRange,
                  -nRange, nRange );
    }

    // Reset Model view matrix stack
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
}

void Scene::keyPressEvent( QKeyEvent *event )
{
    switch ( event->key() ) {
        case Qt::Key_Up:
            xRot -= 5.0f;
            break;
        case Qt::Key_Down:
            xRot += 5.0f;
            break;
        case Qt::Key_Left:
            yRot -= 5.0f;
            break;
        case Qt::Key_Right:
            yRot += 5.0f;
            break;
    }

    if( xRot > 356.0f ) {
        xRot = 0.0f;
    }

    if( xRot < -1.0f ) {
        xRot = 355.0f;
    }

    if( yRot > 356.0f) {
        yRot = 0.0f;
    }

    if( yRot < -1.0f) {
        yRot = 355.0f;
    }

    updateGL();
}

void Scene::initSquare()
{
    // 0 1 2
    m_vertices.push_back( -50.0f );    // X
    m_vertices.push_back( -50.0f );    // Y
    m_vertices.push_back( 50.0f );      // Z

    m_vertices.push_back( 50.0f );
    m_vertices.push_back( -50.0f );
    m_vertices.push_back( 50.0f );

    m_vertices.push_back( -50.0f );
    m_vertices.push_back( 50.0f );
    m_vertices.push_back( 50.0f );

    // 3 4 5
    m_vertices.push_back( 50.0f );
    m_vertices.push_back( -50.0f );
    m_vertices.push_back( 50.0f );

    m_vertices.push_back( 50.0f );
    m_vertices.push_back( 50.0f );
    m_vertices.push_back( 50.0f );

    m_vertices.push_back( -50.0f );
    m_vertices.push_back( 50.0f );
    m_vertices.push_back( 50.0f );

    // 6 7 8
    m_vertices.push_back( 50.0f );
    m_vertices.push_back( -50.0f );
    m_vertices.push_back( 50.0f );

    m_vertices.push_back( 50.0f );
    m_vertices.push_back( -50.0f );
    m_vertices.push_back( -50.0f );

    m_vertices.push_back( 50.0f );
    m_vertices.push_back( 50.0f );
    m_vertices.push_back( 50.0f );

    // 9 10 11
    m_vertices.push_back( 50.0f );
    m_vertices.push_back( -50.0f );
    m_vertices.push_back( -50.0f );

    m_vertices.push_back( 50.0f );
    m_vertices.push_back( 50.0f );
    m_vertices.push_back( -50.0f );

    m_vertices.push_back( 50.0f );
    m_vertices.push_back( 50.0f );
    m_vertices.push_back( 50.0f );

    // 12 13 14
    m_vertices.push_back( 50.0f );
    m_vertices.push_back( -50.0f );
    m_vertices.push_back( -50.0f );

    m_vertices.push_back( -50.0f );
    m_vertices.push_back( -50.0f );
    m_vertices.push_back( -50.0f );

    m_vertices.push_back( 50.0f );
    m_vertices.push_back( 50.0f );
    m_vertices.push_back( -50.0f );

    // 15 16 17
    m_vertices.push_back( -50.0f );
    m_vertices.push_back( -50.0f );
    m_vertices.push_back( -50.0f );

    m_vertices.push_back( -50.0f );
    m_vertices.push_back( 50.0f );
    m_vertices.push_back( -50.0f );

    m_vertices.push_back( 50.0f );
    m_vertices.push_back( 50.0f );
    m_vertices.push_back( -50.0f );

    // 18 19 20
    m_vertices.push_back( -50.0f );
    m_vertices.push_back( -50.0f );
    m_vertices.push_back( -50.0f );

    m_vertices.push_back( -50.0f );
    m_vertices.push_back( -50.0f );
    m_vertices.push_back( 50.0f );

    m_vertices.push_back( -50.0f );
    m_vertices.push_back( 50.0f );
    m_vertices.push_back( -50.0f );

    // 21 22 23
    m_vertices.push_back( -50.0f );
    m_vertices.push_back( -50.0f );
    m_vertices.push_back( 50.0f );

    m_vertices.push_back( -50.0f );
    m_vertices.push_back( 50.0f );
    m_vertices.push_back( 50.0f );

    m_vertices.push_back( -50.0f );
    m_vertices.push_back( 50.0f );
    m_vertices.push_back( -50.0f );

    // 24 25 26
    m_vertices.push_back( -50.0f );
    m_vertices.push_back( -50.0f );
    m_vertices.push_back( -50.0f );

    m_vertices.push_back( 50.0f );
    m_vertices.push_back( -50.0f );
    m_vertices.push_back( -50.0f );

    m_vertices.push_back( -50.0f );
    m_vertices.push_back( -50.0f );
    m_vertices.push_back( 50.0f );

    // 27 28 29
    m_vertices.push_back( 50.0f );
    m_vertices.push_back( -50.0f );
    m_vertices.push_back( -50.0f );

    m_vertices.push_back( 50.0f );
    m_vertices.push_back( -50.0f );
    m_vertices.push_back( 50.0f );

    m_vertices.push_back( -50.0f );
    m_vertices.push_back( -50.0f );
    m_vertices.push_back( 50.0f );

    // 30 31 32
    m_vertices.push_back( -50.0f );
    m_vertices.push_back( 50.0f );
    m_vertices.push_back( 50.0f );

    m_vertices.push_back( 50.0f );
    m_vertices.push_back( 50.0f );
    m_vertices.push_back( 50.0f );

    m_vertices.push_back( -50.0f );
    m_vertices.push_back( 50.0f );
    m_vertices.push_back( -50.0f );

    // 33 34 35
    m_vertices.push_back( 50.0f );
    m_vertices.push_back( 50.0f );
    m_vertices.push_back( 50.0f );

    m_vertices.push_back( 50.0f );
    m_vertices.push_back( 50.0f );
    m_vertices.push_back( -50.0f );

    m_vertices.push_back( -50.0f );
    m_vertices.push_back( 50.0f );
    m_vertices.push_back( -50.0f );

    // Indices
    m_indices.push_back( 0 );
    m_indices.push_back( 1 );
    m_indices.push_back( 2 );

    m_indices.push_back( 3 );
    m_indices.push_back( 4 );
    m_indices.push_back( 5 );

    m_indices.push_back( 6 );
    m_indices.push_back( 7 );
    m_indices.push_back( 8 );

    m_indices.push_back( 9 );
    m_indices.push_back( 10 );
    m_indices.push_back( 11 );

    m_indices.push_back( 12 );
    m_indices.push_back( 13 );
    m_indices.push_back( 14 );

    m_indices.push_back( 15 );
    m_indices.push_back( 16 );
    m_indices.push_back( 17 );

    m_indices.push_back( 18 );
    m_indices.push_back( 19 );
    m_indices.push_back( 20 );

    m_indices.push_back( 21 );
    m_indices.push_back( 22 );
    m_indices.push_back( 23 );

    m_indices.push_back( 24 );
    m_indices.push_back( 25 );
    m_indices.push_back( 26 );

    m_indices.push_back( 27 );
    m_indices.push_back( 28 );
    m_indices.push_back( 29 );

    m_indices.push_back( 30 );
    m_indices.push_back( 31 );
    m_indices.push_back( 32 );

    m_indices.push_back( 33 );
    m_indices.push_back( 34 );
    m_indices.push_back( 35 );

    // Texture
    for ( size_t i = 0; i < 6; ++i ) {
        m_textures.push_back( 0.0f );
        m_textures.push_back( 0.0f );

        m_textures.push_back( 1.0f );
        m_textures.push_back( 0.0f );

        m_textures.push_back( 0.0f );
        m_textures.push_back( 1.0f );

        m_textures.push_back( 1.0f );
        m_textures.push_back( 0.0f );

        m_textures.push_back( 1.0f );
        m_textures.push_back( 1.0f );

        m_textures.push_back( 0.0f );
        m_textures.push_back( 1.0f );
    }
}

void Scene::genTexture()
{
    QImage image;
    image.load( QString(":/textures/picture1.jpg") );
    image = QGLWidget::convertToGLFormat( image );

    GLuint textureID;
    glGenTextures( 1, &textureID );

    glBindTexture( GL_TEXTURE_2D, textureID );

    glTexImage2D( GL_TEXTURE_2D, 0, 3,
                  ( GLsizei ) image.width(),
                  ( GLsizei ) image.height(), 0,
                  GL_RGBA, GL_UNSIGNED_BYTE, image.bits() );

    // дополнительные параметры текстурного объекта
    // задаём линейную фильтрацию вблизи:
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // задаём линейную фильтрацию вдали:
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // задаём: при фильтрации игнорируются тексели, выходящие за границу текстуры для s координаты
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    // задаём: при фильтрации игнорируются тексели, выходящие за границу текстуры для t координаты
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // задаём: цвет текселя полностью замещает цвет фрагмента фигуры
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
}
