INSERT OR IGNORE INTO Emotions (
    emotState,
    angryLevel,
    sadLevel,
    loveLevel,
    fearLevel,
    happyLevel
) VALUES (
    :emotState,
    :angryLevel,
    :sadLevel,
    :loveLevel,
    :fearLevel,
    :happyLevel
);
