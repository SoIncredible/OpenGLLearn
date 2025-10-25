class camera{

public:
    glm::mat4 GetViewMatrix();
    glm::mat4 GetProjectionMatrix();
    void ProcessMouseInput(GLFWwindow *window, double xpos, double ypos);

    void ProcessKeyboardInput(GLFWwindow *window, float deltaTime);

    void ProcessScrollInput(GLFWwindow *window, double xoffset, double yoffset);

    glm::vec3 Position();

private:
    // 巡航角默认值
    float yaw = -90.0f;
    // 俯仰角默认值
    float pitch = 0.0f;

    float fov = 45.0f;

    bool firstMouse = true;
    float lastX = 400, lastY = 300;

    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 10.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
};

glm::mat4 camera::GetViewMatrix(){
    return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

glm::mat4 camera::GetProjectionMatrix(){
    return glm::perspective(glm::radians(fov), 800.0f / 600.0f, 0.1f, 100.0f);
}

void camera::ProcessMouseInput(GLFWwindow* window, double xpos, double ypos){
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
    {
        pitch = 89.0f;
    }

    if (pitch < -89.0f)
    {
        pitch = -89.0f;
    }

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);
}

void camera::ProcessKeyboardInput(GLFWwindow* window, float deltaTime){

    const float cameraSpeed = 2.5f * deltaTime;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        cameraPos += cameraSpeed * cameraFront;
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        cameraPos -= cameraSpeed * cameraFront;
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp) * cameraSpeed);
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp) * cameraSpeed);
    }
}

void camera::ProcessScrollInput(GLFWwindow* window, double xoffset, double yoffset){
    fov -= (float)yoffset;
    if (fov < 1.0f)
    {
        fov = 1.0f;
    }

    if (fov > 45.0f)
    {
        fov = 45.0f;
    }
}

glm::vec3 camera::Position(){
    return cameraPos;
}