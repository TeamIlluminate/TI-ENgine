#include "ShapeMesh.h"
#include "GameObject.h"

using namespace eng;

ShapeMesh::ShapeMesh(shared_ptr<sf::Shape> shape) : currentShape(shape) {}

weak_ptr<sf::Drawable> ShapeMesh::GetDrawable()
{
    currentShape->setPosition(owner.lock()->GetGlobalCoordinates());
    return (weak_ptr<sf::Drawable>) currentShape;
}

sf::RenderStates ShapeMesh::GetRenderStates() { return sf::RenderStates::Default; }