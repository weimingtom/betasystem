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
    enum Step{
        Step_UpdateMsg,
        Step_WaitClick,
		Step_Idle,
    };
private:
    int m_count_frame;
    int m_msg_speed;
    int m_analyze_index; //!< ��͈ʒu.
    std::string m_msg;
    std::string m_draw_msg;
    int m_x;
    int m_y;
    Step m_step;
};


#endif IncludeGuardMsgPrinter

