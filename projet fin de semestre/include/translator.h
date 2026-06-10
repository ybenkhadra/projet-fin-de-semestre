#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include "translation_common.h"

const char *translation_style_name(TranslationStyle style);
int translate_text(const char *text, const char *target_language, TranslationStyle style, char *output, unsigned int output_size);

#endif
