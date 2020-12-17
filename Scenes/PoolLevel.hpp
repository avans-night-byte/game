#pragma onec


#include "LevelBase.hpp"
#include "../Object/Pool.hpp"

class PoolLevel : public LevelBase {
private:
    std::vector<std::unique_ptr<Pool>> _poolList{};

    std::vector<std::string> _loadedEntities{};

public:
    void initialize(const std::string &name, const LevelData &data) override;

    void render() override;

    void update(const Input &inputSystem) override;

    void fixedUpdate(float deltaTime) override;

    void clearEntities() override;

    void addPool(const std::string& loadList,
                 const std::string& entityName,
                 int startAmount);

    Pool &getPool(const std::string &poolName);
};