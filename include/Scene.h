#pragma once
#include "Node.h"

class Scene : public Node{
public:
    Scene(Node*& currentTestPointer);
    virtual ~Scene() {}

    void OnImGuiRender() override;

    template<typename T>
    void AddTest(const std::string& name){
        std::cout<<"Adding test: "<<name<<std::endl;
        m_Tests.push_back(std::make_pair(name, [](){return new T();}));
    }
private:
    Node*& m_CurrentTest;
    std::vector<std::pair<std::string, std::function<Node*()> >> m_Tests;
};