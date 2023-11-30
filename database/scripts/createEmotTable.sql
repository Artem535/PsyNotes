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