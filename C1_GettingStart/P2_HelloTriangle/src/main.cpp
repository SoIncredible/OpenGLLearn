#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "  gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "FragColor = vec4(1.0f, 0.7f, 0.7f, 1.0f);\n"
                                   "}\0\n";
const int windowWidth = 800;
const int windowHeight = 600;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow *window = glfwCreateWindow(windowWidth, windowHeight, "HelloTriangle", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    //竟然是这里多调用了一行
    // glViewport(0, 0, windowWidth, windowHeight);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // 添加验证代码
    std::cout << "程序启动，初始窗口大小: " << windowWidth << "x" << windowHeight << std::endl;
    std::cout << "回调函数地址: " << (void *)framebuffer_size_callback << std::endl;

    float vertices[] = {
        // 第一个三角形
        0.8f, 0.8f, 0.0f,  // 右上角
        0.8f, -0.8f, 0.0f, // 右下角
        -0.8f, 0.8f, 0.0f, // 左上角
        // 第二个三角形
        0.8f, -0.8f, 0.0f,  // 右下角
        -0.8f, -0.8f, 0.0f, // 左下角
        -0.8f, 0.8f, 0.0f   // 左上角
    };

    // float vertices[] = {
    //     0.5f, 0.5f, 0.0f,   // top right
    //     0.5f, -0.5f, 0.0f,  // bottom right
    //     -0.5f, -0.5f, 0.0f, // bottom left
    //     -0.5f, 0.5f, 0.0f   // top left
    // };

    // float vertices[] = {
    //     0.8f, 0.8f, 0.0f,   // 右上角
    //     0.8f, -0.8f, 0.0f,  // 右下角
    //     -0.8f, -0.8f, 0.0f, // 左下角
    //     -0.8f, 0.8f, 0.0f   // 左上角
    // };

    unsigned int indices[] = {
        // note that we start from 0!
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    unsigned int vertexShader;
    // 获得顶点着色器VertexShader的ID
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // 将顶点着色器与顶点着色器源代码关联起来
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    // 编译顶点Shader源代码
    glCompileShader(vertexShader);

    unsigned int fragmentShader;
    // 获得片元着色器
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // 将片元着色器与片元着色器源代码关联起来
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    // 编译片元着色器源代码
    glCompileShader(fragmentShader);

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    unsigned int VBO;
    unsigned int VAO;
    // unsigned int EBO; // element buffer object

    glGenBuffers(1, &VBO);
    // glGenBuffers(1, &EBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    // glViewport(600, 400, 200, 200);
    std::cout << "回调的宽高" << width << "," << height << std::endl;
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}
