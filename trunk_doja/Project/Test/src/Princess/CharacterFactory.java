
/**
    �L�����N�^�[�𐶐�����N���X.
*/
class CharacterFactory
{
    static final int CharaType_BlueSlime = 0 ;
    static final int CharaType_GreenSlime = 1 ;
    static final int CharaType_Furiru = 2 ;
    
    static Character New( int chara_type )
    {
        switch( chara_type )
        {
        case CharaType_BlueSlime:
            return new Character( "B�X���C��" , 4 , 2 , 2 );
        case CharaType_GreenSlime:
            return new Character( "G�X���C��" , 8 , 3 , 4 );
        case CharaType_Furiru:
            return new Character( "�t����" , 10 , 4 , 0 );
        default:
            return null;
        }
    }
};


