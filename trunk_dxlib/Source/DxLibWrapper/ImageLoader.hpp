#ifndef include_guard_7987b1ea_6bbe_469d_a1c0_4422eab02445
#define include_guard_7987b1ea_6bbe_469d_a1c0_4422eab02445

#include <string>
#include <vector>

typedef std::vector<std::string> ImageNameList;

/**
    画像のロードを行うクラス.
*/
class ImageLoader
{
public:
    friend ImageLoader* new_ImageLoader( ImageNameList& name_list );
    virtual ~ImageLoader(){}
    
public:
    /**
        完了復帰のロード.
    */
    virtual void Load() = 0;
    
    /**
        画像ハンドルを返す.
    */
    virtual int ImageHandleOf( char const* name ) = 0;
    
private:
    class Impl;
};

#endif //include_guard_7987b1ea_6bbe_469d_a1c0_4422eab02445

