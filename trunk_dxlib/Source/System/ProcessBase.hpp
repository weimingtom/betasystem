#ifndef include_guard_uuid_2fbafdb0_3a27_4c00_8380_6d2c086ded76
#define include_guard_uuid_2fbafdb0_3a27_4c00_8380_6d2c086ded76

/**
    処理を抽象化するためのクラス.
*/
class ProcessBase
{
public:
    virtual ~ProcessBase(){}
    
public:
    virtual void Run() = 0;
};

#endif //include_guard_uuid_2fbafdb0_3a27_4c00_8380_6d2c086ded76

