//*****************************************************************************
// strlen.c : string function
// 2002/02/04 by Gaku : this is rough sketch
//*****************************************************************************

#include <go_string.hpp>

//=============================================================================
// return the length of D
//=============================================================================
size_t GO_strlen (const char *d)
{
	const char *tmp = d;

	while ('\0' != *d)
		d++;

	return d - tmp;
}
