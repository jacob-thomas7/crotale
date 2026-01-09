#include "SDL3/SDL_video.h"
#include "SDL3/SDL_render.h"

#include "core/application.hpp"
#include "core/system.hpp"
#include "utils/runtime.hpp"
#include "gamedev/window.hpp"

using namespace crotale;

class MyGame : public core::System
{
public:
    MyGame() : System(this)
    {
        add_event_handler(&MyGame::on_render);
    }

    void on_render(gamedev::Render& event)
    {
        // This is an example of an event which also passes information.
        SDL_Renderer* renderer = event.get_renderer();

        int window_width;
        int window_height;
        SDL_GetWindowSizeInPixels(event.get_window(), &window_width, &window_height);

        box.x += velocity.x;
        box.y += velocity.y;

        // Bounce on walls
        if ((box.x + box.w > window_width) || (box.x < 0)) { velocity.x *= -1; }
        if ((box.y + box.h > window_height) || (box.y < 0)) { velocity.y *= -1; }

        // If out of bounds due to screen resizing during movement, just go back to center
        if ((box.x > window_width) || (box.x + box.w < 0)) { box.x = window_width / 2; }
        if ((box.y > window_height) || (box.y + box.h < 0)) { box.y = window_height / 2; }

        SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &box);
    }

private:
    SDL_FRect box { 500, 500, 100, 100 };
    struct {
        int x = 3;
        int y = 3;
    } velocity;
};

int main()
{
    core::Application application;
    
    application.register_system<gamedev::Window>("My Game");
    application.register_system<utils::Runtime>();
    application.register_system<MyGame>();

    application.loop();
}