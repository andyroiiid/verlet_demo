//
// Created by Andrew Huang on 4/15/2022.
//

#include "renderer.h"

#include <SDL_timer.h>

static SDL_Window *window = nullptr;
static SDL_Renderer *renderer = nullptr;

static constexpr int NUM_CIRCLE_POINTS = 13;
static const Vec2 CIRCLE_POINTS[NUM_CIRCLE_POINTS] = {
        {1.00000000f,  0.00000000f},
        {0.86602540f,  0.50000000f},
        {0.50000000f,  0.86602540f},
        {0.00000000f,  1.00000000f},
        {-0.50000000f, 0.86602540f},
        {-0.86602540f, 0.50000000f},
        {-1.00000000f, 0.00000000f},
        {-0.86602540f, -0.50000000f},
        {-0.50000000f, -0.86602540f},
        {-0.00000000f, -1.00000000f},
        {0.50000000f,  -0.86602540f},
        {0.86602540f,  -0.50000000f},
        {1.00000000f,  -0.00000000f},
};

void mainLoop(EventCallback onEvent, FrameCallback onFrame) {
    window = SDL_CreateWindow("VERLET demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, 0);
    renderer = SDL_CreateRenderer(window, -1, 0);

    const auto freq = static_cast<float>(SDL_GetPerformanceFrequency());
    Uint64 prevTime = SDL_GetPerformanceCounter();
    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
                break;
            }
            onEvent(event);
        }

        setColor(BLACK);
        SDL_RenderClear(renderer);

        const Uint64 currTime = SDL_GetPerformanceCounter();
        onFrame(static_cast<float>(currTime - prevTime) / freq);
        prevTime = currTime;

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void setColor(const SDL_Color &color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

void drawPoint(const Vec2 &p, float size) {
    const SDL_FRect rect{
            p.x - size * 0.5f,
            p.y - size * 0.5f,
            size,
            size
    };
    SDL_RenderDrawRectF(renderer, &rect);
}

void drawLine(const Vec2 &p1, const Vec2 &p2) {
    SDL_RenderDrawLineF(renderer, p1.x, p1.y, p2.x, p2.y);
}

void drawCircle(const Vec2 &center, float radius) {
    SDL_FPoint points[NUM_CIRCLE_POINTS];
    for (int i = 0; i < NUM_CIRCLE_POINTS; i++) {
        const Vec2 vertex = center + CIRCLE_POINTS[i] * radius;
        SDL_FPoint &point = points[i];
        point.x = vertex.x;
        point.y = vertex.y;
    }
    SDL_RenderDrawLinesF(renderer, points, NUM_CIRCLE_POINTS);
}
