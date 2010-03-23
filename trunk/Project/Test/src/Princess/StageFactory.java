

class StageFactory
{
    static final int StageType_Sougen = 0 ;
    static final int StageType_Dungeon = 1 ;
    
    static Stage New( int stage_type )
    {
        int monster_list[] ={
            CharacterFactory.CharaType_BlueSlime ,
            CharacterFactory.CharaType_GreenSlime ,
            CharacterFactory.CharaType_BlueSlime , };
        
        switch( stage_type )
        {
        case StageType_Sougen:
            return new Stage( "����" , monster_list );
        case StageType_Dungeon:
            return new Stage( "�_���W����" , monster_list );
        default:
            return null;
        }
    }
};


