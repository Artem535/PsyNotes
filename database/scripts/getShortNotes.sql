SELECT
    nt.id as id,
    nt.title as title,
    nt.unixTime as unixTime,
    STRFTIME("%H:%M", nt.unixTime, "unixepoch", "localtime") as timeValue,
    DATE(nt.unixTime, "unixepoch", "localtime") as dateValue 
FROM
    Notes AS nt
WHERE
    nt.visible == 1