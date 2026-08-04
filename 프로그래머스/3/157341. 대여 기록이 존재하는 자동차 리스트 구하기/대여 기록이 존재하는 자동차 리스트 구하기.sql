select distinct C.CAR_ID
from CAR_RENTAL_COMPANY_CAR C
    join CAR_RENTAL_COMPANY_RENTAL_HISTORY H
    on C.CAR_ID = H.CAR_ID
where C.CAR_TYPE = '세단' and month(H.START_DATE) = 10
order by C.CAR_ID desc