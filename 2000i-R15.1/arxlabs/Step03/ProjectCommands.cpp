/////////////////////////////////////////////
// ObjectARX defined commands

#include "StdAfx.h"
#include "StdArx.h"

// This is command 'MYINPUT'
void asdkmyinput()
{
	// TODO: Implement the command
	int stat, iValue ;
	double rValue ;
	char kWord [133] ;

	acedInitGet (RSG_NONEG | RSG_NOZERO, "") ;

	if ( acedGetInt ("\nEnter an integer value: ", &iValue) != RTNORM )
		return ;

	rValue =12.0 ;
	acedInitGet (RSG_NOZERO, "PI A B C") ;
	stat =acedGetReal ("\nEnter a real value [PI/A/B/C] <C>: ", &rValue) ;
	switch (stat) {
		case RTCAN: // User termination
			return ;
		case RTKWORD: // Got a keyword
			if ( acedGetInput (kWord) != RTNORM )
				return ;
			if ( !strcmp ("PI", kWord) )
				rValue =3.14 ;
			else if ( !strcmp ("A", kWord) )
				rValue =10 ;
			else if ( !strcmp ("B", kWord) )
				rValue =11 ;
			else if ( !strcmp ("C", kWord) )
				rValue =12 ;
			break ;
		case RTNONE:
			acutPrintf ("\nTake default rValue %lf", rValue) ;
			break ;
		case RTNORM:
			break ;
		default:
			return ;
	}

	acutPrintf ("\nInteger : %d", iValue) ;
	acutPrintf ("\nReal    : %lf", rValue) ;
}

// This is command 'MYSELECT'
void asdkmyselect()
{
	// TODO: Implement the command
	ads_name en ;
	ads_point pt ;

	if ( acedEntSel (NULL, en, pt) != RTNORM )
		return ;

	acutPrintf ("\nYou selected entity ID: %ld", en [0]) ;
}
