select ANIMAL_ID, NAME
from ANIMAL_INS
where ANIMAL_TYPE = 'Dog' and NAME like '%el%'
order by NAME, ANIMAL_ID