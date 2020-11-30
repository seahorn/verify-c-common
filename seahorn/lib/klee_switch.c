
#include <klee_switch.h>

size_t alloc_size(size_t sz) {
  switch(sz) {
    case 1: return 1;
    case 2: return 2;
    case 3: return 3;
    case 4: return 4;
    case 5: return 5;
    case 6: return 6;
    case 7: return 7;
    case 8: return 8;
    case 9: return 9;
    case 10: return 10;
    case 11: return 11;
    case 12: return 12;
    case 13: return 13;
    case 14: return 14;
    case 15: return 15;
    case 16: return 16;
    case 17: return 17;
    case 18: return 18;
    case 19: return 19;
    case 20: return 20;
    case 21: return 21;
    case 22: return 22;
    case 23: return 23;
    case 24: return 24;
    case 25: return 25;
    case 26: return 26;
    case 27: return 27;
    case 28: return 28;
    case 29: return 29;
    case 30: return 30;
    case 31: return 31;
    case 32: return 32;
    case 33: return 33;
    case 34: return 34;
    case 35: return 35;
    case 36: return 36;
    case 37: return 37;
    case 38: return 38;
    case 39: return 39;
    case 40: return 40;
    case 41: return 41;
    case 42: return 42;
    case 43: return 43;
    case 44: return 44;
    case 45: return 45;
    case 46: return 46;
    case 47: return 47;
    case 48: return 48;
    case 49: return 49;
    case 50: return 50;
    default: return sz <= 4096 ? 4096 : sz;
  }
}
