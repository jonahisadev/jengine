#include "Animate.h"

#include <utility>

namespace JEngine {

    std::vector<Animation*> Animate::_animations;

    LinearAnimation::LinearAnimation(const Vector2f &from, const Vector2f &to, int ms, Animation::Type type, translate_func translate)
        : Animation(ms), _from(from), _to(to), _translate(std::move(translate))
    {
        if (type == Relative) {
            _to = { from.x() + to.x(), from.y() + to.y()};
        }

        Vector2f diff = {_to.x() - _from.x(), _to.y() - _from.y()};
        _dpms = {diff.x() / float(ms), diff.y() / float(ms) };
    }

    void LinearAnimation::go(float delta) {
        float current_ms = (delta * 100);
        _ms -= current_ms;

        if (_ms <= 0) {
            float last = std::abs(_ms);
            _translate({_dpms.x() * -last, _dpms.y() * -last});
            _finished = true;
        }

        _translate({_dpms.x() * current_ms, _dpms.y() * current_ms });
    }

    SingleVarAnimation::SingleVarAnimation(float from, float to, int ms, Animation::Type type, single_func translate)
            : Animation(ms), _from(from), _to(to), _translate(std::move(translate))
    {
        if (type == Relative) {
            _to = _from + _to;
        }

        _dpms = (to - from) / float(ms);
    }

    void SingleVarAnimation::go(float delta) {
        float current_ms = (delta * 100);
        _ms -= current_ms;

        if (_ms <= 0) {
            float last = std::abs(_ms);
            _translate(_dpms * -last);
            _finished = true;
        }

        _translate(_dpms * current_ms);
    }

    void Animate::run(float delta) {
        auto it = _animations.begin();
        while (it != _animations.end()) {
            if ((*it)->finished()) {
                delete(*it);
                it = _animations.erase(it);
            } else {
                (*it)->go(delta);
                ++it;
            }
        }
    }

    void Animate::linear(const Vector2f &from, const Vector2f &to, int ms, Animation::Type type, translate_func translate) {
        _animations.push_back(new LinearAnimation(from, to, ms, type, translate));
    }

    void Animate::singleVar(float from, float to, int ms, Animation::Type type, single_func translate) {
        _animations.push_back(new SingleVarAnimation(from, to, ms, type, translate));
    }

}