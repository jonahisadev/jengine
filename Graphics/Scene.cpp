#include "Scene.h"

namespace JEngine {

    Scene::Scene(Display* d)
            : _projection(d->screen()), _view(1.0f)
    {}

    Scene::~Scene()
    {}

    void Scene::add(Quad* item)
    {
        _items.push_back(item);
    }

    void Scene::render()
    {
        for (auto* item : _items) {
            item->render(_projection * _view);
        }
    }

    void Scene::translate(const Vector2f& vec)
    {
        _view = glm::translate(_view, glm::vec3(vec.x(), vec.y(), 0));
    }

    void Scene::translateCamera(const Vector2f& vec)
    {
        translate(const_cast<Vector2f&>(vec) * -1);
    }

}