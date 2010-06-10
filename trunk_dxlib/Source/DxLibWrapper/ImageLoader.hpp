#ifndef include_guard_7987b1ea_6bbe_469d_a1c0_4422eab02445
#define include_guard_7987b1ea_6bbe_469d_a1c0_4422eab02445

/**
    画像のロードを行うクラス.
    @note   大規模な開発を想定していないので、
            全データをメモリにロードする事が前提のインターフェース.
            ロードに関しては長くなる可能性があるので、Load処理は別途行えるようにする.
*/
class ImageLoader
{
public:
    /**
        生成関数.
        @param name_list 使用する画像名のリスト.
    */
    friend ImageLoader* new_ImageLoader( char const* const name_list[] );
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

