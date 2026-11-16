#pragma once

#include <unordered_map>
class ImGuiManager;

class MaterialTesterGame : public fw::GameCore
{
public:
    MaterialTesterGame(fw::FWCore* framework);
    virtual ~MaterialTesterGame();

    void reset();
    virtual void update(float deltaTime) override;
    virtual void draw() override;
    virtual void onKey(int keyCode, bool pressed) override;
    virtual void onFocus() override;

private:
    ImGuiManager* m_pImGuiManager = nullptr;
    fw::Camera* m_pCamera = nullptr;

    std::unordered_map<std::string, fw::Mesh*> m_meshes;
    fw::ShaderProgram* m_pTestShader = nullptr;
    fw::ShaderProgram* m_pFallbackShader = nullptr;

    fw::Texture* m_pUVTestTexture = nullptr;
    fw::Texture* m_pCloudTexture = nullptr;

    float m_percentage = 0;
};
