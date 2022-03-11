#pragma once

#include "components/simple_scene.h"
#include <stdlib.h>
#include <iostream>


namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
    public:

        

        

        Tema1();
        ~Tema1();

        void Init() override;
        

    private:
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

    protected:
        float cx, cy;
        glm::mat3 modelMatrix;
        float translateX, translateY, x, y;
        float scaleX, scaleY;
        float angularStep, angularStep2, angularStepEnemy;
        float move;
        float pulse;
        float length;
        float mapSize, obstacleSize, playerRadius, eyeRadius;
        float pi = 3.1415;
        bool shoot = false;
        float bulletDistanceX, bulletDistanceY;
        float movX = 0, movY = 0;
        float cadran;
        float x_player, y_player, x_projectile, y_projectile;
        float time1 = 0, time2;
        bool ok = true;
        float enemyPosX, enemyPosY;
        float i;
        float hpX, hpY;
        float HP;
        float dmgX, dmgY, healX, healY;
        bool enemyON;
        float score;
        bool printScore;
        float vectorX[100], vectorY[100];
        int j;
        float obstacle1X, obstacle1Y, obstacle2X, obstacle2Y, obstacle3X, obstacle3Y;
        float shootRange;
        bool timeAttack = false;
    };
}   // namespace m1
