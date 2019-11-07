#include "Light.h"

#include <cmath>

namespace JEngine {

    Light::Light(float x, float y, float diameter, const JEngine::Vector3f &color)
    : _diameter(diameter), _radius(diameter / 2)
    {
        float o = diameter / 2.0f;
        float buffer[] = {
            -o, -o, 0, 0,
             o, -o, 1, 0,
             o,  o, 1, 1,
            -o,  o, 0, 1
        };
        
        int els[] = {
            0, 1, 2,
            0, 3, 2
        };
        
        _mesh = std::make_shared<TexturedMesh>(buffer, color, els, 4, 6, "../assets/light.png");
        setPosition(x, y);
        _mesh->setColor(color);
        
        delete _mesh->_shader;
        _mesh->_shader = new Shader(Shader::DefaultLightVertexShader, Shader::DefaultLightFragmentShader);
    }

    Light::~Light() {
        _mesh.reset();
    }

    void Light::prepare(std::vector<Quad> &items) {
        // Save light boundaries
        _pos.translate(-_diameter / 2, -_diameter / 2);
        _points.emplace_back(_pos.x(), _pos.y());
        _points.emplace_back(_pos.x() + _diameter, _pos.y());
        _points.emplace_back(_pos.x() + _diameter, _pos.y() + _diameter);
        _points.emplace_back(_pos.x(), _pos.y() + _diameter);
        _pos.translate(_diameter / 2, _diameter / 2);
        
        // Go through each item
        for (auto& item : items) {
            
            // Skip blocks that don't block light
            if (!item.blocksLight())
                continue;
            
            // Go through each point
            for (int p = 0; p < 4; p++) {
                // Point
                auto point = item.getPoints()[p];
                
                // Convert to polar for check point
//                Vector2f dist = {point.x() - center().x(), point.y() - center().y()};
                Vector2f dist = {center().x() - point.x(), center().y() - point.y()};
                float theta = std::atan(dist.y() / dist.x());
                float r = Vector2f::distance(center(), point);
                
                // Go back just a tad
                r -= 0.001f;
                
                // Check if that point is within the quad
                Vector2f check_point = {r * std::cos(theta), r * std::sin(theta)};
                check_point.translate(item.y(), item.y());
                
                // Skip point
                if (item.intersects(check_point))
                    continue;
                
                // Go forward
                r += 0.002f;
                check_point = {r * std::cos(theta), r * std::sin(theta)};
                
                // This ray is tangent the object
                if (!item.intersects(check_point)) {
                    _points.emplace_back(_radius * std::cos(theta), _radius * std::sin(theta));
                }
                
                // Save point
                _points.push_back(point);
            }
        }
        
//        JINFO("Calculated points");
    }

    void Light::setPosition(float x, float y) {
        _pos.setX(x + (_diameter / 2));
        _pos.setY(y + (_diameter / 2));
        _mesh->setPosition(_pos);
    }

    void Light::setCenter(float x, float y) {
        setPosition(x - (_diameter / 2), y - (_diameter / 2));
    }

    void Light::render(JEngine::Matrix4f screen) {
        _mesh->render(screen);
        
        for (auto& point : _points) {
            Quad pt(0, 0, 5, 5);
            pt.setColor(255, 0, 0);
            pt.setCenter(point);
            pt.render(screen);
        }
        
        _points.clear();
    }

}