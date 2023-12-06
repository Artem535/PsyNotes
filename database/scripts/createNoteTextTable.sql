CREATE TABLE IF NOT EXISTS NoteTextDetails (
    id INTEGER PRIMARY KEY,
    thoughtsTxt TEXT DEFAULT "",
    behaviorTxt TEXT DEFAULT "",
    bodyTxt TEXT DEFAULT "",
    situationTxt TEXT DEFAULT "",
    locked INTEGER DEFAULT 0,
    
    UNIQUE (thoughtsTxt,
            behaviorTxt,
            bodyTxt,
            situationTxt, 
            locked)
);