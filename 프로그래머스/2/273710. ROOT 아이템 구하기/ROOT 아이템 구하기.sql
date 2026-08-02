select I.ITEM_ID, I.ITEM_NAME
from ITEM_INFO I
    join ITEM_TREE T
    on I.ITEM_ID = T.ITEM_ID
where T.PARENT_ITEM_ID is null
order by I.ITEM_ID