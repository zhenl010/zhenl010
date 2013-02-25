#include <cstring>
#include <cassert>

class AirplaneLog
{
public:
    AirplaneLog( )
    {
    }

    ~AirplaneLog( )
    { 
        delete [ ] m_pPilotName;
        m_pPilotName = NULL;
    }

    float GetFlightTime( ) const 
    { 
        return m_FlightTime;
    }

    void AddDelay( float delay ) 
    {
        m_FlightTime += delay;
    }

    void SetPilotName( const char* pPilotName )
    {
        assert( pPilotName != NULL );
        pPilotName = new char[strlen( pPilotName )];
        strcpy( m_pPilotName, pPilotName );
    }

protected:
    float   m_FlightTime;
    char*  m_pPilotName;
};


unsigned int Goodness( unsigned int value )
{
    unsigned int result = 0;

    while ( value ) 
    {
        result += !(value & 0x1);
        value >>= 1;
    }
    return result;
}


int main(int argc, char** argv)
{
    unsigned int numzs = Goodness(5);

    return 0;
}