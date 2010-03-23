import java.util.*;

/**
    ワールドマップで表示される各フィールドを表現するクラス.
*/
class Stage
{
    String m_name; //!< フィールド名称.
    Vector m_monster_list; //!< 出現するモンスターのリスト.
    
    /**
        コンストラクタ.
    */
    Stage(
        String name ,
        Vector monster_list )
    {
        m_name = name;
        m_monster_list = monster_list;
    }
};

