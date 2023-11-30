SELECT
    *
FROM
    (Notes n
JOIN Emotions e ON
    n.emotId == e.id)
JOIN NoteTextDetails ntd ON
    ntd.id  == n.noteTextId
WHERE
    n.id == :id