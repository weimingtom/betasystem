#ifndef include_9c91857f_e579_42a8_89bc_72c3a5338feb
#define include_9c91857f_e579_42a8_89bc_72c3a5338feb
/**
    ���s���̕ϐ������������T�|�[�g����N���X.
    
    [�L�[(������)],[�l]
    �̃t�H�[�}�b�g�ŋL�q�����e�L�X�g����͂��A
    �l�����o�����Ƃ��o����.
*/
class RewritableVariable
{
public:
    friend RewritableVariable* new_RewritableVariable( char const* file_name );
    virtual ~RewritableVariable(){}
    
public:
    /**
        �l�̓ǂݒ���.
    */
    virtual void Reload() = 0;
    
    /**
        �l�̎擾.
    */
    virtual int VariableOf( char const* key ) = 0;
    
private:
    class Impl;
};

#endif

