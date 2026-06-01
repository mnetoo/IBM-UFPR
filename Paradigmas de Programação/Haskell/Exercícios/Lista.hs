module Lista where

-- Questão 3
-- A função deve ser recursiva e aplicar a função de transformação (segundo parâmetro) em um elemento da lista apenas se este elemento satisfizer a 
-- função de teste (terceiro parâmetro). Caso não satisfaça, o elemento deve ser mantido na lista sem alterações.

ehPar :: Int -> Bool
ehPar x
    | mod x 2 == 0 = True
    | otherwise = False

dobraValor :: Int -> Int
dobraValor x = x * 2

processaLista :: [Int] -> (Int -> Int) -> (Int -> Bool) -> [Int]
processaLista [] _ _ = []
processaLista (h:t) f1 f2
    | f2 h == True = (f1 h) : processaLista t f1 f2
    | otherwise = h : processaLista t f1 f2