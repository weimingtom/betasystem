/**
    �摜�̃��[�h���s���N���X.
*/
class ImageLoader
{
public:
    friend ImageLoader* new_ImageLoader( );
    virtual ~ImageLoader() = 0;
    
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

