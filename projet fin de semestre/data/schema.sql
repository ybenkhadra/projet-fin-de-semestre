-- Schema de la base de données locale
-- Utilisée pour stocker l'historique des traductions et le vocabulaire

CREATE TABLE IF NOT EXISTS translations (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    source_text TEXT NOT NULL,
    target_language TEXT NOT NULL,
    style INTEGER NOT NULL DEFAULT 1,
    translated_text TEXT NOT NULL,
    timestamp DATETIME DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE IF NOT EXISTS vocabulary (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    source_word TEXT UNIQUE NOT NULL,
    target_word TEXT NOT NULL,
    frequency INTEGER DEFAULT 1,
    last_used DATETIME DEFAULT CURRENT_TIMESTAMP
);

CREATE INDEX IF NOT EXISTS idx_translations_language ON translations(target_language);
CREATE INDEX IF NOT EXISTS idx_vocabulary_source ON vocabulary(source_word);
