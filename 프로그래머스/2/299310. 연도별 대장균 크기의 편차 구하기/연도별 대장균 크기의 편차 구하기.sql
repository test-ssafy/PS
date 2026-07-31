select 
    year(E.DIFFERENTIATION_DATE) as YEAR,
    (M.MAX_SIZE - E.SIZE_OF_COLONY) as YEAR_DEV,
    E.ID
from ECOLI_DATA E
join (
    select
        year(DIFFERENTIATION_DATE) as YEAR,
        max(SIZE_OF_COLONY) as MAX_SIZE
    from ECOLI_DATA
    group by year(DIFFERENTIATION_DATE)
) M
on year(E.DIFFERENTIATION_DATE) = M.YEAR
order by YEAR, YEAR_DEV
