#include <windows.h>
#include <GL/glut.h>
#include <cmath>
#include <cstdlib>
#include <ctime>


float boatPosition = 1.25f;
float boatSpeed = -0.0025f;
float car1Position = 0.0f;
float car2Position = 0.0f;
float carSpeed = -0.0025f;


float timeOfDay = 0.0f;
float dayNightSpeed = 0.001f;

// Linear interpolation for colors
float lerp(float a, float b, float t) {
    return a + (b - a) * t;
}

void init() {
    srand(time(0));
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void timer(int value) {

    boatPosition += boatSpeed;
    if (boatPosition < -1.25f) {
        boatPosition = 1.25f;
        boatSpeed = -0.0025f - (rand() % 10) * 0.00025f;
    }


    car1Position += carSpeed;
    car2Position += carSpeed;

    if (car1Position < -0.55f) {
        car1Position = 0.0f;
        carSpeed = -0.0025f - (rand() % 10) * 0.0001f;
    }
    if (car2Position < -0.55f) {
        car2Position = 0.0f;
        carSpeed = -0.0025f - (rand() % 10) * 0.0001f;
    }


    timeOfDay += dayNightSpeed;
    if (timeOfDay > 1.0f) {
        timeOfDay = 1.0f;
        dayNightSpeed = -dayNightSpeed;
    } else if (timeOfDay < 0.0f) {
        timeOfDay = 0.0f;
        dayNightSpeed = -dayNightSpeed;
    }

    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

void display() {

    float skyR = lerp(200.0f / 255.0f, 0.0f / 255.0f, timeOfDay);
    float skyG = lerp(230.0f / 255.0f, 0.0f / 255.0f, timeOfDay);
    float skyB = lerp(255.0f / 255.0f, 51.0f / 255.0f, timeOfDay);
    glClearColor(skyR, skyG, skyB, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);


    glColor3ub((int)(lerp(200, 0, timeOfDay)), (int)(lerp(230, 0, timeOfDay)), (int)(lerp(255, 51, timeOfDay)));
    glBegin(GL_QUADS);
        glVertex2f(-1.25f, -0.4f);
        glVertex2f(1.25f, -0.4f);
        glVertex2f(1.25f, 1.0f);
        glVertex2f(-1.25f, 1.0f);
    glEnd();


    if (timeOfDay > 0.5f) {
        glColor4f(1.0f, 1.0f, 1.0f, (timeOfDay - 0.5f) * 2.0f);
        glPointSize(2.0f);
        glBegin(GL_POINTS);
            glVertex2f(-0.8f, 0.9f);
            glVertex2f(-0.5f, 0.7f);
            glVertex2f(0.0f, 0.85f);
            glVertex2f(0.4f, 0.95f);
            glVertex2f(0.8f, 0.8f);
            glVertex2f(-0.2f, 0.65f);
            glVertex2f(0.6f, 0.7f);
        glEnd();
    }


    if (timeOfDay > 0.5f) {
        glColor4f(1.0f, 1.0f, 1.0f, (timeOfDay - 0.5f) * 2.0f);
        float cx = 1.0f;
        float cy = 0.8f;
        float r = 0.12f;
        int triangleAmount = 40;
        glBegin(GL_TRIANGLE_FAN);
            glVertex2f(cx, cy);
            for(int i = 0; i <= triangleAmount; i++) {
                float angle = i * 2.0f * 3.14159f / triangleAmount;
                glVertex2f(cx + (r * cos(angle)), cy + (r * sin(angle)));
            }
        glEnd();
    } else {

        glColor4f(1.0f, 1.0f, 0.0f, 1.0f - (timeOfDay * 2.0f));
        float cx = 1.0f;
        float cy = 0.8f;
        float r = 0.12f;
        int triangleAmount = 40;
        glBegin(GL_TRIANGLE_FAN);
            glVertex2f(cx, cy);
            for(int i = 0; i <= triangleAmount; i++) {
                float angle = i * 2.0f * 3.14159f / triangleAmount;
                glVertex2f(cx + (r * cos(angle)), cy + (r * sin(angle)));
            }
        glEnd();
    }

    // The Shard (Glass Building)
    float shardR = lerp(0.6f, 0.4f, timeOfDay);
    float shardG = lerp(0.8f, 0.6f, timeOfDay);
    float shardB = lerp(1.0f, 0.8f, timeOfDay);
    glColor3f(shardR, shardG, shardB);
    glBegin(GL_POLYGON);
        glVertex2f(0.0f, 1.0f);
        glVertex2f(-0.34f, 0.0f);
        glVertex2f(0.1f, 0.3f);
    glEnd();

    glColor3f(lerp(0.7f, 0.5f, timeOfDay), lerp(0.9f, 0.7f, timeOfDay), lerp(1.0f, 0.8f, timeOfDay));
    glBegin(GL_POLYGON);
        glVertex2f(0.0f, 1.0f);
        glVertex2f(0.1f, 0.3f);
        glVertex2f(0.0f, 0.3f);
    glEnd();

    glColor3f(lerp(0.65f, 0.45f, timeOfDay), lerp(0.85f, 0.65f, timeOfDay), lerp(1.0f, 0.8f, timeOfDay));
    glBegin(GL_POLYGON);
        glVertex2f(-0.05f, 0.9f);
        glVertex2f(-0.2f, 0.3f);
        glVertex2f(-0.05f, 0.3f);
    glEnd();

    glColor3f(lerp(0.75f, 0.55f, timeOfDay), lerp(0.95f, 0.75f, timeOfDay), lerp(1.0f, 0.8f, timeOfDay));
    glBegin(GL_POLYGON);
        glVertex2f(0.05f, 0.85f);
        glVertex2f(0.2f, 0.3f);
        glVertex2f(0.05f, 0.3f);
    glEnd();

    // The Shard glowing windows
    if (timeOfDay > 0.5f) {
        glColor4f(1.0f, 1.0f, 0.8f, (timeOfDay - 0.5f) * 2.0f); // Fade in
        glBegin(GL_QUADS);
            glVertex2f(-0.1f, 0.4f);
            glVertex2f(-0.05f, 0.4f);
            glVertex2f(-0.05f, 0.45f);
            glVertex2f(-0.1f, 0.45f);
            glVertex2f(0.05f, 0.5f);
            glVertex2f(0.1f, 0.5f);
            glVertex2f(0.1f, 0.55f);
            glVertex2f(0.05f, 0.55f);
        glEnd();
    }

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(0.0f, 1.0f);
        glVertex2f(-0.34f, 0.0f);
        glVertex2f(0.1f, 0.3f);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glVertex2f(0.0f, 1.0f);
        glVertex2f(0.1f, 0.3f);
        glVertex2f(0.0f, 0.3f);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glVertex2f(-0.05f, 0.9f);
        glVertex2f(-0.2f, 0.3f);
        glVertex2f(-0.05f, 0.3f);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glVertex2f(0.05f, 0.85f);
        glVertex2f(0.2f, 0.3f);
        glVertex2f(0.05f, 0.3f);
    glEnd();

    // Right building
    glColor3f(lerp(0.0f, 0.0f, timeOfDay), lerp(0.0f, 0.0f, timeOfDay), lerp(0.0f, 0.0f, timeOfDay));
    glBegin(GL_POLYGON);
        glVertex2f(1.0f, 0.4f);
        glVertex2f(1.25f, 0.4f);
        glVertex2f(1.25f, -0.4f);
        glVertex2f(0.9f, -0.4f);
        glVertex2f(0.9f, 0.2f);
        glVertex2f(1.0f, 0.2f);
    glEnd();

    glColor3f(lerp(1.0f, 0.7f, timeOfDay), lerp(0.0f, 0.0f, timeOfDay), lerp(0.0f, 0.0f, timeOfDay));
    glBegin(GL_QUADS);
        glVertex2f(1.0f, -0.4f);
        glVertex2f(1.15f, -0.4f);
        glVertex2f(1.15f, -0.3f);
        glVertex2f(1.0f, -0.3f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
        glVertex2f(1.075f, -0.4f);
        glVertex2f(1.075f, -0.3f);
    glEnd();

    // Right building windows
    glColor3f(lerp(0.8f, 0.6f, timeOfDay), lerp(0.8f, 0.6f, timeOfDay), lerp(0.0f, 0.0f, timeOfDay));
    glBegin(GL_QUADS);
        glVertex2f(0.95f, -0.2f);
        glVertex2f(1.0f, -0.2f);
        glVertex2f(1.0f, -0.25f);
        glVertex2f(0.95f, -0.25f);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(1.05f, -0.2f);
        glVertex2f(1.1f, -0.2f);
        glVertex2f(1.1f, -0.25f);
        glVertex2f(1.05f, -0.25f);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(1.15f, -0.2f);
        glVertex2f(1.2f, -0.2f);
        glVertex2f(1.2f, -0.25f);
        glVertex2f(1.15f, -0.25f);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(0.95f, -0.15f);
        glVertex2f(1.0f, -0.15f);
        glVertex2f(1.0f, -0.1f);
        glVertex2f(0.95f, -0.1f);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(1.05f, -0.15f);
        glVertex2f(1.1f, -0.15f);
        glVertex2f(1.1f, -0.1f);
        glVertex2f(1.05f, -0.1f);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(1.15f, -0.15f);
        glVertex2f(1.2f, -0.15f);
        glVertex2f(1.2f, -0.1f);
        glVertex2f(1.15f, -0.1f);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(0.95f, -0.05f);
        glVertex2f(1.0f, -0.05f);
        glVertex2f(1.0f, 0.0f);
        glVertex2f(0.95f, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(1.05f, -0.05f);
        glVertex2f(1.1f, -0.05f);
        glVertex2f(1.1f, 0.0f);
        glVertex2f(1.05f, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(1.15f, -0.05f);
        glVertex2f(1.2f, -0.05f);
        glVertex2f(1.2f, 0.0f);
        glVertex2f(1.15f, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(0.95f, 0.05f);
        glVertex2f(1.0f, 0.05f);
        glVertex2f(1.0f, 0.1f);
        glVertex2f(0.95f, 0.1f);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(1.05f, 0.05f);
        glVertex2f(1.1f, 0.05f);
        glVertex2f(1.1f, 0.1f);
        glVertex2f(1.05f, 0.1f);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(1.15f, 0.05f);
        glVertex2f(1.2f, 0.05f);
        glVertex2f(1.2f, 0.1f);
        glVertex2f(1.15f, 0.1f);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(0.95f, 0.15f);
        glVertex2f(1.0f, 0.15f);
        glVertex2f(1.0f, 0.2f);
        glVertex2f(0.95f, 0.2f);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(1.05f, 0.15f);
        glVertex2f(1.1f, 0.15f);
        glVertex2f(1.1f, 0.2f);
        glVertex2f(1.05f, 0.2f);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(1.15f, 0.15f);
        glVertex2f(1.2f, 0.15f);
        glVertex2f(1.2f, 0.2f);
        glVertex2f(1.15f, 0.2f);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(1.05f, 0.25f);
        glVertex2f(1.1f, 0.25f);
        glVertex2f(1.1f, 0.3f);
        glVertex2f(1.05f, 0.3f);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(1.15f, 0.25f);
        glVertex2f(1.2f, 0.25f);
        glVertex2f(1.2f, 0.3f);
        glVertex2f(1.15f, 0.3f);
    glEnd();

    // Right building glowing windows at night
    if (timeOfDay > 0.5f) {
        glColor4f(1.0f, 1.0f, 0.8f, (timeOfDay - 0.5f) * 2.0f);
        glBegin(GL_QUADS);
            glVertex2f(0.95f, -0.2f);
            glVertex2f(1.0f, -0.2f);
            glVertex2f(1.0f, -0.25f);
            glVertex2f(0.95f, -0.25f);
            glVertex2f(1.05f, -0.15f);
            glVertex2f(1.1f, -0.15f);
            glVertex2f(1.1f, -0.1f);
            glVertex2f(1.05f, -0.1f);
            glVertex2f(1.15f, -0.05f);
            glVertex2f(1.2f, -0.05f);
            glVertex2f(1.2f, 0.0f);
            glVertex2f(1.15f, 0.0f);
            glVertex2f(0.95f, 0.05f);
            glVertex2f(1.0f, 0.05f);
            glVertex2f(1.0f, 0.1f);
            glVertex2f(0.95f, 0.1f);
        glEnd();
    }

    // Right Middle building
    glColor3f(lerp(0.82f, 0.6f, timeOfDay), lerp(0.41f, 0.2f, timeOfDay), lerp(0.12f, 0.0f, timeOfDay));
    glBegin(GL_POLYGON);
        glVertex2f(0.5f, -0.4f);
        glVertex2f(0.9f, -0.4f);
        glVertex2f(0.9f, 0.3f);
        glVertex2f(0.5f, 0.3f);
    glEnd();

    glColor3f(lerp(0.82f, 0.6f, timeOfDay), lerp(0.41f, 0.2f, timeOfDay), lerp(0.12f, 0.0f, timeOfDay));
    glBegin(GL_POLYGON);
        glVertex2f(0.6f, -0.2f);
        glVertex2f(0.8f, -0.2f);
        glVertex2f(0.8f, 0.1f);
        glVertex2f(0.6f, 0.1f);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(0.6f, -0.15f);
        glVertex2f(0.8f, -0.15f);
        glVertex2f(0.8f, 0.05f);
        glVertex2f(0.6f, 0.05f);
    glEnd();

    glColor3f(lerp(0.75f, 0.55f, timeOfDay), lerp(0.75f, 0.55f, timeOfDay), lerp(0.7f, 0.5f, timeOfDay));
    glBegin(GL_POLYGON);
        glVertex2f(0.65f, -0.15f);
        glVertex2f(0.75f, -0.15f);
        glVertex2f(0.75f, 0.05f);
        glVertex2f(0.65f, 0.05f);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(0.65f, -0.15f);
        glVertex2f(0.70f, -0.15f);
        glVertex2f(0.70f, 0.05f);
        glVertex2f(0.65f, 0.05f);
    glEnd();

    // Right Middle building glowing windows at night
    if (timeOfDay > 0.5f) {
        glColor4f(1.0f, 1.0f, 0.8f, (timeOfDay - 0.5f) * 2.0f);
        glBegin(GL_POLYGON);
            glVertex2f(0.5f, -0.2f);
            glVertex2f(0.55f, -0.2f);
            glVertex2f(0.55f, -0.15f);
            glVertex2f(0.5f, -0.15f);
        glEnd();
        glBegin(GL_POLYGON);
            glVertex2f(0.5f, -0.1f);
            glVertex2f(0.55f, -0.1f);
            glVertex2f(0.55f, -0.05f);
            glVertex2f(0.5f, -0.05f);
        glEnd();
        glBegin(GL_POLYGON);
            glVertex2f(0.5f, 0.0f);
            glVertex2f(0.55f, 0.0f);
            glVertex2f(0.55f, 0.05f);
            glVertex2f(0.5f, 0.05f);
        glEnd();
        glBegin(GL_POLYGON);
            glVertex2f(0.85f, 0.1f);
            glVertex2f(0.9f, 0.1f);
            glVertex2f(0.9f, 0.15f);
            glVertex2f(0.85f, 0.15f);
        glEnd();
    }

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(0.6f, -0.2f);
        glVertex2f(0.8f, -0.2f);
        glVertex2f(0.8f, 0.1f);
        glVertex2f(0.6f, 0.1f);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glVertex2f(0.6f, -0.15f);
        glVertex2f(0.8f, -0.15f);
        glVertex2f(0.8f, 0.05f);
        glVertex2f(0.6f, 0.05f);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glVertex2f(0.65f, -0.15f);
        glVertex2f(0.75f, -0.15f);
        glVertex2f(0.75f, 0.05f);
        glVertex2f(0.65f, 0.05f);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glVertex2f(0.65f, -0.15f);
        glVertex2f(0.70f, -0.15f);
        glVertex2f(0.70f, 0.05f);
        glVertex2f(0.65f, 0.05f);
    glEnd();

    glColor3f(lerp(0.4f, 0.2f, timeOfDay), lerp(0.2f, 0.1f, timeOfDay), lerp(0.0f, 0.0f, timeOfDay));
    glBegin(GL_LINE_LOOP);
        glVertex2f(0.6f, -0.4f);
        glVertex2f(0.8f, -0.4f);
        glVertex2f(0.8f, -0.3f);
        glVertex2f(0.6f, -0.3f);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glVertex2f(0.6f, -0.4f);
        glVertex2f(0.7f, -0.4f);
        glVertex2f(0.7f, -0.3f);
        glVertex2f(0.6f, -0.3f);
    glEnd();

    glColor3f(lerp(0.75f, 0.55f, timeOfDay), lerp(0.75f, 0.55f, timeOfDay), lerp(0.7f, 0.5f, timeOfDay));
    glBegin(GL_POLYGON);
        glVertex2f(0.5f, -0.2f);
        glVertex2f(0.55f, -0.2f);
        glVertex2f(0.55f, -0.15f);
        glVertex2f(0.5f, -0.15f);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(0.5f, -0.1f);
        glVertex2f(0.55f, -0.1f);
        glVertex2f(0.55f, -0.05f);
        glVertex2f(0.5f, -0.05f);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(0.5f, 0.0f);
        glVertex2f(0.55f, 0.0f);
        glVertex2f(0.55f, 0.05f);
        glVertex2f(0.5f, 0.05f);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(0.5f, 0.1f);
        glVertex2f(0.55f, 0.1f);
        glVertex2f(0.55f, 0.15f);
        glVertex2f(0.5f, 0.15f);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(0.85f, -0.2f);
        glVertex2f(0.9f, -0.2f);
        glVertex2f(0.9f, -0.15f);
        glVertex2f(0.85f, -0.15f);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(0.85f, -0.1f);
        glVertex2f(0.9f, -0.1f);
        glVertex2f(0.9f, -0.05f);
        glVertex2f(0.85f, -0.05f);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(0.85f, 0.0f);
        glVertex2f(0.9f, 0.0f);
        glVertex2f(0.9f, 0.05f);
        glVertex2f(0.85f, 0.05f);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(0.85f, 0.1f);
        glVertex2f(0.9f, 0.1f);
        glVertex2f(0.9f, 0.15f);
        glVertex2f(0.85f, 0.15f);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(0.6f, 0.2f);
        glVertex2f(0.8f, 0.2f);
        glVertex2f(0.8f, 0.25f);
        glVertex2f(0.6f, 0.25f);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(0.65f, 0.2f);
        glVertex2f(0.75f, 0.2f);
        glVertex2f(0.75f, 0.25f);
        glVertex2f(0.65f, 0.25f);
    glEnd();

    // Middle building
    glColor3f(lerp(0.8f, 0.6f, timeOfDay), lerp(0.7f, 0.5f, timeOfDay), lerp(0.5f, 0.3f, timeOfDay));
    glBegin(GL_QUADS);
        glVertex2f(-0.3f, -0.4f);
        glVertex2f(-0.15f, -0.4f);
        glVertex2f(-0.15f, 0.15f);
        glVertex2f(-0.3f, 0.15f);
    glEnd();

    glColor3f(lerp(0.55f, 0.35f, timeOfDay), lerp(0.35f, 0.15f, timeOfDay), lerp(0.2f, 0.0f, timeOfDay));
    glBegin(GL_QUADS);
        glVertex2f(-0.24f, -0.4f);
        glVertex2f(-0.21f, -0.4f);
        glVertex2f(-0.21f, -0.32f);
        glVertex2f(-0.24f, -0.32f);
    glEnd();

    glColor3f(lerp(0.45f, 0.25f, timeOfDay), lerp(0.25f, 0.1f, timeOfDay), lerp(0.15f, 0.0f, timeOfDay));
    glBegin(GL_QUADS);
        glVertex2f(-0.24f, -0.4f);
        glVertex2f(-0.235f, -0.4f);
        glVertex2f(-0.235f, -0.32f);
        glVertex2f(-0.24f, -0.32f);
    glEnd();

    glColor3f(lerp(0.5f, 0.3f, timeOfDay), lerp(0.85f, 0.65f, timeOfDay), lerp(0.95f, 0.75f, timeOfDay));
    float windowWidth = 0.025f;
    float windowHeight = 0.02f;
    float startX[2] = {-0.285f, -0.205f};
    float startY[4] = {0.12f, 0.05f, -0.02f, -0.09f};

    for(int row=0; row<4; row++){
        for(int col=0; col<2; col++){
            glBegin(GL_QUADS);
                glVertex2f(startX[col], startY[row]);
                glVertex2f(startX[col]+windowWidth, startY[row]);
                glVertex2f(startX[col]+windowWidth, startY[row]-windowHeight);
                glVertex2f(startX[col], startY[row]-windowHeight);
            glEnd();

            // Glowing effect for windows
            if (timeOfDay > 0.5f) {
                glColor4f(1.0f, 1.0f, 0.8f, (timeOfDay - 0.5f) * 2.0f);
                glBegin(GL_QUADS);
                    glVertex2f(startX[col]+0.005f, startY[row]-0.005f);
                    glVertex2f(startX[col]+0.02f, startY[row]-0.005f);
                    glVertex2f(startX[col]+0.02f, startY[row]-0.01f);
                    glVertex2f(startX[col]+0.005f, startY[row]-0.01f);
                glEnd();
                glColor3f(lerp(0.5f, 0.3f, timeOfDay), lerp(0.85f, 0.65f, timeOfDay), lerp(0.95f, 0.75f, timeOfDay));
            } else {
                glColor3f(1.0f, 1.0f, 1.0f);
                glBegin(GL_QUADS);
                    glVertex2f(startX[col]+0.005f, startY[row]-0.005f);
                    glVertex2f(startX[col]+0.02f, startY[row]-0.005f);
                    glVertex2f(startX[col]+0.02f, startY[row]-0.01f);
                    glVertex2f(startX[col]+0.005f, startY[row]-0.01f);
                glEnd();
                glColor3f(lerp(0.5f, 0.3f, timeOfDay), lerp(0.85f, 0.65f, timeOfDay), lerp(0.95f, 0.75f, timeOfDay));
            }
        }
    }

    glColor3f(lerp(0.7f, 0.5f, timeOfDay), lerp(0.6f, 0.4f, timeOfDay), lerp(0.45f, 0.25f, timeOfDay));
    glBegin(GL_QUADS);
        glVertex2f(-0.305f, 0.15f);
        glVertex2f(-0.145f, 0.15f);
        glVertex2f(-0.145f, 0.17f);
        glVertex2f(-0.305f, 0.17f);
    glEnd();

    glColor3f(lerp(0.9f, 0.7f, timeOfDay), lerp(0.8f, 0.6f, timeOfDay), lerp(0.6f, 0.4f, timeOfDay));
    glBegin(GL_QUADS);
        glVertex2f(-0.305f, 0.165f);
        glVertex2f(-0.145f, 0.165f);
        glVertex2f(-0.145f, 0.17f);
        glVertex2f(-0.305f, 0.17f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(-0.3f, -0.4f);
        glVertex2f(-0.15f, -0.4f);
        glVertex2f(-0.15f, 0.15f);
        glVertex2f(-0.3f, 0.15f);
    glEnd();

    // Left middle building
    glColor3f(lerp(0.0f, 0.0f, timeOfDay), lerp(0.5f, 0.3f, timeOfDay), lerp(0.5f, 0.3f, timeOfDay));
    glBegin(GL_POLYGON);
        glVertex2f(-0.15f, -0.4f);
        glVertex2f(0.5f, -0.4f);
        glVertex2f(0.5f, 0.3f);
        glVertex2f(-0.15f, 0.3f);
    glEnd();

    glColor3f(lerp(0.55f, 0.35f, timeOfDay), lerp(0.35f, 0.15f, timeOfDay), lerp(0.2f, 0.0f, timeOfDay));
    glBegin(GL_QUADS);
        glVertex2f(0.1f, -0.4f);
        glVertex2f(0.25f, -0.4f);
        glVertex2f(0.25f, -0.3f);
        glVertex2f(0.1f, -0.3f);
    glEnd();

    glColor3f(lerp(0.45f, 0.25f, timeOfDay), lerp(0.25f, 0.1f, timeOfDay), lerp(0.15f, 0.0f, timeOfDay));
    glBegin(GL_QUADS);
        glVertex2f(0.1f, -0.4f);
        glVertex2f(0.175f, -0.4f);
        glVertex2f(0.175f, -0.3f);
        glVertex2f(0.1f, -0.3f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
        glVertex2f(0.175f, -0.4f);
        glVertex2f(0.175f, -0.3f);
    glEnd();

    glColor3f(lerp(0.5f, 0.3f, timeOfDay), lerp(0.5f, 0.3f, timeOfDay), lerp(0.5f, 0.3f, timeOfDay));
    glBegin(GL_POLYGON);
        glVertex2f(-0.1f, -0.1f);
        glVertex2f(0.0f, -0.1f);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(-0.1f, 0.0f);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(0.05f, -0.1f);
        glVertex2f(0.15f, -0.1f);
        glVertex2f(0.15f, 0.0f);
        glVertex2f(0.05f, 0.0f);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(0.2f, -0.1f);
        glVertex2f(0.3f, -0.1f);
        glVertex2f(0.3f, 0.0f);
        glVertex2f(0.2f, 0.0f);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(0.35f, -0.1f);
        glVertex2f(0.45f, -0.1f);
        glVertex2f(0.45f, 0.0f);
        glVertex2f(0.35f, 0.0f);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(-0.1f, 0.1f);
        glVertex2f(0.0f, 0.1f);
        glVertex2f(0.0f, 0.2f);
        glVertex2f(-0.1f, 0.2f);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(0.05f, 0.1f);
        glVertex2f(0.15f, 0.1f);
        glVertex2f(0.15f, 0.2f);
        glVertex2f(0.05f, 0.2f);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(0.2f, 0.1f);
        glVertex2f(0.3f, 0.1f);
        glVertex2f(0.3f, 0.2f);
        glVertex2f(0.2f, 0.2f);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(0.35f, 0.1f);
        glVertex2f(0.45f, 0.1f);
        glVertex2f(0.45f, 0.2f);
        glVertex2f(0.35f, 0.2f);
    glEnd();

    // Left middle building glowing windows
    if (timeOfDay > 0.5f) {
        glColor4f(1.0f, 1.0f, 0.8f, (timeOfDay - 0.5f) * 2.0f);
        glBegin(GL_POLYGON);
            glVertex2f(-0.1f, -0.1f);
            glVertex2f(0.0f, -0.1f);
            glVertex2f(0.0f, 0.0f);
            glVertex2f(-0.1f, 0.0f);
        glEnd();
        glBegin(GL_POLYGON);
            glVertex2f(0.05f, 0.1f);
            glVertex2f(0.15f, 0.1f);
            glVertex2f(0.15f, 0.2f);
            glVertex2f(0.05f, 0.2f);
        glEnd();
    }

    // ROAD
    glColor3f(lerp(0.2f, 0.1f, timeOfDay), lerp(0.2f, 0.1f, timeOfDay), lerp(0.2f, 0.1f, timeOfDay));
    glBegin(GL_QUADS);
        glVertex2f(-1.25f, 0.3f);
        glVertex2f(-0.7f, -0.15f);
        glVertex2f(-0.7f, 0.05f);
        glVertex2f(-1.25f, 0.5f);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(-1.25f, 0.05f);
        glVertex2f(-0.7f, -0.4f);
        glVertex2f(-0.7f, -0.2f);
        glVertex2f(-1.25f, 0.25f);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
        glVertex2f(-1.25f, 0.15f);
        glVertex2f(-0.7f, -0.3f);
    glEnd();

    glBegin(GL_LINES);
        glVertex2f(-1.25f, 0.4f);
        glVertex2f(-0.7f, -0.05f);
    glEnd();

    // Grass
    glColor3f(lerp(0.3f, 0.15f, timeOfDay), lerp(0.7f, 0.35f, timeOfDay), lerp(0.0f, 0.0f, timeOfDay));
    glBegin(GL_TRIANGLES);
        glVertex2f(-1.25f, 0.05f);
        glVertex2f(-1.25f, -0.4f);
        glVertex2f(-0.7f, -0.4f);
    glEnd();

    glColor3f(lerp(0.4f, 0.2f, timeOfDay), lerp(0.8f, 0.4f, timeOfDay), lerp(0.0f, 0.0f, timeOfDay));
    glBegin(GL_QUADS);
        glVertex2f(-1.25f, 0.25f);
        glVertex2f(-0.7f, -0.2f);
        glVertex2f(-0.7f, -0.15f);
        glVertex2f(-1.25f, 0.3f);
    glEnd();

    glColor3f(lerp(0.5f, 0.25f, timeOfDay), lerp(0.9f, 0.45f, timeOfDay), lerp(0.1f, 0.0f, timeOfDay));
    glBegin(GL_QUADS);
        glVertex2f(-1.25f, 0.5f);
        glVertex2f(-0.7f, 0.05f);
        glVertex2f(-0.7f, 0.2f);
        glVertex2f(-1.25f, 0.65f);
    glEnd();

    // Tree 1
    glColor3f(lerp(0.55f, 0.35f, timeOfDay), lerp(0.27f, 0.1f, timeOfDay), lerp(0.07f, 0.0f, timeOfDay));
    glBegin(GL_QUADS);
        glVertex2f(-1.20f, -0.4f);
        glVertex2f(-1.15f, -0.4f);
        glVertex2f(-1.15f, -0.3f);
        glVertex2f(-1.20f, -0.3f);
    glEnd();

    glColor3f(lerp(0.1f, 0.05f, timeOfDay), lerp(0.4f, 0.2f, timeOfDay), lerp(0.05f, 0.0f, timeOfDay));
    glBegin(GL_TRIANGLES);
        glVertex2f(-1.175f, -0.2f);
        glVertex2f(-1.25f, -0.3f);
        glVertex2f(-1.10f, -0.3f);
    glEnd();

    glBegin(GL_TRIANGLES);
        glVertex2f(-1.175f, -0.15f);
        glVertex2f(-1.25f, -0.25f);
        glVertex2f(-1.10f, -0.25f);
    glEnd();

    glBegin(GL_TRIANGLES);
        glVertex2f(-1.175f, -0.1f);
        glVertex2f(-1.25f, -0.2f);
        glVertex2f(-1.10f, -0.2f);
    glEnd();

    // Tree 2
    glColor3f(lerp(0.55f, 0.35f, timeOfDay), lerp(0.27f, 0.1f, timeOfDay), lerp(0.07f, 0.0f, timeOfDay));
    glBegin(GL_QUADS);
        glVertex2f(-1.05f, -0.4f);
        glVertex2f(-1.0f, -0.4f);
        glVertex2f(-1.0f, -0.3f);
        glVertex2f(-1.05f, -0.3f);
    glEnd();

    glColor3f(lerp(0.1f, 0.05f, timeOfDay), lerp(0.4f, 0.2f, timeOfDay), lerp(0.05f, 0.0f, timeOfDay));
    glBegin(GL_TRIANGLES);
        glVertex2f(-1.025f, -0.2f);
        glVertex2f(-1.1f, -0.3f);
        glVertex2f(-0.95f, -0.3f);
    glEnd();

    glBegin(GL_TRIANGLES);
        glVertex2f(-1.025f, -0.15f);
        glVertex2f(-1.1f, -0.25f);
        glVertex2f(-0.95f, -0.25f);
    glEnd();

    // Top tree 1
    glColor3f(lerp(0.55f, 0.35f, timeOfDay), lerp(0.27f, 0.1f, timeOfDay), lerp(0.07f, 0.0f, timeOfDay));
    glBegin(GL_QUADS);
        glVertex2f(-1.2f, 0.5f);
        glVertex2f(-1.15f, 0.5f);
        glVertex2f(-1.15f, 0.6f);
        glVertex2f(-1.2f, 0.6f);
    glEnd();

    glColor3f(lerp(0.1f, 0.05f, timeOfDay), lerp(0.4f, 0.2f, timeOfDay), lerp(0.05f, 0.0f, timeOfDay));
    glBegin(GL_TRIANGLES);
        glVertex2f(-1.175f, 0.7f);
        glVertex2f(-1.25f, 0.6f);
        glVertex2f(-1.1f, 0.6f);
    glEnd();

    glBegin(GL_TRIANGLES);
        glVertex2f(-1.175f, 0.75f);
        glVertex2f(-1.25f, 0.65f);
        glVertex2f(-1.1f, 0.65f);
    glEnd();

    // Top tree 2
    glColor3f(lerp(0.55f, 0.35f, timeOfDay), lerp(0.27f, 0.1f, timeOfDay), lerp(0.07f, 0.0f, timeOfDay));
    glBegin(GL_QUADS);
        glVertex2f(-1.0f, 0.35f);
        glVertex2f(-0.95f, 0.35f);
        glVertex2f(-0.95f, 0.45f);
        glVertex2f(-1.0f, 0.45f);
    glEnd();

    glColor3f(lerp(0.1f, 0.05f, timeOfDay), lerp(0.4f, 0.2f, timeOfDay), lerp(0.05f, 0.0f, timeOfDay));
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.975f, 0.55f);
        glVertex2f(-1.05f, 0.45f);
        glVertex2f(-0.9f, 0.45f);
    glEnd();

    glBegin(GL_TRIANGLES);
        glVertex2f(-0.975f, 0.6f);
        glVertex2f(-1.05f, 0.5f);
        glVertex2f(-0.9f, 0.5f);
    glEnd();

    glBegin(GL_TRIANGLES);
        glVertex2f(-0.975f, 0.65f);
        glVertex2f(-1.05f, 0.55f);
        glVertex2f(-0.9f, 0.55f);
    glEnd();

    // Top tree 3
    glColor3f(lerp(0.55f, 0.35f, timeOfDay), lerp(0.27f, 0.1f, timeOfDay), lerp(0.07f, 0.0f, timeOfDay));
    glBegin(GL_QUADS);
        glVertex2f(-0.8f, 0.18f);
        glVertex2f(-0.75f, 0.18f);
        glVertex2f(-0.75f, 0.28f);
        glVertex2f(-0.8f, 0.28f);
    glEnd();

    glColor3f(lerp(0.1f, 0.05f, timeOfDay), lerp(0.4f, 0.2f, timeOfDay), lerp(0.05f, 0.0f, timeOfDay));
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.775f, 0.38f);
        glVertex2f(-0.85f, 0.28f);
        glVertex2f(-0.7f, 0.28f);
    glEnd();

    glBegin(GL_TRIANGLES);
        glVertex2f(-0.775f, 0.43f);
        glVertex2f(-0.85f, 0.33f);
        glVertex2f(-0.7f, 0.33f);
    glEnd();

    glBegin(GL_TRIANGLES);
        glVertex2f(-0.775f, 0.48f);
        glVertex2f(-0.85f, 0.38f);
        glVertex2f(-0.7f, 0.38f);
    glEnd();

    // River
    glBegin(GL_QUADS);
        glColor3f(lerp(0.4f, 0.0f, timeOfDay), lerp(0.7f, 0.3f, timeOfDay), lerp(0.95f, 0.6f, timeOfDay));
        glVertex2f(-1.25f, -0.45f);
        glVertex2f(1.25f, -0.45f);
        glColor3f(lerp(0.0f, 0.0f, timeOfDay), lerp(0.3f, 0.15f, timeOfDay), lerp(0.6f, 0.3f, timeOfDay));
        glVertex2f(1.25f, -1.0f);
        glVertex2f(-1.25f, -1.0f);
    glEnd();

    glColor3f(lerp(0.6f, 0.4f, timeOfDay), lerp(0.85f, 0.65f, timeOfDay), lerp(1.0f, 0.8f, timeOfDay));
    for(float x = -1.25f; x < 1.25f; x += 0.1f) {
        glBegin(GL_LINES);
            glVertex2f(x, -0.55f + 0.02f * sin(x*5));
            glVertex2f(x + 0.1f, -0.55f + 0.02f * sin((x+0.1f)*5));
        glEnd();
    }

    // Boat
    glPushMatrix();
    glTranslatef(boatPosition, 0.0f, 0.0f);
    glColor3f(lerp(0.55f, 0.35f, timeOfDay), lerp(0.27f, 0.1f, timeOfDay), lerp(0.07f, 0.0f, timeOfDay));
    glBegin(GL_POLYGON);
        glVertex2f(-0.22f, -0.80f);
        glVertex2f(0.22f, -0.80f);
        glVertex2f(0.18f, -0.92f);
        glVertex2f(-0.18f, -0.92f);
    glEnd();

    glColor3f(lerp(0.95f, 0.75f, timeOfDay), lerp(0.95f, 0.75f, timeOfDay), lerp(0.95f, 0.75f, timeOfDay));
    glBegin(GL_POLYGON);
        glVertex2f(-0.10f, -0.80f);
        glVertex2f(0.10f, -0.80f);
        glVertex2f(0.08f, -0.72f);
        glVertex2f(-0.08f, -0.72f);
    glEnd();

    glColor3f(lerp(0.2f, 0.1f, timeOfDay), lerp(0.7f, 0.5f, timeOfDay), lerp(1.0f, 0.8f, timeOfDay));
    glBegin(GL_QUADS);
        glVertex2f(-0.07f, -0.78f);
        glVertex2f(-0.04f, -0.78f);
        glVertex2f(-0.04f, -0.74f);
        glVertex2f(-0.07f, -0.74f);
        glVertex2f(0.04f, -0.78f);
        glVertex2f(0.07f, -0.78f);
        glVertex2f(0.07f, -0.74f);
        glVertex2f(0.04f, -0.74f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
        glVertex2f(0.0f, -0.72f);
        glVertex2f(0.0f, -0.55f);
    glEnd();

    glColor3f(lerp(1.0f, 0.8f, timeOfDay), lerp(1.0f, 0.8f, timeOfDay), lerp(0.2f, 0.0f, timeOfDay));
    glBegin(GL_TRIANGLES);
        glVertex2f(0.0f, -0.55f);
        glVertex2f(0.0f, -0.72f);
        glVertex2f(0.12f, -0.72f);
    glEnd();
    glPopMatrix();

    // Car 1
    glPushMatrix();
    float x1 = -0.7f, y1 = -0.15f;
    float x2 = -1.25f, y2 = 0.3f;
    float t = -car1Position / 0.55f;
    float carX = x1 + car1Position;
    float carY = y1 + t * (y2 - y1) + 0.015f;
    float dx = x2 - x1;
    float dy = y2 - y1;
    float angle = atan2(dy, dx) * 180 / 3.14159f;
    glTranslatef(carX, carY, 0.0f);
    glRotatef(angle + 180.0f, 0.0f, 0.0f, 1.0f);

    glColor3f(lerp(0.8f, 0.6f, timeOfDay), lerp(0.0f, 0.0f, timeOfDay), lerp(0.0f, 0.0f, timeOfDay));
    glBegin(GL_QUADS);
        glVertex2f(-0.06f, 0.0f);
        glVertex2f(0.06f, 0.0f);
        glVertex2f(0.06f, 0.03f);
        glVertex2f(-0.06f, 0.03f);
    glEnd();

    glColor3f(lerp(0.7f, 0.5f, timeOfDay), lerp(0.0f, 0.0f, timeOfDay), lerp(0.0f, 0.0f, timeOfDay));
    glBegin(GL_QUADS);
        glVertex2f(-0.045f, 0.03f);
        glVertex2f(0.045f, 0.03f);
        glVertex2f(0.04f, 0.045f);
        glVertex2f(-0.04f, 0.045f);
    glEnd();

    glColor3f(lerp(0.6f, 0.4f, timeOfDay), lerp(0.9f, 0.7f, timeOfDay), lerp(1.0f, 0.8f, timeOfDay));
    glBegin(GL_QUADS);
        glVertex2f(-0.04f, 0.032f);
        glVertex2f(0.04f, 0.032f);
        glVertex2f(0.035f, 0.043f);
        glVertex2f(-0.035f, 0.043f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    float rw = 0.01f;
    glBegin(GL_POLYGON);
        for(int i = 0; i < 360; i += 15) {
            float theta = i * 3.14159f / 180;
            glVertex2f(0.045f + rw * cos(theta), 0.0f + rw * sin(theta));
        }
    glEnd();

    glBegin(GL_POLYGON);
        for(int i = 0; i < 360; i += 15) {
            float theta = i * 3.14159f / 180;
            glVertex2f(-0.045f + rw * cos(theta), 0.0f + rw * sin(theta));
        }
    glEnd();

    glColor3f(1.0f, 1.0f, 0.5f);
    glBegin(GL_QUADS);
        glVertex2f(-0.06f, 0.01f);
        glVertex2f(-0.065f, 0.01f);
        glVertex2f(-0.065f, 0.02f);
        glVertex2f(-0.06f, 0.02f);
    glEnd();

    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(0.06f, 0.01f);
        glVertex2f(0.065f, 0.01f);
        glVertex2f(0.065f, 0.02f);
        glVertex2f(0.06f, 0.02f);
    glEnd();
    glPopMatrix();

    // Car 2
    glPushMatrix();
    float rx1 = -0.7f, ry1 = -0.4f;
    float rx2 = -1.25f, ry2 = 0.05f;
    float rt = -car2Position / 0.55f;
    float car2X = rx1 + car2Position;
    float car2Y = ry1 + rt * (ry2 - ry1) + 0.015f;
    float rdx = rx2 - rx1;
    float rdy = ry2 - ry1;
    float rangle = atan2(rdy, rdx) * 180 / 3.14159f;
    glTranslatef(car2X, car2Y, 0.0f);
    glRotatef(rangle + 180.0f, 0.0f, 0.0f, 1.0f);

    glColor3f(lerp(0.0f, 0.0f, timeOfDay), lerp(0.0f, 0.0f, timeOfDay), lerp(0.8f, 0.6f, timeOfDay));
    glBegin(GL_QUADS);
        glVertex2f(-0.05f, 0.0f);
        glVertex2f(0.05f, 0.0f);
        glVertex2f(0.05f, 0.03f);
        glVertex2f(-0.05f, 0.03f);
    glEnd();

    glColor3f(lerp(0.0f, 0.0f, timeOfDay), lerp(0.0f, 0.0f, timeOfDay), lerp(0.6f, 0.4f, timeOfDay));
    glBegin(GL_QUADS);
        glVertex2f(-0.04f, 0.03f);
        glVertex2f(0.04f, 0.03f);
        glVertex2f(0.038f, 0.045f);
        glVertex2f(-0.038f, 0.045f);
    glEnd();

    glColor3f(lerp(0.6f, 0.4f, timeOfDay), lerp(0.9f, 0.7f, timeOfDay), lerp(1.0f, 0.8f, timeOfDay));
    glBegin(GL_QUADS);
        glVertex2f(-0.035f, 0.032f);
        glVertex2f(0.035f, 0.032f);
        glVertex2f(0.033f, 0.043f);
        glVertex2f(-0.033f, 0.043f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    float brw2 = 0.008f;
    glBegin(GL_POLYGON);
        for(int i = 0; i < 360; i += 15) {
            float theta = i * 3.14159f / 180;
            glVertex2f(0.038f + brw2 * cos(theta), 0.0f + brw2 * sin(theta));
        }
    glEnd();

    glBegin(GL_POLYGON);
        for(int i = 0; i < 360; i += 15) {
            float theta = i * 3.14159f / 180;
            glVertex2f(-0.038f + brw2 * cos(theta), 0.0f + brw2 * sin(theta));
        }
    glEnd();

    glColor3f(1.0f, 1.0f, 0.5f);
    glBegin(GL_QUADS);
        glVertex2f(-0.05f, 0.01f);
        glVertex2f(-0.055f, 0.01f);
        glVertex2f(-0.055f, 0.02f);
        glVertex2f(-0.05f, 0.02f);
    glEnd();

    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(0.05f, 0.01f);
        glVertex2f(0.055f, 0.01f);
        glVertex2f(0.055f, 0.02f);
        glVertex2f(0.05f, 0.02f);
    glEnd();
    glPopMatrix();

    // Left building
    glColor3f(lerp(0.7f, 0.5f, timeOfDay), lerp(0.7f, 0.5f, timeOfDay), lerp(0.75f, 0.55f, timeOfDay));
    glBegin(GL_POLYGON);
        glVertex2f(-0.7f, -0.4f);
        glVertex2f(-0.3f, -0.4f);
        glVertex2f(-0.3f, 0.35f);
        glVertex2f(-0.4f, 0.5f);
        glVertex2f(-0.7f, 0.5f);
    glEnd();

    glColor3f(lerp(0.4f, 0.2f, timeOfDay), lerp(0.7f, 0.5f, timeOfDay), lerp(1.0f, 0.8f, timeOfDay));
    glBegin(GL_POLYGON);
        glVertex2f(-0.65f, -0.2f);
        glVertex2f(-0.35f, -0.2f);
        glVertex2f(-0.35f, -0.15f);
        glVertex2f(-0.65f, -0.15f);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(-0.65f, -0.1f);
        glVertex2f(-0.35f, -0.1f);
        glVertex2f(-0.35f, -0.05f);
        glVertex2f(-0.65f, -0.05f);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(-0.65f, 0.0f);
        glVertex2f(-0.35f, 0.0f);
        glVertex2f(-0.35f, 0.05f);
        glVertex2f(-0.65f, 0.05f);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(-0.65f, 0.1f);
        glVertex2f(-0.35f, 0.1f);
        glVertex2f(-0.35f, 0.15f);
        glVertex2f(-0.65f, 0.15f);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(-0.65f, 0.2f);
        glVertex2f(-0.35f, 0.2f);
        glVertex2f(-0.35f, 0.25f);
        glVertex2f(-0.65f, 0.25f);
    glEnd();

    // Left building glowing windows
    if (timeOfDay > 0.5f) {
        glColor4f(1.0f, 1.0f, 0.8f, (timeOfDay - 0.5f) * 2.0f); // Yellowish glow, fades in
        glBegin(GL_POLYGON);
            glVertex2f(-0.65f, -0.2f);
            glVertex2f(-0.35f, -0.2f);
            glVertex2f(-0.35f, -0.15f);
            glVertex2f(-0.65f, -0.15f);
        glEnd();
        glBegin(GL_POLYGON);
            glVertex2f(-0.65f, -0.1f);
            glVertex2f(-0.35f, -0.1f);
            glVertex2f(-0.35f, -0.05f);
            glVertex2f(-0.65f, -0.05f);
        glEnd();
        glBegin(GL_POLYGON);
            glVertex2f(-0.65f, 0.0f);
            glVertex2f(-0.35f, 0.0f);
            glVertex2f(-0.35f, 0.05f);
            glVertex2f(-0.65f, 0.05f);
        glEnd();
        glBegin(GL_POLYGON);
            glVertex2f(-0.65f, 0.1f);
            glVertex2f(-0.35f, 0.1f);
            glVertex2f(-0.35f, 0.15f);
            glVertex2f(-0.65f, 0.15f);
        glEnd();
        glBegin(GL_POLYGON);
            glVertex2f(-0.65f, 0.2f);
            glVertex2f(-0.35f, 0.2f);
            glVertex2f(-0.35f, 0.25f);
            glVertex2f(-0.65f, 0.25f);
        glEnd();
    }

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(-0.7f, 0.35f);
        glVertex2f(-0.3f, 0.35f);
    glEnd();

    glColor3f(lerp(0.4f, 0.2f, timeOfDay), lerp(0.7f, 0.5f, timeOfDay), lerp(1.0f, 0.8f, timeOfDay));
    glBegin(GL_POLYGON);
        glVertex2f(-0.68f, 0.36f);
        glVertex2f(-0.63f, 0.36f);
        glVertex2f(-0.63f, 0.41f);
        glVertex2f(-0.68f, 0.41f);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(-0.61f, 0.36f);
        glVertex2f(-0.56f, 0.36f);
        glVertex2f(-0.56f, 0.41f);
        glVertex2f(-0.61f, 0.41f);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(-0.54f, 0.36f);
        glVertex2f(-0.49f, 0.36f);
        glVertex2f(-0.49f, 0.41f);
        glVertex2f(-0.54f, 0.41f);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(-0.47f, 0.36f);
        glVertex2f(-0.42f, 0.36f);
        glVertex2f(-0.42f, 0.41f);
        glVertex2f(-0.47f, 0.41f);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(-0.68f, 0.43f);
        glVertex2f(-0.63f, 0.43f);
        glVertex2f(-0.63f, 0.48f);
        glVertex2f(-0.68f, 0.48f);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(-0.61f, 0.43f);
        glVertex2f(-0.56f, 0.43f);
        glVertex2f(-0.56f, 0.48f);
        glVertex2f(-0.61f, 0.48f);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(-0.54f, 0.43f);
        glVertex2f(-0.49f, 0.43f);
        glVertex2f(-0.49f, 0.48f);
        glVertex2f(-0.54f, 0.48f);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(-0.47f, 0.43f);
        glVertex2f(-0.42f, 0.43f);
        glVertex2f(-0.42f, 0.48f);
        glVertex2f(-0.47f, 0.48f);
    glEnd();

    // Glowing windows
    if (timeOfDay > 0.5f) {
        glColor4f(1.0f, 1.0f, 0.8f, (timeOfDay - 0.5f) * 2.0f);
        glBegin(GL_POLYGON);
            glVertex2f(-0.68f, 0.36f);
            glVertex2f(-0.63f, 0.36f);
            glVertex2f(-0.63f, 0.41f);
            glVertex2f(-0.68f, 0.41f);
        glEnd();
        glBegin(GL_POLYGON);
            glVertex2f(-0.61f, 0.36f);
            glVertex2f(-0.56f, 0.36f);
            glVertex2f(-0.56f, 0.41f);
            glVertex2f(-0.61f, 0.41f);
        glEnd();
        glBegin(GL_POLYGON);
            glVertex2f(-0.54f, 0.36f);
            glVertex2f(-0.49f, 0.36f);
            glVertex2f(-0.49f, 0.41f);
            glVertex2f(-0.54f, 0.41f);
        glEnd();
        glBegin(GL_POLYGON);
            glVertex2f(-0.47f, 0.36f);
            glVertex2f(-0.42f, 0.36f);
            glVertex2f(-0.42f, 0.41f);
            glVertex2f(-0.47f, 0.41f);
        glEnd();
        glBegin(GL_POLYGON);
            glVertex2f(-0.68f, 0.43f);
            glVertex2f(-0.63f, 0.43f);
            glVertex2f(-0.63f, 0.48f);
            glVertex2f(-0.68f, 0.48f);
        glEnd();
        glBegin(GL_POLYGON);
            glVertex2f(-0.61f, 0.43f);
            glVertex2f(-0.56f, 0.43f);
            glVertex2f(-0.56f, 0.48f);
            glVertex2f(-0.61f, 0.48f);
        glEnd();
    }

    glColor3f(lerp(0.36f, 0.18f, timeOfDay), lerp(0.25f, 0.13f, timeOfDay), lerp(0.20f, 0.10f, timeOfDay));
    glBegin(GL_QUADS);
        glVertex2f(-0.6f, -0.4f);
        glVertex2f(-0.4f, -0.4f);
        glVertex2f(-0.4f, -0.25f);
        glVertex2f(-0.6f, -0.25f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
        glVertex2f(-0.5f, -0.25f);
        glVertex2f(-0.5f, -0.4f);
    glEnd();

    float yPanelGap = 0.05f;
    for(float y = -0.25f + yPanelGap; y > -0.4f; y -= yPanelGap) {
        glBegin(GL_LINES);
            glVertex2f(-0.6f, y);
            glVertex2f(-0.4f, y);
        glEnd();
    }

    glColor3f(lerp(1.0f, 0.8f, timeOfDay), lerp(1.0f, 0.8f, timeOfDay), lerp(0.0f, 0.0f, timeOfDay));
    glBegin(GL_POINTS);
        glVertex2f(-0.52f, -0.325f);
        glVertex2f(-0.48f, -0.325f);
    glEnd();

    // Ground
    glColor3f(lerp(0.6f, 0.3f, timeOfDay), lerp(0.6f, 0.3f, timeOfDay), lerp(0.6f, 0.3f, timeOfDay));
    glBegin(GL_QUADS);
        glVertex2f(-1.25f, -0.45f);
        glVertex2f(1.25f, -0.45f);
        glVertex2f(1.25f, -0.4f);
        glVertex2f(-1.25f, -0.4f);
    glEnd();

    // Clouds
    glColor4f(1.0f, 1.0f, 1.0f, lerp(1.0f, 0.7f, timeOfDay));
    float leftClouds[3][4] = {
        {-0.30f, 0.80f, 0.06f, 0.035f},
        {-0.25f, 0.73f, 0.05f, 0.03f},
        {-0.18f, 0.78f, 0.04f, 0.025f}
    };

    float rightClouds[4][4] = {
        {0.25f, 0.80f, 0.06f, 0.035f},
        {0.30f, 0.75f, 0.05f, 0.03f},
        {0.33f, 0.82f, 0.045f, 0.03f},
        {0.37f, 0.77f, 0.04f, 0.025f}
    };

    for(int c = 0; c < 3; c++) {
        glBegin(GL_POLYGON);
        for(int i = 0; i < 360; i += 15) {
            float theta = i * 3.14159f / 180;
            glVertex2f(leftClouds[c][0] + leftClouds[c][2] * cos(theta),
                       leftClouds[c][1] + leftClouds[c][3] * sin(theta));
        }
        glEnd();
    }

    for(int c = 0; c < 4; c++) {
        glBegin(GL_POLYGON);
        for(int i = 0; i < 360; i += 15) {
            float theta = i * 3.14159f / 180;
            glVertex2f(rightClouds[c][0] + rightClouds[c][2] * cos(theta),
                       rightClouds[c][1] + rightClouds[c][3] * sin(theta));
        }
        glEnd();
    }

    float topLeftCloud[4] = {-0.65f, 0.92f, 0.09f, 0.04f};
    glBegin(GL_POLYGON);
    for(int i = 0; i < 360; i += 15) {
        float theta = i * 3.14159f / 180;
        glVertex2f(topLeftCloud[0] + topLeftCloud[2] * cos(theta),
                   topLeftCloud[1] + topLeftCloud[3] * sin(theta));
    }
    glEnd();

    float topRightCloud[4] = {0.50f, 0.93f, 0.06f, 0.035f};
    glBegin(GL_POLYGON);
    for(int i = 0; i < 360; i += 15) {
        float theta = i * 3.14159f / 180;
        glVertex2f(topRightCloud[0] + topRightCloud[2] * cos(theta),
                   topRightCloud[1] + topRightCloud[3] * sin(theta));
    }
    glEnd();

    glutSwapBuffers();
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(1000, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("The Shard Building");
    glutDisplayFunc(display);
    init();
    glutTimerFunc(0, timer, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.25, 1.25, -1.0, 1.0);
    glutMainLoop();
    return 0;
}
