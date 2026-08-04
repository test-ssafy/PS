select ID, 
    case
        when TILE = 1 then 'CRITICAL'
        when TILE = 2 then 'HIGH'
        when TILE = 3 then 'MEDIUM'
        else 'LOW'
    end as COLONY_NAME
from (
    select ID, ntile(4) over (order by SIZE_OF_COLONY desc) as TILE
    from ECOLI_DATA
) ECOLI_DATA
order by ID