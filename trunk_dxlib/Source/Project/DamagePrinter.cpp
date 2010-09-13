#include "Project/DamagePrinter.hpp"

#include <vector>
#include <boost/foreach.hpp>
#include "DxLibWrapper/DxLibWrapper.hpp"
#include "DxLibWrapper/Color.hpp"

struct DamagePrintObject
{
    Vector2 pos;
    int damage;
    
    DamagePrintObject( Vector2 pos_ , int damage_ )
     : pos( pos_ )
     , damage( damage_ )
    {
    }
};

class DamagePrinter::Impl : public DamagePrinter
{
public:
    void Begin( Vector2 pos , int damage );
    void Update();
    void Draw();
private:
    std::vector< DamagePrintObject > m_object_list;
};

void DamagePrinter::Impl::Begin( Vector2 pos , int damage )
{
    m_object_list.push_back( DamagePrintObject( pos , damage ) );
}

void DamagePrinter::Impl::Update()
{
    int const EndLineY= 200;
    bool delete_flag = false ; // BOOST_FOREACH中は要素の削除が行えないので、削除するかどうかのフラグで管理する.
    BOOST_FOREACH( DamagePrintObject& object , m_object_list )
    {
        object.pos.y--;
        if( object.pos.y < EndLineY )
        {
            delete_flag = true;
        }
    }
    if( delete_flag )
    {
        m_object_list.erase( m_object_list.begin() );
    }
}

void DamagePrinter::Impl::Draw()
{
    BOOST_FOREACH( DamagePrintObject const& object , m_object_list )
    {
        DrawFormatString(
            static_cast<int>( object.pos.x ) , static_cast<int>( object.pos.y ),
            ColorOf( 255 , 255 , 255 ) ,
            "[%d]" , object.damage );
    }
}

DamagePrinter* new_DamagePrinter()
{
    return new DamagePrinter::Impl();
}

