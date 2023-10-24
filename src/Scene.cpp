#include "Scene.h"

void Scene::AddNode(const std::string& name, std::shared_ptr<Renderable> renderable){
    m_Nodes.push_back(std::make_pair(name, renderable));
}
void Scene::OnUpdate(float deltaTime){
    for(auto node: m_Nodes){
        node.second->OnUpdate(deltaTime);
    }
}
void Scene::OnRender(){
    GL_CALL(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
    GL_CALL(glClear(GL_COLOR_BUFFER_BIT));

    for(auto node: m_Nodes){
        node.second->OnRender();
    }
}
void Scene::OnImGuiRender(){
    for(auto node: m_Nodes){
        node.second->OnImGuiRender();
    }
}

const std::vector<std::pair<std::string, std::shared_ptr<Renderable>>> &Scene::GetMNodes() const {
    return m_Nodes;
}
