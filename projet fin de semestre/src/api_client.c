#include "api_client.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

static char g_api_error[256] = "";

static const char *style_prefix(TranslationStyle style) {
    switch (style) {
        case TRANSLATION_STYLE_LITERAL:
            return "literal";
        case TRANSLATION_STYLE_NATURAL:
            return "naturel";
        case TRANSLATION_STYLE_PROFESSIONAL:
            return "professionnel";
        default:
            return "inconnu";
    }
}

int init_api_client(void) {
    const char *api_key = getenv("OPENAI_API_KEY");
    const char *gemini_key = getenv("GEMINI_API_KEY");
    const char *api_mode = getenv("TRANSLATION_API_MODE");

    if (api_mode == NULL) {
        api_mode = "demo";
    }

    if (strcmp(api_mode, "demo") == 0) {
        printf("[API] Mode démo activé\n");
        return 1;
    }

    if (strcmp(api_mode, "openai") == 0 && api_key == NULL) {
        snprintf(g_api_error, sizeof g_api_error, "OPENAI_API_KEY non configurée");
        return 0;
    }

    if (strcmp(api_mode, "gemini") == 0 && gemini_key == NULL) {
        snprintf(g_api_error, sizeof g_api_error, "GEMINI_API_KEY non configurée");
        return 0;
    }

    printf("[API] Mode %s configuré\n", api_mode);
    return 1;
}

const char *get_api_error(void) {
    return g_api_error[0] != '\0' ? g_api_error : "No error";
}

static int format_translation_demo(const char *text, const char *lang, TranslationStyle style, char *output, unsigned int output_size) {
    const char *style_str = style_prefix(style);

    if (snprintf(output, output_size,
                 "[%s -> %s | %s mode] Traduction contextuelle: %s",
                 style_str,
                 lang,
                 "demo",
                 text) < 0) {
        return 0;
    }

    return 1;
}

int fetch_translation(const char *text, const char *target_language, TranslationStyle style, char *output, unsigned int output_size) {
    const char *api_mode = getenv("TRANSLATION_API_MODE");

    if (text == NULL || target_language == NULL || output == NULL || output_size == 0U) {
        return 0;
    }

    if (api_mode == NULL || strcmp(api_mode, "demo") == 0) {
        return format_translation_demo(text, target_language, style, output, output_size);
    }

    if (strcmp(api_mode, "openai") == 0) {
        /* Basic OpenAI call using curl via popen. This is a lightweight integration
         * for local usage. It requires `curl` available in PATH and a valid
         * OPENAI_API_KEY environment variable. The implementation builds a small
         * chat completion request and extracts the assistant content naively.
         */
        const char *api_key = getenv("OPENAI_API_KEY");
        if (api_key == NULL) {
            snprintf(g_api_error, sizeof g_api_error, "OPENAI_API_KEY non configurée");
            return 0;
        }

        /* escape JSON for text and target_language */
        size_t esc_size = strlen(text) * 2 + 1024;
        char *esc_text = malloc(esc_size);
        if (esc_text == NULL) return 0;
        size_t ei = 0;
        for (size_t i = 0; text[i] != '\0' && ei + 6 < esc_size; ++i) {
            char c = text[i];
            switch (c) {
                case '\\': esc_text[ei++] = '\\'; esc_text[ei++] = '\\'; break;
                case '"': esc_text[ei++] = '\\'; esc_text[ei++] = '"'; break;
                case '\n': esc_text[ei++] = '\\'; esc_text[ei++] = 'n'; break;
                case '\r': esc_text[ei++] = '\\'; esc_text[ei++] = 'r'; break;
                default: esc_text[ei++] = c; break;
            }
        }
        esc_text[ei] = '\0';

        size_t esc_lang_size = strlen(target_language) * 2 + 128;
        char *esc_lang = malloc(esc_lang_size);
        if (esc_lang == NULL) { free(esc_text); return 0; }
        ei = 0;
        for (size_t i = 0; target_language[i] != '\0' && ei + 4 < esc_lang_size; ++i) {
            char c = target_language[i];
            if (c == '"' || c == '\\') { esc_lang[ei++] = '\\'; esc_lang[ei++] = c; } else esc_lang[ei++] = c;
        }
        esc_lang[ei] = '\0';

        const char *style_str = style_prefix(style);

        /* Build JSON payload */
        const char *template = "{\"model\":\"gpt-3.5-turbo\",\"messages\":[{\"role\":\"system\",\"content\":\"You are a helpful translation assistant. Respond only with the translated text.\"},{\"role\":\"user\",\"content\":\"Translate the following text to %s using a %s style: %s\"}] ,\"max_tokens\":800}";
        size_t payload_size = strlen(template) + strlen(esc_lang) + strlen(style_str) + strlen(esc_text) + 64;
        char *payload = malloc(payload_size);
        if (payload == NULL) { free(esc_text); free(esc_lang); return 0; }
        snprintf(payload, payload_size, template, esc_lang, style_str, esc_text);

        /* Build curl command */
        size_t cmd_size = payload_size + strlen(api_key) + 256;
        char *cmd = malloc(cmd_size);
        if (cmd == NULL) { free(esc_text); free(esc_lang); free(payload); return 0; }
        snprintf(cmd, cmd_size,
                 "curl -s -X POST https://api.openai.com/v1/chat/completions -H \"Authorization: Bearer %s\" -H \"Content-Type: application/json\" -d '%s'",
                 api_key, payload);

        FILE *fp = popen(cmd, "r");
        if (fp == NULL) {
            snprintf(g_api_error, sizeof g_api_error, "popen failed: %s", strerror(errno));
            free(esc_text); free(esc_lang); free(payload); free(cmd);
            return 0;
        }

        char response[65536];
        size_t offset = 0;
        while (!feof(fp) && offset + 1024 < sizeof response) {
            size_t r = fread(response + offset, 1, sizeof response - offset - 1, fp);
            if (r == 0) break;
            offset += r;
        }
        response[offset] = '\0';
        pclose(fp);

        /* naive parse: find the assistant content in the JSON */
        const char *needle = "\"content\":\"";
        char *found = strstr(response, needle);
        int result = 0;
        if (found != NULL) {
            found += strlen(needle);
            char *end = strstr(found, "\"}\"]");
            if (end == NULL) {
                end = strchr(found, '\"');
            }
            if (end != NULL) {
                size_t len = (size_t)(end - found);
                if (len >= output_size) len = output_size - 1;
                /* unescape simple sequences */
                size_t wi = 0;
                for (size_t ri = 0; ri < len && wi + 1 < output_size; ++ri) {
                    if (found[ri] == '\\' && ri + 1 < len) {
                        char next = found[ri+1];
                        switch (next) {
                            case 'n': output[wi++] = '\n'; break;
                            case 'r': output[wi++] = '\r'; break;
                            case '\\': output[wi++] = '\\'; break;
                            case '"': output[wi++] = '"'; break;
                            default: output[wi++] = next; break;
                        }
                        ri++;
                    } else {
                        output[wi++] = found[ri];
                    }
                }
                output[wi] = '\0';
                result = 1;
            }
        }

        free(esc_text); free(esc_lang); free(payload); free(cmd);
        if (!result) {
            /* Attach a short snippet of the raw response to the error to help debugging */
            size_t resp_len = strlen(response);
            size_t snippet_len = resp_len < 512 ? resp_len : 512;
            char snippet[520];
            if (snippet_len > 0) {
                memcpy(snippet, response, snippet_len);
            }
            snippet[snippet_len] = '\0';
            snprintf(g_api_error, sizeof g_api_error, "Impossible d'extraire la réponse API. Reponse (tronc): %s", snippet_len > 0 ? snippet : "<vide>");
            fprintf(stderr, "[API DEBUG] Raw response (truncated): %s\n", snippet_len > 0 ? snippet : "<empty>");
            return 0;
        }

        return 1;
    }

    if (strcmp(api_mode, "gemini") == 0) {
        return format_translation_demo(text, target_language, style, output, output_size);
    }

    snprintf(g_api_error, sizeof g_api_error, "Mode API inconnu: %s", api_mode);
    return 0;
}
