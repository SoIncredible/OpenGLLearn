class camera{

public:
    void UpdateCamera();

private:
    float fov;
    // 巡航角默认值
    float yaw = -90.0f;
    // 俯仰角默认值
    float pitch = 0.0f;
    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;
};