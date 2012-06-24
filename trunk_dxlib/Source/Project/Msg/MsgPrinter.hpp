#ifndef IncludeGuardMsgPrinter
#define IncludeGuardMsgPrinter

#include <string>

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
private:
    void Init();
private:
    int m_count_frame;
    int m_msg_speed;
    int m_visible_index; //!< 文字列で表示する部分までのインデックス.
    std::string m_msg;
    int m_x;
    int m_y;
};


#endif IncludeGuardMsgPrinter

