#include "Animate.h"

#include <utility>

namespace JEngine {

    std::vector<Animation*> Animate::_animations;

    LinearAnimation::LinearAnimation(const Vector2f &from, const Vector2f &to, int ms, translate_func translate)
        : _from(from), _to(to), _ms(ms), _translate(std::move(translate))
    {
        Vector2f diff = {to.x() - from.x(), to.y() - from.y()};
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

    SingleVarAnimation::SingleVarAnimation(float from, float to, int ms, single_func translate)
            : _from(from), _to(to), _ms(ms), _translate(std::move(translate))
    {
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

    void Animate::linear(const Vector2f &from, const Vector2f &to, int ms, translate_func translate) {
        _animations.push_back(new LinearAnimation(from, to, ms, translate));
    }

    void Animate::singleVar(float from, float to, int ms, single_func translate) {
        _animations.push_back(new SingleVarAnimation(from, to, ms, translate));
    }

}