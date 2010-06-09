#ifndef include_guard_7987b1ea_6bbe_469d_a1c0_4422eab02445
#define include_guard_7987b1ea_6bbe_469d_a1c0_4422eab02445

#include <string>
#include <vector>

typedef std::vector<std::string> ImageNameList;

/**
    �摜�̃��[�h���s���N���X.
*/
class ImageLoader
{
public:
    friend ImageLoader* new_ImageLoader( ImageNameList& name_list );
    virtual ~ImageLoader(){}
    
public:
    /**
        �������A�̃��[�h.
    */
    virtual void Load() = 0;
    
    /**
        �摜�n���h����Ԃ�.
    */
    virtual int ImageHandleOf( char const* name ) = 0;
    
private:
    class Impl;
};

#endif //include_guard_7987b1ea_6bbe_469d_a1c0_4422eab02445

