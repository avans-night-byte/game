#include "AIComponent.hpp"
#include "../Helpers/GameTime.h"

Component* AIComponent::build(EntityId entityId, const Components::component *component) {

    auto newAiComponent = new AIComponent(entityId);
    auto &aiComponent = component->AIComponent().get();

    auto &followingString = aiComponent.followingName();



    return newAiComponent;
}

void AIComponent::render() {
    // Nothing

    std::string color = "ffffff";

    for(auto& item : _path){
        auto pos = gridToPosition(item);
//        Game::getInstance()->getRenderingApi().drawRectangle(pos, 16 * 4, 16 * 4, color, 255);

            Vector2 vert[4]{};
            vert[0] = Vector2{pos.x, pos.y};
            vert[1] = Vector2{pos.x + (16 * 4), pos.y};
            vert[2] = Vector2{pos.x + (16 * 4), pos.y + (16 * 4)};
            vert[3] = Vector2{pos.x, pos.y + (16 * 4)};

          Game::getInstance()->getRenderingApi().drawBox(vert, 4);
    }
}

void AIComponent::update(const Input &inputSystem) {
    float time = GameTime::getInstance().getTotalTimeSeconds();


    if(time > _nextTime){
        _nextTime = time + _period;
        this->updatePath();
    }
}

void AIComponent::fixedUpdate(const float &deltaTime) {
    // Update path every x time.
    this->navigatePath(deltaTime);
}

void AIComponent::initialize(EntityObject &entityParent) {
    _parent = &entityParent;
}



std::string AIComponent::name() const {
    return "AIComponent";
}

void AIComponent::follow(EntityObject& entityObject){
    _following = &entityObject;
    _followTransform = true;
}

void AIComponent::updatePath() {
    // Get the target location and
    if(_followTransform){

        auto transform = _following->getTransform();
        auto position = transform->getPosition();
        auto pPosition = _parent->getTransform();



        // Transform into gridlocation and generate a path to it.
        auto goal = positionToGrid(position);


        if(!_path.empty()){
            if(goal == _path[_path.size()]){
                return;
            }
        }


        auto start = positionToGrid(Vector2{pPosition->getPosition().x, pPosition->getPosition().y});
        int** items;
        items = new int*[30];
        Game::getInstance()->getLevel().getLevel().GetGrid(items);
        auto grid = GridWithWeights::fromArray(items);

        // Cleanup.
        for (  int i = 0; i < 30; i++)
        {
            delete [] items[i];
        }
        delete [] items;

        items = nullptr;
        std::unordered_map<GridLocation, GridLocation>came_from{};
        std::unordered_map<GridLocation, double> cost_so_far{};
        std::vector<GridLocation> path = std::vector<GridLocation>();
        Astar::search(grid, start, goal,came_from, cost_so_far);

        Astar::reconstruct_path(path, start, goal, came_from);

        _path = path;

        std::cout << _path.size() << std::endl;
    }
}

GridLocation AIComponent::positionToGrid(Vector2 pos) {
    int x = pos.x / (16 * 4);
    int y = pos.y / (16 * 4);

    return GridLocation{x, y};
}


Vector2 AIComponent::gridToPosition(GridLocation location){
    float x = (location.x * (16 * 4));
    float y = (location.y * (16 * 4));
    return Vector2{x, y};
}

void AIComponent::navigatePath(const float& deltaTime) {
    auto currentPos = _parent->getTransform()->getPosition();


    if(_path.size() < 1)
        return;

    auto nextPos = gridToPosition(_path[_currentPosition]);


    nextPos.y = nextPos.y + 32;
    nextPos.x = nextPos.x + 32;


    float dx = (nextPos.x - currentPos.x);
    float dy = (nextPos.y - currentPos.y);

    // Normalize the items.
    float length = sqrtf(dx*dx+dy*dy);
    dx/=length;
    dy/=length;

    // Speed (constant of 1 for now)
    dx *= 1000 * deltaTime;
    dy *= 1000 * deltaTime;

    GridLocation gridLoc = positionToGrid(currentPos);

    if( gridLoc == positionToGrid(nextPos)){
        if(_currentPosition < _path.size()){
            _currentPosition++;
        }
        else{
            _currentPosition = 1;
        }
    }
    _parent->getPhysicsComponent()->setVelocity(Vector2{dx, dy});
}

AIComponent::AIComponent(EntityId &entityId) {
}


void AIComponent::postInitialize(EntityObject &entityObject) {
    auto* character = (EntityObject*) Game::getInstance()->getCharacter();

    this->follow(*character);
}
