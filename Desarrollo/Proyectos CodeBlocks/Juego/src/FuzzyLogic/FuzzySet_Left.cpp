#include "FuzzySet_Left.h"

FuzzySet_Left::FuzzySet_Left()
{
    //ctor
}

FuzzySet_Left::~FuzzySet_Left()
{
    //dtor
}

float FuzzySet_Left::CalculateDOM(float val)const
{
    //test for the case where the left or right offsets are zero
    //(to prevent divide by zero errors below)
    if (  (m_dRightOffset == 0.0 && m_dPeakPoint == val)
       || (m_dLeftOffset  == 0.0 && m_dPeakPoint == val))
    {
        return 1.0;
    }

    //find DOM if right of center
    else if ( (val >= m_dPeakPoint) && (val < (m_dPeakPoint + m_dRightOffset)) )
    {
        float grad = 1.0 / -m_dRightOffset;
        return grad * (val - m_dPeakPoint) + 1.0;
    }

    //find DOM if left of center
    else if ( (val < m_dPeakPoint) && (val >= m_dPeakPoint-m_dLeftOffset) )
    {
        return 1.0;
    }

    //out of range of this FLV, return zero
    else
    {
        return 0.0;
    }

}