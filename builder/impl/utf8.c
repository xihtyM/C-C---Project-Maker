#include "../include/utf8.h"

#ifdef __cplusplus
extern "C"
#endif
char *set_utf8(void)
{
#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)

    //
    // try to set the codepage to CP_UTF8
    // (generally 65001).
    //
    // basically the same as:
    //     system("chcp 65001")
    // 
    // just doesn't print anything
    // and is faster.
    //

    if (!SetConsoleOutputCP(CP_UTF8))
    {
        return null;
    }
    
    //
    // it is easier to loop over a predefined array
    // of locales on windows, so try every locale
    // until setlocale suceeds, return the return
    // value of setlocale.
    //
    // if none of the predefined locales work,
    // just return null for now because utf8
    // is probably not supported.
    //
    // TODO: figure out how to loop over
    // every utf8 locale without just getting
    // generic ones.
    //

    for (int8_t index = 0; locales[index]; index++) {
        char *ret = setlocale(LC_ALL, locales[index]);

        if (ret) {
            return ret;
        }
    }
    
#else
    FILE *locales = popen("locale -a | grep -i '\\.utf-8$\\|\\.utf8$'", "r");

    if (locales)
    {
        //
        // 32 characters should be enough
        // for most utf8 locales.
        //

        char locale[32];
        while (fgets(locale, sizeof(locale), locales))
        {
            //
            // replace the line break with \0 to terminate it
            // with a simple for loop, cannot use strlen incase
            // there is no \n found (the locale is too long).
            //
            
            int8_t index;

            for (index = 0; index < 32; index++)
            {
                if (locale[index] == '\n')
                {
                    locale[index] = '\0';
                    break;
                }
            }

            //
            // if locale name is too long
            // continue to next line.
            //

            if (index >= 32)
            {
                continue;
            }
            
            char *ret = setlocale(LC_ALL, locale);

            if (ret) {
                return ret;
            }
        }
        pclose(locales);
    }
#endif

    return null;
}
