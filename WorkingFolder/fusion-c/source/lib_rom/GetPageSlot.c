// ExxxSSPP
// │   ││└┴─ Primary slot number (00-11)
// │   └┴─── Secondary slot number (00-11)
// └──────── Expanded slot (0 = no, 1 = yes)

#define P_PPI_A 	0xA8    				// Port to access the primary Slot selection register
#define M_SLTSL    	0xFFFF    				// Access address to selection register of secondary slots
#define M_EXPTBL    0xFCC1    				// Slot expansion
#define SLOT_EXP (1 << 7)

const char __at(M_EXPTBL) g_EXPTBL[4];
const char __at(M_SLTSL) g_SLTSL;

__sfr __at(P_PPI_A) g_PortPrimarySlot;

inline char GetPageSlot(char page)
{
    char slot = (g_PortPrimarySlot >> (page * 2)) & 0x03;
    if(g_EXPTBL[slot] & 0x80)
    {
        slot |= SLOT_EXP;
        slot |= (((~g_SLTSL) >> (page * 2)) & 0x03) << 2;
    }
    return slot;
}