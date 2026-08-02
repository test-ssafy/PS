select count(*) as FISH_COUNT, month(TIME) as MONTH
from FISH_INFO
group by month(TIME)
having count(*) > 0
order by MONTH