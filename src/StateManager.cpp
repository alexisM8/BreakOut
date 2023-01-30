#include "../include/StateManager.hpp"

Engine::StateManager::StateManager(): m_add(false), 
                                      m_replace(false),
                                      m_remove(false){/*empty*/}

Engine::StateManager::~StateManager(){/*empty*/}

void Engine::StateManager::add(std::unique_ptr<State> toAdd, bool replace){
    m_add = true;
    m_newSate = std::move(toAdd);
    m_replace = replace;
}

void Engine::StateManager::popCurrent(){
    m_remove = true;
}

void Engine::StateManager::processStateChange(){
    if(m_remove && (!m_stateStack.empty())){
        m_stateStack.pop();
        if(!m_stateStack.empty()){
            m_stateStack.top()->Start();
        }
        m_remove = false;
    }
    if(m_add){
        if(m_replace && (!m_stateStack.empty())){
            m_stateStack.pop();
            m_replace = false;
        }
        if(!m_stateStack.empty()){
            m_stateStack.top()->Pause();
        }
        m_stateStack.push(std::move(m_newSate));
        m_stateStack.top()->Init();
        m_stateStack.top()->Start();
        m_add = false;
    }
    
}

std::unique_ptr<Engine::State>& Engine::StateManager::getCurrentState(){
    return m_stateStack.top();
}

int Engine::StateManager::getSize(){
    return m_stateStack.size();
}
 
