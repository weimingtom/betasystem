#ifndef include_9c91857f_e579_42a8_89bc_72c3a5338feb
#define include_9c91857f_e579_42a8_89bc_72c3a5338feb
/**
    実行中の変数書き換えをサポートするクラス.
    
    [キー(文字列)],[値]
    のフォーマットで記述したテキストを解析し、
    値を取り出すことが出来る.
*/
class RewritableVariable
{
public:
    friend RewritableVariable* new_RewritableVariable( char const* file_name );
    virtual ~RewritableVariable(){}
    
public:
    /**
        値の読み直し.
    */
    virtual void Reload() = 0;
    
    /**
        値の取得.
    */
    virtual int VariableOf( char const* key ) = 0;
    
private:
    class Impl;
};

#endif

