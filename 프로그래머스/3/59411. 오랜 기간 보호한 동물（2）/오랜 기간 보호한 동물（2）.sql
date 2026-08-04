select I.ANIMAL_ID, I.NAME
from ANIMAL_INS I
    left join ANIMAL_OUTS O
    on I.ANIMAL_ID = O.ANIMAL_ID
where O.ANIMAL_ID is not null
order by datediff(O.DATETIME, I.DATETIME) desc
limit 2