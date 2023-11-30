CREATE TABLE IF NOT EXISTS Notes (
    id INTEGER PRIMARY KEY,
    visible INTEGER DEFAULT 1,
    title TEXT,
    unixTime INTEGER DEFAULT (UNIXEPOCH('now')),
    noteTextId INTEGER DEFAULT 0 NOT NULL,
    emotId INTEGER DEFAULT 0 NOT NULL,
    
    FOREIGN KEY (noteTextId) REFERENCES NoteTextDetails (id),
    FOREIGN KEY (emotId) REFERENCES Emotions (id)
   
    UNIQUE(noteTextId, emotId)
);