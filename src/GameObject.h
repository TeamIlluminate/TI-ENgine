#include "Utils.h"
#include "Transform.h"
#pragma once
namespace eng
{

class Component;

    class GameObject
    {
        public:

            GameObject(const std::string name = "empty");

            void AddChild(GameObject * child);
            sf::Vector2f GetGlobalCoordinates();
            std::list<GameObject *> GetChilds();
            GameObject * GetParent();


            //Add component to components list and set to him this gameobject as parent
            void AddNewComponent(Component * component);
            std::list<Component* > GetComponents() const; 
            template <class T>
            T *GetComponent()
            {
                for (Component* component : this->components)
                {
                    T *requeredComponent = dynamic_cast<T *>(component);
                    if (requeredComponent) return requeredComponent;
                }
                return nullptr;
            }

            //return true only if find and deleted 
            //not implemented
            bool RemoveComponent(Component * component);
            const std::string GetName() const;
            void SetName(const std::string newName);
            //Coordinates on scene OR coordinates on scene relative to parent (parent is 0 0 point)
            Transform transform = Transform(sf::Vector2f(0, 0));

        protected:

            GameObject * parent = nullptr;
            std::string name;
            std::list<GameObject *> childs;
            std::list<Component *> components;

    };
} // namespace eng