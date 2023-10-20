#pragma once
#include "Node.h"

class Scene : public Node{
public:
    Scene();
    virtual ~Scene() {
        m_Nodes.clear();
    }

    void AddNode(const std::string& name, Node* node){
        std::cout<<"Adding Node: "<<name<<std::endl;
        m_Nodes.push_back(std::make_pair(name, node));
    }
    void OnUpdate(float deltaTime){
        for(auto node: m_Nodes){
            node.second->OnUpdate(deltaTime);
        }
    }
    void OnRender(){
        for(auto node: m_Nodes){
            node.second->OnRender();
        }
    }
    void OnImGuiRender(){
        for(auto node: m_Nodes){
            node.second->OnImGuiRender();
        }
    }

private:
    std::vector<std::pair<std::string,Node*>> m_Nodes;
};