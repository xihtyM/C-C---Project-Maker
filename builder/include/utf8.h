#pragma once

#include "null.h"

#ifdef __cplusplus
#include <locale>
#include <cstdint>
#else
#include <locale.h>
#include <stdio.h>
#include <stdint.h>
#endif

#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
#include <windows.h>

#ifdef __cplusplus
constexpr inline
#else
static
#endif

// Common UTF-8 locales
const char *const locales[] = {
    ".utf-8",
    ".utf8",
    ".UTF-8",
    ".UTF8",
    
    // Locale names with language codes
    // hyphen syntax
    "en-US.utf-8",
    "en-GB.utf-8",
    "fr-FR.utf-8",
    "es-ES.utf-8",
    "de-DE.utf-8",
    "it-IT.utf-8",
    "ja-JP.utf-8",
    
    // underscore syntax
    "en_US.utf-8",
    "en_GB.utf-8",
    "fr_FR.utf-8",
    "es_ES.utf-8",
    "de_DE.utf-8",
    "it_IT.utf-8",
    "ja_JP.utf-8",


    // Additional variations
    "C.UTF-8",  // Standard C locale with UTF-8
    "POSIX.UTF-8",  // POSIX locale with UTF-8
    "en.utf-8",     // English (generic) with UTF-8
    "en_US.UTF-8",  // English (United States) with UTF-8
    
    // Maybe works like codepages
    // in some weird examples
    ".65001",

    // If it reaches here, there
    // is probably no utf-8 support
    null,
};
#endif

#ifdef __cplusplus
extern "C"
#endif
char *set_utf8(
    void);
