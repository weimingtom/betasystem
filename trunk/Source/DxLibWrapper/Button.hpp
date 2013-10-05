#ifndef include_c5b4571e_b687_429b_aa72_b7a2a9dd5334
#define include_c5b4571e_b687_429b_aa72_b7a2a9dd5334

#include <string>
#include <vector>
//#include <boost/shared_ptr.hpp>
#include "System/CollisionObject.hpp"

class Button : public CollisionObject
{
public:
    Button(
        int image_handle ,
        Vector2 pos ,
        Vector2 size ,
        std::string name = "" );
    
public:
    void Draw() const ;
    std::string Name() const { return m_name; };
    
private:
    int const m_image_handle;
    std::string const m_name;

};

//typedef boost::shared_ptr< Button > ButtonPtr;
//typedef std::vector< ButtonPtr > ButtonPtrList;

#endif

