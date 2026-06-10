#!/bin/bash
# Initialize local SQLite database for development

DB_FILE="data/local.db"
SCHEMA_FILE="data/schema.sql"

if [ ! -f "$DB_FILE" ]; then
    echo "Creating local database at $DB_FILE..."
    sqlite3 "$DB_FILE" < "$SCHEMA_FILE"
    echo "Database initialized successfully."
else
    echo "Database already exists at $DB_FILE"
fi
