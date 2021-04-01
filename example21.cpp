#include "sand.h"

const int num_points = 5000;


void init() {
    std::array<vec<2>, num_points> points;
    std::array<vec<2>, 3> vertices = {
        vec<2>(-1, -1), vec<2>(0, 1), vec<2>(1, -1)
    };
    
    points[0] = vec<2>(0.25, 0.5);
    
    for(int i = 1; i < num_points; ++i) { 
        int j = rand() % 3;
        points[i] = (points[i-1] + vertices[j]) / 2.0;
    }
    

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points.data(), GL_STATIC_DRAW);
    
    GLuint program = InitShader("vshader21.glsl", "fshader21.glsl");
    glUseProgram(program);
    
    GLuint loc = glGetAttribLocation(program, "vPosition");
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    
    glClearColor(1.0, 1.0, 1.0, 1.0); // white background
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_POINTS, 0, num_points);
    glFlush();
}

void keyboard(unsigned char key, int x, int y) {
    switch(key) {
        case 033:
            exit(EXIT_SUCCESS);
            break;
    }
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowSize(512, 512);
    

    // freeglut version check
    glutInitContextVersion(3, 2);
    glutInitContextProfile(GLUT_CORE_PROFILE);
    
    glutCreateWindow("Sierpinski Gasket");
    glewInit();
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}