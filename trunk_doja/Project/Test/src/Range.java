
class Range
{
    static int Clamp( int min , int var , int max )
    {
        if( var < min )
        {
            return min ;
        } else if( var > max ){
            return max;
        }else{
            return var;
        }
    }
}

