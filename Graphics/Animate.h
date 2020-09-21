#pragma once

#include <vector>
#include <functional>
#include <cmath>
#include "../Math/Vector.h"
#include "../Util/Logger.h"

namespace JEngine {
    
    // Definitions
    typedef std::function<void(const Vector2f&)> translate_func;
    typedef std::function<void(float)> single_func;

    // Base Animation
    class Animate;
    class Animation
    {
    public:
        enum Type {
            Absolute,
            Relative
        };

    protected:
        float _ms;
        Type _type;
        bool _finished = false;

        Animation(int ms) : _ms(ms) {}
        virtual ~Animation() = default;

        virtual void go(float delta) = 0;
        bool finished() const { return _finished; }
        friend class Animate;
    };

    // LinearAnimation
    class LinearAnimation : public Animation
    {
    private:
        Vector2f _from;
        Vector2f _to;
        Vector2f _dpms;
        translate_func _translate;

    protected:
        void go(float delta) override;

    public:
        LinearAnimation(const Vector2f& from, const Vector2f& to, int ms, Animation::Type type, translate_func translate);
    };

    class SingleVarAnimation : public Animation
    {
    private:
        float _from;
        float _to;
        float _dpms;
        single_func _translate;

    protected:
        void go(float delta) override;

    public:
        SingleVarAnimation(float from, float to, int ms, Animation::Type type, single_func translate);
    };

    // "Factory"
    class Animate
    {
    private:
        static std::vector<Animation*> _animations;

    public:
        static void run(float delta);
        static void linear(const Vector2f& from, const Vector2f& to, int ms, Animation::Type type, translate_func translate);
        static void singleVar(float from, float to, int ms, Animation::Type type, single_func translate);
    };

}