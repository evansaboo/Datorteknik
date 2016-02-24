#include "rand.h"
#include "pic32mx.h"
#include "displ.h"

int m_w = 0xab659f1d;
int m_z = 0x1453bbac;

/*
 * Generates a 'random' positive number with a modulo of the given limit.
 */
int rand(short limit){
    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    return (((m_z << 16) + m_w) & 0x7fffffff) % limit;
}