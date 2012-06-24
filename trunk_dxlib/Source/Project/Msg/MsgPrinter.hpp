#ifndef IncludeGuardMsgPrinter
#define IncludeGuardMsgPrinter

#include <string>

/**
    ���b�Z�[�W�\���N���X.
*/
class MsgPrinter
{
public:
    MsgPrinter();
    ~MsgPrinter();
public:
    void Update();
    void Draw() const;
    void SetMsg(std::string str);
private:
    void Init();
private:
    int m_count_frame;
    int m_msg_speed;
    int m_visible_index; //!< ������ŕ\�����镔���܂ł̃C���f�b�N�X.
    std::string m_msg;
    int m_x;
    int m_y;
};


#endif IncludeGuardMsgPrinter

