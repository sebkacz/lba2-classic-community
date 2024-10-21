// ──────────────────────────────────────────────────────────────────────────
#ifndef LIB_SYSTEM_HQRLOAD
#define LIB_SYSTEM_HQRLOAD

#include <cstdint>
#ifdef __cplusplus
extern "C" {
#endif

// ──────────────────────────────────────────────────────────────────────────
//  alloue la memoire necessaire et charge une fiche d'une ressource .HQR
extern void *LoadMalloc_HQR(const char *name, int32_t index);

// ──────────────────────────────────────────────────────────────────────────
//  charge une fiche à l'adresse voulue depuis une ressource
extern uint32_t Load_HQR(const char *name, void *ptr, int32_t index);

// ──────────────────────────────────────────────────────────────────────────
#ifdef __cplusplus
}
#endif

// ──────────────────────────────────────────────────────────────────────────
#endif // LIB_SYSTEM_HQRLOAD

// ──────────────────────────────────────────────────────────────────────────
