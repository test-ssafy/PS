select C.ITEM_ID, C.ITEM_NAME, C.RARITY
from ITEM_INFO C
    left join ITEM_TREE P
    on C.ITEM_ID = P.PARENT_ITEM_ID
where P.PARENT_ITEM_ID is null
order by C.ITEM_ID desc