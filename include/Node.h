#pragma once
#include <string>
#include <vector>
#include <functional>
#include <iostream>

class Node{
    public:
        Node() {};
        virtual ~Node() {}

        virtual void OnUpdate(float deltaTime){}
        virtual void OnRender(){}
        virtual void OnImGuiRender(){}
};