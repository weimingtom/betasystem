#include "snow.hpp"

#include "DxLibWrapper/Random.hpp"

namespace {

static int const ScreenWidth = 640;
static int const ScreenHeight = 480;
static int const ImageSize = 16;


} // namespace unnamed

// ============================================================================
// �f�t�H���g�R���X�g���N�^
// ============================================================================
Snow::Snow()
{
    this->is = false;
}

// ============================================================================
// ������
// ============================================================================
void Snow::Init()
{
    /* �������W�ݒ� */
    this->SetPoint(
        GetRand() % (ScreenWidth - ImageSize),
        -ImageSize);

    /* �ړ��ʐݒ� */
    this->SetMove(
        GetRand() % 100 * 0.0001 - 0.005,
        GetRand() % 100 * 0.01   + 0.7);

    /* �����x�ݒ� */
    this->SetAccel(
        GetRand() % 100 * 0.0001 - 0.005,
        GetRand() % 100 * 0.0001 - 0.005);

    this->b = 1;
    this->cnt = 0;
}

// ============================================================================
// ���W�ݒ�
// ============================================================================
void Snow::SetPoint(double x, double y)
{
    this->p.x = x;
    this->p.y = y;
}

// ============================================================================
// �ړ��ʐݒ�
// ============================================================================
void Snow::SetMove(double mx, double my)
{
    this->mv.x = mx;
    this->mv.y = my;
}

// ============================================================================
// �����x�ݒ�
// ============================================================================
void Snow::SetAccel(double ax, double ay)
{
    this->a.x = ax;
    this->a.y = ay;
}

// ============================================================================
// �X�V
// @return �\���I���̏ꍇ��false��Ԃ��B
// ============================================================================
bool Snow::Update()
{
    /* ���� */
    this->Accel();

    /* �ړ� */
    bool ret = this->Move();

    return ret;
}

// ============================================================================
// �ړ�
// @return �\���I���̏ꍇ��false��Ԃ��B
// ============================================================================
bool Snow::Move()
{
    bool ret = true;

    /* X���ړ� */
    this->p.x += this->mv.x;
    if(this->p.x < 0 - ImageSize || ScreenWidth < this->p.x)
    {
        ret = false;
    }

    /* Y���ړ� */
    this->p.y += this->mv.y;
    if(this->p.y > ScreenHeight + ImageSize)
    {
        this->p.y = ScreenHeight + ImageSize;
        /* �\���I�� */
        ret = false;
    }

    /* �u�����h�l */
    this->cnt++;
    if(this->cnt > 150)
    {
        this->b -= 0.007;
        if(this->b < 0)
        {
            this->b = 0;
            ret = false;
        }
    }

    return ret;
}

// ============================================================================
// ����
// ============================================================================
void Snow::Accel()
{
    /* X�������� */
    this->mv.x += this->a.x;
    if(this->a.x > 0 && this->mv.x > (this->a.x * 60))
    {
        /* ���] */
        this->a.x *= -1;
    }
    else if(this->a.x < 0 && this->mv.x < (this->a.x * 60))
    {
        /* ���] */
        this->a.x *= -1;
    }

    /* Y�������� */
    this->mv.y += this->a.y;
    if(this->a.y > 0 && this->mv.y > (this->a.y * 60))
    {
        /* ���] */
        this->a.y *= -1;
    }
    else if(this->a.y < 0 && this->mv.y < 0.3)
    {
        /* �Œᑬ�x�ݒ� */
        this->mv.y = 0.3;
        /* ���] */
        this->a.y *= -1;
    }
}
