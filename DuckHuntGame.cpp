#include "DuckHuntGame.h"
#include "TimerManager.h"
#include "AudioManager.h"
#include "CameraManager.h"
#include "Level.h"
#include "HUD.h"

using namespace Camera;
using namespace UI;

DuckHuntGame::DuckHuntGame() : Game()
{
    background = nullptr;
    music = nullptr;
    floor = nullptr;
    wall1 = nullptr;
    wall2 = nullptr;
    ball = nullptr;
    label = nullptr;
    scrollBar = nullptr;
}

void DuckHuntGame::Start()
{
    Super::Start();

    MeshActor* _background = Level::SpawnActor(MeshActor(RectangleShapeData(Vector2f(window.getSize()), "Background_2", JPG)));

    /*const Vector2f& _floorSize = Vector2f(window.getSize().x, window.getSize().y * 0.2f);
    floor = Level::SpawnActor(MeshActor(RectangleShapeData(_floorSize, "Floor_2", JPG)));
    floor->SetPosition(Vector2f(0.0f, window.getSize().y - _floorSize.y));

    const Vector2f& _wallSize = Vector2f(window.getSize().x * 0.05f, window.getSize().y * 0.6f - _floorSize.y);

    wall1 = Level::SpawnActor(MeshActor(RectangleShapeData(_wallSize, "Wall", JPG)));
    wall1->SetPosition(Vector2f(0.0f, window.getSize().y * 0.4f));

    wall2 = Level::SpawnActor(MeshActor(RectangleShapeData(_wallSize, "Wall", JPG)));
    wall2->SetPosition(Vector2f(window.getSize().x - _wallSize.x, window.getSize().y * 0.4f));

    ball = Level::SpawnActor(Ball(20.0f));
    ball->SetOriginAtMiddle();
    ball->SetPosition(Vector2f(window.getSize().x * 0.5f, window.getSize().y * 0.3f));
    M_CAMERA.GetCurrent()->SetTarget(ball);*/

    // Création de la ScrollBar
    scrollBar = Level::SpawnActor(ScrollBar(MeshActor(RectangleShapeData(Vector2f(20.0f, 80.0f), "ScrollBar", JPG)), 10,
        [](bool directionUp)
        {
            if (directionUp)
                cout << "haut" << endl;
            else
                cout << "bas" << endl;
        }));

    scrollBar->SetPosition(Vector2f(200, 500));
    scrollBar->SetZOrder(10);
}

bool DuckHuntGame::Update()
{
    Super::Update();



    return IsOver();
}

void DuckHuntGame::Stop()
{
    Super::Stop();
}