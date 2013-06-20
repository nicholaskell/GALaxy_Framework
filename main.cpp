////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#define WIDTH 10
#define HEIGHT 10

int myBoard[HEIGHT][WIDTH];
int enemyBoard[HEIGHT][WIDTH];

void drawBoard() {

    glColor3f(0.0f, 0.50f, 0.60f);
    glTranslatef(0, 0, 2);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glTranslatef(0, 0, -2);

    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
    {
        glVertex3f(-100.0f, 100.0f, 0.0f);              // Top Left
        glVertex3f(100.0f, 100.0f, 0.0f);              // Top Right
        glVertex3f(100.0f, -100.0f, 0.0f);              // Bottom Right
        glVertex3f(-100.0f, -100.0f, 0.0f);              // Bottom Left
    }
    glEnd();



    glTranslatef(-100, 100, 0);

    GLfloat spacing = WIDTH * 2;

    glTranslatef(spacing / 2, -spacing / 2, 0);
    GLfloat xMoves = 0;
    GLfloat yMoves = 0;
    for (int h = 0; h < HEIGHT; h++) {
        for (int w = 0; w < WIDTH; w++) {

            if (myBoard[h][w] == 0) {
                glColor3f(0.0f, 0.0f, 0.0f);
            } else if (myBoard[h][w] == 1) {
                glColor3f(1.0f, 0.0f, 0.0f);
            } else {
                glColor3f(1.0f, 1.0f, 1.0f);
            }
            glDrawArrays(GL_TRIANGLES, 0, 36);
            glTranslatef(spacing, 0, 0);
            xMoves += spacing;

        }
        glTranslatef(-(spacing * WIDTH), -spacing, 0);
        xMoves += -(spacing * WIDTH);
        yMoves += -spacing;
    }
//    glTranslatef(-spacing / 2, spacing / 2, 0);
    glTranslatef(-xMoves,-yMoves, 0);
    glTranslatef(-spacing / 2, spacing / 2, 0);
    glTranslatef(100, -100, 0);

//    glTranslatef(100, spacing, 0);
//    glTranslatef(-100, 100, 0);
//    glTranslatef(spacing / 2, -spacing / 2, 0);

    glColor3f(1.0f, 0.50f, 0.60f);          // Set The Color To Red
    glTranslatef(0, 0, 3);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glTranslatef(0, 0, -3);
}

void drawBoardGame(float x, float y) {

    float viewAngle = x;
    glLoadIdentity();
    glTranslatef(0, -100, -300);

//    glTranslatef(x, y, 0);

//    glRotatef(viewAngle,1,0,0);

    glRotatef(viewAngle,1,0,0);
    glTranslatef(0,0,-100);
    drawBoard();
//    glLoadIdentity();
//    glRotatef(viewAngle,1,0,0);

    glTranslatef(0, 0, 100);
//    glTranslatef(x, y, 0);
//    glRotatef(viewAngle,1,0,0);

    glRotatef(-90, 1, 0, 0);
    glTranslatef(0, 0, -100);
    drawBoard();
}
////////////////////////////////////////////////////////////
/// Entry point of application
///
/// \return Application exit code
///
////////////////////////////////////////////////////////////
int main() {

    for (int h = 0; h < HEIGHT; h++) {
        for (int w = 0; w < WIDTH; w++) {
            myBoard[h][w] = (h * w) % 2;
            enemyBoard[h][w] = (h + w) % 2;
        }
    }

    // Request a 32-bits depth buffer when creating the window
    sf::ContextSettings contextSettings;
    contextSettings.depthBits = 32;

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600),
            "SFML graphics with OpenGL", sf::Style::Default, contextSettings);
    window.setVerticalSyncEnabled(true);

    // Make it the active window for OpenGL calls
    window.setActive();

    // Create a sprite for the background
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("resources/background.jpg"))
        return EXIT_FAILURE;
    sf::Sprite background(backgroundTexture);

    // Create some text to draw on top of our OpenGL object
    sf::Font font;
    if (!font.loadFromFile("resources/sansation.ttf"))
        return EXIT_FAILURE;
    sf::Text text("SFML / OpenGL demo", font);
    text.setColor(sf::Color(255, 255, 255, 170));
    text.setPosition(250.f, 450.f);

    // Load an OpenGL texture.
    // We could directly use a sf::Texture as an OpenGL texture (with its Bind() member function),
    // but here we want more control on it (generate mipmaps, ...) so we create a new one from an image
    GLuint texture = 0;
    {
        sf::Image image;
        if (!image.loadFromFile("resources/texture.jpg"))
            return EXIT_FAILURE;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, image.getSize().x,
                image.getSize().y, GL_RGBA, GL_UNSIGNED_BYTE,
                image.getPixelsPtr());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                GL_LINEAR_MIPMAP_LINEAR);
    }

    // Enable Z-buffer read and write
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glClearDepth(1.f);

    // Disable lighting
    glDisable(GL_LIGHTING);

    // Configure the viewport (the same size as the window)
    glViewport(0, 0, window.getSize().x, window.getSize().y);

    // Setup a perspective projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat ratio = static_cast<float>(window.getSize().x) / window.getSize().y;
    glFrustum(-ratio, ratio, -1.f, 1.f, 1.f, 500.f);
    glDepthRange(0.0, 1.0);

    // Bind the texture
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Define a 3D cube (6 faces made of 2 triangles composed by 3 vertices)
    GLfloat width = 5;
    GLfloat cube[] = {
    // positions    // texture coordinates
            -width, -width, -width, 0, 0, //
            -width, width, -width, 1, 0, //
            -width, -width, width, 0, 1, //
            -width, -width, width, 0, 1,  //
            -width, width, -width, 1, 0,  //
            -width, width, width, 1, 1, //

            width, -width, -width, 0, 0,  //
            width, width, -width, 1, 0,  //
            width, -width, width, 0, 1,  //
            width, -width, width, 0, 1,  //
            width, width, -width, 1, 0,  //
            width, width, width, 1, 1,

            -width, -width, -width, 0, 0,  //
            width, -width, -width, 1, 0,  //
            -width, -width, width, 0, 1,  //
            -width, -width, width, 0, 1,  //
            width, -width, -width, 1, 0,  //
            width, -width, width, 1, 1,

            -width, width, -width, 0, 0,  //
            width, width, -width, 1, 0,  //
            -width, width, width, 0, 1,  //
            -width, width, width, 0, 1,  //
            width, width, -width, 1, 0,  //
            width, width, width, 1, 1,

            -width, -width, -width, 0, 0,  //
            width, -width, -width, 1, 0,  //
            -width, width, -width, 0, 1,  //
            -width, width, -width, 0, 1,  //
            width, -width, -width, 1, 0,  //
            width, width, -width, 1, 1,

            -width, -width, width, 0, 0,  //
            width, -width, width, 1, 0,  //
            -width, width, width, 0, 1,  //
            -width, width, width, 0, 1,  //
            width, -width, width, 1, 0,  //
            width, width, width, 1, 1  //
            };

    // Enable position and texture coordinates vertex components
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glVertexPointer(3, GL_FLOAT, 5 * sizeof(GLfloat), cube);
    glTexCoordPointer(2, GL_FLOAT, 5 * sizeof(GLfloat), cube + 3);

    // Disable normal and color vertex components
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

    // Create a clock for measuring the time elapsed
    sf::Clock clock;

    // Start game loop
    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                window.close();

            // Escape key : exit
            if ((event.type == sf::Event::KeyPressed)
                    && (event.key.code == sf::Keyboard::Escape))
                window.close();

            // Adjust the viewport when the window is resized
            if (event.type == sf::Event::Resized)
                glViewport(0, 0, event.size.width, event.size.height);
        }

        // Draw the background
        window.pushGLStates();
        window.draw(background);
        window.popGLStates();

        // Clear the depth buffer
        glClear(GL_DEPTH_BUFFER_BIT);

        // We get the position of the mouse cursor, so that we can move the box accordingly
        float x = sf::Mouse::getPosition(window).x * 200.f / window.getSize().x
                - 100.f;
        float y = -sf::Mouse::getPosition(window).y * 200.f / window.getSize().y
                + 100.f;

        // Apply some transformations
        glMatrixMode(GL_MODELVIEW);
        drawBoardGame(x, y);

//        glTranslatef(-300, 30, 0);
//        for (int i = 0; i < 10; i++) {
//            glDrawArrays(GL_TRIANGLES, 0, 36);
//            glTranslatef(30, 0, 0);
//        }
//        glTranslatef(-300, 30, 0);
//        for (int i = 0; i < 10; i++) {
//            glDrawArrays(GL_TRIANGLES, 0, 36);
//            glTranslatef(30, 0, 0);
//        }
//        glTranslatef(-100, 30, 0);
//        glTranslatef(0, 0, 50);
//        glRotatef(-90, 1, 0, 0);
//        glTranslatef(0, 0, -100);
//
//////        glTranslatef(0, 0, -200);
//        glBegin(GL_QUADS);                      // Draw A Quad
//        {
//            glRotatef(.9, 1, 1, 0);
//            glColor3f(0.0f, 1.0f, 0.0f);          // Set The Color To Red
//            glVertex3f(-100.0f, 100.0f, 0.0f);              // Top Left
//            glVertex3f(100.0f, 100.0f, 0.0f);              // Top Right
//            glVertex3f(100.0f, -100.0f, 0.0f);              // Bottom Right
//            glVertex3f(-100.0f, -100.0f, 0.0f);              // Bottom Left
//        }
//        glEnd();                            // Done Drawing The Quad

//        glRotatef(clock.getElapsedTime().asSeconds() * 50.f, 1.f, 0.f, 0.f);
//        glRotatef(clock.getElapsedTime().asSeconds() * 30.f, 0.f, 1.f, 0.f);
//        glRotatef(clock.getElapsedTime().asSeconds() * 90.f, 0.f, 0.f, 1.f);

        // Draw the cube
//        glDrawArrays(GL_TRIANGLES, 0, 36);
//        glTranslatef(x + 40, y, -100.f);
//        glDrawArrays(GL_TRIANGLES, 0, 36);
//        glTranslatef(x, y + 40, 100.f);
//        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Draw some text on top of our OpenGL object
        window.pushGLStates();
        window.draw(text);
        window.popGLStates();

        // Finally, display the rendered frame on screen
        window.display();
    }

    // Don't forget to destroy our texture
    glDeleteTextures(1, &texture);

    return EXIT_SUCCESS;
}
