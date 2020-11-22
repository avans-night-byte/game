#include "../../../API/Rendering/EngineRenderingAPI.hpp"
#include "../../../API/Engine/EngineWindowAPI.hpp"
#include "../../../API/Audio/AudioAPI.hpp"
#include "../../../Engine/Input/Input.hpp"

class Credits {
public:
    static void init(EngineRenderingAPI *renderAPI, EngineWindowAPI *engineWindowAPI, AudioAPI *audioApi);
    static void render(EngineRenderingAPI *renderAPI, EngineWindowAPI *engineWindowAPI, Input i);
};