#include "snow.hpp"

#include "DxLibWrapper/Random.hpp"

namespace {

static int const ScreenWidth = 640;
static int const ScreenHeight = 480;
static int const ImageSize = 16;


} // namespace unnamed

// ============================================================================
// デフォルトコンストラクタ
// ============================================================================
Snow::Snow()
{
    this->is = false;
}

// ============================================================================
// 初期化
// ============================================================================
void Snow::Init()
{
    /* 初期座標設定 */
    this->SetPoint(
        GetRand() % (ScreenWidth - ImageSize),
        -ImageSize);

    /* 移動量設定 */
    this->SetMove(
        GetRand() % 100 * 0.0001 - 0.005,
        GetRand() % 100 * 0.01   + 0.7);

    /* 加速度設定 */
    this->SetAccel(
        GetRand() % 100 * 0.0001 - 0.005,
        GetRand() % 100 * 0.0001 - 0.005);

    this->b = 1;
    this->cnt = 0;
}

// ============================================================================
// 座標設定
// ============================================================================
void Snow::SetPoint(double x, double y)
{
    this->p.x = x;
    this->p.y = y;
}

// ============================================================================
// 移動量設定
// ============================================================================
void Snow::SetMove(double mx, double my)
{
    this->mv.x = mx;
    this->mv.y = my;
}

// ============================================================================
// 加速度設定
// ============================================================================
void Snow::SetAccel(double ax, double ay)
{
    this->a.x = ax;
    this->a.y = ay;
}

// ============================================================================
// 更新
// @return 表示終了の場合はfalseを返す。
// ============================================================================
bool Snow::Update()
{
    /* 加速 */
    this->Accel();

    /* 移動 */
    bool ret = this->Move();

    return ret;
}

// ============================================================================
// 移動
// @return 表示終了の場合はfalseを返す。
// ============================================================================
bool Snow::Move()
{
    bool ret = true;

    /* X軸移動 */
    this->p.x += this->mv.x;
    if(this->p.x < 0 - ImageSize || ScreenWidth < this->p.x)
    {
        ret = false;
    }

    /* Y軸移動 */
    this->p.y += this->mv.y;
    if(this->p.y > ScreenHeight + ImageSize)
    {
        this->p.y = ScreenHeight + ImageSize;
        /* 表示終了 */
        ret = false;
    }

    /* ブレンド値 */
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
// 加速
// ============================================================================
void Snow::Accel()
{
    /* X方向加速 */
    this->mv.x += this->a.x;
    if(this->a.x > 0 && this->mv.x > (this->a.x * 60))
    {
        /* 反転 */
        this->a.x *= -1;
    }
    else if(this->a.x < 0 && this->mv.x < (this->a.x * 60))
    {
        /* 反転 */
        this->a.x *= -1;
    }

    /* Y方向加速 */
    this->mv.y += this->a.y;
    if(this->a.y > 0 && this->mv.y > (this->a.y * 60))
    {
        /* 反転 */
        this->a.y *= -1;
    }
    else if(this->a.y < 0 && this->mv.y < 0.3)
    {
        /* 最低速度設定 */
        this->mv.y = 0.3;
        /* 反転 */
        this->a.y *= -1;
    }
}
