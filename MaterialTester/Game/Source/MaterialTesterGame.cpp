#include "Framework.h"
#include "Imgui.h"

#include "GameDataTypes.h"
#include "ImGuiManager.h"
#include "MaterialTesterGame.h"

MaterialTesterGame::MaterialTesterGame(fw::FWCore* framework)
    : GameCore( framework )
{
    onFocus();

    m_pImGuiManager = new ImGuiManager( framework );

    m_pFallbackShader = new fw::ShaderProgram( "Data/Fallback.vert", "Data/Fallback.frag" );

    // Create meshes.
    //m_meshes["tile"] = new fw::Mesh( GL_TRIANGLE_STRIP, {
    //    { {-0.9f,-0.9f}, 255,255,255,255, {0,0} },
    //    { { 0.9f,-0.9f}, 255,255,255,255, {1,0} },
    //    { {-0.9f, 0.9f}, 255,255,255,255, {0,1} },
    //    { { 0.9f, 0.9f}, 255,255,255,255, {1,1} } } );

    vec2 vertCount = {20,20};
    vec2 startPos = {-0.9f,-0.9f};
    vec2 size = {1.8f,1.8f};
    vec2 step = size / (vertCount-1);
    vec2 uvStep = 1.0f / (vertCount-1);
    std::vector<fw::VertexFormat> verts;
    for( int y=0; y<vertCount.y-1; y++ )
    {
        for( int x=0; x<vertCount.x-1; x++ )
        {
            verts.push_back( {startPos + step*vec2((float)x  ,(float)y  ), 255,255,255,255, uvStep*vec2((float)x  ,(float)y  )} );
            verts.push_back( {startPos + step*vec2((float)x+1,(float)y  ), 255,255,255,255, uvStep*vec2((float)x+1,(float)y  )} );
            verts.push_back( {startPos + step*vec2((float)x  ,(float)y+1), 255,255,255,255, uvStep*vec2((float)x  ,(float)y+1)} );
            verts.push_back( {startPos + step*vec2((float)x  ,(float)y+1), 255,255,255,255, uvStep*vec2((float)x  ,(float)y+1)} );
            verts.push_back( {startPos + step*vec2((float)x+1,(float)y  ), 255,255,255,255, uvStep*vec2((float)x+1,(float)y  )} );
            verts.push_back( {startPos + step*vec2((float)x+1,(float)y+1), 255,255,255,255, uvStep*vec2((float)x+1,(float)y+1)} );
        }
    }
    m_meshes["tile"] = new fw::Mesh( GL_TRIANGLES, verts );

    // Create a camera.
    m_pCamera = new fw::Camera();

    float aspectRatio = (float)framework->getWindowWidth() / framework->getWindowHeight();
    m_pCamera->setAspectRatio( aspectRatio );

    m_pUVTestTexture = new fw::Texture( "Data/TexelDensityTexture.png" );
    m_pCloudTexture = new fw::Texture( "Data/Clouds.png" );

    reset();
}

MaterialTesterGame::~MaterialTesterGame()
{
    for( const auto& meshPair : m_meshes )
    {
        delete meshPair.second;
    }

    delete m_pCamera;

    delete m_pTestShader;
    delete m_pFallbackShader;

    delete m_pImGuiManager;
}

void MaterialTesterGame::reset()
{
}

void MaterialTesterGame::update(float deltaTime)
{
    m_pImGuiManager->startFrame( deltaTime );

    m_pCamera->update( deltaTime );

    if( ImGui::Begin("Shader Compiler", nullptr, ImGuiWindowFlags_AlwaysAutoResize) )
    {
        ImGui::SliderFloat( "Percentage", &m_percentage, 0, 1 );
        static bool checked = false;
        if( ImGui::Checkbox("WireFrame", &checked) )
        {
            glPolygonMode( GL_FRONT_AND_BACK, checked ? GL_LINE : GL_FILL );
        }
    }
    ImGui::End();

    if( m_pTestShader->isValid() == false )
    {
        if( m_pTestShader->getLastErrorMessage() )
        {
            if( ImGui::Begin("Shader Compiler", nullptr, ImGuiWindowFlags_AlwaysAutoResize) )
            {
                ImGui::Text( m_pTestShader->getLastErrorMessage() );
            }
            ImGui::End();
        }
    }

}

void MaterialTesterGame::draw()
{
    glClearColor( 0.0f, 0.0f, 0.3f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT );
    glPointSize( 10.0f );

    fw::ShaderProgram* shaderToUse = m_pTestShader->isValid() ? m_pTestShader : m_pFallbackShader;
    m_meshes["tile"]->draw( m_pCamera, shaderToUse, 1, 0, 0, color4f::white(), m_pUVTestTexture, m_pCloudTexture, m_percentage );

    m_pImGuiManager->endFrame();

    m_pFramework->swapBuffers();
}

void MaterialTesterGame::onKey(int keyCode, bool pressed)
{
    if( pressed == true && keyCode == 'R' )
    {
        reset();
    }
}

void MaterialTesterGame::onFocus()
{
    delete m_pTestShader;
    m_pTestShader = new fw::ShaderProgram( "Data/Test.vert", "Data/Test.frag" );
}
