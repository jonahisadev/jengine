#pragma once

#include <vector>
#include <functional>
#include <cmath>
#include "../Math/Vector.h"
#include "../Util/Logger.h"

namespace JEngine {
    
    // Definitions
    typedef std::function<void(const Vector2f&)> translate_func;

    // Base Animation
    class Animate;
    class Animation {
    protected:
        bool _finished = false;

        virtual void go(float delta) = 0;
        bool finished() { return _finished; }
        friend class Animate;
    };

    // LinearAnimation
    class LinearAnimation : public Animation {
    private:
        Vector2f _from;
        Vector2f _to;
        float _ms;
        Vector2f _ppms;
        translate_func _translate;

    protected:
        void go(float delta) override;

    public:
        LinearAnimation(const Vector2f& from, const Vector2f& to, int ms, translate_func translate);
    };

    // "Factory"
    class Animate {
    private:
        static std::vector<Animation*> _animations;

    public:
        static void run(float delta);
        static void linear(const Vector2f& from, const Vector2f& to, int ms, translate_func translate);
    };

}