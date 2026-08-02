select sum(SCORE) as SCORE, E.EMP_NO, EMP_NAME, POSITION, EMAIL
from HR_EMPLOYEES E
    join HR_GRADE G
    on E.EMP_NO = G.EMP_NO
group by EMP_NO
order by sum(SCORE) desc
limit 1
#점수, 사번, 성명, 직책, 이메일
#상하반기 점수 합