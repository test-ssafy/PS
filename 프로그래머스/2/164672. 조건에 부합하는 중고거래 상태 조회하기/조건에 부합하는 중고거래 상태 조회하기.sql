select BOARD_ID, WRITER_ID, TITLE, PRICE,
    case
        when STATUS = 'SALE' then '판매중'
        when STATUS = 'RESERVED' then '예약중'
        when STATUS = 'DONE' then '거래완료'
    end as STATUS
from USED_GOODS_BOARD
where year(CREATED_DATE) = 2022 and month(CREATED_DATE) = 10 and day(CREATED_DATE) = 5
order by BOARD_ID desc