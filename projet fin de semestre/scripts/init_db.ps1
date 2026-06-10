# Initialize local SQLite database for development (Windows PowerShell)

$DB_FILE = "data/local.db"
$SCHEMA_FILE = "data/schema.sql"

if (-Not (Test-Path $DB_FILE)) {
    Write-Host "Creating local database at $DB_FILE..."
    if (-Not (Test-Path "data")) {
        New-Item -ItemType Directory -Path "data" -Force | Out-Null
    }
    # Using sqlite3 command-line if available, or manual SQL execution
    sqlite3.exe "$DB_FILE" "$(Get-Content $SCHEMA_FILE)"
    Write-Host "Database initialized successfully."
} else {
    Write-Host "Database already exists at $DB_FILE"
}
