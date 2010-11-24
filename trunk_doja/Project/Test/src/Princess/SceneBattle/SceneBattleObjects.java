import com.nttdocomo.ui.*;

/**
    SceneBattle において、共通して使用するオブジェクト群.
*/
class SceneBattleObjects
{
    private Graphics g = StaticObjects.getGraphicsInstance();
    DamagePrinter m_damage_printer = new DamagePrinter();
    Character m_player = CharacterFactory.New( CharacterFactory.CharaType_Furiru );
    Character m_enemy;
    private Background m_background = new Background();
    private ImageManager m_image_manager = StaticObjects.getImageManagerInstance();
    private Image m_image_player = m_image_manager.ImageOf( ImageManager.Image_Player );
    private Image m_image_enemy = m_image_manager.ImageOf( ImageManager.Image_Slime );
    private SceneManagerBase m_battle_scene_manager;
    private SceneManagerBase m_princess_scene_manager;
    
    int m_monster_list_index;
    
    SceneBattleObjects(
        SceneManagerBase battle_scene_manager ,
        SceneManagerBase princess_scene_manager )
    {
        m_battle_scene_manager = battle_scene_manager;
        m_princess_scene_manager = princess_scene_manager;
        NextEnemy();
    }
    
    void Update()
    {
        m_background.Update();
        m_damage_printer.Update();
    }
    
    void Draw()
    {
        m_background.Draw();
        DrawCharacter();
        m_damage_printer.Draw();
    }
    
    private void DrawCharacter()
    {
        if( m_player.m_hp > 0 )
        {
            g.drawImage( m_image_player , 120 , 80 );
        }
        if( m_enemy.m_hp > 0 )
        {
            g.drawImage( m_image_enemy , 40 , 150 );
        }
        DrawStatus( m_player , 120 , 210 );
        DrawStatus( m_enemy , 20 , 210 );
    }
    
    private void DrawStatus( Character character , int x , int y )
    {
        g.drawString("m_name:"+character.m_name ,       x , y +=8 );
        g.drawString("m_hp:"+character.m_hp ,           x , y +=8 );
        g.drawString("m_attack:"+character.m_attack ,   x , y +=8 );
        g.drawString("m_exp:"+character.m_exp ,         x , y +=8 );
    }
    
    void ActionAttack( boolean is_player_turn )
    {
        Character attaker;
        Character target;
        
        if( is_player_turn )
        {
            attaker = m_player;
            target = m_enemy;
        }else{
            attaker = m_enemy;
            target = m_player;
        }
        
        final int damage = attaker.m_attack;
        target.m_hp -= damage;
        if( target.m_hp <= 0 ){ target.m_hp = 0; }
        
        m_damage_printer.Begin( damage , is_player_turn );
    }
    
    private boolean IsBeNextEnemy()
    {
        return ( m_monster_list_index < StaticObjects.getStage().m_monster_list.length );
    }
    
    private void NextEnemy()
    {
        m_enemy = CharacterFactory.New( StaticObjects.getStage().m_monster_list[ m_monster_list_index ] );
        m_monster_list_index++;
    }
    
    public void EndTurn( int battle_scene_index )
    {
        switch( battle_scene_index )
        {
        case BattleSceneManager.Scene_PlayerTurn:
            if( m_enemy.m_hp <= 0 )
            {
                m_player.m_exp += m_enemy.m_exp;
                m_player.LevelUp();
                m_battle_scene_manager.ChangeScene( BattleSceneManager.Scene_Win );
            }else{
                m_battle_scene_manager.ChangeScene( BattleSceneManager.Scene_EnemyTurn );
            }
            break;
            
        case BattleSceneManager.Scene_EnemyTurn:
            if( m_player.m_hp <= 0 )
            {
                m_battle_scene_manager.ChangeScene( BattleSceneManager.Scene_Lose );
            }else{
                m_battle_scene_manager.ChangeScene( BattleSceneManager.Scene_PlayerTurn );
            }
            break;
            
        case BattleSceneManager.Scene_Win:
            if( IsBeNextEnemy() )
            {
                NextEnemy();
                m_battle_scene_manager.ChangeScene( BattleSceneManager.Scene_PlayerTurn );
            }else{
                m_princess_scene_manager.ChangeScene( PrincessSceneManager.SceneWorldMap );
            }
            break;
            
        case BattleSceneManager.Scene_Lose:
            m_princess_scene_manager.ChangeScene( PrincessSceneManager.SceneGameOver );
            break;
            
        }
    }
}

