#include "StateBattle.hpp"

#include "System/StateManagerBase.hpp"
#include "System/Camera.hpp"
#include "System/Range.hpp"
#include "System/StringOf.hpp"
#include "Project/State/ProjectStateManager.hpp"
#include "DxLibWrapper/InputMouse.hpp"
#include "DxLibWrapper/Color.hpp"
#include "DxLibWrapper/Random.hpp"
#include "DxLibWrapper/AnimTexture.hpp"
#include "Project/Singleton/SingletonInputMouse.hpp"
#include "Project/Singleton/SingletonSoundLoader.hpp"
#include "Project/Singleton/SingletonInputKey.hpp"
#include "Project/Draw.hpp"
#include "Project/ScrollBackground.hpp"
#include "Project/AnimData.hpp"
#include "Project/SaveData.hpp"
#include "Project/PlayerLife.hpp"
#include "Project/BreakEnemyCounter.hpp"
#include <math.h>
#include "Gauge.hpp"

StateBattle::StateBattle( StateManagerBase& manager )
 : m_manager( manager )
 , m_background( new ScrollBackground() )
 , m_frame(0)
 , m_camera( new Camera() )
 , m_player_texture( new AnimTexture(
    ImageHandleOf( ImageType_Player ), AnimDataOf( AnimType_PlayerIdling ) ) )
 , mPlayerLife( new PlayerLife(1) )
 , mBreakEnemyCounter( new BreakEnemyCounter() )
 , m_stage_info( StageInfoOf( static_cast<StageType>(gSaveData.m_selected_stage) ) )
 , m_is_debug_draw( false )
 , m_msg_printer( new MsgPrinter() )
 , m_log_printer( new_LogPrinter(250,150) )
 , m_kyuukei_frame(1)
{
    m_player_pos.x = 0;
    m_player_pos.y = 300;
    InitPreTalk();
}

StateBattle::~StateBattle()
{
}

/**
    �񕜖��@.
*/
bool StateBattle::RecoverMagic()
{
    if( gSaveData.m_player_mp >= 3 ){
        gSaveData.m_player_mp -= 3;
        gSaveData.m_player_hp += 30;
        gSaveData.m_player_hp = Clamp(0,gSaveData.m_player_hp, gSaveData.m_player_max_hp);
        m_log_printer->Print("�񕜖��@���g����.");
        return true;
    }
    m_log_printer->Print("MP������Ȃ�.");
    return false;
}

void StateBattle::StepBattlePlayer()
{
    //�U��.
    if( KeyInput()->IsTrig( static_cast<InputKey::Type>( InputKey::Type_1 ) ) ){
        if( GetRandToMax(100) < 95 ){ 
            //���ʂɍU��.
            m_enemy->SetHP( m_enemy->GetHP() - gSaveData.m_player_attack );
            m_log_printer->Print("�G���U�������B");
        }else{
            m_log_printer->Print("�U�����͂������B");
        }
        SetStep(Step_Battle_Enemy);
    }
    //���@.
    else if( KeyInput()->IsTrig( static_cast<InputKey::Type>( InputKey::Type_2 ) ) ){
        //MP����Ă�Ȃ��_���[�W.
        if( gSaveData.m_player_mp >= 3 ){
            m_log_printer->Print("�U�����@���g�����B");
            gSaveData.m_player_mp -= 3;
            m_enemy->SetHP( m_enemy->GetHP() - gSaveData.m_player_attack*2 );
            SetStep( Step_Battle_Enemy );
        }else{
            m_log_printer->Print("�����AMP������Ȃ��c");
        }
    }
    //��.
    else if( KeyInput()->IsTrig( static_cast<InputKey::Type>( InputKey::Type_3 ) ) ){
        if( RecoverMagic() ){
            SetStep( Step_Battle_Enemy );
        }
    }
    //�ߊl.
    else if( KeyInput()->IsTrig( static_cast<InputKey::Type>( InputKey::Type_4 ) ) ){
        if( GetRandToMax(3) == 0 ){
            m_log_printer->Print("�ߊl����.");
            if( GetRandToMax(100) < 80 ){
                gSaveData.m_item[ItemType_Meet]++;
                m_log_printer->Print("���Q�b�g.");
            }else{
                gSaveData.m_item[ItemType_Maseki]++;
                m_log_printer->Print("���΃Q�b�g");
            }
	        SetStep(Step_Dash);
        }else{
            m_log_printer->Print("�ߊl���s.");
            SetStep(Step_Battle_Enemy);
        }
    }
    //������.
    else if( KeyInput()->IsTrig( static_cast<InputKey::Type>( InputKey::Type_5 ) ) ){
        if( GetRandToMax(3) == 0 ){
            m_log_printer->Print("��������荞�܂ꂽ.");
            SetStep(Step_Battle_Enemy);
        }else{
            m_log_printer->Print("��ڎU�ɓ����o����.");
	        SetStep(Step_Dash);
        }
    }
    
    //�G�̎��S����.
    if( m_enemy->GetHP() <= 0 ){
        SetStep(Step_Dash);
        m_log_printer->Print("�G��|����.");
    }
}

void StateBattle::Update()
{
    UpdateDebug();
    UpdateCommon();
	switch( m_step )
	{
	case Step_PreTalk:
	    if( m_msg_printer->IsEnd() ){
	        SetStep( Step_Dash );
	    }
	    break;
	case Step_Dash:
		StepDash();
		break;
	case Step_Result:
	    if( SingletonInputMouse::Get()->IsTrig( InputMouse::Type_Left ) ){
            gSaveData.Reset(); // �Z�[�u�f�[�^����.
	    	m_manager.ChangeState( ProjectState_Title );
	    }
		break;
    case Step_Clear:
	    if( SingletonInputMouse::Get()->IsTrig( InputMouse::Type_Left ) ){
	        if( gSaveData.m_selected_stage < StageType_Num ){
    	        gSaveData.m_selected_stage++;
            }
    	    m_manager.ChangeState( ProjectState_SelectStage );
        }
        break;
	case Step_Battle_Player:
	    StepBattlePlayer();
        break;
    case Step_Battle_Enemy:
        //�G�̍U��
        if( 95 > GetRandToMax(100) ){
            m_log_printer->Print("�G����U�����󂯂�.");
            gSaveData.m_player_hp -= m_enemy->GetAttack();
        }else{
            m_log_printer->Print("�G�͍U�����~�X����.");
        }
        //�v���C���[���S����.
        if(gSaveData.m_player_hp <= 0){
            SetStep(Step_Result);
            m_log_printer->Print("����Ă��܂����c");
	    }else{
            //�v���C���[�^�[���ɖ߂�.
            SetStep(Step_Battle_Player);
        }
        break;
    case Step_OpenGate:
	    if( SingletonInputMouse::Get()->IsTrig( InputMouse::Type_Left ) ){
	        SetStep(Step_Dash);
	    }
	    else if( SingletonInputMouse::Get()->IsTrig( InputMouse::Type_Right ) ){
            gSaveData.m_selected_stage = GetRandToMax( StageType_Num );
            m_manager.ChangeState( ProjectState_Battle );
	    }
        break;
    case Step_TreasureBox:
	    if( SingletonInputMouse::Get()->IsTrig( InputMouse::Type_Left ) ){
	        SetStep(Step_Dash);
	    }
        break;
	}
}

void StateBattle::Draw() const
{
    //�w�i�F�̃��Z�b�g.
    DrawBox( 0, 0, 640 , 480, GetColor( 200,222,200 ), TRUE );
    m_background->Draw( m_camera->Position() );
    m_player_texture->Draw( m_camera->Position() );

    switch( m_step )
    {
    case Step_DecideMeter:
		//����
        DrawTexture( Vector2(120,100), ImageType_Explain );
        break;
    case Step_Dash:
        DrawFormatString( 0 , 60 , ColorOf() , "���N���b�N:�i��,�E�N���b�N:�x�e" );
        DrawFormatString( 0 , 80 , ColorOf() , "1:�񕜖��@" );
        break;
	case Step_WaitDash:
        break;
    case Step_DashEnd:
        DrawFormatString( 250 , 200 , ColorOf() , "���ꂽ�[" );
        break;
    case Step_Result:
        DrawFormatString( 250 , 200 , ColorOf() , "���߂��ׂ�" );
        break;
    case Step_Clear:
        DrawFormatString( 250 , 200 , ColorOf() , "�X�e�[�W�N���A�I");
        break;
    case Step_Battle_Player:
    case Step_Battle_Enemy:
        {
            DrawFormatString( 0 , 60 , ColorOf() , "1:�U��,2:���@,3:��,4:�ߊl,5:������");
            DrawFormatString( 250 , 200 , ColorOf() , "�퓬��!");
            DrawFormatString( 250 , 220 , ColorOf() , "EnemyLevel[%d]",m_enemy->GetLevel());
            DrawFormatString( 250 , 240 , ColorOf() , "EnemyHp[%d]",m_enemy->GetHP());
            if( m_enemy.get() ){
                Vector2 const dummy;
                m_enemy->Draw(dummy);
            }
        }
        break;
    case Step_OpenGate:
        DrawFormatString( 250 , 200 , ColorOf() , "������!");
        break;
    case Step_TreasureBox:
        DrawFormatString( 250 , 200 , ColorOf() , "�󔠔���!");
        break;
    }
	m_msg_printer->Draw();
    m_log_printer->Draw();

    DrawItem();

    DrawDebug();
}

void StateBattle::SetStep( Step step )
{
	m_step = step;
}

void StateBattle::InitStepWaitDash()
{
    SetStep( Step_WaitDash );
    m_frame = 0;
    m_player_texture->Set( AnimDataOf( AnimType_PlayerCharge ) );
}

void StateBattle::StepWaitDash()
{
    m_frame++;
    if( m_frame > 100 ){
        m_player_texture->Set( AnimDataOf( AnimType_PlayerDash ) );
        SetStep( Step_Dash );
    }
}

void StateBattle::StepDash()
{
    UseItem();

    if( KeyInput()->IsTrig( static_cast<InputKey::Type>( InputKey::Type_1 ) ) ){
        RecoverMagic();
    }
    //�i��
    else if( SingletonInputMouse::Get()->IsHold( InputMouse::Type_Left ) ){
        m_player_pos.x += 3.0f;
        
        //�G���J�E���g����.
        int const rand_num = GetRandToMax(200);
        if( rand_num == 0 ){

            m_log_printer->Print("���������ꂽ�B");
            //�퓬�������āA�퓬�J�ڂ�
            SetStep(Step_Battle_Player);
            int const enemy_level = gSaveData.m_selected_stage+1;
            m_enemy.reset( new Enemy( Enemy::Type_GreenSlime, enemy_level ) );
            Vector2 pos(400,350);
            m_enemy->SetPosition(pos);

        }else{
            //�ŏI�n�_���B.
            StageInfo const info = StageInfoOf( static_cast<StageType>(gSaveData.m_selected_stage) );
            if( m_player_pos.x > info.length ){
                //�ЂƂ܂����̃X�e�[�W��.
				gSaveData.m_selected_stage++;
				m_manager.ChangeState( ProjectState_Battle );
            }
        }
    }
    //�x�e.
    else if( SingletonInputMouse::Get()->IsHold( InputMouse::Type_Right ) ){
        m_kyuukei_frame++;
        if( m_kyuukei_frame % 15 == 0 ){
            gSaveData.m_player_hp++;
            gSaveData.m_player_hp = Clamp(0,gSaveData.m_player_hp,gSaveData.m_player_max_hp);
        }
    }
}

/**
    �f�o�b�O���`��.
*/
void StateBattle::DrawDebug() const
{
    //hp
    int const x = 0;
    int y = 100;
    DrawFormatString( x , y+=20,    ColorOf() , "hp[%d/%d]", gSaveData.m_player_hp, gSaveData.m_player_max_hp);
	y+=20;
	int width = gSaveData.m_player_max_hp;
	int height = 20;
	DrawBox( x, y, x+width , y+height, GetColor( 0,0,0 ), TRUE );
	DrawBox( x, y, x+gSaveData.m_player_hp , y+height, GetColor( 0,255,0 ), TRUE );
    DrawFormatString( x , y+=20,    ColorOf() , "mp[%d/%d]", gSaveData.m_player_mp, gSaveData.m_player_max_mp);

    DrawFormatString( x , y+=20,    ColorOf() , "m_player_x[%f]", m_player_pos.x);
    DrawFormatString( x , y+=20,    ColorOf() , "m_player_exp[%d]", gSaveData.m_player_exp);
    DrawFormatString( x , y+=20,    ColorOf() , "m_player_level[%d]", gSaveData.m_player_level);
    StageInfo const info = StageInfoOf( static_cast<StageType>(gSaveData.m_selected_stage) );
    DrawFormatString( x , y+=20 , ColorOf(0,0,0) , "stage_name[%s]", info.name);

    DrawFormatString( x , y+=20 , ColorOf(0,0,0) , "�X�e�[�W�i�s�x");
    {
        float width = 200.0f;
    	int height = 20;
    	DrawBox( x , y+=20, static_cast<int>(x+width) , y+height, GetColor( 0,255,0 ), TRUE );
    	DrawBox( x , y, static_cast<int>(x+width*(float)m_player_pos.x/info.length) , y+height, GetColor( 255,0,0 ), TRUE );
    }
}

void StateBattle::UpdateCommon()
{
    m_player_texture->Update();
    m_player_texture->Set( m_player_pos );

    if( m_enemy.get() ){
	    m_enemy->Update();
    }

    //�J�����̓v���C���[�ǔ�.
	m_camera->SetPosition( m_player_pos - Vector2( 640/2 - 200, 480/2 + 50 ) );
	//�w�i�X�N���[��
    m_background->SetScroll( m_camera->Position() );

    m_msg_printer->Update();
    
    m_log_printer->Update();
}

void StateBattle::InitResult()
{
	SetStep( Step_Result );
	m_player_texture->Set( AnimDataOf( AnimType_PlayerGrave ) );
}

void StateBattle::InitPreTalk()
{
    m_step = Step_PreTalk;
    std::string msg("[image,]�y�t�����z\n�V�������E�ɒ��������B[click][clear]");
    m_msg_printer->SetMsg(msg.c_str());
}

/**
    ���[�^�[����ւ̑J��.
    �S�ď�����.
*/
void StateBattle::InitStepDecideMeter()
{
    SetStep( Step_DecideMeter );
	m_player_texture->Set( AnimDataOf( AnimType_PlayerIdling ) );
}

void StateBattle::StepDecideMeter()
{
	if( SingletonInputMouse::Get()->IsTrig( InputMouse::Type_Left ) )
    {
		//�A�ŉ�.
        SingletonSoundLoader::Get()->Play( NameOf( SoundType_OK ) );
	}

	if( SingletonInputMouse::Get()->IsTrig( InputMouse::Type_Right ) )
    {
	    SingletonSoundLoader::Get()->Play( NameOf( SoundType_Just ) );
        InitStepWaitDash();
    }
}

/**
    �A�C�e���̎g�p.
*/
void StateBattle::UseItem()
{
    for( int i = 0 ; i < ItemType_Num ; i++ ){
        if( KeyInput()->IsTrig( static_cast<InputKey::Type>( InputKey::Type_F1 + i ) ) )
        {
            if( gSaveData.m_item[i] != 0 ){
                gSaveData.m_item[i]--;

                std::string log = NameOf( static_cast<ItemType>(i) );
                log += "���g�����B";
                m_log_printer->Print(log);
                UseItem( static_cast<ItemType>( i ) );
            }
        }
    }
}

void StateBattle::UseItem( ItemType type )
{
	switch( type ){
    case ItemType_Meet:
        gSaveData.m_player_hp += 50;
        break;
    case ItemType_Maseki:
        gSaveData.m_player_mp += 10;
        break;
    case ItemType_LifeWater:
        gSaveData.m_player_max_hp += 10;
        break;
    }
    gSaveData.m_player_hp = Clamp(0,gSaveData.m_player_hp,gSaveData.m_player_max_hp);
    
    SingletonSoundLoader::Get()->Play( NameOf( SoundType_Item ) );
}

void StateBattle::GetItem()
{
    int const rand_num = GetRandToMax(10000); //������.
    int total = 0;
    for( int i = 1; i < ItemType_Num; i++ )// ItemType_None �͍l���Ȃ��̂� i = 1 ����.
    {
        total += DropPamiriado( static_cast<ItemType>(i) );

        // �擾����.
        if( rand_num < total ){
            ItemType const get_item = static_cast<ItemType>(i);
            gSaveData.m_item[get_item]++;
            SingletonSoundLoader::Get()->Play( NameOf( SoundType_Decide ) );
            std::string log = NameOf(static_cast<ItemType>(i));
            log+="����ɓ��ꂽ�B";
            m_log_printer->Print(log);
            return;
        }
    }
}

void StateBattle::DrawItem() const
{
    DrawTexture( Vector2(0,0), ImageType_ItemList );
    DrawTexture( Vector2(0,0), ImageType_ItemFrame );
    for( int i = 0 ; i < ItemType_Num ; i++ ){
        DrawFormatString( i*50 , 40 , ColorOf(0,0,0) , "[%d]" , gSaveData.m_item[i] );
    }
}

void StateBattle::UpdateHiScore()
{
    if( gSaveData.m_max_break < mBreakEnemyCounter->Num() ){
        gSaveData.m_max_break = mBreakEnemyCounter->Num();
    }
}

void StateBattle::UpdateDebug()
{
}



