#include "star.h"
#include <cmath>

Star::Star(const glm::vec2& position, float rotation, float radius, float aspect)
    : _position(position), _rotation(rotation), _radius(radius) {
    // TODO: assemble the vertex data of the star
    // write your code here
    // -------------------------------------
    float cur_rotation = rotation, cur_inner_rotation;
    float inner_radius = radius / 2.61803;
    const float angle_increment = M_PI / 5;
    for (int i = 0; i < 5; ++i) {
        _vertices.push_back(glm::vec2(
            position.x + radius * sin(cur_rotation) / aspect,
            position.y + radius * cos(cur_rotation)));
        cur_inner_rotation = cur_rotation + angle_increment* 3;
        _vertices.push_back(glm::vec2(
            position.x + inner_radius * sin(cur_inner_rotation) / aspect,
            position.y + inner_radius * cos(cur_inner_rotation)));
        cur_inner_rotation += angle_increment * 4;
        _vertices.push_back(glm::vec2(
            position.x + inner_radius * sin(cur_inner_rotation) / aspect,
            position.y + inner_radius * cos(cur_inner_rotation)));
        cur_rotation += 2 * angle_increment;
    // -------------------------------------
    }

    glGenVertexArrays(1, &_vao);
    glGenBuffers(1, &_vbo);

    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(
        GL_ARRAY_BUFFER, sizeof(glm::vec2) * _vertices.size(), _vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

Star::Star(Star&& rhs) noexcept
    : _position(rhs._position), _rotation(rhs._rotation), _radius(rhs._radius), _vao(rhs._vao),
      _vbo(rhs._vbo) {
    rhs._vao = 0;
    rhs._vbo = 0;
}

Star::~Star() {
    if (_vbo) {
        glDeleteVertexArrays(1, &_vbo);
        _vbo = 0;
    }

    if (_vao) {
        glDeleteVertexArrays(1, &_vao);
        _vao = 0;
    }
}

void Star::draw() const {
    glBindVertexArray(_vao);
    glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(_vertices.size()));
}