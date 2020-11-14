#define QxGetInteger(_i, _d, _a) (_a >> _d)
#define QxGetDecimal(_i, _d, _a) ((((_a & ((1 << _d) - 1)) >> (_d >> 1)) * 100) >> (_d >> 1))

//-----------------------------------------------------------------------------
// 8-bits fixed-point number

// Q4.4
#define Q4_4_GetInteger(_a) QxGetInteger(4, 4, _a)
#define Q4_4_GetDecimal(_a) QxGetDecimal(4, 4, _a)

// Q2.6
#define Q2_6_GetInteger(_a) QxGetInteger(2, 6, _a)
#define Q2_6_GetDecimal(_a) QxGetDecimal(2, 6, _a)

//-----------------------------------------------------------------------------
// 16-bits fixed-point number

// Q8.8
#define Q8_8_GetInteger(_a) QxGetInteger(8, 8, _a)
#define Q8_8_GetDecimal(_a) QxGetDecimal(8, 8, _a)

// Q4.12
#define Q4_12_GetInteger(_a) QxGetInteger(4, 12, _a)
#define Q4_12_GetDecimal(_a) QxGetDecimal(4, 12, _a)

// Q2.14
#define Q2_14_GetInteger(_a) QxGetInteger(2, 14, _a)
#define Q2_14_GetDecimal(_a) QxGetDecimal(2, 14, _a)