#ifndef include_guard_7987b1ea_6bbe_469d_a1c0_4422eab02445
#define include_guard_7987b1ea_6bbe_469d_a1c0_4422eab02445

/**
    �摜�̃��[�h���s���N���X.
    @note   ��K�͂ȊJ����z�肵�Ă��Ȃ��̂ŁA
            �S�f�[�^���������Ƀ��[�h���鎖���O��̃C���^�[�t�F�[�X.
            ���[�h�Ɋւ��Ă͒����Ȃ�\��������̂ŁALoad�����͕ʓr�s����悤�ɂ���.
*/
class ImageLoader
{
public:
    /**
        �����֐�.
        @param name_list �g�p����摜���̃��X�g.
        @param list_size ���X�g�̃T�C�Y.
    */
    friend ImageLoader* new_ImageLoader( char const* const name_list[] , int list_size );
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

ImageLoader* new_ImageLoader( char const* const name_list[] );

#endif

