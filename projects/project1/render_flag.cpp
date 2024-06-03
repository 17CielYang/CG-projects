#include "render_flag.h"

RenderFlag::RenderFlag(const Options& options) : Application(options) {
    // create star shader
    const char* vsCode =
        "#version 330 core\n"
        "layout(location = 0) in vec2 aPosition;\n"
        "void main() {\n"
        "    gl_Position = vec4(aPosition, 0.0f, 1.0f);\n"
        "}\n";

    const char* fsCode =
        "#version 330 core\n"
        "out vec4 fragColor;\n"
        "void main() {\n"
        "    fragColor = vec4(1.0f, 0.870f, 0.0f, 1.0f);\n"
        "}\n";

    _starShader.reset(new GLSLProgram);
    _starShader->attachVertexShader(vsCode);
    _starShader->attachFragmentShader(fsCode);
    _starShader->link();

    // TODO: create 5 stars
    // hint: aspect_of_the_window = _windowWidth / _windowHeight
    // write your code here
    // ---------------------------------------------------------------
    float aspect_ratio = static_cast<float> (_windowWidth) / _windowHeight;
    float streched = aspect_ratio * 2.0 / 3.0;

    std::vector<std::pair<glm::vec2, float>> starSettings = {
        {{-2.0 / 3.0 / streched, 0.5},                          0},
        {{-1.0 / 3.0 / streched, 0.8}, -M_PI / 2 - 0.540319500271},
        {      {-0.2 / streched, 0.6}, -M_PI / 2 - 0.165148677415},
        {      {-0.2 / streched, 0.3},             -1.29249666779},
        {{-1.0 / 3.0 / streched, 0.1},            -0.896055384571}
    };

    for (size_t i = 0; i < starSettings.size(); i++) {
        float radius = (i == 0 ? 0.3 : 0.1);
        _stars[i].reset(
            new Star(starSettings[i].first, starSettings[i].second, radius, aspect_ratio));
    }
    // ---------------------------------------------------------------
}

void RenderFlag::handleInput() {
    if (_input.keyboard.keyStates[GLFW_KEY_ESCAPE] != GLFW_RELEASE) {
        glfwSetWindowShouldClose(_window, true);
        return;
    }
}

void RenderFlag::renderFrame() {
    showFpsInWindowTitle();

    // we use background as the flag
    glClearColor(0.87f, 0.161f, 0.063f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    _starShader->use();
    for (int i = 0; i < 5; ++i) {
        if (_stars[i] != nullptr) {
            _stars[i]->draw();
        }
    }
}