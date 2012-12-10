#define WHITE_CC "\e[0m"
#define GREEN_CC "\e[32m"
#define RED_CC   "\e[31m"

#define BIN_INT uint
#define BIN_BITS sizeof(BIN_INT)*4


typedef struct bin {
  BIN_INT bits[BIN_BITS];
} bin;
