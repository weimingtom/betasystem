

class StageFactory
{
    static final int StageType_Sougen = 0 ;
    static final int StageType_Dungeon = 1 ;
    static final int StageType_Mountain = 2 ;
    static final int StageType_Num = 3 ;
    
    static Stage new_Stage( int stage_type )
    {
        int monster_list1[] = {
            CharacterFactory.CharaType_BlueSlime ,
            CharacterFactory.CharaType_GreenSlime ,
            CharacterFactory.CharaType_GreenSlime ,
        };
        int monster_list2[] = {
            CharacterFactory.CharaType_GreenSlime ,
            CharacterFactory.CharaType_BlueSlime ,
            CharacterFactory.CharaType_BlueSlime ,
            CharacterFactory.CharaType_GreenSlime ,
        };
        int monster_list3[] = {
            CharacterFactory.CharaType_GreenSlime ,
            CharacterFactory.CharaType_BlueSlime ,
            CharacterFactory.CharaType_GreenSlime ,
            CharacterFactory.CharaType_GreenSlime ,
            CharacterFactory.CharaType_GreenSlime ,
            CharacterFactory.CharaType_GreenSlime ,
        };
        
        switch( stage_type )
        {
        case StageType_Sougen:
            return new Stage( "ëêå¥" , monster_list1 );
        case StageType_Dungeon:
            return new Stage( "É_ÉìÉWÉáÉì" , monster_list2 );
        case StageType_Mountain:
            return new Stage( "âŒéR" , monster_list3 );
        default:
            return null;
        }
    }
};


