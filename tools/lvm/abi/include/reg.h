#ifndef REG_H
#define REG_H

/* Register File Mapping */

/* Read-only registers */

#define REG_RC 255
#define REG_FL 254
#define REG_PC 253
#define REG_SP 252

/* Read-write registers */

#define REG_HP 250
#define REG_BP 250
#define REG_AD0 249
#define REG_AD1 248

/* Unnamed Reserved registers */

#define REG_RSV0 247
#define REG_RSV1 246
#define REG_RSV2 245
#define REG_RSV3 244
#define REG_RSV4 243
#define REG_RSV5 242
#define REG_RSV6 241
#define REG_RSV7 240

/* Temporary Value Registers */

#define REG_TV0 REG_RSV0
#define REG_TV1 REG_RSV1


/* Argument registers */

#define ABI_ARG_REG_START 0x00
#define ABI_ARG_REG_END   0x0F

/* Temporary / volatile registers */

#define ABI_TEMP_REG_START 0x10
#define ABI_TEMP_REG_END   0x7F

/* Saved / non-volatile registers */

#define ABI_SAVED_REG_START 0x80
#define ABI_SAVED_REG_END   0xEF


/* Register Counts */

#define ABI_REG_COUNT \
    256

#define ABI_ARG_REG_COUNT \
    ((ABI_ARG_REG_END - ABI_ARG_REG_START) + 1)

#define ABI_TEMP_REG_COUNT \
    ((ABI_TEMP_REG_END - ABI_TEMP_REG_START) + 1)

#define ABI_SAVED_REG_COUNT \
    ((ABI_SAVED_REG_END - ABI_SAVED_REG_START) + 1)


/* Register Classification */

#define ABI_REG_IS_ARG(r) \
    ((r) >= ABI_ARG_REG_START && (r) <= ABI_ARG_REG_END)

#define ABI_REG_IS_TEMP(r) \
    ((r) >= ABI_TEMP_REG_START && (r) <= ABI_TEMP_REG_END)

#define ABI_REG_IS_SAVED(r) \
    ((r) >= ABI_SAVED_REG_START && (r) <= ABI_SAVED_REG_END)

#define ABI_REG_IS_RESERVED(r) \
    ((r) >= REG_RSV7 && (r) <= REG_RSV0)

#define ABI_REG_IS_SPECIAL(r) \
    ((r) >= REG_RSV7 && (r) <= REG_RC)

#define ABI_REG_IS_VOLATILE(r) \
    (ABI_REG_IS_ARG(r) || ABI_REG_IS_TEMP(r))

#define ABI_REG_IS_NONVOLATILE(r) \
    ABI_REG_IS_SAVED(r)

#define ABI_REG_IS_ALLOCATABLE(r) \
    (ABI_REG_IS_ARG(r) || \
     ABI_REG_IS_TEMP(r) || \
     ABI_REG_IS_SAVED(r))

#endif /* REG_H */