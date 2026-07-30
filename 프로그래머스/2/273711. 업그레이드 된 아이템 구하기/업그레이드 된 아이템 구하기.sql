select ITEM_ID, ITEM_NAME, RARITY
from ITEM_INFO
where ITEM_ID in (
    select T.ITEM_ID
    from ITEM_INFO I
    join ITEM_TREE T
    on I.ITEM_ID = T.PARENT_ITEM_ID
    where I.RARITY = 'RARE'
)
order by ITEM_ID desc