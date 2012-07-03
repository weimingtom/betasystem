#ifndef IncludeGuardMsgPrinter
#define IncludeGuardMsgPrinter

#include <string>
#include <vector>
#include "Project/CharacterDrawer/CharacterDrawer.hpp"

/**
    メッセージ表示クラス.
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
    bool IsEnd() const;
private:
    void Init();
private:
    enum Step{
        Step_UpdateMsg,
        Step_WaitClick,
		Step_Idle,
		Step_End,
    };
private:
    int m_count_frame;
    int m_msg_speed;
    int m_analyze_index; //!< 解析位置.
    std::string m_msg;
    std::vector<std::string> m_draw_msg;
    Step m_step;
    std::auto_ptr<CharacterDrawer> m_chara_drawer; //保持はちょっとありえないけど、メッセージ解析後指示出すために参照か何か持つのは確定なので今はこれ。
    bool m_is_visible;
};

#endif

