#include <iostream>
#include <string>
#include <vector>
#include <stdarg.h>

struct State 
{
	std::string name;
	std::string color;

	int neighbours [ 5 ];

	State ( std::string name, ... ) : name ( std::move ( name ) ), color ( "" )
	{
		va_list args;
		va_start ( args, name );

		for ( int i = 0; i < 5; ++i )
		{
			neighbours [ i ] = va_arg ( args, int );
		}

		va_end ( args );
	}
};

std::vector < State > states;
std::vector < std::string > colors = { "red", "green", "blue" };

bool TestColor ( const State& state )
{
	for ( int i = 0; i < ( sizeof ( state.neighbours ) / sizeof ( int ) ); ++i )
	{
		if ( state.neighbours [ i ] > 5 )
			break;

		if ( state.color == states.at ( state.neighbours [ i ] ).color )
			return false;
	}

	return true;
}

bool SolveMapColoring ( int state_index )
{
	//	Successful
	if ( state_index == 7 )
		return true;

	//	Get state
	State& current_state = states.at ( state_index );

	//	Assign Color
	for ( int i = 0; i < 3; ++i )
	{
		current_state.color = colors.at ( i );

		if ( TestColor ( current_state ) )
		{
			//	Test next state
			if ( SolveMapColoring ( ++state_index ) )
				return true;
		}

		current_state.color = "";
	}

	//	Failed
	return false;
}

int main ( void )
{
	states.emplace_back ( "WA", 1, 2 );
	states.emplace_back ( "NT", 0, 2, 3 );
	states.emplace_back ( "SA", 0, 1, 3, 4 );
	states.emplace_back ( "QU", 1, 2, 4 );
	states.emplace_back ( "NSW", 2, 3 );
	states.emplace_back ( "V", 2, 4 );
	states.emplace_back ( "TA" );

	if ( SolveMapColoring ( 0 ) )
		std::cout << "Success" << std::endl;

	for ( State state : states )
	{
		std::cout << "STATE : " << state.name << " COLOR : " << state.color << std::endl;
	}

	return 0;
}
