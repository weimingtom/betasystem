#include "BreakEnemyCounter.hpp"
#include "Project/Singleton/SingletonImageLoader.hpp"
#include "Project/Draw.hpp"
#include <math.h>

BreakEnemyCounter::BreakEnemyCounter()
 : mBreakNum(0)
{
}

BreakEnemyCounter::~BreakEnemyCounter()
{
}

void BreakEnemyCounter::Draw() const
{
/*
    int const width = 50;
    int const height = 100;
    int max_digit = 5;
    
    //��̌��̗L���ɂ���āA�\����\�������肷��.
    //���̌����O�ŁA����ʌ����S�ĂO�Ȃ�Ε\�����Ȃ�.
    
    for(int i = 1 ; i < max_digit ; i++ ){
        if( DigitOf(mBreakNum,i) == 0 ){
            int total = 0;
            for( int j = i + 1 ; j < max_digit ; j++ ){
                total += DigitOf(mBreakNum,j);
            }
            if( total == 0 ){ continue; }
        }
        DrawRectGraph(
            600 - i*width, 30,
            0 + width * DigitOf(mBreakNum,i), 0,
            width, height,
            ImageHandleOf(ImageType_Number), TRUE, FALSE );
    }
*/
}

/**
    �w�肵�����̐������擾����.
    @param num ����Ώۂ̐��l.
    @param digit �擾��������. �P���ڂȂ�΂P�A�Q���ڂȂ�΂Q.
*/
int BreakEnemyCounter::DigitOf(int num,int digit) const
{
    double const d_digit = static_cast<double>(digit);
    double const Ten = 10.0f;
    double const result = num % static_cast<int>( pow( Ten, d_digit ) );
    return static_cast<int>( result / pow(Ten,d_digit-1.0f) );
}

