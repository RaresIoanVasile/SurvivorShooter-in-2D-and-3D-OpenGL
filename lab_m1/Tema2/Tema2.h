#pragma once

#include "components/simple_scene.h"
#include "components/transform.h"
#include "lab_m1/Tema2/lab_camera_tema.h"


namespace m1
{
    class Tema2 : public gfxc::SimpleScene
    {
    public:
        Tema2();
        ~Tema2();

        void Init() override;

    private:
        void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color = glm::vec3(1));
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

        float x, y = 1, z;
        implemented::Camera2 *camera;
        glm::vec3 lightPosition;
        unsigned int materialShininess;
        float materialKd;
        float materialKs;
        glm::mat4 projectionMatrix;
        bool begin = true;
        int map[10][10];
        int map1[10][10] = {
            {1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
            {1, 0, 1, 1, 1, 1, 1, 1, 2, 1},
            {1, 0, 1, 1, 1, 1, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
            {1, 1, 0, 1, 0, 1, 0, 1, 0, 1},
            {1, 1, 2, 1, 0, 1, 0, 1, 0, 1},
            {1, 1, 0, 1, 0, 2, 0, 2, 0, 1},
            {1, 1, 0, 0, 1, 1, 1, 1, 0, 1},
            {1, 1, 1, 2, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 0, 1, 1, 1, 1, 1, 1},
        };
        int map2[10][10] = {
            {1, 1, 1, 1, 0, 0, 1, 1, 1, 1},
            {1, 0, 0, 0, 0, 1, 1, 1, 2, 1},
            {1, 0, 1, 1, 1, 1, 0, 0, 0, 1},
            {1, 0, 1, 0, 0, 0, 0, 1, 0, 1},
            {1, 0, 0, 1, 0, 1, 0, 1, 2, 1},
            {1, 1, 0, 0, 0, 1, 0, 1, 0, 1},
            {0, 2, 0, 1, 0, 2, 0, 1, 2, 1},
            {1, 1, 0, 0, 1, 1, 0, 1, 0, 1},
            {1, 1, 0, 0, 0, 0, 0, 1, 1, 1},
            {1, 1, 1, 1, 1, 0, 1, 1, 1, 1},
        };
        int map3[10][10] = {
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 0, 2, 0, 0, 1, 1, 1, 2, 1},
            {1, 0, 1, 1, 0, 1, 0, 0, 0, 1},
            {1, 0, 0, 2, 0, 0, 0, 1, 0, 1},
            {1, 1, 1, 1, 0, 1, 0, 1, 2, 1},
            {1, 1, 0, 0, 0, 1, 0, 1, 0, 1},
            {1, 1, 0, 1, 0, 2, 0, 1, 2, 1},
            {1, 0, 2, 1, 1, 0, 2, 0, 0, 0},
            {1, 0, 1, 1, 1, 1, 0, 1, 1, 1},
            {1, 0, 1, 1, 1, 1, 1, 1, 1, 1},
        };
        int map4[10][10] = {
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 2, 0, 1, 0, 1, 1, 1, 1, 1},
            {1, 1, 0, 0, 0, 1, 0, 0, 0, 1},
            {1, 0, 0, 1, 0, 2, 0, 1, 2, 1},
            {1, 0, 1, 1, 0, 1, 0, 1, 0, 1},
            {1, 1, 0, 0, 2, 1, 1, 0, 0, 1},
            {1, 1, 1, 1, 0, 1, 1, 0, 1, 1},
            {1, 1, 1, 1, 0, 0, 2, 0, 0, 1},
            {1, 0, 2, 0, 0, 1, 1, 1, 2, 1},
            {1, 0, 1, 1, 1, 1, 1, 1, 1, 1},
        };
        int map5[10][10] = {
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 0, 2, 0, 1, 1, 1},
            {1, 1, 1, 0, 0, 1, 0, 0, 1, 1},
            {1, 0, 1, 1, 0, 0, 0, 1, 1, 1},
            {0, 0, 1, 1, 0, 1, 0, 0, 2, 0},
            {1, 0, 0, 0, 2, 1, 1, 0, 0, 1},
            {1, 1, 1, 0, 0, 0, 1, 0, 1, 1},
            {1, 1, 2, 0, 1, 0, 1, 0, 0, 1},
            {1, 1, 0, 1, 1, 0, 1, 0, 2, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        };
        int map6[10][10] = {
            {1, 1, 1, 1, 0, 1, 1, 1, 1, 1},
            {1, 1, 1, 0, 2, 0, 1, 1, 1, 1},
            {1, 1, 0, 2, 1, 2, 0, 1, 1, 1},
            {1, 0, 2, 1, 1, 1, 2, 0, 1, 1},
            {0, 2, 1, 1, 1, 1, 1, 2, 0, 1},
            {1, 0, 2, 1, 1, 1, 1, 1, 2, 0},
            {1, 1, 0, 2, 1, 1, 1, 2, 0, 1},
            {1, 1, 1, 0, 2, 1, 2, 0, 1, 1},
            {1, 1, 1, 1, 0, 2, 0, 1, 1, 1},
            {1, 1, 1, 1, 1, 0, 1, 1, 1, 1},
        };
        int map7[10][10] = {
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 2, 0, 0, 0, 0, 0, 0, 2, 1},
            {1, 0, 1, 2, 1, 1, 1, 1, 0, 0},
            {1, 0, 1, 0, 0, 0, 0, 1, 0, 1},
            {1, 2, 1, 0, 2, 1, 0, 1, 2, 1},
            {1, 2, 1, 0, 1, 2, 0, 1, 2, 1},
            {1, 0, 1, 0, 0, 0, 0, 1, 0, 1},
            {0, 0, 1, 1, 1, 1, 2, 1, 0, 1},
            {1, 2, 0, 0, 0, 0, 0, 0, 2, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        };
        bool ok = false;
        bool move = true, move2 = true;
        float moveX = 0, moveY = 0;
        float angle = 0;
        float time = 0;
        bool startGame = false;
        float hp = 0;

    };
}   // namespace m1