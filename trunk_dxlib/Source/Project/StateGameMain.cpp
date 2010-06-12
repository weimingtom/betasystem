#include "System/StateBase.hpp"

#include <assert.h>
#include <memory>
#include "DxLibWrapper/DxLibWrapper.hpp"
#include "DxLibWrapper/ImageLoader.hpp"


enum ImageType
{
    ImageType_Forest,
    ImageType_Num,
};

char const* const image_name[ ImageType_Num ] =
{
    "Resource/Image.png",
};

class StateGameMain : public StateBase
{
public:
    StateGameMain();
public:
    void Update();
    void Draw();
private:
    std::auto_ptr< ImageLoader > m_image_loader;
};

StateGameMain::StateGameMain()
 : m_image_loader( new_ImageLoader( image_name ) )
{
    m_image_loader->Load();
}

void StateGameMain::Update()
{
}

void StateGameMain::Draw()
{
    DrawFormatString( 0 , 0 , DefaultFontColor() , "GameMainState." );
    DrawGraph( 0 , 0 , m_image_loader->ImageHandleOf( image_name[ImageType_Forest] ) , TRUE );
}

StateBase* new_StateGameMain()
{
    return new StateGameMain();
}

