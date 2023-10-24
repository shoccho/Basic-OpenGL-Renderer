#pragma once

#include "Node.h"
#include "Renderable.h"

class Scene : public Node {
public:
    Scene() {};

    virtual ~Scene() {
        m_Nodes.clear();
    }

    void AddNode(const std::string &name, std::shared_ptr<Renderable> renderable);

    void OnUpdate(float deltaTime);

    void OnRender();

    void OnImGuiRender();

    const std::vector<std::pair<std::string, std::shared_ptr<Renderable>>> &GetMNodes() const;

private:
    std::vector<std::pair<std::string, std::shared_ptr<Renderable >>> m_Nodes;
};