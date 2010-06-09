/**
    画像のロードを行うクラス.
*/
class ImageLoader
{
public:
    friend ImageLoader* new_ImageLoader( );
    virtual ~ImageLoader() = 0;
    
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

