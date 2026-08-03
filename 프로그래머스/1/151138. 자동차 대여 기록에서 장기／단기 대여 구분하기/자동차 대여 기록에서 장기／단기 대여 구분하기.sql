select *,
    case
        when DATEDIFF(END_DATE, START_DATE) + 1 >= 30 then '장기 대여'
        else '단기 대여'
    end as RENT_TYPE
from CAR_RENTAL_COMPANY_RENTAL_HISTORY
where year(START_DATE) = 2022 and month(START_DATE) = 9
order by HISTORY_ID desc