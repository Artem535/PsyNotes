CREATE TABLE IF NOT EXISTS NoteTextDetails (
    id INTEGER PRIMARY KEY,
    thoughtsTxt TEXT DEFAULT "",
    behaviorTxt TEXT DEFAULT "",
    bodyTxt TEXT DEFAULT "",
    situationTxt TEXT DEFAULT "",
    
    UNIQUE (thoughtsTxt,
            behaviorTxt,
            bodyTxt,
            situationTxt)
);