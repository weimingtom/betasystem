#ifndef include_36815a75_e9c1_401e_aa3a_c9f2b62191b7
#define include_36815a75_e9c1_401e_aa3a_c9f2b62191b7

#include <string>

/**
    ��ʏ�Ƀ��O���o�͂���N���X.
*/
class LogPrinter
{
public:
    friend LogPrinter* new_LogPrinter( int x , int y );
    virtual ~LogPrinter(){}
public:
    virtual void Print( std::string log ) = 0;
    virtual void Draw() = 0;
    
private:
    class Impl;
};

/**
    �����֐�.
*/
LogPrinter* new_LogPrinter( int x , int y );

#endif // include_36815a75_e9c1_401e_aa3a_c9f2b62191b7

