/*
 ___________________________________________________________
/               __           _                              \
|              / _|         (_)                             |
|             | |_ _   _ ___ _  ___  _ __                   |
|             |  _| | | / __| |/ _ \| '_ \                  |
|             | | | |_| \__ \ | (_) | | | |                 |
|             |_|  \__,_|___/_|\___/|_| |_| *               |
|                                                           |
|               The MSX C Library for SDCC                  |
|                     V1.3 - 12- 2019 			            |
|                                                           |
|                Eric Boez &  Fernando Garcia               |
|                                                           |
|   |
|                                                           |
|                                                           |
|                                                           |
\___________________________________________________________/
*                         (°□°)
*	Original code by Eric Boez - 2019
*	
*/

char BitReturn(char nbit, char byte)			// Return the bit number nbit from the byte
{
    nbit = 1 << nbit;
    return(nbit & byte);
}

void BitReset(char nbit, char *byte)	// Reset the bit nbit inside the *byte
{
    nbit = 1 << nbit;
    nbit ^= 0xff;
    *byte = *byte & nbit;
}
