#include "lab_m1/Tema2/Tema2.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace m1;

Tema2::Tema2()
{
    int map_number = rand() % 7 + 1;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (map_number == 1) {
                map[i][j] = map1[i][j];
            }
            if (map_number == 2) {
                map[i][j] = map2[i][j];
            }
            if (map_number == 3) {
                map[i][j] = map3[i][j];
            }
            if (map_number == 4) {
                map[i][j] = map4[i][j];
            }
            if (map_number == 5) {
                map[i][j] = map5[i][j];
            }
            if (map_number == 6) {
                map[i][j] = map6[i][j];
            }
            if (map_number == 7) {
                map[i][j] = map7[i][j];
            }
        }
    }
    
    int x_aux, z_aux;
    while (!ok) {
        x_aux = rand() % 10;
        z_aux = rand() % 10;
        if (map[x_aux][z_aux] == 0 && x_aux != 0 && x_aux != 9 && z_aux != 0 && z_aux != 9) {
            ok = true;
        }
        x = (float)x_aux + 0.5;
        z = (float)z_aux + 0.5;
    }
}


Tema2::~Tema2()
{
}


void Tema2::Init()
{
    camera = new implemented::Camera2();
    camera->Set(glm::vec3(5, 11, 10), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
    camera->RotateThirdPerson_OY(-0.465);
    camera->RotateThirdPerson_OX(-0.4);
    
    {
        Mesh* mesh = new Mesh("box");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("plane");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "plane50.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("teapot");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "teapot.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Shader* shader = new Shader("LabShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    {
        lightPosition = glm::vec3(0, 10, 0);
        materialShininess = 30;
        materialKd = 0.5;
        materialKs = 0.5;
    }
    projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 100.0f);

}


void Tema2::FrameStart()
{
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema2::Update(float deltaTimeSeconds)
{
    if (map[(int)x][(int)z] == 2) {
        hp += 0.005;
    }
    if (x > 9.9 || z > 9.9 || x < 0 || z < 0) {
        cout << "You Won!" << endl;
        exit(0);
    }
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(x, y+0.85, z));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.25f));
        RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix, glm::vec3(0.9, 0.7, 0.5));
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(x, y+0.5, z));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
        RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix, glm::vec3(1, 1, 0));
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(x - 0.35, y + 0.6, z));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.15f));
        RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix, glm::vec3(1, 1, 0));
    }
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(x + 0.35, y + 0.6, z));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.15f));
        RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix, glm::vec3(1, 1, 0));
    }
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(x - 0.35, y + 0.45, z));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.15f));
        RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix, glm::vec3(0.9, 0.7, 0.5));
    }
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(x + 0.35, y + 0.45, z));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.15f));
        RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix, glm::vec3(0.9, 0.7, 0.5));
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(x - 0.15, y+0.15, z));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.25f));
        RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix, glm::vec3(1, 0.2, 1));
    }
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(x - 0.15, y, z));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.25f));
        RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix, glm::vec3(1, 0.2, 1));
    }
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(x + 0.15, y + 0.15, z));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.25f));
        RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix, glm::vec3(1, 0.2, 1));
    }
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(x + 0.15, y, z));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.25f));
        RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix, glm::vec3(1, 0.2, 1));
    }
    if (startGame == true) {
        time += deltaTimeSeconds / 4;
    }
    {
        projectionMatrix = glm::ortho(0.01f, 3.f, -4.f, 0.01f, 0.01f, 100.0f);
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, camera->GetTargetPosition() + camera->forward);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(1.5, -0.35, 0));

        if (2 - time > 0) {
            modelMatrix = glm::scale(modelMatrix, glm::vec3(2 - time, 0.5, 0.1));
        }
        else {
            cout << "Time's Up! Game Over!" << endl;
            exit(0);
        }
        RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix, glm::vec3(1, 0.4, 0.2));
        projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 100.0f);
    }
    {
        projectionMatrix = glm::ortho(0.01f, 3.f, -4.f, 0.01f, 0.01f, 100.0f);
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, camera->GetTargetPosition() + camera->forward);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(1.5, -1, 0));
        if (2 - hp > 0) {
            modelMatrix = glm::scale(modelMatrix, glm::vec3(2 - hp, 0.5, 0.1));
        }
        else {
            cout << "No HP Left! Game Over!" << endl;
            exit(0);
        }
        RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix, glm::vec3(0, 0, 1));
        projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 100.0f);
    }
    
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(5, 0.8, 5));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
        RenderSimpleMesh(meshes["plane"], shaders["LabShader"], modelMatrix, glm::vec3(1, 0, 0));
    }
    if (move == true) {
        moveX += deltaTimeSeconds;
    }
    if (move == false) {
        moveX -= deltaTimeSeconds;
    }
    if (moveX > 0.5) {
        move = false;
        move2 = false;
    }
    if (moveX < 0) {
        move = true;
        move2 = true;
    }
    if (move2 == true) {
        moveY = moveX;
    }
    if (move2 == false) {
        moveY = -moveX;
    }
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (map[i][j] == 1) {
                {
                    glm::mat4 modelMatrix = glm::mat4(1);
                    modelMatrix = glm::translate(modelMatrix, glm::vec3(i + 0.5, 1, j + 0.5));
                    modelMatrix = glm::scale(modelMatrix, glm::vec3(1, 2, 1));
                    RenderSimpleMesh(meshes["box"], shaders["LabShader"], modelMatrix, glm::vec3(1, 0.2, 1));
                }
            }
            if (map[i][j] == 2) {
                {
                    glm::mat4 modelMatrix = glm::mat4(1);
                    modelMatrix = glm::translate(modelMatrix, glm::vec3(i + 0.25 + moveX, 1.25 + moveY, j + 0.25 + moveX));
                    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5));
                    RenderSimpleMesh(meshes["teapot"], shaders["LabShader"], modelMatrix, glm::vec3(0, 1, 0));
                }
            }
        }
    }
}


void Tema2::FrameEnd()
{
    
}


void Tema2::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    glUseProgram(shader->program);

    GLint locLightPos = glGetUniformLocation(shader->program, "light_position");
    glUniform3fv(locLightPos, 1, glm::value_ptr(lightPosition));

    glm::vec3 eyePosition = camera->position;
    GLint locEyePos = glGetUniformLocation(shader->program, "eye_position");
    glUniform3fv(locEyePos, 1, glm::value_ptr(eyePosition));

    GLint locMaterial = glGetUniformLocation(shader->program, "material_shininess");
    glUniform1i(locMaterial, materialShininess);

    GLint locMaterialKd = glGetUniformLocation(shader->program, "material_kd");
    glUniform1f(locMaterialKd, materialKd);

    GLint locMaterialKs = glGetUniformLocation(shader->program, "material_ks");
    glUniform1f(locMaterialKs, materialKs);

    GLint locObject = glGetUniformLocation(shader->program, "object_color");
    glUniform3fv(locObject, 1, glm::value_ptr(color));

    GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
    glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    glm::mat4 viewMatrix = camera->GetViewMatrix();
    int loc_view_matrix = glGetUniformLocation(shader->program, "View");
    glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
    glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}

void Tema2::OnInputUpdate(float deltaTime, int mods)
{
        
        float cameraSpeed = 1;
        
        if (window->KeyHold(GLFW_KEY_UP)) {
            camera->MoveForward(cameraSpeed * deltaTime);
            z -= 2.5 * deltaTime;
            if (map[(int)x][(int)z] == 1) {
                camera->MoveForward(-0.1);
                z += 0.5;
            }
            
        }

        if (window->KeyHold(GLFW_KEY_LEFT)) {
            camera->TranslateRight(-cameraSpeed * deltaTime);
            x -= 2.5 * deltaTime;
            if (map[(int)x][(int)z] == 1) {
                camera->TranslateRight(0.1);
                x += 0.5;
                
            }
            
        }

        if (window->KeyHold(GLFW_KEY_DOWN)) {
            camera->MoveForward(-cameraSpeed * deltaTime);
            z += 2.5 * deltaTime;
            if (map[(int)x][(int)z] == 1) {
                camera->MoveForward(0.1);
                z -= 0.5;
            }
            
        }

        if (window->KeyHold(GLFW_KEY_RIGHT)) {
            camera->TranslateRight(cameraSpeed * deltaTime);
            x += 2.5 * deltaTime;
            if (map[(int)x][(int)z] == 1) {
                x -= 0.5;
                camera->TranslateRight(-0.1);
            }
        }

        if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
        {
            float cameraSpeed = 5;
            if (window->KeyHold(GLFW_KEY_W)) {
                camera->MoveForward(cameraSpeed * deltaTime);
            }

            if (window->KeyHold(GLFW_KEY_A)) {
                camera->TranslateRight(-cameraSpeed * deltaTime);
                
            }

            if (window->KeyHold(GLFW_KEY_S)) {
                camera->MoveForward(-cameraSpeed * deltaTime);
                
            }

            if (window->KeyHold(GLFW_KEY_D)) {
                camera->TranslateRight(cameraSpeed * deltaTime);
                
            }

            if (window->KeyHold(GLFW_KEY_E)) {
                camera->TranslateUpward(cameraSpeed * deltaTime);
            }

            if (window->KeyHold(GLFW_KEY_Q)) {
                camera->TranslateUpward(-cameraSpeed * deltaTime);
            }
        }
}


void Tema2::OnKeyPress(int key, int mods)
{
    if (window->KeyHold(GLFW_KEY_P)) {
        startGame = true;
    }
}


void Tema2::OnKeyRelease(int key, int mods)
{
}


void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
}


void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{  
}


void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
}


void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema2::OnWindowResize(int width, int height)
{
}
