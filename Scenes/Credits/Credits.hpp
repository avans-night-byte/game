#include "../../../API/Rendering/EngineRenderingAPI.hpp"
#include "../../../API/Engine/EngineWindowAPI.hpp"
#include "../../../API/Audio/AudioAPI.hpp"
#include "../../../Engine/Input/Input.hpp"

class Credits {
public:
    static void init(RenderingAPI *renderAPI, EngineWindowAPI *engineWindowAPI, AudioAPI *audioApi);
    static void render(RenderingAPI *renderAPI, EngineWindowAPI *engineWindowAPI, Input i);
};