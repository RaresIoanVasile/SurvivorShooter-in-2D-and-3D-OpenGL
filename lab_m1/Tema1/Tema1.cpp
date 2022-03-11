#include "lab_m1/Tema1/Tema1.h"

#include <vector>
#include <iostream>

#include "lab_m1/Tema1/transform2D.h"
#include "lab_m1/Tema1/object2D.h"

using namespace std;
using namespace m1;

Tema1::Tema1()
{
    translateX = 640;
    translateY = 360;
    x = 0;
    y = 0;
    mapSize = 1500;
    obstacleSize = 100;
    eyeRadius = 10;
    playerRadius = 25;
    i = 0;
    srand(time(NULL));
    for (j = 0; j < 100; j++) {
        vectorX[j] = rand() % 1501;
        vectorY[j] = rand() % 1501;
    }
    j = 0;
    enemyPosX = rand() % 1501;
    enemyPosY = rand() % 1501;
    hpX = 900;
    hpY = 650;
    HP = 3;
    dmgX = 600;
    dmgY = 800;
    healX = 1000;
    healY = 800;
    enemyON = true;
    score = 0;
    printScore = true;
    obstacle1X = 500;
    obstacle1Y = 500;
    obstacle3X = 500;
    obstacle3Y = 1000;
    shootRange = 350;
}


Tema1::~Tema1()
{
}


void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);


 
    glm::vec3 corner = glm::vec3(0, 0, 0);

    Mesh* enemy = object2D::CreateSquare("enemy", corner, obstacleSize, glm::vec3(1, 0, 0), true);
    AddMeshToList(enemy);
    Mesh* obstacle = object2D::CreateSquare("obstacle", corner, obstacleSize, glm::vec3(0.4, 0.6, 0.1), true);
    AddMeshToList(obstacle);
    Mesh* projectile = object2D::CreateSquare("projectile", corner, obstacleSize, glm::vec3(0, 0, 0.1), true);
    AddMeshToList(projectile);
    Mesh* circle1 = object2D::CreateCircle("circle1", corner, playerRadius, glm::vec3(0.9, 0.8, 0.4), true);
    AddMeshToList(circle1);
    Mesh* dmg = object2D::CreateCircle("dmg", corner, playerRadius, glm::vec3(1, 0, 0), true);
    AddMeshToList(dmg);
    Mesh* heal = object2D::CreateCircle("heal", corner, playerRadius, glm::vec3(0, 1, 0), true);
    AddMeshToList(heal);
}

void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(1, 0, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema1::Update(float deltaTimeSeconds)
{
    auto camera = GetSceneCamera();
    camera->SetPosition(glm::vec3(x, y, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);
    if (printScore == true)
        std::cout << "Score: " << score << "\n";
    
    printScore = false;
    angularStepEnemy = glm::atan(y + 720 + translateY - enemyPosY, x + translateX - enemyPosX) - pi/2;
    float xdmg = (dmgX + playerRadius * 2) - (translateX + playerRadius + eyeRadius);
    float ydmg = (dmgY + playerRadius * 2) - (translateY + playerRadius + eyeRadius);
    float distancedmg = sqrt(xdmg * xdmg + ydmg * ydmg);
    if (distancedmg < playerRadius * 2 + playerRadius + eyeRadius) {
        if (HP > 0.001) {
            HP -= 0.001;
        }
    }
    float xheal = (healX + playerRadius * 2) - (translateX + playerRadius + eyeRadius);
    float yheal = (healY + playerRadius * 2) - (translateY + playerRadius + eyeRadius);
    float distanceheal = sqrt(xheal * xheal + yheal * yheal);
    if (distanceheal < playerRadius * 2 + playerRadius + eyeRadius) {
        if (HP < 1.5) {
            HP += 0.001;
        }
    }
    if (HP < 0.001) {
        exit(0);
    }
    {
        if (enemyON == true) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(vectorX[j] - 20, vectorY[j] + 70);
            modelMatrix *= transform2D::Scale(0.5, 0.5);
            RenderMesh2D(meshes["enemy"], shaders["VertexColor"], modelMatrix);
        }
    }
    {
        if (enemyON == true) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(vectorX[j] + 70, vectorY[j] + 70);
            modelMatrix *= transform2D::Scale(0.5, 0.5);
            RenderMesh2D(meshes["enemy"], shaders["VertexColor"], modelMatrix);
        }
    }
    {
        if (enemyON == true) {
            modelMatrix = glm::mat3(1);
            float aux1 = vectorX[j];
            float aux2 = vectorY[j];
            modelMatrix *= transform2D::Translate(aux1, aux2);
            RenderMesh2D(meshes["enemy"], shaders["VertexColor"], modelMatrix);
        }
    }
    {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(hpX, hpY);
        modelMatrix *= transform2D::Scale(HP, 0.5);
        RenderMesh2D(meshes["enemy"], shaders["VertexColor"], modelMatrix);
    }
    {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(hpX - 1, hpY - 0.51);
        modelMatrix *= transform2D::Scale(3.02, 0.52);
        RenderMesh2D(meshes["obstacle"], shaders["Simple"], modelMatrix);
    }
    
    {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(obstacle2X, obstacle2Y);
        modelMatrix *= transform2D::Scale(3, 1);

        RenderMesh2D(meshes["obstacle"], shaders["Simple"], modelMatrix);
    }
    {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(translateX, translateY);
        modelMatrix *= transform2D::Rotate(angularStep);
        modelMatrix *= transform2D::Translate(-(translateX), -(translateY));
        modelMatrix *= transform2D::Translate(translateX - 15, translateY + 20);
        modelMatrix *= transform2D::Scale(0.4, 0.4);
        RenderMesh2D(meshes["circle1"], shaders["Simple"], modelMatrix);
    }
    {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(translateX, translateY);
        modelMatrix *= transform2D::Rotate(angularStep);
        modelMatrix *= transform2D::Translate(-(translateX), -(translateY));
        modelMatrix *= transform2D::Translate(translateX + 15, translateY + 20);
        modelMatrix *= transform2D::Scale(0.4, 0.4);
        RenderMesh2D(meshes["circle1"], shaders["Simple"], modelMatrix);
    }
    
    {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(translateX, translateY);
        
        RenderMesh2D(meshes["circle1"], shaders["VertexColor"], modelMatrix);
    }
    {
        if (shoot == true) {
            time1 = time2;
            modelMatrix = glm::mat3(1);
            if (cadran == 4) {
                if (movX < shootRange && movY < shootRange) {
                    if (movX + x_player > 1500 || movY + y_player < 0) {
                        modelMatrix *= transform2D::Translate(-movX, -movY);
                        movX = 0;
                        movY = 0;
                        shoot = false;
                    }
                    if (movX < vectorX[j] - x_player + 100 &&
                        movX + 20 > vectorX[j] - x_player &&
                        movY < vectorY[j] - y_player + 100 &&
                        movY + 20 > vectorY[j] - y_player &&
                        enemyON == true) {
                        enemyON = false;
                        score += 1;
                        printScore = true;
                        modelMatrix *= transform2D::Translate(-movX, movY);
                        movX = 0;
                        movY = 0;
                        shoot = false;
                        j++;
                        enemyON = true;
                    }
                    movX += (bulletDistanceX / 30) * 40 * deltaTimeSeconds;
                    movY += (bulletDistanceY / 30) * 40 * deltaTimeSeconds;
                    modelMatrix *= transform2D::Translate(movX, movY);
                    if (movX > shootRange || (-movY) > shootRange) {
                        modelMatrix *= transform2D::Translate(-movX, movY);
                        movX = 0;
                        movY = 0;
                        shoot = false;
                    }
                }
            }
            if (cadran == 3) {
                if (movX < shootRange && movY < shootRange) {
                    if (movX + x_player < 0 || movY + y_player < 0) {
                        modelMatrix *= transform2D::Translate(-movX, -movY);
                        movX = 0;
                        movY = 0;
                        shoot = false;
                    }
                    if (movX < vectorX[j] - x_player + 100 &&
                        movX + 20 > vectorX[j] - x_player &&
                        movY < vectorY[j] - y_player + 100 &&
                        movY + 20 > vectorY[j] - y_player &&
                        enemyON == true) {
                        enemyON = false;
                        score += 1;
                        printScore = true;
                        modelMatrix *= transform2D::Translate(-movX, -movY);
                        movX = 0;
                        movY = 0;
                        shoot = false;
                        j++;
                        enemyON = true;
                    }
                    movX += (bulletDistanceX / 30) * 40 * deltaTimeSeconds;
                    movY += (bulletDistanceY / 30) * 40 * deltaTimeSeconds;
                    modelMatrix *= transform2D::Translate(movX, movY);
                    if ((-movX) > shootRange || (-movY) > shootRange) {
                        modelMatrix *= transform2D::Translate(-movX, -movY);
                        movX = 0;
                        movY = 0;
                        shoot = false;
                    }
                }

            }
            if (cadran == 2) {
                if (movX < shootRange && movY < shootRange) {
                    if (movX + x_player < 0 || movY + y_player > 1500) {
                        modelMatrix *= transform2D::Translate(-movX, -movY);
                        movX = 0;
                        movY = 0;
                        shoot = false;
                    }
                    if (movX < vectorX[j] - x_player + 100 &&
                        movX + 20 > vectorX[j] - x_player &&
                        movY < vectorY[j] - y_player + 100 &&
                        movY + 20 > vectorY[j] - y_player &&
                        enemyON == true) {
                        enemyON = false;
                        score += 1;
                        printScore = true;
                        modelMatrix *= transform2D::Translate(movX, -movY);
                        movX = 0;
                        movY = 0;
                        shoot = false;
                        j++;
                        enemyON = true;
                    }
                    movX += (bulletDistanceX / 30) * 40 * deltaTimeSeconds;
                    movY += (bulletDistanceY / 30) * 40 * deltaTimeSeconds;
                    modelMatrix *= transform2D::Translate(movX, movY);
                    if ( (-movX) > shootRange || movY > shootRange) {
                        modelMatrix *= transform2D::Translate(movX, -movY);
                        movX = 0;
                        movY = 0;
                        shoot = false;
                    }
                }
            }
            if (cadran == 1) { 
                if (movX < shootRange && movY < shootRange) {
                    if (movX + x_player > 1500 || movY + y_player > 1500) {
                        modelMatrix *= transform2D::Translate(-movX, -movY);
                        movX = 0;
                        movY = 0;
                        shoot = false;
                    }
                    if (movX < vectorX[j] - x_player + 100 &&
                        movX + 20 > vectorX[j] - x_player &&
                        movY < vectorY[j] - y_player + 100 &&
                        movY + 20 > vectorY[j] - y_player &&
                        enemyON == true) {
                        enemyON = false;
                        score += 1;
                        printScore = true;
                        modelMatrix *= transform2D::Translate(-movX, -movY);
                        movX = 0;
                        movY = 0;
                        shoot = false;
                        j++;
                        enemyON = true;
                    }
                    movX += (bulletDistanceX / 30) * 40 * deltaTimeSeconds;
                    movY += (bulletDistanceY / 30) * 40 * deltaTimeSeconds;
                    modelMatrix *= transform2D::Translate(movX, movY);
                    if (movX > shootRange || movY > shootRange) {
                        modelMatrix *= transform2D::Translate(-movX, -movY);
                        movX = 0;
                        movY = 0;
                        shoot = false;
                    }
                }
            }
            modelMatrix *= transform2D::Translate(x_player, y_player);
            modelMatrix *= transform2D::Rotate(angularStep2);
            modelMatrix *= transform2D::Translate(-(x_player), -(y_player));   
            
            modelMatrix *= transform2D::Translate(x_player - 10, y_player - 10);
            modelMatrix *= transform2D::Scale(0.2, 0.2);
            RenderMesh2D(meshes["projectile"], shaders["VertexColor"], modelMatrix);
        }
    }
    {
        modelMatrix = glm::mat3(1);
        
        modelMatrix *= transform2D::Translate(dmgX,dmgY);
        modelMatrix *= transform2D::Scale(2, 2);
        RenderMesh2D(meshes["dmg"], shaders["VertexColor"], modelMatrix);
    }
    {
        modelMatrix = glm::mat3(1);

        modelMatrix *= transform2D::Translate(healX, healY);
        modelMatrix *= transform2D::Scale(2, 2);
        RenderMesh2D(meshes["heal"], shaders["VertexColor"], modelMatrix);
    }
    {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(obstacle3X, obstacle3Y);

        RenderMesh2D(meshes["obstacle"], shaders["Simple"], modelMatrix);
    }
    {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(obstacle1X, obstacle1Y);

        RenderMesh2D(meshes["obstacle"], shaders["Simple"], modelMatrix);
    }
    {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Scale(15, 15);
        RenderMesh2D(meshes["obstacle"], shaders["VertexColor"], modelMatrix);
    }
}

void Tema1::FrameEnd()
{
}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{
    float xW = (obstacle1X + 0.7 * 100) - (translateX + playerRadius + eyeRadius);
    float yW = (obstacle1Y + 0.7 * 100) - (translateY + playerRadius + eyeRadius);
    float distance = sqrt(xW * xW + yW * yW);
    float xW1 = (obstacle3X + 0.7 * 100) - (translateX + playerRadius + eyeRadius);
    float yW1 = (obstacle3Y + 0.7 * 100) - (translateY + playerRadius + eyeRadius);
    float distance11 = sqrt(xW1 * xW1 + yW1 * yW1);
    float x1 = (obstacle2X + 0.7 * 100) - (translateX + playerRadius + eyeRadius);
    float y1 = (obstacle2Y + 0.7 * 100) - (translateY + playerRadius + eyeRadius);
    float distance1 = sqrt(x1 * x1 + y1 * y1);
    float x2 = (obstacle2X + 100 + 0.7 * 100) - (translateX + playerRadius + eyeRadius);
    float y2 = (obstacle2Y + 0.7 * 100) - (translateY + playerRadius + eyeRadius);
    float distance2 = sqrt(x2 * x2 + y2 * y2);
    float x3 = (obstacle2X + 200 + 0.7 * 100) - (translateX + playerRadius + eyeRadius);
    float y3 = (obstacle2Y + 0.7 * 100) - (translateY + playerRadius + eyeRadius);
    float distance3 = sqrt(x3 * x3 + y3 * y3);
    if (window->KeyHold(GLFW_KEY_W)) {
        if (translateY < mapSize - eyeRadius - playerRadius) {
            if (distance1 < 0.4 * 100 + playerRadius + eyeRadius || distance2 < 0.4 * 100 + playerRadius + eyeRadius || distance3 < 0.4 * 100 + playerRadius + eyeRadius) {
                translateY -= 0.3 * 100;
                y -= 0.3 * 100;
                hpY -= 0.3 * 100;
                if (HP > 0.001) {
                    HP -= 0.1;
                }
            }
            if (distance < 0.4 * 100 + playerRadius + eyeRadius) {
                translateY -= 0.3 * 100;
                y -= 0.3 * 100;
                hpY -= 0.3 * 100;
                if (HP > 0.001) {
                    HP -= 0.1;
                }
            }
            if (distance11 < 0.4 * 100 + playerRadius + eyeRadius) {
                translateY -= 0.3 * 100;
                y -= 0.3 * 100;
                hpY -= 0.3 * 100;
                if (HP > 0.001) {
                    HP -= 0.1;
                }
            }
            else {
                translateY += 150 * deltaTime;
                y += 150 * deltaTime;
                hpY += 150 * deltaTime;
            }
        }
    }
    if (window->KeyHold(GLFW_KEY_A)) {
        if (translateX > 0 + eyeRadius + playerRadius) {
            if (distance1 < 0.5 * 100 + playerRadius + eyeRadius || distance2 < 0.5 * 100 + playerRadius + eyeRadius || distance3 < 0.5 * 100 + playerRadius + eyeRadius) {
                translateX += 0.2 * 100;
                x += 0.2 * 100;
                hpX += 0.2 * 100;
                if (HP > 0.001) {
                    HP -= 0.1;
                }
            }
            if (distance < 0.5 * 100 + playerRadius + eyeRadius) {
                translateX += 0.2 * 100;
                x += 0.2 * 100;
                hpX += 0.2 * 100;
                if (HP > 0.001) {
                    HP -= 0.1;
                }
            }
            if (distance11 < 0.5 * 100 + playerRadius + eyeRadius) {
                translateX += 0.2 * 100;
                x += 0.2 * 100;
                hpX += 0.2 * 100;
                if (HP > 0.001) {
                    HP -= 0.1;
                }
            }
            else {
                translateX -= 150 * deltaTime;
                x -= 150 * deltaTime;
                hpX -= 150 * deltaTime;
            }
        }
    }
    if (window->KeyHold(GLFW_KEY_S)) {
        if (translateY > 0 + 30) {
            if (distance1 < 0.5 * 100 + playerRadius + eyeRadius || distance2 < 0.5 * 100 + playerRadius + eyeRadius || distance3 < 0.5 * 100 + playerRadius + eyeRadius) {
                translateY += 0.2 * 100;
                y += 0.2 * 100;
                hpY += 0.2 * 100;
                if (HP > 0.001) {
                    HP -= 0.1;
                }
            }
            if (distance < 0.5 * 100 + playerRadius + eyeRadius) {
                translateY += 0.2 * 100;
                y += 0.2 * 100;
                hpY += 0.2 * 100;
                if (HP > 0.001) {
                    HP -= 0.1;
                }
            }
            if (distance11 < 0.5 * 100 + playerRadius + eyeRadius) {
                translateY += 0.2 * 100;
                y += 0.2 * 100;
                hpY += 0.2 * 100;
                if (HP > 0.001) {
                    HP -= 0.1;
                }
            }
            else {
                translateY -= 150 * deltaTime;
                y -= 150 * deltaTime;
                hpY -= 150 * deltaTime;
            }
        }
    }
    if (window->KeyHold(GLFW_KEY_D)) {
        if (translateX < mapSize - 30) {
            if (distance1 < 0.4 * 100 + playerRadius + eyeRadius || distance2 < 0.4 * 100 + playerRadius + eyeRadius || distance3 < 0.4 * 100 + playerRadius + eyeRadius) {
                translateX -= 0.3 * 100;
                x -= 0.3 * 100;
                hpX -= 0.3 * 100;
                if (HP > 0.001) {
                    HP -= 0.1;
                }
            }
            if (distance < 0.4 * 100 + playerRadius + eyeRadius) {
                translateX -= 0.3 * 100;
                x -= 0.3 * 100;
                hpX -= 0.3 * 100;
                if (HP > 0.001) {
                    HP -= 0.1;
                }
            }
            if (distance11 < 0.4 * 100 + playerRadius + eyeRadius) {
                translateX -= 0.3 * 100;
                x -= 0.3 * 100;
                hpX -= 0.3 * 100;
                if (HP > 0.001) {
                    HP -= 0.1;
                }
            }
            else {
                translateX += 150 * deltaTime;
                x += 150 * deltaTime;
                hpX += 150 * deltaTime;
            }
        }
    }
    if (timeAttack == true) {
        HP -= 0.0015;
    }
}



void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
    if (window->KeyHold(GLFW_KEY_T)) {
        std::cout << "Time Attack Mode Started! Good Luck!" << endl;
        timeAttack = true; 
    }
    

}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
    glm::ivec2 resolution = window->GetResolution();
    float dx = x + mouseX - (translateX);
    float dy = y + resolution.y - mouseY - (translateY);
    angularStep = glm::atan(dy, dx) - pi/2;
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
    glm::ivec2 resolution = window->GetResolution();
    time2 = glfwGetTime();
    if (time2 - time1 > 0.5) {
        shoot = true;
        x_player = translateX;
        y_player = translateY;
        bulletDistanceX = x + mouseX - translateX;
        bulletDistanceY = y + resolution.y - mouseY - translateY;
        angularStep2 = glm::atan(bulletDistanceY, bulletDistanceX) + pi/2;
        if (bulletDistanceX > 0 && bulletDistanceY > 0) {
            cadran = 1;
        }
        if (bulletDistanceX < 0 && bulletDistanceY > 0) {
            cadran = 2;
        }
        if (bulletDistanceX < 0 && bulletDistanceY < 0) {
            cadran = 3;
        }
        if (bulletDistanceX > 0 && bulletDistanceY < 0) {
            cadran = 4;
        }
    }
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}
