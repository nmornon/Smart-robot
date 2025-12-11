#include "direction.h"

Direction directionOpposee(Direction dir) {
    switch(dir) {
        case NORD: return SUD;
        case SUD:  return NORD;
        case EST:  return OUEST;
        case OUEST: return EST;
        default:   return -1; 
    }
}
