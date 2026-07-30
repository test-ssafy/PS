select C.ID, C.GENOTYPE, P.GENOTYPE
from ECOLI_DATA C
join ECOLI_DATA P
on C.PARENT_ID = P.ID
# 부모의 형질을 모두 보유한 자식
where (C.GENOTYPE & P.GENOTYPE) >= P.GENOTYPE 
order by ID