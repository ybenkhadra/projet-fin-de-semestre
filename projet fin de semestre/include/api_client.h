#ifndef API_CLIENT_H
#define API_CLIENT_H

#include "translation_common.h"

int fetch_translation(const char *text, const char *target_language, TranslationStyle style, char *output, unsigned int output_size);
int init_api_client(void);
const char *get_api_error(void);

#endif
