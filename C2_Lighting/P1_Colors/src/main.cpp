#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "shader.h"
// 引入加载图片用的头文件
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "camera.h"

float deltaTime = 0.0f; // Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

camera cam = camera();

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "Shaders", NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    Shader ourShader("../src/shaders/shader.vs", "../src/shaders/shader.fs");
    Shader lightShader("../src/shaders/shader.vs", "../src/shaders/light.fs");
    // 创建要绘制的顶点 这些顶点是NDC坐标空间?
    // 这些数据应该是模型空间的数据
    float vertices[] = {
        // 后
        0.5f,
        0.5f,
        -0.5f, // 右上
        0.5f,
        -0.5f,
        -0.5f, // 右下
        -0.5f,
        -0.5f,
        -0.5f, // 左下

        -0.5f,
        -0.5f,
        -0.5f, // 左下
        -0.5f,
        0.5f,
        -0.5f, // 左上
        0.5f,
        0.5f,
        -0.5f, // 右上

        // 前
        0.5f,
        0.5f,
        0.5f, // 右上
        0.5f,
        -0.5f,
        0.5f, // 右下
        -0.5f,
        -0.5f,
        0.5f, // 左下

        -0.5f,
        -0.5f,
        0.5f, // 左下
        -0.5f,
        0.5f,
        0.5f, // 左上
        0.5f,
        0.5f,
        0.5f, // 右上

        // 左
        -0.5f,
        0.5f,
        0.5f, // 右上
        -0.5f,
        -0.5f,
        0.5f, // 右下
        -0.5f,
        -0.5f,
        -0.5f, // 左下

        -0.5f,
        -0.5f,
        -0.5f, // 左下
        -0.5f,
        0.5f,
        -0.5f, // 左上
        -0.5f,
        0.5f,
        0.5f, // 右上

        // 右
        0.5f,
        0.5f,
        0.5f, // 右上
        0.5f,
        -0.5f,
        0.5f, // 右下
        0.5f,
        -0.5f,
        -0.5f, // 左下

        0.5f,
        -0.5f,
        -0.5f, // 左下
        0.5f,
        0.5f,
        -0.5f, // 左上
        0.5f,
        0.5f,
        0.5f, // 右上

        // 上
        0.5f,
        0.5f,
        -0.5f, // 右上
        0.5f,
        0.5f,
        0.5f, // 右下
        -0.5f,
        0.5f,
        0.5f, // 左下

        -0.5f,
        0.5f,
        0.5f, // 左下
        -0.5f,
        0.5f,
        -0.5f, // 左上
        0.5f,
        0.5f,
        -0.5f, // 右上

        // 下
        0.5f,
        -0.5f,
        0.5f, // 右上
        0.5f,
        -0.5f,
        -0.5f, // 右下
        -0.5f,
        -0.5f,
        -0.5f, // 左下

        -0.5f,
        -0.5f,
        -0.5f, // 左下
        -0.5f,
        -0.5f,
        0.5f, // 左上
        0.5f,
        -0.5f,
        0.5f, // 右上
    };

    // 颜色
    float colors[] = {
 
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f,

        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f,

        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f,

        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f,

        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f,

        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f,
    };

    // 纹理坐标
    float tex[] = {
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
       
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,

        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
       
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,

        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
       
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,

        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
       
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,

        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
       
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,

        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
       
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
    };

    // unsigned int indices[] = {
    //     // 注意索引从0开始
    //     // 此例的索引(0, 1, 2, 3)就是顶点数组的vertices的下标，
    //     // 这样就可以由下表代表顶点组合成矩形

    //     0, 1, 3, // 第一个三角形
    //     1, 2, 3  // 第二个三角形
    // };

    unsigned int lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);

    // 位置属性
    unsigned int VBO_Pos;
    glGenBuffers(1, &VBO_Pos);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Pos);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    unsigned int VAO;
    // , EBO;
    glGenVertexArrays(1, &VAO);
    // glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // 位置属性
    glGenBuffers(1, &VBO_Pos);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Pos);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // 颜色属性
    unsigned int VBO_Color;
    glGenBuffers(1, &VBO_Color);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Color);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(1);

    // 纹理坐标
    unsigned int VBO_Tex;
    glGenBuffers(1, &VBO_Tex);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Tex);
    glBufferData(GL_ARRAY_BUFFER, sizeof(tex), tex, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(2);

    // load and create a texture
    // -------------------------
    stbi_set_flip_vertically_on_load(true);

    // 这些数据是世界空间下的数据
    // glm::vec3 cubePositions[] = {
    //     glm::vec3(0.0f, 0.0f, 0.0f),
    //     glm::vec3(2.0f, 5.0f, -15.0f),
    //     glm::vec3(-1.5f, -2.2f, -2.5f),
    //     glm::vec3(-3.8f, -2.0f, -12.3f),
    //     glm::vec3(2.4f, -0.4f, -3.5f),
    //     glm::vec3(-1.7f, 3.0f, -7.5f),
    //     glm::vec3(1.3f, -2.0f, -2.5f),
    //     glm::vec3(1.5f, 2.0f, -2.5f),
    //     glm::vec3(1.5f, 0.2f, -1.5f),
    //     glm::vec3(-1.3f, 1.0f, -1.5f)
    // };

   
    glEnable(GL_DEPTH_TEST);

    // ourShader.setInt("texture1", 0);
    // ourShader.setInt("texture2", 1);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // create transformations
        // glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        // transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        // // x分量平移0.5, y分量平移-0.5
        // transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));

        // glm::mat4 transform = glm::mat4(1.0f);
        // transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));                   // 最终位置
        // transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f)); // 旋转
        // transform = glm::translate(transform, glm::vec3(-0.5f, 0.5f, 0.0f));                   // 先将中心移到原点（反向平移）

        // glm::mat4 model = glm::mat4(1.0f);
        // model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));

        glm::mat4 view = cam.GetViewMatrix();

        // 投影矩阵是干什么的?
        glm::mat4 projection = glm::mat4(1.0f);
        projection = cam.GetProjectionMatrix();

        glm::mat4 model = glm::mat4(1.0f);
        // glm::vec3(0.0f, 0.0f, 0.0f),
        //     glm::vec3(2.0f, 5.0f, -15.0f),
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));

        glBindVertexArray(lightVAO);
        lightShader.use();

        unsigned int viewLoc = glGetUniformLocation(lightShader.ID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        unsigned int projectionLoc = glGetUniformLocation(lightShader.ID, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        lightShader.setMat4("model", model);
        // render container
        glBindVertexArray(VAO);
        ourShader.use();

        viewLoc = glGetUniformLocation(ourShader.ID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        projectionLoc = glGetUniformLocation(ourShader.ID, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        model = glm::mat4(1.0f);
        // glm::vec3(0.0f, 0.0f, 0.0f),
        //     glm::vec3(2.0f, 5.0f, -15.0f),
        model = glm::translate(model, glm::vec3(2.0f, 5.0f, -15.0f));
        ourShader.setMat4("model", model);
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // for (int i = 0; i < 10; i++){ // 这10个cube用的是同一组顶点信息
        //     glm::mat4 model = glm::mat4(1.0f);
        //     float angle = 20.0f * (i+1);
        //     // 先平移回原点
        //     // model = glm::translate(model, -1.0f * cubePositions[i]);
        //     // model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        //     // 记住先平移再旋转!!! 为什么?
        //     // 有两种理解矩阵变换的视角: 一种是主动变换(active transformation), 另一种是被动变换(positive transformation) 
        //     // 在主动变换的视角下, 我们认为参与变换的各个坐标系都是不动的, 所有的顶点在移动
        //     // 在被动变换的视角下, 我们认为参与变换的各个坐标是移动的, 而所有的顶点是不动的
        //     // 我在这里理解错了, 这里是模型矩阵Model Transform 将顶点从坐标空间转换到世界空间
        //     // Model Matrix为何会按照下面的方式构建呢?
        //     model = glm::translate(model, cubePositions[i]);
        //     // 计算旋转
        //     model = glm::rotate(model, (float) glfwGetTime() * glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        //     ourShader.setMat4("model", model);
        //     glDrawArrays(GL_TRIANGLES, 0, 36);
        // }
            
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &lightVAO);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO_Pos);
    glDeleteBuffers(1, &VBO_Color);
    glDeleteBuffers(1, &VBO_Tex);
    // glDeleteBuffers(1, &EBO);

    glfwTerminate();

    return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    const float cameraSpeed = 2.5f * deltaTime;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    cam.ProcessKeyboardInput(window, cameraSpeed);
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos){
    cam.ProcessMouseInput(window, xpos, ypos);
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) 
{
    cam.ProcessScrollInput(window, xoffset, yoffset);
}