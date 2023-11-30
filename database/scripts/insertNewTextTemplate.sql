INSERT OR FAIL INTO NoteTextDetails (
    thoughtsTxt,
    behaviorTxt,
    bodyTxt,
    situationTxt
) VALUES (
    :thoughts,
    :behavior,
    :body,
    :situation
);
