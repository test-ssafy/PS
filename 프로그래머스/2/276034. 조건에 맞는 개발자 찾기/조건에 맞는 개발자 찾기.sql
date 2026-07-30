select distinct D.ID, D.EMAIL, D.FIRST_NAME, D.LAST_NAME
from DEVELOPERS D
join SKILLCODES S
on (S.CODE & D.SKILL_CODE) > 0
where S.NAME = 'Python' or S.NAME = 'C#'
order by D.ID;