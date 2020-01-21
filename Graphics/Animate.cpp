#include "Animate.h"

#include <utility>

namespace JEngine {

    std::vector<Animation*> Animate::_animations;

    LinearAnimation::LinearAnimation(const Vector2f &from, const Vector2f &to, int ms, translate_func translate)
        : _from(from), _to(to), _ms(ms), _translate(std::move(translate))
    {
        _dist = { to.x() - from.x(), to.y() - from.y() };
        _current_ms = _ms;
    }

    void LinearAnimation::go(float delta) {
        _current_ms -= (delta * 100);

        // TODO: movement

        if (_current_ms <= 0)
            _finished = true;
    }

    void Animate::run(float delta) {
        for (auto* a : _animations) {
            if (a->finished()) {
                // TODO: remove from list
                continue;
            }
            a->go(delta);
        }
    }

    void Animate::linear(const Vector2f &from, const Vector2f &to, int ms, translate_func translate) {
        _animations.push_back(new LinearAnimation(from, to, ms, translate));
    }

}