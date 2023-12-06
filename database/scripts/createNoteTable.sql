CREATE TABLE IF NOT EXISTS Notes (
    id INTEGER PRIMARY KEY,
    visible INTEGER DEFAULT 1,
    title TEXT,
    unixTime INTEGER DEFAULT (UNIXEPOCH('now')),
    noteTextId INTEGER DEFAULT 0 NOT NULL,
    emotId INTEGER DEFAULT 0 NOT NULL,
    locked INTEGER DEFAULT 0,
    
    FOREIGN KEY (noteTextId) REFERENCES NoteTextDetails (id),
    FOREIGN KEY (emotId) REFERENCES Emotions (id)
   
);