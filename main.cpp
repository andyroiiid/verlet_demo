#include <SDL.h>

#include "renderer.h"

const Vec2 constraintCenter{640.0f, 360.0f};
const float constraintRadius = 200.0f;

class Circle {
public:
    explicit Circle(const Vec2 &pos, float radius = 16.0f, const Vec2 &accel = {0.0f, 980.0f}) noexcept
            : radius(radius), currPos(pos), prevPos(pos), accel(accel) {}

    void applyConstraint() {
        const Vec2 deltaPos = currPos - constraintCenter;
        const float distance = deltaPos.length();
        if (distance > constraintRadius - radius) {
            currPos = constraintCenter + deltaPos.normalize() * (constraintRadius - radius);
        }
    }

    void verlet(float dtSquared) {
        const Vec2 deltaPos = currPos - prevPos;
        prevPos = currPos;
        currPos = currPos + deltaPos + accel * dtSquared;
    }

    void draw() const {
        drawCircle(currPos, radius);
    }

private:
    const float radius;
    Vec2 currPos;
    Vec2 prevPos;
    Vec2 accel;
};

Circle circle({800.0f, 360.0f});

void init() {
}

void eventCallback(const SDL_Event &event) {
}

void frameCallback(float deltaTime) {
    circle.applyConstraint();
    circle.verlet(deltaTime * deltaTime);

    setColor(RED);
    drawCircle(constraintCenter, constraintRadius);
    setColor(WHITE);
    circle.draw();
}

int main(int, char *[]) {
    SDL_Init(SDL_INIT_EVERYTHING);
    init();
    mainLoop(eventCallback, frameCallback);
    SDL_Quit();
    return 0;
}
