#include "Scene.h"
#include "GameObject.h"
#include "GameMaster.h"
#include "Components/Camera.h"

using namespace eng;

Scene::Scene(std::string name)
{
    this->name = name;
    b2Vec2 gravity(0, 0);
    world = new b2World(gravity);
    collisionEventManager = new CollisionEventManager(this);
    (*world).SetContactListener(collisionEventManager);
    physicThread = new sf::Thread(&Scene::PhysicsLoop, this);
    physicThread->launch(); 
}

b2World* Scene::GetWorld() const 
{
    return this->world;
}

std::list<GameObject*> Scene::GetGameObjects() const
{
    return this->sceneObjects;
}

void Scene::AddGameObject(GameObject* object)
{
    this->sceneObjects.push_back(object);
}

GameObject* Scene::FindGameObject(std::string objectName) const
{
    for(GameObject* gameObject : sceneObjects)
    {
        if(gameObject->GetName() == objectName) return gameObject;
    }

    return nullptr;
}

std::list<GameObject*> Scene::FindGameObjects(std::string objectName) const
{
    std::list<GameObject*> findedObjects;

    for(GameObject* gameObject : sceneObjects)
    {
        if(gameObject->GetName() == objectName) findedObjects.push_back(gameObject);
    }

    return findedObjects;
}

void Scene::RemoveFromScene(GameObject* gameObject)
{
    sceneObjects.remove(gameObject);
}

void Scene::PhysicsLoop() {
    while(GameMaster::Get().IsGameStarted())
    {          
        float32 timeStep = 0.02f; 
        world->Step(timeStep, velocityIterations, positionIterations);
        for (GameObject* gameObject : sceneObjects) {
           auto components = gameObject->GetComponents();
           for (Component * component : components) {
               component->FixedUpdate();
           }
        }
        
        sf::sleep(sf::milliseconds(20));
    }
}