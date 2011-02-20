#include "StateBattle.hpp"

#include "System/StateManagerBase.hpp"
#include "System/Camera.hpp"
#include "Project/State/ProjectStateManager.hpp"
#include "DxLibWrapper/InputMouse.hpp"
#include "DxLibWrapper/Color.hpp"
#include "DxLibWrapper/Random.hpp"
#include "DxLibWrapper/AnimTexture.hpp"
#include "Project/Singleton/SingletonInputMouse.hpp"
#include "Project/Singleton/SingletonSoundLoader.hpp"
#include "Project/Draw.hpp"
#include "Project/ScrollBackground.hpp"
#include "Project/AnimData.hpp"
#include "Project/SaveData.hpp"

StateBattle::StateBattle( StateManagerBase& manager )
 : m_manager( manager )
 , m_add_meter(0)
 , m_background( new ScrollBackground() )
 , m_player_speed(0.0f)
 , m_frame(0)
 , m_camera( new Camera() )
 , m_player_power(0)
 , m_player_texture( new AnimTexture(
    ImageHandleOf( ImageType_Player ), AnimDataOf( AnimType_PlayerIdling ) ) )
 , m_get_item( ItemType_Meet )
 , m_player_life(2)//�K��.
 , m_meter_max(120)
{
    m_player_pos.y = 300;
    for( int i = 0 ; i < EnemyNum; i++ ){
        m_enemy[i].SetPosition( Vector2( i * 100 + 300 , 350 ) );
    }
    InitStepDecideMeter();
}

void StateBattle::Update()
{
    UpdateCommon();
	switch( m_step )
	{
	case Step_DecideMeter:
	    StepDecideMeter();
	    break;
    case Step_WaitDash:
        StepWaitDash();
        break;
	case Step_Dash:
		DashPlayer();
		break;
    case Step_DashEnd:
	    if( SingletonInputMouse::Get()->IsTrig( InputMouse::Type_Left ) ){
	    	SetStep( Step_Result );
	    	InitResult();
	    }
        break;
	case Step_Result:
	    if( SingletonInputMouse::Get()->IsTrig( InputMouse::Type_Left ) ){
	        if( m_player_life > 0 ){
	            InitStepDecideMeter();
	        }else{
    	    	m_manager.ChangeState( ProjectState_Battle );
            }
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
	//�G�̕`��.
    for( int i = 0 ; i < EnemyNum ; i++ ){
		m_enemy[i].Draw( m_camera->Position() );
    }
    //�v���C���[�p���[�̕`��.
    DrawBox( 0, 50, m_player_power , 20, GetColor( 255, 0, 0 ), TRUE );

    switch( m_step )
    {
    case Step_DecideMeter:
        DrawGauge();
		//����
        DrawTexture( Vector2(200,30), ImageType_Explain );
        break;
	case Step_WaitDash:
        DrawGauge();
		//�J�b�g�C���̕`��.
		DrawTexture( Vector2(100,100), ImageType_Cutin );
        break;
    case Step_DashEnd:
        DrawTexture( Vector2(100,100), ImageType_GameEnd );
        break;
    case Step_Result:
        DrawTexture( Vector2(100,100), ImageType_Result );
        //�|�������v�Z
        int break_enemy = 0;
        for( int i = 0 ; i < EnemyNum ; i++ ){
            if( !m_enemy[i].IsAlive() ){
                break_enemy++;
            }
        }
        DrawFormatString( 250 , 200 , ColorOf() , "%d�C�I", break_enemy );
        DrawFormatString( 250 , 220 , ColorOf() , "�u%s�v���Q�b�g�����I", NameOf(m_get_item) );
        break;
    }
    DrawDebug();
}

/**
	���[�^�[�̍X�V.
*/
void StateBattle::UpdateMeter( int meter_index )
{
	m_meter[meter_index] += m_add_meter;
	if( m_meter[meter_index] >= m_meter_max ){
		m_add_meter = -2;
	}
	if( m_meter[meter_index] <= 0){
		m_add_meter = 2;
	}
}

void StateBattle::SetStep( Step step )
{
	m_step = step;
}

void StateBattle::InitStepWaitDash()
{
    SetStep( Step_WaitDash );
    m_frame = 0;
	m_player_power = m_meter[0] + m_meter[1] ;
}

void StateBattle::StepWaitDash()
{
    m_frame++;
    if( m_frame > 100 ){
        SetStep( Step_Dash );
    }
}

void StateBattle::DashPlayer()
{
    m_player_speed = 50;
    m_player_pos.x += m_player_speed;
    /**
        �v���C���[�ƓG���Ԃ�������A�G���ӂ��Ƃ΂�.
    */
    for( int i = 0 ; i < EnemyNum ; i++ ){
        if( m_enemy[i].IsAlive() ){
            if( m_enemy[i].Position().x < m_player_pos.x ){
                m_player_power--;
                SingletonSoundLoader::Get()->Play( NameOf( SoundType_OK ) );
                m_enemy[i].SetSpeed( Vector2( m_player_speed * 2, - GetRand(20) ) );
                m_enemy[i].SetAlive( false );
            }
        }
    }
    //�_�b�V���I��.
	if( m_player_power <= 0 ){
		SetStep( Step_DashEnd );
	}
}

/**
    �f�o�b�O���`��.
*/
void StateBattle::DrawDebug() const
{
    DrawFormatString( 0 , 0 , ColorOf() , "m_player_pos[%f,%f]", m_player_pos.x , m_player_pos.y );
    DrawFormatString( 0 , 10 , ColorOf() , "m_player_speed[%f]", m_player_speed );
    DrawFormatString( 0 , 20 , ColorOf() , "m_meter1[%d]", m_meter[0] );
    DrawFormatString( 0 , 30 , ColorOf() , "m_meter2[%d]", m_meter[1] );

    DrawFormatString( 0 , 200 , ColorOf() , "�c�@[%d]", m_player_life  );
    //�����A�C�e���̕\��.
    DrawFormatString( 0 , 210 , ColorOf() , "�����A�C�e��." );
    for( int i = 0; i < ItemType_Num ; i++ ){
        DrawFormatString( 0 , 220 + i*10 , ColorOf() , "%s[%d��]", NameOf( static_cast<ItemType>(i) ) , gSaveData.m_item[i] );
    }
}

/**
    �Q�[�W�̕`��
*/
void StateBattle::DrawGauge() const
{
	for( int i = 0; i < 2 ; i++ ){
		int const x = 50;
		int const y = 70 * i + 300;
		DrawCircle( x, y, m_meter_max / 3, GetColor( 0,0,0 ), TRUE );
		int color = GetColor( 0, 255 / m_meter_max * m_meter[i], 0);
		if( m_meter[i] == m_meter_max ){ color = GetColor( 255, 255, 0 ); }
		if( i == 0 ){
    		DrawCircle( x, y, m_meter[i] / 3 , color, TRUE );
		}else{
			DrawCircle( x, y, m_meter[i] / 3 , color, TRUE ); 
		}
	}
}

void StateBattle::UpdateCommon()
{
    m_player_texture->Update();
    m_player_texture->Set( m_player_pos );
    //�G�X�V
    for( int i = 0 ; i < EnemyNum ; i++ ){
        m_enemy[i].Update();
    }
    //��蒼���@�\.
    if( SingletonInputMouse::Get()->IsTrig( InputMouse::Type_Right ) ){
        m_manager.ChangeState( ProjectState_Battle );
    }
    //�J�����̓v���C���[�ǔ�.
	m_camera->SetPosition( m_player_pos - Vector2( 640/2 - 200, 480/2 + 50 ) );
	//�w�i�X�N���[��
    m_background->SetScroll( m_camera->Position() );
}

void StateBattle::InitResult()
{
    // �A�C�e���Q�b�g.
    ItemType const type = static_cast<ItemType>( GetRandToMax(ItemType_Num) );
    gSaveData.m_item[type]++;
    m_get_item = type;
    //�v���C���[�����炷.
    m_player_life--;
}

void StateBattle::InitStepDecideMeter()
{
    SetStep( Step_DecideMeter );
    m_target_meter = 0;
    m_meter[0]=0;
    m_meter[1]=0;
}

void StateBattle::StepDecideMeter()
{
	UpdateMeter( m_target_meter );
    if( SingletonInputMouse::Get()->IsTrig( InputMouse::Type_Left ) )
    {
        if( m_meter[m_target_meter] == m_meter_max ){
            SingletonSoundLoader::Get()->Play( NameOf( SoundType_Just ) );
        }else{
            SingletonSoundLoader::Get()->Play( NameOf( SoundType_Decide ) );
        }
        if( m_target_meter >= 1 ){
            InitStepWaitDash();
        }else{
            m_target_meter++;
        }
    }
}

