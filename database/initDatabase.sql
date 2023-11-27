CREATE TABLE IF NOT EXISTS Notes (
    id INTEGER PRIMARY KEY,
    visible INTEGER DEFAULT 1,
    title TEXT,
    noteTextId INTEGER DEFAULT 0 NOT NULL,
    emotId INTEGER DEFAULT 0 NOT NULL,
    
    FOREIGN KEY (noteTextId) REFERENCES NoteTextDetails (id),
    FOREIGN KEY (emotId) REFERENCES Emotions (id)
);

CREATE TABLE IF NOT EXISTS Emotions (
    id INTEGER PRIMARY KEY,
    emotState INTEGER DEFAULT 0,
    angryLevel INTEGER DEFAULT 0,
    sadLevel INTEGER DEFAULT 0,
    loveLevel INTEGER DEFAULT 0,
    fearLevel INTEGER DEFAULT 0,
    happyLevel INTEGER DEFAULT 0,
    
    UNIQUE (emotState,
            angryLevel,
            sadLevel,
            loveLevel,
            fearLevel,
            happyLevel)
);

CREATE TABLE IF NOT EXISTS NoteTextDetails (
    id INTEGER PRIMARY KEY,
    thoughtsTxt TEXT DEFAULT "",
    behaviorTxt TEXT DEFAULT "",
    bodyTxt TEXT DEFAULT "",
    feelsTxt TEXT DEFAULT "",
    situationTxt TEXT DEFAULT "",
    
    UNIQUE (thoughtsTxt,
            behaviorTxt,
            bodyTxt,
            feelsTxt,
            situationTxt)
);
